<?php

namespace Siropu\ReferralContests\Finder;

use XF\Mvc\Entity\Finder;

class Invitation extends Finder
{
     public function dateBetween($start, $end)
     {
          $this->where('invitation_date', 'BETWEEN', [$start, $end]);
          return $this;
     }
}
