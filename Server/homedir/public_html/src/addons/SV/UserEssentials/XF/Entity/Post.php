<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Entity;

use SV\UserEssentials\Entity\Mentionable;
use SV\UserEssentials\Entity\MentionableInterface;
use SV\UserEssentials\XF\Logger;
use XF\Mvc\Entity\Structure;

/*
 * Extends \XF\Entity\Post
 */
class Post extends XFCP_Post implements MentionableInterface
{
    /**
     * Enable mentioned user fetching for posts.
     */
    use Mentionable
    {
        getStructure as protected getStructureMentionable;
    }

    public function canEdit(&$error = null)
    {
        $canEdit = parent::canEdit($error);

        if($canEdit)
        {
            return $canEdit;
        }

        $visitor = \XF::visitor();
        $thread = $this->Thread;
        if (!$visitor->user_id || !$thread)
        {
            return false;
        }

        if ($visitor->user_id != $thread->user_id)
        {
            return false;
        }

        if (!$thread->discussion_open && !$thread->canLockUnlock())
        {
            $error = \XF::phraseDeferred(
                'you_may_not_perform_this_action_because_discussion_is_closed'
            );

            return false;
        }

        $editLimit = $visitor->hasNodePermission($thread->node_id, 'editOwnPostTimeLimit');
        if ($editLimit != -1 && (!$editLimit || $this->post_date < \XF::$time - 60 * $editLimit))
        {
            $error = \XF::phraseDeferred('message_edit_time_limit_expired', ['minutes' => $editLimit]);
            return false;
        }

        if (!$thread->Forum || !$thread->Forum->allow_posting)
        {
            $error = \XF::phraseDeferred('you_may_not_perform_this_action_because_forum_does_not_allow_posting');
            return false;
        }

        return $visitor->hasNodePermission(
            $thread->node_id,
            'useressEditPostsOwnThread'
        );
    }

    /**
     * @param string      $type
     * @param string|null $error
     * @return bool
     */
    public function canDelete($type = 'soft', &$error = null)
    {
        $canDelete = parent::canDelete($type, $error);

        if ($canDelete)
        {
            return $canDelete;
        }

        $visitor = \XF::visitor();
        $thread = $this->Thread;
        if (!$visitor->user_id || !$thread)
        {
            return false;
        }

        if ($visitor->user_id != $thread->user_id)
        {
            return false;
        }

        if ($type != 'soft')
        {
            return false;
        }

        if (!$thread->discussion_open && !$thread->canLockUnlock())
        {
            $error = \XF::phraseDeferred(
                'you_may_not_perform_this_action_because_discussion_is_closed'
            );

            return false;
        }

        if ($this->isFirstPost())
        {
            return false;
        }

        return $visitor->hasNodePermission(
            $thread->node_id,
            'useressDelPostsOwnThread'
        );
    }

    /**
     * Writes changes to the user log.
     */
    protected function _postSave()
    {
        parent::_postSave();

        if ($this->isUpdate() && $this->getOption('sv_log_user'))
        {
            /** @var Logger $logger */
            $logger = $this->app()->logger();
            $logger->logUserChanges('post', $this);
        }
    }

    /**
     * @param Structure $structure
     * @return Structure
     */
    public static function getStructure(Structure $structure)
    {
        $structure = static::getStructureMentionable($structure);

        $structure->options['sv_log_user'] = true;

        return $structure;
    }
}
