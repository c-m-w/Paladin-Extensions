<?php

namespace xenMade\AED\XF\Entity;

class User extends XFCP_User
{
    public function canBypassAED(&$error = null)
    {
        return $this->hasPermission('general', 'canBypassAED');
    }
}
if(false)
{
    class XFCP_User extends \XF\Entity\User {};
}