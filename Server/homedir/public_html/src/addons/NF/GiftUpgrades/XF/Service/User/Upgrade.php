<?php

namespace NF\GiftUpgrades\XF\Service\User;

/**
 * Extends \XF\Service\User\Upgrade
 */
class Upgrade extends XFCP_Upgrade
{
    public function upgrade()
    {
        $purchaseRequest = \XF::em()->findOne('XF:PurchaseRequest', ['request_key' => $this->purchaseRequestKey]);

        if ($purchaseRequest && array_key_exists('is_gift', $purchaseRequest->extra_data)
            && $purchaseRequest->extra_data['is_gift']
        )
        {
            $this->user = \XF::em()->findOne('XF:User', ['username' => $purchaseRequest->extra_data['giftTo']]);
            $this->activeUpgrade->user_id = $this->user->user_id;
        }
        else if (is_null($purchaseRequest) || ($purchaseRequest && !array_key_exists('is_gift', $purchaseRequest->extra_data)))
        {
            return parent::upgrade();
        }

        $existing = \XF::em()->findOne('XF:UserUpgradeActive', [
            'user_id' => $this->user->user_id,
            'user_upgrade_id' => $this->userUpgrade->user_upgrade_id
        ]);

        $this->activeUpgrade->pay_user_id = $purchaseRequest->extra_data['payUser']['user_id'];
        $this->activeUpgrade->is_gift = true;

        if ($existing)
        {
            if (!$this->userUpgrade->length_unit)
            {
                $endDate = 0;
            }
            else
            {
                $endDate = strtotime('+' . $this->userUpgrade->length_amount . ' ' . $this->userUpgrade->length_unit, $existing->end_date);
            }

            $existing->fastUpdate([
                'end_date' => $endDate,
                'pay_user_id' => $purchaseRequest->extra_data['payUser']['user_id'],
                'is_gift' => true,
            ]);

            \XF::db()->query("
                INSERT INTO xf_nixfifty_gift_upgrade_statistics
                  (gift_upgrade_id, stat_date)
                VALUES
                  (?, ?)
            ", [$this->userUpgrade->user_upgrade_id, \XF::$time]);

            /** @var \XF\Repository\UserAlert $alertRepo */
            $alertRepo = $this->app->repository('XF:UserAlert');

            if ($purchaseRequest->extra_data['is_anonymous'])
            {
                $alertRepo->alert(
                    $this->user,
                    $this->user->user_id,
                    $this->user->username,
                    'user', $this->user->user_id, 'upgrade_gifted_anon'
                );
            }
            else
            {
                $alertRepo->alert(
                    $this->user,
                    $purchaseRequest->extra_data['payUser']['user_id'],
                    $purchaseRequest->extra_data['payUser']['username'],
                    'user', $this->user->user_id, 'upgrade_gifted'
                );
            }

            return $existing;
        }
        else
        {
            return parent::upgrade();
        }
    }
}