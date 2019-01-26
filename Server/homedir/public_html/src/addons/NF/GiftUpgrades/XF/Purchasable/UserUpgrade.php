<?php

namespace NF\GiftUpgrades\XF\Purchasable;

use NF\GiftUpgrades\Globals;

/**
 * Extends \XF\Purchasable\UserUpgrade
 */
class UserUpgrade extends XFCP_UserUpgrade
{
    public function getPurchaseFromRequest(\XF\Http\Request $request, \XF\Entity\User $purchaser, &$error = null)
    {
        if (Globals::$isGift = $request->filter('gift', 'bool'))
        {
            Globals::$giftTo = $request->filter('username', 'str');
            Globals::$isAnonymous = $request->filter('anonymous', 'bool');
            Globals::$payUserId = \XF::visitor()->user_id;
            Globals::$payUsername = \XF::visitor()->username;

            $user = \XF::em()->findOne('XF:User', ['username' => Globals::$giftTo]);
            if (!$user)
            {
                $error = \XF::phrase('requested_user_not_found');
                return false;
            }

            if ($user->user_id == Globals::$payUserId)
            {
                $error = \XF::phrase('nixfifty_giftupgrades_you_cannot_gift_yourself');
                return false;
            }
        }

        return parent::getPurchaseFromRequest($request, $purchaser, $error);
    }

    public function getPurchaseFromExtraData(array $extraData, \XF\Entity\PaymentProfile $paymentProfile, \XF\Entity\User $purchaser, &$error = null)
    {
        if (array_key_exists('is_gift', $extraData))
        {
            Globals::$isGift = $extraData['is_gift'];
        }

        return parent::getPurchaseFromExtraData($extraData, $paymentProfile, $purchaser, $error);
    }

    public function getPurchaseObject(\XF\Entity\PaymentProfile $paymentProfile, $purchasable, \XF\Entity\User $purchaser)
    {
        $parent = parent::getPurchaseObject($paymentProfile, $purchasable, $purchaser);

        try
        {
            if (Globals::$isGift)
            {
                // no worky
                //$parent->extraData['is_gift'] = true;

                $temp = $parent->extraData;

                $temp['is_gift'] = Globals::$isGift;
                $temp['is_anonymous'] = Globals::$isAnonymous;
                $temp['giftTo'] = Globals::$giftTo;
                $temp['payUser'] = [
                    'user_id' => Globals::$payUserId,
                    'username' => Globals::$payUsername
                ];

                $parent->extraData = $temp;
            }
        }
        finally
        {
            Globals::$giftTo = null;
            Globals::$isGift = null;
            Globals::$isAnonymous = null;
            Globals::$payUserId = null;
            Globals::$payUsername = null;
        }

        return $parent;
    }
}