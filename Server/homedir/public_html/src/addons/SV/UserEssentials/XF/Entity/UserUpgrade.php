<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Entity;

use XF\Mvc\Entity\Structure;

/**
 * Extends \XF\Entity\UserUpgrade
 *
 * @property int purchase_count
 * @property bool purchase_count_reached
 * @property int quantity
 */
class UserUpgrade extends XFCP_UserUpgrade
{
    /**
     * @return bool
     */
    public function canPurchase()
    {
        $canPurchase = parent::canPurchase();

        if ($canPurchase && $this->purchase_count_reached)
        {
            return false;
        }

        return $canPurchase;
    }

    /**
     * @return int
     */
    protected function getPurchaseCount()
    {
        return $this->db()->fetchOne(
            'SELECT COUNT(*)
                FROM xf_user_upgrade_active
                WHERE xf_user_upgrade_active.user_upgrade_id = ?',
            [$this->user_upgrade_id]
        );
    }

    /**
     * @return bool
     */
    protected function getPurchaseCountReached()
    {
        if (!$this->quantity)
        {
            return false;
        }

        return ($this->purchase_count >= $this->quantity);
    }

    /**
     * Entity pre-save events.
     */
    protected function _preSave()
    {
        parent::_preSave();

        if ($this->recurring && $this->quantity)
        {
            $this->error(
                \XF::phrase(
                    'sv_ue_recurring_user_upgrades_cannot_have_a_quantity'
                ),
                'quantity'
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

        $structure->columns['quantity'] = [
            'type'    => self::UINT,
            'default' => 0
        ];
        $structure->columns['cost_amount']['min'] = 0;

        $structure->getters['purchase_count'] = true;
        $structure->getters['purchase_count_reached'] = true;

        return $structure;
    }
}
