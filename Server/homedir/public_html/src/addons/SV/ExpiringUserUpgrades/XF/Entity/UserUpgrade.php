<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\ExpiringUserUpgrades\XF\Entity;

use XF\Mvc\Entity\Structure;

/**
 * Extends \XF\Entity\UserUpgrade
 *
 * @property int exup_days
 */
class UserUpgrade extends XFCP_UserUpgrade
{
    /**
     * @return bool
     */
    public function canPurchase()
    {
        $visitor = \XF::visitor();

        if ($this->Active[$visitor->user_id])
        {
            return $this->canExtend();
        }

        return parent::canPurchase();
    }

    /**
     * @param null $error
     * @return bool
     */
    public function canExtend(&$error = null)
    {
        $visitor = \XF::visitor();
        $activeUpgrade = $this->Active[$visitor->user_id];

        if (!$this->can_purchase)
        {
            $error = "exup_upgrade_can_not_be_purchased";

            return false;
        }

        if (!$this->length_amount)
        {
            $error = "exup_upgrade_does_not_end";

            return false;
        }

        if ($this->recurring)
        {
            $error = "exup_upgrade_is_recurring";

            return false;
        }

        $extra = $activeUpgrade->extra;

        if (isset($extra['recurring']) && $this->recurring != $extra['recurring'])
        {
            $error = "exup_upgrade_recurring_status_has_changed";

            return false;
        }

        if (isset($extra['extra_group_ids']) && $this->extra_group_ids != $extra['extra_group_ids'])
        {
            $error = "exup_upgrade_usergroups_added_has_changed";

            return false;
        }

        // length and cost details are still the same
        if (isset($extra['cost_amount']) && $this->cost_amount != $activeUpgrade->extra['cost_amount'])
        {
            $error = "exup_upgrade_cost_has_changed";

            return false;
        }

        if (isset($extra['cost_currency']) && $this->cost_currency != $activeUpgrade->extra['cost_currency'])
        {
            $error = "exup_upgrade_currency_changed";

            return false;
        }

        if (isset($extra['length_amount']) && $this->length_amount != $activeUpgrade->extra['length_amount'])
        {
            $error = "exup_upgrade_length_changed";

            return false;
        }

        if (isset($extra['length_unit']) && $this->length_unit != $activeUpgrade->extra['length_unit'])
        {
            $error = "exup_upgrade_length_units_changed";

            return false;
        }

        if ($this->length_unit === '')
        {
            $error = "exup_upgrade_has_no_length_units";

            return false;
        }

        if ($this->length_amount === 0)
        {
            $error = "exup_upgrade_has_no_length_amount";

            return false;
        }

        if (empty($activeUpgrade->end_date))
        {
            $error = "exup_upgrade_has_no_end_date";

            return false;
        }

        return true;
    }

    /**
     * @param Structure $structure
     * @return Structure
     */
    public static function getStructure(Structure $structure)
    {
        $structure = parent::getStructure($structure);

        $structure->columns['exup_days'] = ['type' => self::UINT, 'default' => 7, 'max' => 30];

        return $structure;
    }
}