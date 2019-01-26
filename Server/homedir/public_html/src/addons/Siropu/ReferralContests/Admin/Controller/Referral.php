<?php

namespace Siropu\ReferralContests\Admin\Controller;

use XF\Mvc\ParameterBag;

class Referral extends AbstractController
{
     public function actionIndex(ParameterBag $params)
     {
          $linkParams = [];
          $page       = $this->filterPage();
          $perPage    = 20;

          $finder = $this->finder('XF:User')
               ->with('SRC_Referrer')
               ->order('register_date', 'desc')
               ->limitByPage($page, $perPage);

          $referrer = $this->filter([
               'username' => 'str',
               'user_id'  => 'uint'
          ]);

          if ($referrer['username'] && ($user = $this->em()->findOne('XF:User', ['username' => $referrer['username']])))
          {
               $finder->where('siropu_referrer_id', $user->user_id);
               $linkParams['user_id'] = $user->user_id;
          }
          else if ($referrer['user_id'])
          {
               $finder->where('siropu_referrer_id',  $referrer['user_id']);
               $linkParams['user_id'] = $referrer['user_id'];
          }
          else
          {
               $finder->where('siropu_referrer_id', '<>', 0);
          }

          $viewParams = [
               'referrals'  => $finder->fetch(),
               'total'      => $finder->total(),
               'page'       => $page,
               'perPage'    => $perPage,
               'linkParams' => $linkParams
          ];

          return $this->view('Siropu\ReferralContests:Referral', 'siropu_referral_contests_referral_list', $viewParams);
     }
     public function actionAdd()
     {
          return $this->view('Siropu\ReferralContests:Referral\Add', 'siropu_referral_contests_referral_add');
     }
     public function actionSave()
     {
          $referral = $this->em()->findOne('XF:User', ['username' => $this->filter('referral', 'str')]);
          $referrer = $this->em()->findOne('XF:User', ['username' => $this->filter('referrer', 'str')]);

          if (!$referral)
          {
               return $this->error(\XF::phrase('siropu_referral_contests_requested_referral_not_found'));
          }

          if (!$referrer)
          {
               return $this->error(\XF::phrase('siropu_referral_contests_requested_referrer_not_found'));
          }

          if ($referral->siropu_referrer_id)
          {
               return $this->error(\XF::phrase('siropu_referral_contests_x_is_referral_of_x', [
                    'referral' => $referral->username,
                    'referrer' => $referral->SRC_Referrer->username
               ]));
          }

          if ($referral->register_date < $referrer->register_date)
		{
               return $this->error(\XF::phrase('siropu_referral_contests_x_cannot_be_referral_of_x', [
                    'referral' => $referral->username,
                    'referrer' => $referrer->username
               ]));
          }

          $referral->siropu_referrer_id = $referrer->user_id;
          $referral->save();

          $referrer->siropu_referral_count++;
          $referrer->save();

          return $this->redirect($this->buildLink('referral-contests/referrals'));
     }
     public function actionDelete(ParameterBag $params)
     {
          $user = $this->assertUserExists($params->user_id);

          if ($this->isPost())
          {
               $referrer = $this->em()->find('XF:User', $user->siropu_referrer_id);

               if ($referrer)
               {
                    $user->siropu_referrer_id = 0;
                    $user->save();

                    $referrer->siropu_referral_count--;
                    $referrer->save();
               }

               return $this->redirect($this->buildLink('referral-contests/referrals'));
          }

          $viewParams = [
               'referral' => $user
          ];

          return $this->view('Siropu\ReferralContests:Referral\Delete', 'siropu_referral_contests_referral_delete', $viewParams);
     }
     protected function assertUserExists($id = null, $with = null)
     {
          return $this->assertRecordExists('XF:User', $id, $with, 'requested_user_not_found');
     }
}
