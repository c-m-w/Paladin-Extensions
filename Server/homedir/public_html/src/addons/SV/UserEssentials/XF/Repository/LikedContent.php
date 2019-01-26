<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Repository;

use XF\Entity\User;

/**
 * Extends \XF\Repository\LikedContent
 */
class LikedContent extends XFCP_LikedContent
{
    /**
     * @param User|int $userId
     * @return \XF\Mvc\Entity\Finder
     */
    public function findUserLikesGiven($userId)
    {
        if ($userId instanceof User)
        {
            $userId = $userId->user_id;
        }

        $finder = $this->finder('XF:LikedContent')
                       ->with('Owner')
                       ->where('like_user_id', $userId)
                       ->setDefaultOrder('like_date', 'DESC');

        return $finder;
    }
}
