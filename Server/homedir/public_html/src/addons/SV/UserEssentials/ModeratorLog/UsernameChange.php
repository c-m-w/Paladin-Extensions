<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\ModeratorLog;

use XF\Entity\ModeratorLog;
use XF\ModeratorLog\AbstractHandler;
use XF\Mvc\Entity\Entity;

/**
 * A moderator log handler for user name changes.
 */
class UsernameChange extends AbstractHandler
{
    /**
     * @param Entity $content
     * @param string $field
     * @param mixed  $newValue
     * @param mixed  $oldValue
     * @return string
     */
    protected function getLogActionForChange(
        Entity $content,
        $field,
        $newValue,
        $oldValue
    )
    {
        switch ($field)
        {
            case 'status':
                if ($newValue === 'approved' && $oldValue === 'moderated')
                {
                    return 'approve';
                }
                if ($newValue === 'denied' && $oldValue === 'moderated')
                {
                    return 'reject';
                }
                break;
        }

        return false;
    }

    /**
     * @param ModeratorLog $log
     * @param Entity       $content
     */
    protected function setupLogEntityContent(ModeratorLog $log, Entity $content)
    {
        /** @var \SV\UserEssentials\Entity\UsernameChange $content */
        $log->content_user_id = $content->user_id;
        $log->content_username = $content->from_username;
        $log->content_title = $content->from_username;
        $log->content_url = \XF::app()->router('public')->buildLink(
            'nopath:members',
            [
                'user_id'  => $content->user_id,
                'username' => $content->from_username
            ]
        );
        $log->discussion_content_type = 'unc';
        $log->discussion_content_id = $content->user_id;
    }

    /**
     * @param ModeratorLog $log
     * @return \XF\Phrase
     */
    public function getContentTitle(ModeratorLog $log)
    {
        return \XF::phrase('member_x', [
            'username' => $log->content_title_
        ]);
    }
}
