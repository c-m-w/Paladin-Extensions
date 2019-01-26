<?php

namespace XR\PM\Repository;

use XF\Mvc\Entity\ArrayCollection;
use XF\Mvc\Entity\Repository;

class ProductPurchase extends Repository
{
	/**
	 * @param \XF\Entity\User $user
	 * @param bool $displayable
	 *
	 * @return \XR\PM\Finder\ProductPurchase
	 */
	public function findPurchasesForUser(\XF\Entity\User $user, $displayable = true)
	{
		$finder = $this->finder('XR\PM:ProductPurchase')
			->with('Product', true)
			->with('Product.Category')
			->with('Product.Version')
			->with('User')
			->where('user_id', $user->user_id)
			->setDefaultOrder('purchase_date', 'DESC');

		if ($displayable)
		{
			$finder->userDisplayable();
		}

		return $finder;
	}

	public function groupPurchasesByState(ArrayCollection $purchases)
	{
		$grouped = $purchases->groupBy('purchase_state');

		$nonExpiredStates = ['active', 'inactive'];
		foreach ($nonExpiredStates AS $state)
		{
			if (!isset($grouped[$state]))
			{
				continue;
			}
			/** @var \XR\PM\Entity\ProductPurchase $purchase */
			foreach ($grouped[$state] AS $purchaseId => $purchase)
			{
				if ($this->expirePurchaseIfNeeded($purchase))
				{
					unset($grouped[$state][$purchaseId]);
					$grouped['expired'][$purchaseId] = $purchase;
				}
			}
		}

		return $grouped;
	}

	public function expirePurchaseIfNeeded(\XR\PM\Entity\ProductPurchase $purchase, $notify = false)
	{
		if ($purchase->purchase_state != 'active' && $purchase->purchase_state != 'inactive')
		{
			return false;
		}

		$expired = false;

		if ($purchase->isExpired())
		{
			$purchase->purchase_state = 'expired';
			$purchase->saveIfChanged($expired);
		}

		$user = $purchase->User;
		if ($expired && $notify && !$user->is_banned && $user->user_state == 'valid')
		{
			$alertRepo = $this->repository('XF:UserAlert');
			$alertRepo->alert(
				$user,
				0, '',
				'xr_pm_product_purchase',
				$purchase->purchase_id,
				'expired'
			);

			$params = [
				'receiver' => $user,
				'purchase' => $purchase,
				'product' => $purchase->Product
			];

			$this->app()->mailer()->newMail()
				->setToUser($user)
				->setTemplate('xr_pm_purchase_expired', $params)
				->queue();
		}

		return $expired;
	}

	public function getPurchaseStates()
	{
		return [
			'active' => [
				'label' => \XF::phrase('xr_pm_purchase_state.active_label'),
				'explain' => \XF::phrase('xr_pm_purchase_state.active_explain')
			],
			'inactive' => [
				'label' => \XF::phrase('xr_pm_purchase_state.inactive_label'),
				'explain' => \XF::phrase('xr_pm_purchase_state.inactive_explain')
			],
			'pending' => [
				'label' => \XF::phrase('xr_pm_purchase_state.pending_label'),
				'explain' => \XF::phrase('xr_pm_purchase_state.pending_explain')
			],
			'expired' => [
				'label' => \XF::phrase('xr_pm_purchase_state.expired_label'),
				'explain' => \XF::phrase('xr_pm_purchase_state.expired_explain')
			],
			'revoked' => [
				'label' => \XF::phrase('xr_pm_purchase_state.revoked_label'),
				'explain' => \XF::phrase('xr_pm_purchase_state.revoked_explain')
			],
			'complete' => [
				'label' => \XF::phrase('xr_pm_purchase_state.complete_label'),
				'explain' => \XF::phrase('xr_pm_purchase_state.complete_explain')
			]
		];
	}

	public function getPurchaseStatesOptionsData()
	{
		$states = $this->getPurchaseStates();

		$output = [];

		foreach ($states AS $key => $phrases)
		{
			$output[$key] = $phrases['label'];
		}

		return $output;
	}

	public function getPurchaseTypes()
	{
		return [
			'product' => \XF::phrase('xr_pm_product'),
			'extras' => \XF::phrase('xr_pm_extras'),
			'renewal' => \XF::phrase('xr_pm_renewal')
		];
	}

	public function getExtrasForPurchaseCache(array $extraIds)
	{
		$extras = $this->em->findByIds('XR\PM:Extra', $extraIds);

		$output = [];

		foreach ($extras AS $extraId => $extra)
		{
			$output[$extraId] = [
				'extra_id' => $extraId,
				'extra_price' => $extra['extra_price']
			];
		}

		return $output;
	}
}