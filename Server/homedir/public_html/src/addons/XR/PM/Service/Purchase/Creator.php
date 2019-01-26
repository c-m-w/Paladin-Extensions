<?php

namespace XR\PM\Service\Purchase;

use XF\Service\AbstractService;
use XF\Service\ValidateAndSavableTrait;
use XR\PM\Entity\Coupon;

class Creator extends AbstractService
{
	use ValidateAndSavableTrait;

	/**
	 * @var \XR\PM\Entity\Product
	 */
	protected $product;

	/**
	 * @var \XR\PM\Entity\ProductPurchase
	 */
	protected $purchase;

	public function __construct(\XF\App $app, \XR\PM\Entity\Product $product)
	{
		parent::__construct($app);

		$visitor = \XF::visitor();

		$this->product = $product;
		$this->purchase = $this->em()->create('XR\PM:ProductPurchase');
		$this->purchase->user_id = $visitor->user_id;
		$this->purchase->username = $visitor->username;
		$this->purchase->product_id = $product->product_id;
	}

	/**
	 * @return \XR\PM\Entity\Product
	 */
	public function getProduct()
	{
		return $this->product;
	}

	/**
	 * @return \XR\PM\Entity\ProductPurchase
	 */
	public function getPurchase()
	{
		return $this->purchase;
	}

	public function setExtras(array $extras)
	{
		// filter chosen extras down to those allowed by the product
		$extras = array_intersect($this->product->optional_extras, $extras);
		$extras = $this->repository('XR\PM:ProductPurchase')->getExtrasForPurchaseCache($extras);

		$this->purchase->extras = $extras;
		$this->purchase->extras_price = array_sum(array_map(function($extra)
		{
			return $extra['extra_price'];
		}, $extras));
	}

	public function applyCoupon(Coupon $coupon, &$error = null)
	{
		$discount = $this->purchase->discount_total;
		$coupons = $this->purchase->coupons;

		$product = $this->product;
		$extras = $this->purchase->extras;

		if (!$coupon->active)
		{
			$error = \XF::phrase('xr_pm_not_valid_coupon_code');
			return false;
		}

		if (in_array($coupon->coupon_id, $coupons))
		{
			$error = \XF::phrase('xr_pm_you_cannot_use_same_coupon_more_than_once');
			return false;
		}

		if (!$coupon->canUse($error))
		{
			return false;
		}

		switch ($coupon->coupon_type)
		{
			case 'extra':
			{
				if (!$extras)
				{
					$error = \XF::phrase('xr_pm_coupon_x_applies_to_extras_and_none_selected_for', ['coupon_code' => $coupon->coupon_code]);
					return false;
				}

				$valid = false;

				foreach ($extras AS $extraId => $extra)
				{
					if (in_array($extraId, $coupon->coupon_extra_ids))
					{
						$valid = true;
						$discount += $coupon->getDiscountAmount($extra['extra_price']);
					}
				}

				if (!$valid)
				{
					$error = \XF::phrase('xr_pm_coupon_x_does_not_apply_to_any_of_selected_extras', ['coupon_code' => $coupon->coupon_code]);
					return false;
				}

				break;
			}

			case 'product':
			{
				if (!in_array($product->product_id, $coupon->coupon_product_ids))
				{
					$error = \XF::phrase('xr_pm_coupon_x_does_not_apply_to_any_of_selected_products', ['coupon_code' => $coupon->coupon_code]);
					return false;
				}

				$discount += $coupon->getDiscountAmount($product->price);

				break;
			}

			case 'renewal':
			{
				if ($coupon->coupon_product_ids && !in_array($product->product_id, $coupon->coupon_product_ids))
				{
					$error = \XF::phrase('xr_pm_coupon_x_does_not_apply_to_any_of_selected_products', ['coupon_code' => $coupon->coupon_code]);
					return false;
				}

				$discount += $coupon->getDiscountAmount($this->purchase->product_price);

				break;
			}

			case 'purchase':
			{
				$discount += $coupon->getDiscountAmount($this->calculateTotalPrice());

				break;
			}
		}

		$this->purchase->discount_total = $discount;
		$coupons[] = $coupon->coupon_id;
		$this->purchase->coupons = $coupons;

		return true;
	}

	public function setProductPrice($price, $currency)
	{
		$this->purchase->product_price = $price;
		$this->purchase->purchase_currency = $currency;
	}

	public function setPurchasableType($type, $parentPurchaseKey = null)
	{
		$this->purchase->purchase_type = $type;

		if ($parentPurchaseKey)
		{
			$this->purchase->parent_purchase_key = $parentPurchaseKey;
		}
	}

	public function calculateTotalPrice()
	{
		$purchase = $this->purchase;
		return ($purchase->product_price + $purchase->extras_price - $purchase->discount_total);
	}

	protected function finalSetup()
	{
		$this->purchase->total_price = $this->calculateTotalPrice();
	}

	protected function _validate()
	{
		$this->finalSetup();

		$this->purchase->preSave();
		return $this->purchase->getErrors();
	}

	protected function _save()
	{
		$purchase = $this->purchase;

		$purchase->save();

		return $purchase;
	}
}