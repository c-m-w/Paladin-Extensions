<?php

namespace NF\GiftUpgrades\XF\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

/**
 * Extends \XF\Entity\UserUpgradeActive
 *
 * @property int is_gift
 * @property int pay_user_id
 */
class UserUpgradeActive extends XFCP_UserUpgradeActive
{
    /**
     * @param Structure $structure
     * @return Structure
     */
    public static function getStructure(Structure $structure)
    {
        $structure = parent::getStructure($structure);

        $structure->columns['is_gift'] = ['type' => self::BOOL, 'default' => false];
        $structure->columns['pay_user_id'] = ['type' => self::UINT, 'default' => 0];

        return $structure;
    }
}