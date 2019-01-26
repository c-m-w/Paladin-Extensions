<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\UserLog;

use XF\Entity\User as UserEntity;
use XF\Mvc\Entity\Entity;

use SV\UserEssentials\Entity\UserLog;

/**
 * A user log handler for posts.
 */
class Post extends AbstractHandler
{
    /**
     * @param Entity     $content
     * @param string     $action
     * @param UserEntity $actor
     * @return bool
     */
    public function isLoggable(Entity $content, $action, UserEntity $actor)
    {
        /** @var \SV\UserEssentials\XF\Entity\User $content */
        if ($actor->user_id != $content->user_id)
        {
            return false;
        }

        return parent::isLoggable($content, $action, $actor);
    }

    /**
     * @param Entity $content
     * @param string $field
     * @param string $newValue
     * @param string $oldValue
     * @return string|bool|array
     */
    protected function getLogActionForChange(
        Entity $content,
        $field,
        $newValue,
        $oldValue
    )
    {
        /** @var \SV\UserEssentials\XF\Entity\Post $content */
        switch ($field)
        {
            case 'message':
                return 'edit';

            case 'message_state':
                if ($newValue === 'visible' && $oldValue === 'deleted')
                {
                    return 'undelete';
                }
                elseif ($newValue === 'deleted')
                {
                    $reason = $content->DeletionLog ? $content->DeletionLog->delete_reason : '';

                    return ['delete_soft', ['reason' => $reason]];
                }
                break;
        }

        return false;
    }

    /**
     * @param UserLog $log
     * @param Entity  $content
     */
    protected function setupLogEntityContent(UserLog $log, Entity $content)
    {
        /** @var \XF\Entity\Post $content */
        $log->content_user_id = $content->user_id;
        $log->content_username = $content->username;
        $log->content_title = $content->Thread->title;
        $log->content_url = \XF::app()->router('public')->buildLink(
            'nopath:posts',
            $content
        );
        $log->discussion_content_type = 'thread';
        $log->discussion_content_id = $content->thread_id;
    }

    /**
     * @param UserLog $log
     * @return string
     */
    public function getContentTitle(UserLog $log)
    {
        $threadTitle = \XF::app()->stringFormatter()->censorText(
            $log->content_title_
        );

        return \XF::phrase('post_in_thread_x', ['title' => $threadTitle]);
    }
}
