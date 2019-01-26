<?php

namespace Siropu\ReferralContests\Pub\Controller;

use XF\Mvc\ParameterBag;

class Invitation extends \XF\Pub\Controller\AbstractController
{
     public function actionIndex(ParameterBag $params)
     {
          $invitation = $this->assertInvitationExists($this->filter('code', 'str'));

          if (!$invitation->isValid())
          {
              return $this->noPermission();
          }

          $viewParams = [
               'invitation' => $invitation
          ];

          return $this->view('Siropu\ReferralContests:Invitation', 'siropu_referral_contests_invitation_page', $viewParams);
     }
     protected function assertInvitationExists($id, $with = null)
     {
          return $this->assertRecordExists('Siropu\ReferralContests:Invitation', $id, $with, 'siropu_referral_contests_invitation_required');
     }
}
