<?php

namespace xenMade\LAU\XF\Repository;

use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Repository;
use XF\Mvc\ParameterBag;

class UserAlert extends XFCP_UserAlert
{
    public function markUserAlertsRead(\XF\Entity\User $user, $viewDate = null)
    {
        $session = \XF::app()->session();

        if(!$session->exists())
            return parent::markUserAlertsRead($user, $viewDate);

        if(
            $session->offsetExists('lau_id') &&
            $session->offsetExists('lau_stealth')
        )
        {
            return false;
        }

        return parent::markUserAlertsRead($user, $viewDate);
    }
}
if(false)
{
    class XFCP_UserAlert extends \XF\Repository\UserAlert {}
}