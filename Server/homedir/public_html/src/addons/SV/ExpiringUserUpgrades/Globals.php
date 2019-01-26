<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\ExpiringUserUpgrades;

/**
 * Add-on globals.
 */
class Globals
{
    /** @var bool */
    public static $forceDowngradeAlert = false;

    /** @var null|string */
    public static $downgradeReason = null;

    /**
     * Private constructor, use statically.
     */
    private function __construct()
    {
    }
}
