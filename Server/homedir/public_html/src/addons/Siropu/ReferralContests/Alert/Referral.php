<?php

namespace Siropu\ReferralContests\Alert;

use XF\Mvc\Entity\Entity;

class Referral extends \XF\Alert\AbstractHandler
{
     public function canViewContent(Entity $entity, &$error = null)
     {
          return true;
     }
}
