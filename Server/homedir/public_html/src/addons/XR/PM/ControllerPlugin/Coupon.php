<?php

namespace XR\PM\ControllerPlugin;

use XF\ControllerPlugin\AbstractPlugin;
use XR\PM\Entity\Product;

class Coupon extends AbstractPlugin
{
	/**
	 * @param Product $product Product the coupons are being applied to
	 * @param array $validCouponTypes These should be presented in the order that the coupons should be applied
	 *
	 * @return array
	 *
	 * @throws \XF\Mvc\Reply\Exception
	 */
	public function getAppliedCouponsData(Product $product, array $validCouponTypes, $price = null, $currency = null, $extras = [])
	{
		$couponIds = $this->filter('coupon_ids', 'json-array');
		if (!$limit = $product->canUseCoupons(false, $error))
		{
			if (count($couponIds) > $limit)
			{
				throw $this->exception($this->noPermission('~~You are only allowed to use ' . $limit . ' coupons per purchase.'));
			}
			else
			{
				throw $this->exception($this->noPermission($error));
			}
		}

		$code = $this->filter('coupon_code', 'str');
		if ($code)
		{
			/** @var \XR\PM\Entity\Coupon $newCoupon */
			$newCoupon = $this->finder('XR\PM:Coupon')
				->where('coupon_code', $code)
				->fetchOne();

			if (!$newCoupon)
			{
				throw $this->exception($this->error(\XF::phrase('xr_pm_not_valid_coupon_code_x', ['code' => $code])));
			}

			$couponIds[] = $newCoupon->coupon_id;
		}

		/** @var \XR\PM\Service\Purchase\Creator $creator */
		$creator = $this->service('XR\PM:Purchase\Creator', $product);

		$price = $price ?: $product->price;
		$currency = $currency ?: $product->currency;
		$creator->setProductPrice($price, $currency);

		$extras = $extras ?: $this->filter('extras', 'array-uint');
		if ($extras)
		{
			$creator->setExtras($extras);
		}

		$coupons = $this->finder('XR\PM:Coupon')
			->where('coupon_id', $couponIds)
			->where('active', 1)
			->fetch();

		$groupedCoupons = $coupons->groupBy('coupon_type');
		$types = array_keys($groupedCoupons);

		if (array_diff($types, $validCouponTypes))
		{
			throw $this->exception($this->error(\XF::phrase('xr_pm_coupon_not_valid_type_for_this_purchase')));
		}

		$newCoupons = [];
		foreach ($validCouponTypes AS $type)
		{
			if (!isset($groupedCoupons[$type]))
			{
				continue;
			}

			foreach ($groupedCoupons[$type] AS $coupon)
			{
				if (!$creator->applyCoupon($coupon, $error))
				{
					throw $this->exception($this->error($error));
				}

				$newCoupons[$coupon->coupon_id] = $coupon;
			}
		}

		$purchase = $creator->getPurchase();
		$discount = $purchase->discount_total;

		return [
			'newCoupons' => $newCoupons,
			'discount' => $discount
		];
	}
}