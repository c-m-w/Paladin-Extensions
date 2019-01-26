<?php

namespace XR\PM\Searcher;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Manager;
use XF\Searcher\AbstractSearcher;

/**
 * @method \XF\Finder\User getFinder()
 */
class ProductPurchase extends AbstractSearcher
{
	protected $allowedRelations = ['Product', 'User'];

	protected $formats = [
		'username' => 'like',
		'license_name' => 'like',
		'license_url' => 'like',
		'purchase_key' => 'like',
		'old_cart_key' => 'like',
		'parent_purchase_key' => 'like',
		'purchase_date' => 'date',
		'expiry_date' => 'date'
	];

	protected $order = [['purchase_date', 'desc']];

	protected function getEntityType()
	{
		return 'XR\PM:ProductPurchase';
	}

	protected function getDefaultOrderOptions()
	{
		$orders = [
			'purchase_date' => \XF::phrase('xr_pm_purchase_date'),
			'expiry_date' => \XF::phrase('xr_pm_expiry_date'),
			'username' => \XF::phrase('user_name'),
			'total_price' => \XF::phrase('xr_pm_total_price')
		];

		return $orders;
	}

	public function getFormData()
	{
		return [
			'products' => $this->em->getRepository('XR\PM:Product')->findProductsForList(null, false)->fetch(),
			'purchaseStates' => $this->em->getRepository('XR\PM:ProductPurchase')->getPurchaseStatesOptionsData(),
			'purchaseTypes' => $this->em->getRepository('XR\PM:ProductPurchase')->getPurchaseTypes()
		];
	}

	public function getFormDefaults()
	{
		return [
			'purchase_state' => array_keys($this->em->getRepository('XR\PM:ProductPurchase')->getPurchaseStates()),
			'purchase_type' => ['product', 'renewal', 'extras'],
			'Product' => [
				'active' => [0, 1],
			]
		];
	}
}