<?php

namespace Siropu\ReferralContests\Admin\Controller;

use XF\Mvc\ParameterBag;

class Invitation extends AbstractController
{
     public function actionIndex(ParameterBag $params)
     {
          $linkParams = [];
          $page       = $this->filterPage();
          $perPage    = 20;

          $finder = $this->getInvitationRepo()
               ->findInvitationsForList()
               ->limitByPage($page, $perPage);

          $referrer = $this->filter([
               'username' => 'str',
               'user_id'  => 'uint'
          ]);

          if ($referrer['username'] && ($user = $this->em()->findOne('XF:User', ['username' => $referrer['username']])))
          {
               $finder->where('user_id',  $user->user_id);
               $linkParams['user_id'] = $user->user_id;
          }
          else if ($referrer['user_id'])
          {
               $finder->where('user_id', $referrer['user_id']);
               $linkParams['user_id'] = $referrer['user_id'];
          }

          $viewParams = [
               'invitations' => $finder->fetch(),
               'total'       => $finder->total(),
               'page'        => $page,
               'perPage'     => $perPage,
               'linkParams'  => $linkParams
          ];

          return $this->view('Siropu\ReferralContests:Invitation', 'siropu_referral_contests_invitation_list', $viewParams);
     }
     public function actionAdd()
     {
          $invitation = $this->em()->create('Siropu\ReferralContests:Invitation');

          $viewParams = [
               'invitation' => $invitation
          ];

          return $this->view('Siropu\ReferralContests:Invitation\Add', 'siropu_referral_contests_invitation_add', $viewParams);
     }
     public function actionSave(ParameterBag $params)
     {
          $this->assertPostOnly();

          $invitationCount = $this->filter('invitation_count', 'uint');
          $expirationDate  = $this->filter('expiration_date', 'datetime');
          $invitations     = [];

          $referrer        = $this->em()->findOne('XF:User', ['username' => $this->filter('referrer', 'str')]);

          for ($i = 0; $i < $invitationCount; $i++)
          {
               $invitation = $this->em()->create('Siropu\ReferralContests:Invitation');

               if ($referrer)
               {
                    $invitation->user_id = $referrer->user_id;
               }

               $invitation->generateCode($i);
               $invitation->expiration_date = $expirationDate;
               $invitation->save();

               $invitations[] = $invitation;
          }

          $visitor = \XF::visitor();

          if ($referrer)
          {
               \XF::repository('XF:UserAlert')->alert(
                    $referrer,
                    $visitor->user_id,
                    $visitor->username,
                    'user',
                    $visitor->user_id,
                    'siropu_referral_invit_granted',
                    [
                         'count' => $i
                    ]
               );
          }

          $viewParams = [
               'invitations'  => $invitations,
               'generateLink' => $this->filter('generate_link', 'bool')
          ];

		return $this->view('Siropu\ReferralContests:Invitation\Add', 'siropu_referral_contests_invitation_result', $viewParams);
     }
     public function actionDelete(ParameterBag $params)
     {
          $invitation = $this->assertInvitationExists($params->invitation_code);

          if ($this->isPost())
          {
               $invitation->delete();
               return $this->redirect($this->buildLink('referral-contests/invitations'));
          }

          $viewParams = [
               'invitation' => $invitation
          ];

          return $this->view('Siropu\ReferralContests:Invitation\Delete', 'siropu_referral_contests_invitation_delete', $viewParams);
     }
     public function actionLink(ParameterBag $params)
     {
          $invitation = $this->assertInvitationExists($params->invitation_code);

          $viewParams = [
               'invitation' => $invitation
          ];

          return $this->view('Siropu\ReferralContests:Invitation\Link', 'siropu_referral_contests_invitation_link', $viewParams);
     }
     public function getInvitationRepo()
     {
          return $this->repository('Siropu\ReferralContests:Invitation');
     }
     protected function assertInvitationExists($id, $with = null)
     {
          return $this->assertRecordExists('Siropu\ReferralContests:Invitation', $id, $with, 'siropu_referral_contests_invitation_not_found');
     }
}
