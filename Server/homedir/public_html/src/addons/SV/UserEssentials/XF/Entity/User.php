<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Entity;

use XF\Mvc\Entity\AbstractCollection;
use XF\Mvc\Entity\Structure;

use SV\UserEssentials\Entity\UsernameChange;

/**
 * Extends \XF\Entity\User
 *
 * @property array useress_tags
 * @property boolean visible
 * @property boolean visible_
 * @property boolean activity_visible
 * @property boolean activity_visible_
 * @property UsernameChange[]|AbstractCollection username_changes_in_period
 * @property int remaining_username_changes_in_period
 * @property boolean username_change_period_end
 * @property boolean has_username_changes
 * @property UsernameChange|null pending_username_change
 * @property UsernameChange[] UsernameChange
 */
class User extends XFCP_User
{
    /**
     * @return bool
     */
    public function canGoInvisible()
    {
        return $this->hasPermission('general', 'useressGoInvisible');
    }

    /**
     * @param string|null $error
     * @return bool
     */
    public function canChangeUsername(
        /** @noinspection PhpUnusedParameterInspection */
        &$error = null
    )
    {
        if (!$this->hasPermission('general', 'canUserNameChange'))
        {
            return false;
        }

        $usernameChangePeriodEnd = $this->username_change_period_end;
        if ($usernameChangePeriodEnd)
        {
            // the user does not necessarily have changes left in the period
            // but they are still able to change their username in general
            return true;
        }

        $remainingUsernameChanges = $this->remaining_username_changes_in_period;
        if ($remainingUsernameChanges !== 0)
        {
            return true;
        }

        return false;
    }

    /**
     * @param User|int|null $userId
     * @return bool
     */
    public function canViewUsernameChanges($userId = null)
    {
        if ($userId instanceof User)
        {
            $userId = $userId->user_id;
        }

        $visibility = $this->app()->options()->useressDisplayProfileTab;

        if ($this->is_admin)
        {
            return true;
        }

        if ($visibility === 'nobody')
        {
            return false;
        }

        if ($visibility === 'everybody')
        {
            return true;
        }

        if (($visibility === 'members') && $this->user_id)
        {
            return true;
        }

        if (($visibility === 'mods_and_member') && ($this->user_id === $userId))
        {
            return true;
        }

        if (
            (($visibility === 'mods') || ($visibility === 'mods_and_member'))
            && ($this->is_admin || $this->is_moderator)
        )
        {
            return true;
        }

        return false;
    }

    /**
     * @param User|int|null $userId
     * @return bool
     */
    public function canViewUsernameChangeDetails($userId = null)
    {
        if ($userId instanceof User)
        {
            $userId = $userId->user_id;
        }

        if (!$this->canViewUsernameChanges($userId))
        {
            return false;
        }

        if ($this->canApproveRejectUsername())
        {
            return true;
        }

        if ($this->user_id === $userId)
        {
            return true;
        }

        return false;
    }

    /**
     * @return bool
     */
    public function canApproveRejectUsername()
    {
        return (
            $this->is_moderator
            && $this->hasPermission('general', 'manageUserNameChange')
        );
    }

    /**
     * @return bool
     */
    public function isUsernameChangeModerated()
    {
        if ($this->canApproveRejectUsername())
        {
            return false;
        }

        return $this->app()->options()->uncModerate;
    }

    /**
     * Checks whether or not the *visitor* can edit *this user's* tags.
     *
     * @return bool
     */
    public function canEditTags()
    {
        if (!$this->app()->options()->enableTagging)
        {
            return false;
        }

        $visitor = \XF::visitor();

        if ($visitor->user_id === $this->user_id)
        {
            return $visitor->hasPermission('general', 'useress_manageowntags');
        }

        return $visitor->hasPermission('general', 'useress_managealltags');
    }

    /**
     * @return \SV\UserEssentials\Entity\UsernameChange
     */
    public function getNewUsernameChange()
    {
        /** @var \SV\UserEssentials\Entity\UsernameChange $usernameChange */
        $usernameChange = $this->_em->create('SV\UserEssentials:UsernameChange');
        $usernameChange->user_id = $this->user_id;
        $usernameChange->from_username = $this->username;

        return $usernameChange;
    }

    /**
     * @param bool $forList
     *
     * @return \SV\UserEssentials\Entity\UsernameChange
     */
    public function getLastUsernameChange($forList = false)
    {
        $usernameChangeRepo = $this->getUsernameChangeRepo();
        if ($forList) {
            $finder = $usernameChangeRepo->findUsernameChangesForList($this);
        } else {
            $finder = $usernameChangeRepo->findUsernameChangesForUser($this);
        }
        return $finder->fetchOne();
    }

    /**
     * @return bool
     */
    public function revertUsernameChangeTitle()
    {
        $userTitle = $this->username_change_title;
        if (!$userTitle) {
            return false;
        }

        if ($this->custom_title == $userTitle['new_custom_title']) {
            $this->fastUpdate(
                'custom_title',
                $userTitle['old_custom_title']
            );
        }

        $this->db()->delete('xf_sv_unc_cron', 'user_id =  ?', $this->user_id);
        $this->clearCache('username_change_title');
        return true;
    }

    /**
     * @return bool
     */
    public function getVisible()
    {
        if (!$this->canGoInvisible())
        {
            return true;
        }

        return $this->visible_;
    }

    /**
     * @return bool
     */
    public function getActivityVisible()
    {
        if (!$this->canGoInvisible())
        {
            return true;
        }

        return $this->activity_visible_;
    }

    /**
     * @return bool
     */
    public function getHasUsernameChanges()
    {
        $usernameChangeRepo = $this->getUsernameChangeRepo();
        $finder = $usernameChangeRepo->findUsernameChangesForList($this);

        return ($finder->total() > 0);
    }

    /**
     * @return UsernameChange|null
     */
    public function getPendingUsernameChange()
    {
        $usernameChangeRepo = $this->getUsernameChangeRepo();
        $finder = $usernameChangeRepo->findPendingUsernameChangesForUser($this);

        return $finder->fetchOne();
    }

    /**
     * @return \XF\Mvc\Entity\AbstractCollection
     */
    public function getUsernameChangesInPeriod()
    {
        $usernameChangeRepo = $this->getUsernameChangeRepo();
        $finder = $usernameChangeRepo->findUsernameChangesInPeriodForUser($this);

        return $finder->fetch();
    }

    /**
     * @return int
     */
    public function getRemainingUsernameChangesInPeriod()
    {
        $options = $this->app()->options();

        $maxMessageCount = $options->uncMaxPostCount;
        if ($maxMessageCount && ($this->message_count > $maxMessageCount))
        {
            return 0;
        }

        $maxUsernameChanges = $options->uncMaxChanges;
        if (!$maxUsernameChanges)
        {
            return -1;
        }

        $usernameChanges = $this->username_changes_in_period;
        $remaining = ($maxUsernameChanges - $usernameChanges->count());

        return max(0, $remaining);
    }

    /**
     * @return int
     */
    public function getUsernameChangePeriodEnd()
    {
        $usernameChangePeriod = ($this->app()->options()->uncResetDays * 86400);
        if (!$usernameChangePeriod)
        {
            return 0;
        }

        $usernameChanges = $this->username_changes_in_period;
        if ($usernameChanges->count())
        {
            $earliestDate = $usernameChanges->first()->date;
        }
        else
        {
            $earliestDate = \XF::$time;
        }

        return ($earliestDate + $usernameChangePeriod);
    }

    /**
     * @return array
     */
    public function getUsernameChangeTitle()
    {
        return $this->db()->fetchRow(
            'SELECT *
                FROM xf_sv_unc_cron
                WHERE user_id = ?',
            $this->user_id
        );
    }

    /**
     * Entity post-save events.
     */
    protected function _postSave()
    {
        parent::_postSave();

        if ($this->isChanged('custom_title')) {
            $this->db()->delete(
                'xf_sv_unc_cron',
                'user_id = ?',
                $this->user_id
            );
        }
    }

    /**
     * @param Structure $structure
     * @return Structure
     */
    public static function getStructure(Structure $structure)
    {
        $structure = parent::getStructure($structure);

        $structure->columns['useress_tags'] = [
            'type'     => self::SERIALIZED_ARRAY,
            'default'  => [],
            'nullable' => true
        ];

        $structure->getters['visible'] = true;
        $structure->getters['activity_visible'] = true;
        $structure->getters['has_username_changes'] = true;
        $structure->getters['pending_username_change'] = true;
        $structure->getters['username_changes_in_period'] = true;
        $structure->getters['remaining_username_changes_in_period'] = true;
        $structure->getters['username_change_period_end'] = true;
        $structure->getters['username_change_title'] = true;

        $structure->relations['UsernameChange'] = [
            'entity'     => 'SV\UserEssentials:UsernameChange',
            'type'       => self::TO_MANY,
            'conditions' => 'user_id',
            'key'        => 'unc_id'
        ];

        $structure->behaviors['XF:Taggable'] = ['stateField' => ''];

        return $structure;
    }

    /**
     * @return \SV\UserEssentials\Repository\UsernameChange|\XF\Mvc\Entity\Repository
     */
    protected function getUsernameChangeRepo()
    {
        return $this->repository('SV\UserEssentials:UsernameChange');
    }
}
