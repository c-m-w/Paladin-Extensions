<?php

namespace XR\PM\Admin\Controller;

use XF\Admin\Controller\AbstractField;
use XF\Mvc\ParameterBag;

class ProductField extends AbstractField
{
	protected function preDispatchController($action, ParameterBag $params)
	{
		$this->assertAdminPermission('xr_pm_products');
	}

	protected function getClassIdentifier()
	{
		return 'XR\PM:ProductField';
	}

	protected function getLinkPrefix()
	{
		return 'product-manager/products/fields';
	}

	protected function getTemplatePrefix()
	{
		return 'xr_pm_product_field';
	}
}