<?php

namespace XR\PM\Service\Purchase;

use XF\Service\AbstractService;

class Updater extends AbstractService
{
	/**
	 * @var \XR\PM\Entity\ProductPurchase
	 */
	protected $purchase;

	public function __construct(\XF\App $app, \XR\PM\Entity\ProductPurchase $purchase)
	{
		parent::__construct($app);

		$this->purchase = $purchase;
	}

	/**
	 * @return \XR\PM\Entity\ProductPurchase
	 */
	public function getPurchase()
	{
		return $this->purchase;
	}

	public function renewPurchase()
	{
		$purchase = $this->purchase;

		$originalPurchase = $this->em()->findOne('XR\PM:ProductPurchase', [
			'purchase_key' => $purchase->parent_purchase_key
		]);
		$product = $originalPurchase->Product;

		if ($purchase->purchase_date > $originalPurchase->expiry_date)
		{
			$originalPurchase->expiry_date = strtotime(
				'+' . $product->duration . ' ' . $product->duration_unit, $purchase->purchase_date
			);
		}
		else
		{
			$originalPurchase->expiry_date = strtotime(
				'+' . $product->duration . ' ' . $product->duration_unit, $originalPurchase->expiry_date
			);
		}

		if ($product->requires_activation)
		{
			if ($originalPurchase->hasLicenseDetails())
			{
				$originalPurchase->purchase_state = 'active';
			}
			else
			{
				$originalPurchase->purchase_state = 'inactive';
			}
		}
		else
		{
			$originalPurchase->purchase_state = 'active';
		}

		$originalPurchase->save();
		$purchase->fastUpdate('purchase_state', 'complete');

		$this->updateCouponUsage($purchase->coupons);
	}

	public function addExtras()
	{
		$purchase = $this->purchase;

		$originalPurchase = $this->em()->findOne('XR\PM:ProductPurchase', [
			'purchase_key' => $purchase->parent_purchase_key
		]);

		$extras = $originalPurchase->extras += $purchase->extras;
		$originalPurchase->extras = $extras;

		$originalPurchase->extras_price += $purchase->extras_price;
		$originalPurchase->discount_total += $purchase->discount_total;

		$originalPurchase->total_price = (
			$originalPurchase->product_price + $originalPurchase->extras_price - $originalPurchase->discount_total
		);

		$originalPurchase->save();
		$purchase->fastUpdate('purchase_state', 'complete');

		$this->updateCouponUsage($purchase->coupons);
	}

	public function completePurchase()
	{
		$purchase = $this->purchase;
		$product = $purchase->Product;

		if ($product->requires_activation && !$purchase->hasLicenseDetails())
		{
			$purchase->purchase_state = 'inactive';
		}
		else
		{
			$purchase->purchase_state = 'active';
		}

		if ($product->duration)
		{
			$purchase->expiry_date = strtotime(
				'+' . $product->duration . ' ' . $product->duration_unit, $purchase->purchase_date
			);
		}
		else
		{
			$purchase->expiry_date = 0;
		}

		$purchase->save();

		$this->updateCouponUsage($purchase->coupons);
	}

	public function reinstatePurchase()
	{
		$purchase = $this->purchase;

		if ($purchase->purchase_state != 'revoked')
		{
			return;
		}

		if ($purchase->purchase_type == 'extras')
		{
			$this->addExtras();
			return;
		}
		else if ($purchase->purchase_type == 'renewal')
		{
			$this->renewPurchase();
			return;
		}
		else
		{
			$this->completePurchase();
			return;
		}
	}

	public function reversePurchase()
	{
		$purchase = $this->purchase;

		if ($purchase->purchase_type == 'extras')
		{
			$originalPurchase = $this->em()->findOne('XR\PM:ProductPurchase', [
				'purchase_key' => $purchase->parent_purchase_key
			]);

			$existingExtras = $originalPurchase->extras;
			foreach (array_keys($purchase->extras) AS $extraId)
			{
				unset($existingExtras[$extraId]);
			}
			$originalPurchase->extras = $existingExtras;

			$originalPurchase->extras_price -= $purchase->extras_price;
			$originalPurchase->discount_total -= $purchase->discount_total;

			$originalPurchase->total_price = (
				$originalPurchase->product_price + $originalPurchase->extras_price - $originalPurchase->discount_total
			);

			$originalPurchase->save();
		}
		else if ($purchase->purchase_type == 'renewal')
		{
			$originalPurchase = $this->em()->findOne('XR\PM:ProductPurchase', [
				'purchase_key' => $purchase->parent_purchase_key
			]);
			$product = $originalPurchase->Product;

			$originalPurchase->expiry_date = strtotime(
				'-' . $product->duration . ' ' . $product->duration_unit, $originalPurchase->expiry_date
			);

			$originalPurchase->purchase_state = 'expired';

			$originalPurchase->save();
		}

		$purchase->purchase_state = 'revoked';

		$purchase->save();
	}

	protected function updateCouponUsage(array $couponIds)
	{
		/** @var \XR\PM\Entity\Coupon[] $coupons */
		$coupons = $this->em()->findByIds('XR\PM:Coupon', $couponIds);
		foreach ($coupons AS $coupon)
		{
			if ($coupon->coupon_set_limit)
			{
				$coupon->coupon_limit = $coupon->coupon_limit - 1;
				$coupon->save();
			}
		}
	}
}