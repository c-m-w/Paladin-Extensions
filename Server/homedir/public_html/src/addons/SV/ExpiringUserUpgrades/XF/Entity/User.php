<?php

namespace SV\ExpiringUserUpgrades\XF\Entity;

/**
 * Class User
 *
 * @package SV\ExpiringUserUpgrades
 */
class User extends XFCP_User
{

    /**
     * @param null $error
     * @return bool
     */
    public function canChangeSVExUpEmailPreferences(/** @noinspection PhpUnusedParameterInspection */ &$error = null)
    {
        $activeUpgradesCount = $this->finder('XF:UserUpgradeActive')
                                    ->where('user_id', '=', $this->user_id)
                                    ->total();

        if ($activeUpgradesCount > 0)
        {
            return true;
        }

        /** @var \XF\Entity\Purchasable $purchasable */
        $purchasable = $this->em()->find('XF:Purchasable', 'user_upgrade', 'AddOn');
        if ($purchasable->isActive())
        {
            return true;
        }

        return false;
    }
}