<?php

/*************************************************************************
 * Login As User - XenConcept (c) 2017
 * All Rights Reserved.
 **************************************************************************
 * This file is subject to the terms and conditions defined in the Licence
 * Agreement available at Try it like it buy it :)
 *************************************************************************/

namespace XenConcept\LoginAsUser\XF\ControllerPlugin;

use XF\Entity\User;

class Login extends XFCP_Login
{

    public function loginAsUser(User $user, User $oldUser)
    {
        $this->session->changeUser($user);
        $this->session->set('login_as_user', $oldUser['user_id']);
    }

    public function logoutAsUser()
    {
        $session = $this->session;

        $userRepo = $this->getUserRepo();

        $user = $userRepo->getVisitor($session->get('login_as_user'));

        $session->changeUser($user);

        $session->set('login_as_user', null);

        return;
    }

    /**
     * @return \XF\Repository\User
     */
    protected function getUserRepo()
    {
        return $this->repository('XF:User');
    }

}