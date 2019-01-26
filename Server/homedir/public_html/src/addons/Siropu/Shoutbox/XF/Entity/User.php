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
}
