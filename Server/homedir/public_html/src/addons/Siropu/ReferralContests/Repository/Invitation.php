<?php

namespace Siropu\ReferralContests\Repository;

use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Repository;

class Invitation extends Repository
{
     public function findInvitations()
     {
          return $this->finder('Siropu\ReferralContests:Invitation');
     }
     public function findInvitationsForList()
     {
          return $this->findInvitations()
               ->with(['User', 'Registered'])
               ->order('invitation_date', 'desc');
     }
}
