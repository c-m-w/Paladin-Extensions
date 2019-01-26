<?php

namespace Siropu\ReferralContests\Repository;

use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Repository;

class RewardType extends Repository
{
     public function findRewardTypesForList()
     {
          return $this->finder('Siropu\ReferralContests:RewardType');
     }
}
