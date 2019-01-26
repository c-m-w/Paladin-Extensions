<?php

namespace Siropu\Shoutbox\Pub\Controller;

use XF\Pub\Controller\AbstractController;
use XF\Mvc\ParameterBag;

class Shoutbox extends AbstractController
{
     use \Siropu\Shoutbox\Shoutbox;

     protected $lastId;

     protected function preDispatchController($action, ParameterBag $params)
	{
          $this->lastId = $this->filter('last_id', 'uint');
     }
     public function actionIndex(ParameterBag $params)
     {
          $visitor = \XF::visitor();

          if (!$visitor->canViewSiropuShoutbox())
          {
               return $this->noPermission();
          }

          return $this->view('Siropu\Shoutbox:Shoutbox', 'siropu_shoutbox', ['shoutbox' => $this->getShoutboxParams()]);
     }
     public function actionSubmit()
     {
          $visitor = \XF::visitor();
          $options = \XF::options();

          if (!$visitor->canUseSiropuShoutbox())
          {
               return $this->noPermission();
          }

          $message    = $this->filter('shout', 'str');
          $viewParams = ['action' => 'submit'];

          if (preg_match('/^\/prune/i', $message) && $visitor->canPruneSiropuShoutbox())
          {
               $this->getShoutRepo()->prune();

               $message = \XF::phrase('siropu_shoutbox_has_been_pruned');
               $viewParams['prune'] = true;
          }

          $shoutService = $this->service('Siropu\Shoutbox:Shout\Preparer');
          $shoutService->prepare($message);

          if ($shoutService->isValid())
          {
               $message = $shoutService->getMessage();
          }
          else
          {
               return $this->message($shoutService->getErrors());
          }

          $shout = $this->em()->create('Siropu\Shoutbox:Shout');
          $shout->shout_message = $message;
          $shout->save();

          return $this->rerouteController(__CLASS__, 'refresh', $viewParams);
     }
     public function actionRefresh(ParameterBag $params)
     {
          $reverse = $this->getReverseState();

          $shouts = $this->getShoutRepo()
               ->findShouts()
               ->where('shout_id', '>', $params->prune ? 0 : $this->lastId)
               ->fetch();

          if ($reverse)
          {
               $shouts = $shouts->reverse();
          }

          $viewParams = [
               'shoutbox' => [
                    'shouts' => $shouts
               ]
          ];

          $reply = $this->view('Siropu\Shoutbox:Shoutbox', 'siropu_shoutbox_shout_list', $viewParams);

          if ($shouts->count())
          {
               $reply->setJsonParams([
                    'lastId' => $reverse ? $shouts->last()->shout_id : $shouts->first()->shout_id,
                    'prune'  => $params->prune ? true : false
               ]);
          }

          return $reply;
     }
     public function actionLoadMore()
     {
          $lastId = $this->filter('last_id', 'uint');

          if (!\XF::visitor()->canUseSiropuShoutbox())
          {
               if ($this->isLoggedIn())
               {
                    return $this->noPermission();
               }

               return $this->view();
          }

          $shouts = $this->getShoutRepo()
               ->findShouts()
               ->where('shout_id', '<', $lastId)
               ->fetch();

          $reverse = $this->getReverseState();

          if ($reverse)
          {
               $shouts = $shouts->reverse();
          }

          $viewParams = [
               'shoutbox' => [
                    'shouts' => $shouts
               ]
          ];

          return $this->view('Siropu\Shoutbox:Shoutbox', 'siropu_shoutbox_shout_list', $viewParams);
     }
     public function actionEdit(ParameterBag $params)
     {
          $shout = $this->assertShoutExists($params->shout_id);

          if (!$shout->canEdit())
          {
               return $this->noPermission();
          }

          if ($this->isPost())
          {
               $shoutService = $this->service('Siropu\Shoutbox:Shout\Preparer');
               $shoutService->prepare($this->filter('message', 'str'));

               if ($shoutService->isValid())
               {
                    $message = $shoutService->getMessage();
               }
               else
               {
                    return $this->message($shoutService->getErrors());
               }

               $shout->shout_message = $message;
               $shout->save();

               $reply = $this->view();
               $reply->setJsonParams([
                    'shout_id'      => $shout->shout_id,
                    'shout_message' => $this->app->bbCode()->render($message, 'html', 'siropu_shoutbox', $shout)
               ]);

               return $reply;
          }

          $viewParams = [
               'shout' => $shout
          ];

          return $this->view('Siropu\Shoutbox:ShoutEdit', 'siropu_shoutbox_shout_edit', $viewParams);
     }
     public function actionDelete(ParameterBag $params)
     {
          $shout = $this->assertShoutExists($params->shout_id);

          if (!$shout->canDelete())
          {
               return $this->noPermission();
          }

          if ($this->isPost())
          {
               $shout->delete();

               $reply = $this->view();
               $reply->setJsonParams([
                    'shout_id' => $shout->shout_id
               ]);

               return $reply;
          }

          $viewParams = [
               'shout' => $shout
          ];

          return $this->view('Siropu\Shoutbox:ShoutDelete', 'siropu_shoutbox_shout_delete', $viewParams);
     }
     protected function assertShoutExists($id, $with = null)
	{
		return $this->assertRecordExists('Siropu\Shoutbox:Shout', $id, $with, 'siropu_shoutbox_requested_shout_not_found');
	}
}
