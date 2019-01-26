<?php

namespace NF\GiftUpgrades\XF\Service\User;

/**
 * Extends \XF\Service\User\Downgrade
 */
class Downgrade extends XFCP_Downgrade
{
    public function downgrade()
    {
        $parent = parent::downgrade();

        return $parent;
    }
}