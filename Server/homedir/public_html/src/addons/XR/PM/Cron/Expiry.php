<?php

namespace XR\PM\Cron;

class Expiry
{
	public static function expire()
	{
		$repo = \XF::repository('XR\PM:ProductPurchase');

		$expired = \XF::finder('XR\PM:ProductPurchase')
			->with('User', true)
			->where('purchase_state', ['active', 'inactive'])
			->with('Product', true)
			->where('expiry_date', '<', \XF::$time)
			->where('expiry_date', '>', 0)
			->order('expiry_date')
			->fetch(1000);

		foreach ($expired AS $purchase)
		{
			$repo->expirePurchaseIfNeeded($purchase, true);
		}
	}
}