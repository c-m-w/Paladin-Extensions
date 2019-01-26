<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\UserLog;

use XF\Mvc\Entity\Entity;

use SV\UserEssentials\Entity\UserLog;

/**
 * A user log handler for users.
 */
class User extends AbstractHandler
{
    /**
     * @param Entity $content
     * @param string $field
     * @param string $newValue
     * @param string $oldValue
     * @return string|bool
     */
    protected function getLogActionForChange(
        Entity $content,
        $field,
        $newValue,
        $oldValue
    )
    {
        return false;
    }

    /**
     * @param UserLog $log
     * @param Entity  $content
     */
    protected function setupLogEntityContent(UserLog $log, Entity $content)
    {
        /** @var \XF\Entity\User $content */
        $log->content_user_id = $content->user_id;
        $log->content_username = $content->username;
        $log->content_title = $content->username;
        $log->content_url = \XF::app()->router('public')->buildLink(
            'nopath:members',
            $content
        );
        $log->discussion_content_type = 'user';
        $log->discussion_content_id = $content->user_id;
    }

    /**
     * @param UserLog $log
     * @return string
     */
    public function getContentTitle(UserLog $log)
    {
        return \XF::phrase('member_x', [
            'username' => $log->content_title_
        ]);
    }
}
