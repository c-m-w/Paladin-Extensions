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
 * A user log handler for threads.
 */
class Thread extends AbstractHandler
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
        /** @var \SV\UserEssentials\XF\Entity\Thread $content */
        switch ($field)
        {
            case 'custom_fields':
                return 'custom_fields_edit';

            case 'sticky':
                return $newValue ? 'stick' : 'unstick';

            case 'discussion_open':
                return $newValue ? 'unlock' : 'lock';

            case 'discussion_state':
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

            case 'title':
                return ['title', ['old' => $oldValue]];

            case 'prefix_id':
                if ($oldValue)
                {
                    $old = \XF::phrase('thread_prefix.' . $oldValue)->render();
                }
                else
                {
                    $old = '-';
                }

                return ['prefix', ['old' => $old]];
        }

        return false;
    }

    /**
     * @param UserLog $log
     * @param Entity  $content
     */
    protected function setupLogEntityContent(UserLog $log, Entity $content)
    {
        /** @var \XF\Entity\Thread $content */
        $log->content_user_id = $content->user_id;
        $log->content_username = $content->username;
        $log->content_title = $content->title;
        $log->content_url = \XF::app()->router('public')->buildLink(
            'nopath:threads',
            $content
        );
        $log->discussion_content_type = 'thread';
        $log->discussion_content_id = $content->thread_id;
    }

    /**
     * @param UserLog $log
     * @return array
     */
    protected function getActionPhraseParams(UserLog $log)
    {
        if ($log->action === 'edit')
        {
            return ['elements' => implode(', ', array_keys($log->action_params))];
        }
        else
        {
            return parent::getActionPhraseParams($log);
        }
    }
}
