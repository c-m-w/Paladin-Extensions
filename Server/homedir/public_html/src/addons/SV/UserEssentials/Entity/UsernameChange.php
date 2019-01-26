<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

use SV\UserEssentials\XF\Entity\User;

/**
 * COLUMNS
 * @property int|null unc_id
 * @property int user_id
 * @property string from_username
 * @property string to_username
 * @property int date
 * @property string ip_address
 * @property bool is_private
 * @property bool via_acp
 * @property string user_note
 * @property string moderator_note
 * @property int moderator_id
 * @property int moderation_date
 * @property string status
 *
 * RELATIONS
 * @property \XF\Entity\User User
 * @property \XF\Entity\User Moderator
 * @property \XF\Entity\ApprovalQueue ApprovalQueue
 */
class UsernameChange extends Entity
{
    /**
     * @param null $error
     * @return bool
     */
    public function canView(
        /** @noinspection PhpUnusedParameterInspection */
        &$error = null
    )
    {
        if (!$this->canViewInList())
        {
            return false;
        }

        /** @var User $visitor */
        $visitor = \XF::visitor();

        return $visitor->canViewUsernameChangeDetails($this->user_id);
    }

    /**
     * @return bool
     */
    public function canViewInList()
    {
        /** @var User $visitor */
        $visitor = \XF::visitor();
        if (!$visitor->canViewUsernameChanges($this->user_id))
        {
            return false;
        }

        if ($visitor->user_id == $this->user_id)
        {
            return true;
        }

        if ($this->is_private && !$this->canEditPrivacy())
        {
            return false;
        }

        if (
            ($this->status == 'approved')
            || $visitor->canApproveRejectUsername()
        )
        {
            return true;
        }

        return false;
    }

    /**
     * @return bool
     */
    public function canEditPrivacy()
    {
        return \XF::visitor()->hasPermission('general', 'svEditUncPrivacy');
    }

    /**
     * @return bool
     */
    public function isApproved()
    {
        return ($this->status === 'approved');
    }

    /**
     * @return string
     */
    public function getNewStatus()
    {
        /** @var User $visitor */
        $visitor = \XF::visitor();
        if ($visitor->isUsernameChangeModerated())
        {
            return 'moderated';
        }

        return 'approved';
    }

    public function applyUsernameChange()
    {
        $user = $this->User;
        $user->username = $this->to_username;
        $user->save();
    }

    /**
     * @return bool
     */
    public function applyUserTitle()
    {
        $userTitleDays = $this->app()->options()->uncCustomTitleDays;
        if ($userTitleDays)
        {
            $user = $this->User;
            $oldCustomTitle = $user->custom_title;
            $newCustomTitle = \XF::app()->language(0)->phrase(
                'sv_ue_username_change_user_title',
                ['oldName' => $this->from_username]
            );

            $user->fastUpdate('custom_title', $newCustomTitle);

            $values = [
                'user_id'          => $user->user_id,
                'date'             => \XF::$time,
                'old_custom_title' => $oldCustomTitle,
                'new_custom_title' => $newCustomTitle
            ];
            $onDupe = [];
            foreach (['date', 'new_custom_title'] as $update)
            {
                $onDupe[] = "{$update} = VALUES({$update})";
            }
            $onDupe = implode(', ', $onDupe);
            $this->db()->insert('xf_sv_unc_cron', $values, false, $onDupe);

            return true;
        }

        return false;
    }

    /**
     * @return bool
     */
    public function isLastUsernameChange()
    {
        /** @var \SV\UserEssentials\XF\Entity\User $user */
        $user = $this->User;
        $lastUsernameChange = $user->getLastUsernameChange();
        if (!$lastUsernameChange) {
            return true;
        }

        return ($this->unc_id === $lastUsernameChange->unc_id);
    }

    /**
     * @param $username
     * @return bool
     */
    protected function verifyToUsername(&$username)
    {
        /** @var \XF\Validator\Username $validator */
        $validator = $this->app()->validator('Username');
        $username = $validator->coerceValue($username);

        $validator->setOption('self_user_id', $this->user_id);
        if ($this->getOption('admin_edit'))
        {
            $validator->setOption('admin_edit', true);
        }

        if (!$validator->isValid($username, $errorKey))
        {
            $this->error(
                $validator->getPrintableErrorValue($errorKey),
                'username'
            );

            return false;
        }

        return true;
    }

    protected function _postSave()
    {
        if ($this->isInsert())
        {
            /** @var \SV\UserEssentials\Repository\UsernameChange $usernameChangeRepo */
            $usernameChangeRepo = $this->repository('SV\UserEssentials:UsernameChange');
            $finder = $usernameChangeRepo->findPendingUsernameChangesForUser($this->user_id)
                                         ->where('unc_id', '!=', $this->unc_id);
            $pendingUsernameChanges = $finder->fetch();

            foreach ($pendingUsernameChanges as $pendingUsernameChange)
            {
                $pendingUsernameChange->fastUpdate('status', 'denied');
                $pendingUsernameChange->ApprovalQueue->delete();
            }
        }

        $moderatedChange = $this->isStateChanged('status', 'moderated');
        if ($moderatedChange === 'enter')
        {
            $approvalQueue = $this->getRelationOrDefault('ApprovalQueue', false);
            $approvalQueue->content_date = $this->date;
            $approvalQueue->save();
        }
        if ($this->isUpdate())
        {
            if ($moderatedChange === 'leave' && $this->ApprovalQueue)
            {
                $this->ApprovalQueue->delete();
            }
        }
    }

    protected function _postDelete()
    {
        if ($this->status === 'moderated' && $this->ApprovalQueue)
        {
            $this->ApprovalQueue->delete();
        }
    }

    /**
     * @param Structure $structure
     * @return Structure
     */
    public static function getStructure(Structure $structure)
    {
        $structure->table = 'xf_sv_unc';
        $structure->shortName = 'SV\UserEssentials:UsernameChange';
        $structure->contentType = 'unc';
        $structure->primaryKey = 'unc_id';
        $structure->columns = [
            'unc_id'          => [
                'type'          => self::UINT,
                'autoIncrement' => true,
                'nullable'      => true
            ],
            'user_id'         => [
                'type'     => self::UINT,
                'required' => true
            ],
            'from_username'   => [
                'type'      => self::STR,
                'maxLength' => 50,
                'required'  => true
            ],
            'to_username'     => [
                'type'      => self::STR,
                'maxLength' => 50,
                'required'  => 'please_enter_valid_name'
            ],
            'date'            => [
                'type'    => self::UINT,
                'default' => \XF::$time
            ],
            'ip_address'      => [
                'type'      => self::BINARY,
                'maxLength' => 16,
                'default'   => ''
            ],
            'is_private'      => [
                'type'    => self::BOOL,
                'default' => false
            ],
            'via_acp'         => [
                'type'    => self::BOOL,
                'default' => false
            ],
            'user_note'       => [
                'type'      => self::STR,
                'maxLength' => 255,
                'default'   => ''
            ],
            'moderator_note'  => [
                'type'      => self::STR,
                'maxLength' => 255,
                'default'   => ''
            ],
            'moderator_id'    => [
                'type'    => self::UINT,
                'default' => 0
            ],
            'moderation_date' => [
                'type'    => self::UINT,
                'default' => 0
            ],
            'status'          => [
                'type'          => self::STR,
                'default'       => 'approved',
                // changes should be reflected in the alert handler opt outs
                'allowedValues' => ['approved', 'denied', 'moderated']
            ]
        ];
        $structure->getters = [];
        $structure->relations = [
            'User'          => [
                'entity'     => 'XF:User',
                'type'       => self::TO_ONE,
                'conditions' => 'user_id',
                'primary'    => true
            ],
            'Moderator'     => [
                'entity'     => 'XF:User',
                'type'       => self::TO_ONE,
                'conditions' => [['user_id', '=', '$moderator_id']],
                'primary'    => true
            ],
            'ApprovalQueue' => [
                'entity'     => 'XF:ApprovalQueue',
                'type'       => self::TO_ONE,
                'conditions' => [
                    ['content_type', '=', 'unc'],
                    ['content_id', '=', '$unc_id']
                ],
                'primary'    => true
            ]
        ];
        $structure->options = [
            'admin_edit' => false
        ];

        return $structure;
    }
}
