<?php

namespace XR\PM\Pub\Controller;

use XF\Mvc\ParameterBag;
use XF\Pub\Controller\AbstractController;

class Category extends AbstractController
{
	protected function preDispatchController($action, ParameterBag $params)
	{
		/** @var \XR\PM\XF\Entity\User $visitor */
		$visitor = \XF::visitor();

		if (!$visitor->canViewProducts($error))
		{
			throw $this->exception($this->noPermission($error));
		}
	}

	public function actionIndex(ParameterBag $params)
	{
		$category = $this->assertViewableCategory($params->category_id);

		/** @var \XR\PM\ControllerPlugin\ProductList $listPlugin */
		$listPlugin = $this->plugin('XR\PM:ProductList');

		$categoryParams = $listPlugin->getCategoryListData($category);

		/** @var \XF\Tree $categoryTree */
		$categoryTree = $categoryParams['categoryTree'];
		$descendants = $categoryTree->getDescendants($category->category_id);

		$sourceCategoryIds = array_keys($descendants);
		$sourceCategoryIds[] = $category->category_id;

		$listParams = $listPlugin->getCoreListData($sourceCategoryIds);

		$this->assertValidPage(
			$listParams['page'],
			$listParams['perPage'],
			$listParams['total'],
			'products/categories',
			$category
		);
		$this->assertCanonicalUrl($this->buildLink(
			'products/categories',
			$category,
			['page' => $listParams['page']]
		));

		$viewParams = [
			'category' => $category
		];
		$viewParams += $categoryParams + $listParams;

		return $this->view('XR\PM:Category\View', 'xr_pm_category_view', $viewParams);
	}

	public function actionFilters()
	{
		/** @var \XR\PM\ControllerPlugin\ProductList $listPlugin */
		$listPlugin = $this->plugin('XR\PM:ProductList');

		return $listPlugin->actionFilters();
	}

	public function actionWatch(ParameterBag $params)
	{
//		$category = $this->assertViewableCategory($params->category_id);
//		if (!$category->canWatch($error))
//		{
//			return $this->noPermission($error);
//		}
//
//		$visitor = \XF::visitor();
//
//		if ($this->isPost())
//		{
//			if ($this->filter('stop', 'bool'))
//			{
//				$action = 'delete';
//				$config = [];
//			}
//			else
//			{
//				$action = 'watch';
//				$config = $this->filter([
//					'notify_on' => 'str',
//					'send_alert' => 'bool',
//					'send_email' => 'bool',
//					'include_children' => 'bool'
//				]);
//			}
//
//			/** @var \XR\PM\Repository\CategoryWatch $watchRepo */
//			$watchRepo = $this->repository('XR\PM:CategoryWatch');
//			$watchRepo->setWatchState($category, $visitor, $action, $config);
//
//			$redirect = $this->redirect($this->buildLink('resources/categories', $category));
//			$redirect->setJsonParam('switchKey', $action == 'delete' ? 'watch' : 'unwatch');
//			return $redirect;
//		}
//		else
//		{
//			$viewParams = [
//				'category' => $category,
//				'isWatched' => !empty($category->Watch[$visitor->user_id])
//			];
//			return $this->view('XR\PM:Category\Watch', 'xfrm_category_watch', $viewParams);
//		}
	}

	/**
	 * @param integer $categoryId
	 * @param array $extraWith
	 *
	 * @return \XR\PM\Entity\Category
	 *
	 * @throws \XF\Mvc\Reply\Exception
	 */
	protected function assertViewableCategory($categoryId, array $extraWith = [])
	{
		$visitor = \XF::visitor();

		$extraWith[] = 'Permissions|' . $visitor->permission_combination_id;

		/** @var \XR\PM\Entity\Category $category */
		$category = $this->em()->find('XR\PM:Category', $categoryId, $extraWith);
		if (!$category)
		{
			throw $this->exception($this->notFound(\XF::phrase('requested_category_not_found')));
		}

		if (!$category->canView($error))
		{
			throw $this->exception($this->noPermission($error));
		}

		return $category;
	}

	public static function getActivityDetails(array $activities)
	{
		return self::getActivityDetailsForContent(
			$activities, \XF::phrase('viewing_category'), 'category_id',
			function(array $ids)
			{
				$categories = \XF::em()->findByIds(
					'XR\PM:Category',
					$ids,
					['Permissions|' . \XF::visitor()->permission_combination_id]
				);

				$router = \XF::app()->router('public');
				$data = [];

				foreach ($categories->filterViewable() AS $id => $category)
				{
					$data[$id] = [
						'title' => $category->title,
						'url' => $router->buildLink('products/categories', $category)
					];
				}

				return $data;
			}
		);
	}
}