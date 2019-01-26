<?php

namespace xenMade\LAU\XF\Repository;

use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Repository;
use XF\Mvc\ParameterBag;

class SessionActivity extends XFCP_SessionActivity
{
    public function updateSessionActivity($userId, $ip, $controller, $action, array $params, $viewState, $robotKey)
    {
        $session = \XF::app()->session();

        if(!$session->exists())
            return parent::updateSessionActivity($userId, $ip, $controller, $action, $params, $viewState, $robotKey);

        if(
            $session->offsetExists('lau_id') &&
            $session->offsetExists('lau_stealth')
        )
        {
            if(\XF::options()->lau_Stealth == true)
            {
                return false;
            }
        }

        return parent::updateSessionActivity($userId, $ip, $controller, $action, $params, $viewState, $robotKey);
    }
}
if(false)
{
    class XFCP_SessionActivity extends \XF\Repository\SessionActivity {}
}