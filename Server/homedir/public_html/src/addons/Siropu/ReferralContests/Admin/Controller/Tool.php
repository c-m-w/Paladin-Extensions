<?php

namespace Siropu\ReferralContests\Admin\Controller;

use XF\Mvc\ParameterBag;
use XF\Mvc\FormAction;

class Tool extends AbstractController
{
     public function actionIndex(ParameterBag $params)
     {
          $finder = $this->getToolRepo()->findToolsForList();

          $viewParams = [
               'tools' => $finder->fetch(),
               'total' => $finder->total()
          ];

          return $this->view('Siropu\ReferralContests:Tool', 'siropu_referral_contests_tool_list', $viewParams);
     }
     public function actionAdd(ParameterBag $params)
     {
          $tool = $this->em()->create('Siropu\ReferralContests:Tool');
          $tool->type = $this->filter('type', 'str');

          return $this->toolAddEdit($tool);
     }
     public function actionEdit(ParameterBag $params)
     {
          $tool = $this->assertToolExists($params->tool_id);
          return $this->toolAddEdit($tool);
     }
     public function actionSave(ParameterBag $params)
     {
          $this->assertPostOnly();

		if ($params->tool_id)
		{
			$tool = $this->assertToolExists($params->tool_id);
		}
		else
		{
			$tool = $this->em()->create('Siropu\ReferralContests:Tool');
               $tool->type = $this->filter('type', 'str');
		}

		$this->toolSaveProcess($tool)->run();

		return $this->redirect($this->buildLink('referral-contests/tools'));
     }
     public function actionToggle()
     {
          $plugin = $this->plugin('XF:Toggle');
		return $plugin->actionToggle('Siropu\ReferralContests:Tool', 'enabled');
     }
     public function actionDelete(ParameterBag $params)
     {
          $tool = $this->assertToolExists($params->tool_id);

          if ($this->isPost())
          {
               $tool->delete();
               return $this->redirect($this->buildLink('referral-contests/tools'));
          }

          $viewParams = [
               'tool' => $tool
          ];

          return $this->view('Siropu\ReferralContests:Tool\Delete', 'siropu_referral_contests_tool_delete', $viewParams);
     }
     public function getToolRepo()
     {
          return $this->repository('Siropu\ReferralContests:Tool');
     }
     protected function toolAddEdit(\Siropu\ReferralContests\Entity\Tool $tool)
	{
          $viewParams = [
               'tool' => $tool
          ];

          return $this->view('Siropu\ReferralContests:Tool\Edit', 'siropu_referral_contests_tool_edit', $viewParams);
     }
     protected function toolSaveProcess(\Siropu\ReferralContests\Entity\Tool $tool)
	{
          $input = $this->filter([
               'name'       => 'str',
               'content'    => 'str',
               'size'       => 'str',
               'target_url' => 'str',
               'enabled'    => 'bool'
          ]);

          if ($tool->isBanner())
          {
               unset($input['content']);
          }

          $form = $this->formAction();
          $form->basicEntitySave($tool, $input);

          $upload = $this->app()->request->getFile('upload', false, false);

          $form->validate(function(FormAction $form) use ($tool, $upload, $input)
          {
               if ($tool->isBanner())
               {
                    if ($upload && !$upload->isValid($errors))
                    {
                         $form->logErrors($errors);
                    }
                    else if (!$tool->content)
                    {
                         $form->logError(\XF::phrase('siropu_referral_contests_please_provide_valid_banner'));
                    }
               }
               else if (!$tool->content)
               {
                    $form->logError(\XF::phrase('siropu_referral_contests_please_enter_valid_link_text'));
               }
          });

          $form->setup(function() use ($tool, $upload)
          {
               if ($tool->isBanner() && $upload)
               {
                    \XF\Util\File::copyFileToAbstractedPath($upload->getTempFile(), "data://siropu/rc/{$upload->getFileName()}");

                    $tool->content = $upload->getFileName();
               }
          });

		return $form;
     }
     protected function assertToolExists($id, $with = null)
     {
          return $this->assertRecordExists('Siropu\ReferralContests:Tool', $id, $with, 'siropu_referral_contests_tool_not_found');
     }
}
