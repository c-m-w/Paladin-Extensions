<?php

namespace xenMade\LAU\XF\Entity;

class User extends XFCP_User
{
    public function canUseLau(&$error = null)
    {
        return $this->hasPermission('general', 'canUseLau');
    }
}
if(false)
{
    class XFCP_User extends \XF\Entity\User {};
}