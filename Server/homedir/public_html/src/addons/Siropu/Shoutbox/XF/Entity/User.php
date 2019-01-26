<?php

namespace Siropu\Shoutbox\XF\Entity;

class User extends XFCP_User
{
     public function canViewSiropuShoutbox()
     {
          return $this->hasPermission('siropuShoutbox', 'view');
     }
     public function canUseSiropuShoutbox()
	{
          return $this->hasPermission('siropuShoutbox', 'use');
     }
     public function canPruneSiropuShoutbox()
     {
          return $this->hasPermission('siropuShoutbox', 'prune');
     }
     public function canBypassFloodCheckSiropuShoutbox()
     {
          return $this->hasPermission('siropuShoutbox', 'bypassFloodCheck');
     }
     public function hasRequiredAge()
     {
          $visitor = \XF::visitor();
          $minAge  = \XF::options()->siropuShoutboxMinAge;

          if ($minAge && $visitor->user_id && $visitor->Profile && $visitor->Profile->dob_year)
          {
               $dobYear = $visitor->Profile->dob_year;
               $userAge = date('Y', \XF::$time) - $dobYear;

               if ($userAge < $minAge)
               {
                    return false;
               }
          }

          return true;
     }
}
