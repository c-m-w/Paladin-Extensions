<?php

namespace ThemeHouse\Reactions\Listener;

use XF\AddOn\AddOn;
use XF\Entity\AddOn as AddOnEntity;

class AddOnPostInstall
{
    /**
     * @param AddOn $addOn
     * @param AddOnEntity $installedAddOn
     * @param array $json
     * @param array $stateChanges
     */
    public static function run(AddOn $addOn, AddOnEntity $installedAddOn, array $json, array &$stateChanges)
    {
        \XF::repository('ThemeHouse\Reactions:Setup')->setupColumnsForAddOn($addOn->getAddOnId());
    }
}