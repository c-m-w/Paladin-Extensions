<?php

namespace XR\PM\Admin\Controller;

use XF\Admin\Controller\AbstractController;
use XF\Mvc\ParameterBag;

class ProductManager extends AbstractController
{
	protected function preDispatchController($action, ParameterBag $params)
	{
		$this->assertAdminPermission('xr_pm_products');
	}

	public function actionIndex()
	{
		return $this->view('XR\PM:ProductManager', 'xr_pm_product_manager');
	}
}