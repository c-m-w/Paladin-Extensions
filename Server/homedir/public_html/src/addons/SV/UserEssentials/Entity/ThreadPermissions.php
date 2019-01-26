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

/**
 * COLUMNS
 * @property int thread_id
 * @property int user_id
 * @property bool lockedByUser
 * @property bool allowLockByUser
 * @property bool allowUnlockByUser
 * @property bool replyBanInOwnThread
 */
class ThreadPermissions extends Entity
{
    /**
     * @param Structure $structure
     * @return Structure
     */
    public static function getStructure(Structure $structure)
    {
        $structure->table = 'xf_sv_thread_lock';
        $structure->shortName = 'SV\UserEssentials:ThreadPermissions';
        $structure->primaryKey = 'thread_id';
        $structure->columns = [
            'thread_id'           => [
                'type' => self::UINT
            ],
            'user_id'             => [
                'type' => self::UINT
            ],
            'lockedByUser'        => [
                'type'    => self::BOOL,
                'default' => false
            ],
            'allowLockByUser'     => [
                'type'    => self::BOOL,
                'default' => true
            ],
            'allowUnlockByUser'   => [
                'type'    => self::BOOL,
                'default' => true
            ],
            'replyBanInOwnThread' => [
                'type'    => self::BOOL,
                'default' => true
            ]
        ];
        $structure->getters = [];
        $structure->relations = [];

        return $structure;
    }
}
