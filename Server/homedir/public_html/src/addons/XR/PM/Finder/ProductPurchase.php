<?php

namespace XR\PM\Finder;

use XF\Mvc\Entity\Finder;

class ProductPurchase extends Finder
{
	public function userDisplayable()
	{
		$this->where('purchase_state', [
			'inactive',
			'active',
			'expired'
		]);

		$this->where('purchase_type', 'product');
	}
}