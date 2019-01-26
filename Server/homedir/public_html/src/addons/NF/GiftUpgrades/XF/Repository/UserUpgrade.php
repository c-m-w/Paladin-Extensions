<?php

namespace NF\GiftUpgrades\XF\Repository;

/**
 * Extends \XF\Repository\UserUpgrade
 */
class UserUpgrade extends XFCP_UserUpgrade
{
    public function getFilteredUserUpgradesForList()
    {
        list($upgrades, $purchased) = parent::getFilteredUserUpgradesForList();

        if (!empty($purchased))
        {
            foreach ($purchased AS $upgrade)
            {
                if ($upgrade->canGift())
                {
                    $upgrades[] = $upgrade;
                }
            }
        }

        return [$upgrades, $purchased];
    }

    public function expireActiveUpgrade(\XF\Entity\UserUpgradeActive $active, \XF\Entity\UserUpgradeExpired $expired = null)
    {
        if ($active->is_gift)
        {
            if ($expired === null)
            {
                $expired = $this->em->create('XF:UserUpgradeExpired');
            }

            $expired->is_gift = $active->is_gift;
            $expired->pay_user_id = $active->pay_user_id;
        }

        return parent::expireActiveUpgrade($active, $expired);
    }
}