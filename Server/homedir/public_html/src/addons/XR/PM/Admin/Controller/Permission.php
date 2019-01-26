<?php

namespace XR\PM\Admin\Controller;

use XF\Admin\Controller\AbstractController;
use XF\Mvc\ParameterBag;

class Permission extends AbstractController
{
	protected function preDispatchController($action, ParameterBag $params)
	{
		$this->assertAdminPermission('xr_pm_products');
	}

	/**
	 * @return \XR\PM\ControllerPlugin\CategoryPermission
	 */
	protected function getCategoryPermissionPlugin()
	{
		/** @var \XR\PM\ControllerPlugin\CategoryPermission $plugin */
		$plugin = $this->plugin('XR\PM:CategoryPermission');
		$plugin->setFormatters('XR\PM\Permission\Category%s', 'xr_pm_permission_category_%s');
		$plugin->setRoutePrefix('permissions/product-manager-categories');

		return $plugin;
	}

	public function actionCategory(ParameterBag $params)
	{
		if ($params->category_id)
		{
			return $this->getCategoryPermissionPlugin()->actionList($params);
		}
		else
		{
			$categoryRepo = $this->repository('XR\PM:Category');
			$categories = $categoryRepo->findCategoryList()->fetch();
			$categoryTree = $categoryRepo->createCategoryTree($categories);

			$customPermissions = $this->repository('XF:PermissionEntry')->getContentWithCustomPermissions('xr_pm_category');

			$viewParams = [
				'categoryTree' => $categoryTree,
				'customPermissions' => $customPermissions
			];
			return $this->view('XR\PM:Permission\CategoryOverview', 'xr_pm_permission_category_overview', $viewParams);
		}
	}

	public function actionCategoryEdit(ParameterBag $params)
	{
		return $this->getCategoryPermissionPlugin()->actionEdit($params);
	}

	public function actionCategorySave(ParameterBag $params)
	{
		return $this->getCategoryPermissionPlugin()->actionSave($params);
	}
}