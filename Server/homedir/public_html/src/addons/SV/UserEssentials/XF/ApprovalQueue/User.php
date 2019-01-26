<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\ApprovalQueue;

/**
 * Extends \XF\ApprovalQueue\User
 */
class User extends XFCP_User
{
    /**
     * @param int $id
     * @return \XF\Entity\User|\XF\Mvc\Entity\ArrayCollection|\XF\Mvc\Entity\Entity
     */
    public function getContent($id)
    {
        $db = \XF::db();
        $quotedIds = $db->quote($id);
        $db->query(
            "UPDATE xf_user AS user
                INNER JOIN xf_session_activity AS activity
                    ON (activity.user_id = user.user_id)
                SET user.last_activity = activity.view_date
                WHERE user.user_id IN ({$quotedIds})
                    AND user.last_activity < activity.view_date"
        );

        return parent::getContent($id);
    }
}
