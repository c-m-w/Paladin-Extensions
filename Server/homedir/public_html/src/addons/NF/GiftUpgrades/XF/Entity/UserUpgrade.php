<?php

namespace NF\GiftUpgrades\XF\Entity;

use NF\GiftUpgrades\Globals;
use XF\Mvc\Entity\Structure;

/**
 * Extends \XF\Entity\UserUpgrade
 *
 * @property int can_gift
 */
class UserUpgrade extends XFCP_UserUpgrade
{
    public function canGift()
    {
        return ($this->can_gift && !$this->recurring);
    }

    public function canPurchase()
    {
        if (Globals::$isGift)
        {
            return $this->canGift();
        }

        return parent::canPurchase();
    }

    /**
     * @param Structure $structure
     * @return Structure
     */
    public static function getStructure(Structure $structure)
    {
        $structure = parent::getStructure($structure);

        $structure->columns['can_gift'] = ['type' => self::BOOL, 'default' => true];

        return $structure;
    }
}