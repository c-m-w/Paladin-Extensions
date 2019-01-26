<?php

namespace NF\GiftUpgrades\XF\Pub\Controller;

use XF\Mvc\ParameterBag;

/**
 * Extends \XF\Pub\Controller\Purchase
 */
class Purchase extends XFCP_Purchase
{
    public function actionIndex(ParameterBag $params)
    {
        $isGift = $this->filter('gift', 'bool');
        $isConfirmed = $this->filter('confirmed', 'bool');
        $profileId = $this->filter('payment_profile_id', 'uint');

        if ($isGift && !$isConfirmed)
        {
            $paymentProfile = \XF::em()->find('XF:PaymentProfile', $profileId);
            if (!$paymentProfile || !$paymentProfile->active)
            {
                $error = \XF::phrase('please_choose_valid_payment_profile_to_continue_with_your_purchase');
                throw $this->exception($this->error($error));
            }

            $purchasable = $this->assertPurchasableExists($params->purchasable_type_id);

            $userUpgradeId = $this->filter('user_upgrade_id', 'uint');
            $userUpgrade = \XF::em()->find('XF:UserUpgrade', $userUpgradeId);

            $viewParams = [
                'purchasable' => $purchasable,
                'upgrade' => $userUpgrade,
                'profileId' => $profileId
            ];
            return $this->view(
                'NF\GiftUpgrades:Purchase\Gift',
                'nf_giftupgrades_account_upgrades_gift',
                $viewParams
            );
        }

        return parent::actionIndex($params);
    }
}