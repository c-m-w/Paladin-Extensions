<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Purchasable;

use XF\Entity\User;
use XF\Http\Request;

/**
 * Extends \XF\Purchasable\UserUpgrade
 */
class UserUpgrade extends XFCP_UserUpgrade
{
    /**
     * @param Request $request
     * @param User  $purchaser
     * @param string|null      $error
     * @return \XF\Purchasable\Purchase|bool
     */
    public function getPurchaseFromRequest(
        Request $request,
        User $purchaser,
        &$error = null
    )
    {
        $purchase = parent::getPurchaseFromRequest($request, $purchaser, $error);
        if ($purchase && ($purchase->cost === '0.00'))
        {
            $costAmount = round($request->filter('cost_amount', 'unum'), 2);
            // this maximum is not arbitrary
            // some payment providers error on values over 999.99
            $svCustomUpgradeMinimum = \XF::options()->svCustomUpgradeMinimum;
            $svCustomUpgradeMaximum = \XF::options()->svCustomUpgradeMaximum;

            if (($costAmount < $svCustomUpgradeMinimum) || ($costAmount > $svCustomUpgradeMaximum))
            {
                $error = \XF::phrase(
                    'sv_ue_please_enter_a_valid_price_to_continue_with_your_purchase',
                    [
                        'min' => $svCustomUpgradeMinimum,
                        'max' => $svCustomUpgradeMaximum
                    ]
                );

                return false;
            }

            $purchase->cost = (string)number_format($costAmount, 2);
        }

        return $purchase;
    }
}
