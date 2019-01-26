<?php

namespace Siropu\ReferralContests\Repository;

use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Repository;

class ReferrerLog extends Repository
{
     public function logHttpReferrer($referrerId)
     {
          if (\XF::options()->siropuReferralContestsTrackHttpReferrer && ($referrer = \XF::app()->request()->getReferrer()))
          {
               $log = $this->em->create('Siropu\ReferralContests:ReferrerLog');
               $log->user_id = $referrerId;
               $log->url = $referrer;
               $log->save();
          }
     }
}
