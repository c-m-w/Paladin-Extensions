<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\Util;

/**
 * Utility methods for add-ons.
 */
class AddOn
{
    /**
     * @param string $addOnId
     * @param int    $versionId
     * @param string $operator
     *
     * return bool|int
     */
    public static function isActive(
        $addOnId,
        $versionId = null,
        $operator = '>='
    ) {
        $addOns = \XF::registry()['addOns'];
        if (!isset($addOns[$addOnId])) {
            return false;
        }

        if ($versionId === null) {
            return $addOns[$addOnId];
        }
        $activeVersionId = $addOns[$addOnId];

        switch ($operator) {
            case '>':
                return ($activeVersionId > $versionId);
            case '>=':
                return ($activeVersionId >= $versionId);
            case '<':
                return ($activeVersionId < $versionId);
            case '<=':
                return ($activeVersionId <= $versionId);
            default:
                return $addOns[$addOnId];
        }
    }
}
