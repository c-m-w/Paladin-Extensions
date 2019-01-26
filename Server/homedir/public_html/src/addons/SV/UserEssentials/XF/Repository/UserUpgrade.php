<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Repository;

/*
 * Extends \XF\Repository\UserUpgrade
 */
class UserUpgrade extends XFCP_UserUpgrade
{
    /**
     * @return array
     */
    public function getFilteredUserUpgradesForList()
    {
        list($upgrades, $purchased) = parent::getFilteredUserUpgradesForList();

        foreach ($upgrades as $upgradeId => $upgrade)
        {
            if ($upgrade->purchase_count_reached)
            {
                unset($upgrades[$upgradeId]);
            }
        }

        return [$upgrades, $purchased];
    }
}
