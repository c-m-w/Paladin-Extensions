<?php

namespace Siropu\ReferralContests\Admin\Controller;

use XF\Mvc\ParameterBag;

class ReferrerLog extends AbstractController
{
     public function actionIndex(ParameterBag $params)
     {
          $viewParams = [];

          return $this->view('Siropu\ReferralContests:ReferrerLog', 'siropu_referral_contests_referrer_log_list', $viewParams);
     }
}
