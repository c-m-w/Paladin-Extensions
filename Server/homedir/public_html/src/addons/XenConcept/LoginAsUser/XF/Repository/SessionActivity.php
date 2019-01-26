<?php

/*************************************************************************
 * Restrict Guest Views  - XenConcept (c) 2017
 * All Rights Reserved.
 **************************************************************************
 * This file is subject to the terms and conditions defined in the Licence
 * Agreement available at Try it like it buy it :)
 *************************************************************************/

namespace XenConcept\LoginAsUser\XF\Repository;

class SessionActivity extends XFCP_SessionActivity
{

    public function getOnlineStatsBlockData($forceIncludeVisitor = true, $userLimit, $staffQuery = false)
    {
        $response =  parent::getOnlineStatsBlockData($forceIncludeVisitor, $userLimit, $staffQuery);

        $visitor = \XF::visitor();
        $session = \XF::session();
        $options = \XF::options();


        $stealthLogin  = $options->xc_login_as_user_enable_stealth_login;
        $userId    = $visitor->user_id;
        $logAsUser = $session->get('login_as_user');

        if ($stealthLogin && $logAsUser)
        {
            $users = $response['users'];

            unset($users[$userId]);

            $response['users'] = $users;
        }

        return $response;
    }

    public function updateSessionActivity($userId, $ip, $controller, $action, array $params, $viewState, $robotKey)
    {
        $options = \XF::options();
        $stealthLogin  = $options->xc_login_as_user_enable_stealth_login;

        if (!\XF::session()->get('login_as_user'))
        {
            parent::updateSessionActivity($userId, $ip, $controller, $action, $params, $viewState, $robotKey);
        }

        if (!$stealthLogin)
        {
            parent::updateSessionActivity($userId, $ip, $controller, $action, $params, $viewState, $robotKey);
        }
    }

    public function updateUserLastActivityFromSession()
    {
        $options = \XF::options();
        $stealthLogin  = $options->xc_login_as_user_enable_stealth_login;

        if (!\XF::session()->get('login_as_user'))
        {
            parent::updateUserLastActivityFromSession();
        }

        if (!$stealthLogin)
        {
            parent::updateUserLastActivityFromSession();
        }
    }

}