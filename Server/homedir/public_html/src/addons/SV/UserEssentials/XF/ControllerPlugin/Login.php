<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\ControllerPlugin;

use XF\Entity\User;

/**
 * Extends \XF\ControllerPlugin\Login
 */
class Login extends XFCP_Login
{
    /**
     * @param User $user
     * @param bool $remember
     */
    public function completeLogin(User $user, $remember)
    {
        parent::completeLogin($user, $remember);

        $this->app->db()->query(
            "UPDATE xf_user AS user
                INNER JOIN xf_session_activity AS activity
                    ON (activity.user_id > 0 AND activity.user_id = user.user_id)
                SET user.last_activity = activity.view_date
                WHERE user.user_id = ?
                    AND user.last_activity < activity.view_date",
            $user->user_id
        );
    }
}
