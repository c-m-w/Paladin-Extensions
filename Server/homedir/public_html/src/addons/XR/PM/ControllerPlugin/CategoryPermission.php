<?php

namespace XR\PM\ControllerPlugin;

use XF\ControllerPlugin\AbstractPermission;

class CategoryPermission extends AbstractPermission
{
	protected $viewFormatter = 'XR\PM:Permission\Category%s';
	protected $templateFormatter = 'xr_pm_permission_category_%s';
	protected $routePrefix = 'permissions/product-categories';
	protected $contentType = 'xr_pm_category';
	protected $entityIdentifier = 'XR\PM:Category';
	protected $primaryKey = 'category_id';
	protected $privatePermissionGroupId = 'xr_pm';
	protected $privatePermissionId = 'view';
}