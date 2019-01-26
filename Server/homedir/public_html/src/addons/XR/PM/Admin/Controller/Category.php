<?php

namespace XR\PM\Admin\Controller;

use XF\Admin\Controller\AbstractController;
use XF\Mvc\ParameterBag;

class Category extends AbstractController
{
	protected function preDispatchController($action, ParameterBag $params)
	{
		$this->assertAdminPermission('xr_pm_products');
	}

	/**
	 * @return \XR\PM\ControllerPlugin\CategoryTree
	 */
	protected function getCategoryTreePlugin()
	{
		return $this->plugin('XR\PM:CategoryTree');
	}

	public function actionIndex()
	{
		return $this->getCategoryTreePlugin()->actionList([
			'permissionContentType' => 'xr_pm_category'
		]);
	}

	protected function categoryAddEdit(\XR\PM\Entity\Category $category)
	{
		$categoryRepo = $this->getCategoryRepo();
		$categoryTree = $categoryRepo->createCategoryTree();

		$viewParams = [
			'category' => $category,
			'categoryTree' => $categoryTree
		];
		return $this->view('XR\PM:Category\Edit', 'xr_pm_category_edit', $viewParams);
	}

	public function actionEdit(ParameterBag $params)
	{
		$category = $this->assertCategoryExists($params->category_id);
		return $this->categoryAddEdit($category);
	}

	public function actionAdd()
	{
		$parentCategoryId = $this->filter('parent_category_id', 'uint');

		$category = $this->em()->create('XR\PM:Category');
		$category->parent_category_id = $parentCategoryId;

		return $this->categoryAddEdit($category);
	}

	protected function categorySaveProcess(\XR\PM\Entity\Category $category)
	{
		$form = $this->formAction();

		$input = $this->filter([
			'title' => 'str',
			'description' => 'str',
			'parent_category_id' => 'uint',
			'display_order' => 'uint'
		]);

		$form->basicEntitySave($category, $input);

		return $form;
	}

	public function actionSave(ParameterBag $params)
	{
		if ($params->category_id)
		{
			$category = $this->assertCategoryExists($params->category_id);
		}
		else
		{
			$category = $this->em()->create('XR\PM:Category');
		}

		$this->categorySaveProcess($category)->run();

		return $this->redirect($this->buildLink('product-manager/categories') . $this->buildLinkHash($category->category_id));
	}

	public function actionDelete(ParameterBag $params)
	{
		return $this->getCategoryTreePlugin()->actionDelete($params);
	}

	public function actionSort()
	{
		return $this->getCategoryTreePlugin()->actionSort();
	}

	/**
	 * @return \XR\PM\ControllerPlugin\CategoryPermission
	 */
	protected function getCategoryPermissionPlugin()
	{
		/** @var \XR\PM\ControllerPlugin\CategoryPermission $plugin */
		$plugin = $this->plugin('XR\PM:CategoryPermission');
		$plugin->setFormatters('XR\PM:Category\Permission%s', 'xr_pm_category_permission_%s');
		$plugin->setRoutePrefix('product-manager/categories/permissions');

		return $plugin;
	}

	public function actionPermissions(ParameterBag $params)
	{
		return $this->getCategoryPermissionPlugin()->actionList($params);
	}

	public function actionPermissionsEdit(ParameterBag $params)
	{
		return $this->getCategoryPermissionPlugin()->actionEdit($params);
	}

	public function actionPermissionsSave(ParameterBag $params)
	{
		return $this->getCategoryPermissionPlugin()->actionSave($params);
	}

	/**
	 * @param string $id
	 * @param array|string|null $with
	 * @param null|string $phraseKey
	 *
	 * @return \XR\PM\Entity\Category
	 */
	protected function assertCategoryExists($id, $with = null, $phraseKey = null)
	{
		return $this->assertRecordExists('XR\PM:Category', $id, $with, $phraseKey);
	}

	/**
	 * @return \XR\PM\Repository\Category
	 */
	protected function getCategoryRepo()
	{
		return $this->repository('XR\PM:Category');
	}
}