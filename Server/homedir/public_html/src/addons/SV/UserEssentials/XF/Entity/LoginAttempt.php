<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Entity;

/**
 * Extends \XF\Entity\LoginAttempt
 */
class LoginAttempt extends XFCP_LoginAttempt
{
    /**
     * @return bool
     */
    public function canDelete()
    {
        return \XF::visitor()->hasAdminPermission('user');
    }
}
