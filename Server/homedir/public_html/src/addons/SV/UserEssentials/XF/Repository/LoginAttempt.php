<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Repository;

/**
 * Extends XF\Repository\LoginAttempt
 */
class LoginAttempt extends XFCP_LoginAttempt
{
    /**
     * @return \XF\Mvc\Entity\Finder
     */
    public function findLoginAttemptsForList()
    {
        return $this->finder('XF:LoginAttempt')
                    ->setDefaultOrder('attempt_date', 'DESC');
    }

    /**
     * @param \XF\Entity\User $user
     * @return \XF\Finder\LoginAttempt
     */
    public function findLoginAttemptsForUser(\XF\Entity\User $user)
    {
        return $this->finder('XF:LoginAttempt')
                    ->whereOr([
                                  ['login', $user->username],
                                  ['login', $user->email]
                              ])
                    ->setDefaultOrder('attempt_date', 'DESC');
    }
}
