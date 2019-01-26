<?php

namespace XR\PM\ControllerPlugin;

use XF\ControllerPlugin\AbstractCategoryTree;

class CategoryTree extends AbstractCategoryTree
{
	protected $viewFormatter = 'XR\PM:Category\%s';
	protected $templateFormatter = 'xr_pm_category_%s';
	protected $routePrefix = 'product-manager/categories';
	protected $entityIdentifier = 'XR\PM:Category';
	protected $primaryKey = 'category_id';
}