<?php

namespace Siropu\ReferralContests\Finder;

use XF\Mvc\Entity\Finder;

class Contest extends Finder
{
     public function isEnabled()
     {
          $this->where('enabled', true);
          return $this;
     }
}
