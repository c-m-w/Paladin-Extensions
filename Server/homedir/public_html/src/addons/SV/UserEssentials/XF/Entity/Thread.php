<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Entity;

use SV\UserEssentials\XF\Logger;
use XF\Mvc\Entity\Structure;

/**
 * Extends \XF\Entity\Thread
 *
 * @property \SV\UserEssentials\Entity\ThreadPermissions ThreadPermissions
 */
class Thread extends XFCP_Thread
{
    /**
     * @param string|null $error
     * @return bool
     */
    public function canEditTitle(&$error = null)
    {
        $canEdit = $this->canEdit($error);
        if (!$this->app()->options()->useressSeparateTitleEdit)
        {
            return $canEdit;
        }

        if (!$canEdit)
        {
            return false;
        }

        $visitor = \XF::visitor();
        if (!$visitor->user_id)
        {
            return false;
        }

        $nodeId = $this->node_id;
        if ($visitor->hasNodePermission($nodeId, 'manageAnyThread'))
        {
            return true;
        }

        if (!$this->discussion_open && !$this->canLockUnlock())
        {
            $error = \XF::phraseDeferred('you_may_not_perform_this_action_because_discussion_is_closed');

            return false;
        }

        if ($visitor->user_id == $this->user_id)
        {
            if (!$visitor->hasNodePermission($nodeId, 'editOwnPost'))
            {
                return false;
            }

            if (!$visitor->hasNodePermission($nodeId, 'editOwnThreadTitle'))
            {
                return false;
            }

            $editLimit = $visitor->hasNodePermission($nodeId, 'editOwnThreadTitleLimit');
            if (
                ($editLimit != -1) &&
                (!$editLimit || $this->post_date < (\XF::$time - (60 * $editLimit)))
            )
            {
                $error = \XF::phraseDeferred(
                    'sv_ue_title_edit_time_limit_expired',
                    ['minutes' => $editLimit]
                );

                return false;
            }

            if (!$this->Forum || !$this->Forum->allow_posting)
            {
                $error = \XF::phraseDeferred('you_may_not_perform_this_action_because_forum_does_not_allow_posting');

                return false;
            }
        }

        return true;
    }

    /**
     * @param string|null $error
     * @return bool
     */
    public function canCreatePoll(&$error = null)
    {
        $canCreatePoll = parent::canCreatePoll($error);

        if ($canCreatePoll)
        {
            $visitor = \XF::visitor();
            if ($visitor->hasNodePermission($this->node_id, 'manageAnyThread'))
            {
                return true;
            }

            return $visitor->hasNodePermission($this->node_id, 'createPoll');
        }

        return $canCreatePoll;
    }

    /**
     * @param string|null $error
     * @return bool
     */
    public function canReply(&$error = null)
    {
        $canReply = parent::canReply($error);

        if ($canReply)
        {
            $visitor = \XF::visitor();
            if (!$visitor->user_id || ($visitor->user_id != $this->user_id))
            {
                return $visitor->hasNodePermission(
                    $this->node_id,
                    'userEssReplyToOthers'
                );
            }
        }

        return $canReply;
    }

    /**
     * @param string|null $error
     * @return bool
     */
    public function canLockUnlock(&$error = null)
    {
        $canLockUnlock = parent::canLockUnlock($error);

        if (!$canLockUnlock)
        {
            $visitor = \XF::visitor();
            if (!$visitor->user_id || ($visitor->user_id != $this->user_id))
            {
                return false;
            }

            if (!$visitor->hasNodePermission(
                $this->node_id,
                'lockUnlockOwnThread'
            ))
            {
                return false;
            }

            $threadPermissions = $this->ThreadPermissions;
            if (!$threadPermissions)
            {
                return true;
            }

            if ($threadPermissions->lockedByUser)
            {
                return true;
            }

            return ($this->discussion_open)
                ?
                $threadPermissions->allowLockByUser
                :
                $threadPermissions->allowUnlockByUser;
        }

        return $canLockUnlock;
    }

    /**
     * @param string|null $error
     * @return bool
     */
    public function canReplyBan(&$error = null)
    {
        $canReplyBan = parent::canReplyBan($error);

        if (!$canReplyBan)
        {
            if (!$this->discussion_open)
            {
                $error = \XF::phraseDeferred(
                    'you_may_not_perform_this_action_because_discussion_is_closed'
                );

                return false;
            }

            $visitor = \XF::visitor();
            if (!$visitor->user_id || ($visitor->user_id != $this->user_id))
            {
                return false;
            }

            if (!$visitor->hasNodePermission(
                $this->node_id,
                'userEssThreadReplyBan'
            ))
            {
                return false;
            }

            if (!$this->ThreadPermissions)
            {
                return true;
            }

            return $this->ThreadPermissions->replyBanInOwnThread;
        }

        return $canReplyBan;
    }

    /**
     * @param string|null $error
     * @return bool
     */
    public function canEditLockPermissions(/** @noinspection PhpUnusedParameterInspection */
        &$error = null)
    {
        $visitor = \XF::visitor();
        $user = $this->User;
        $nodeId = $this->node_id;

        if (!$user)
        {
            return false;
        }

        if (
            $visitor->hasNodePermission($nodeId, 'lockUnlockThread')
            && $user->hasNodePermission($nodeId, 'lockUnlockOwnThread')
        )
        {
            return true;
        }

        return false;
    }

    /**
     * @param string|null $error
     * @return bool
     */
    public function canEditReplyBanPermissions(/** @noinspection PhpUnusedParameterInspection */
        &$error = null)
    {
        $visitor = \XF::visitor();
        $user = $this->User;
        $nodeId = $this->node_id;

        if (!$user)
        {
            return false;
        }

        if (
            $visitor->hasNodePermission($nodeId, 'threadReplyBan')
            && $user->hasNodePermission($nodeId, 'userEssThreadReplyBan')
        )
        {
            return true;
        }

        return false;
    }

    /**
     * Entity pre-save events.
     */
    protected function _preSave()
    {
        parent::_preSave();

        if ($this->isChanged('discussion_open'))
        {
            $visitor = \XF::visitor();
            $lockedByUser = (
                ($visitor->user_id == $this->user_id)
                && !$visitor->hasNodePermission(
                    $this->node_id,
                    'lockUnlockThread'
                )
            );

            $threadPermissions = $this->getRelationOrDefault(
                'ThreadPermissions'
            );
            $threadPermissions->user_id = \XF::visitor()->user_id;
            $threadPermissions->lockedByUser = $lockedByUser;
            if (!$lockedByUser)
            {
                $threadPermissions->allowUnlockByUser = $this->discussion_open;
            }
        }
    }

    /**
     * Entity post-save events.
     */
    protected function _postSave()
    {
        parent::_postSave();

        if ($this->isUpdate() && $this->getOption('sv_log_user'))
        {
            /** @var Logger $logger */
            $logger = $this->app()->logger();
            $logger->logUserChanges('thread', $this);
        }
    }

    /**
     * Entity post-delete events.
     */
    protected function _postDelete()
    {
        parent::_postDelete();

        if ($this->ThreadPermissions)
        {
            $this->ThreadPermissions->delete();
        }
    }

    /**
     * @param Structure $structure
     * @return Structure
     */
    public static function getStructure(Structure $structure)
    {
        $structure = parent::getStructure($structure);

        $structure->relations['ThreadPermissions'] = [
            'entity'     => 'SV\UserEssentials:ThreadPermissions',
            'type'       => self::TO_ONE,
            'conditions' => 'thread_id',
            'primary'    => true
        ];
        $structure->options['sv_log_user'] = true;

        return $structure;
    }
}
