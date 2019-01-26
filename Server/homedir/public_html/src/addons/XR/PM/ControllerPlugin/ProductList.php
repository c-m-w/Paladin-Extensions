<?php

namespace XR\PM\ControllerPlugin;

use XF\ControllerPlugin\AbstractPlugin;

class ProductList extends AbstractPlugin
{
	public function getCategoryListData(\XR\PM\Entity\Category $category = null)
	{
		$categoryRepo = $this->getCategoryRepo();
		$categories = $categoryRepo->getViewableCategories();
		$categoryTree = $categoryRepo->createCategoryTree($categories);
		$categoryExtras = $categoryRepo->getCategoryListExtras($categoryTree);

		return [
			'categories' => $categories,
			'categoryTree' => $categoryTree,
			'categoryExtras' => $categoryExtras
		];
	}

	public function getCoreListData(array $sourceCategoryIds, \XR\PM\Entity\Category $category = null)
	{
		$productRepo = $this->getProductRepo();

		$productFinder = $productRepo->findProductsForList($sourceCategoryIds);

		$filters = $this->getProductFilterInput();
		$this->applyProductFilters($productFinder, $filters);

		$totalProducts = $productFinder->total();

		// TODO: Per page setting
		$page = $this->filterPage();
		$perPage = 20;

		$productFinder->limitByPage($page, $perPage);
		$products = $productFinder->fetch()->filterViewable();

		if (!empty($filters['creator_id']))
		{
			$creatorFilter = $this->em()->find('XF:User', $filters['creator_id']);
		}
		else
		{
			$creatorFilter = null;
		}

		return [
			'products' => $products,
			'filters' => $filters,
			'creatorFilter' => $creatorFilter,

			'total' => $totalProducts,
			'page' => $page,
			'perPage' => $perPage
		];
	}

	public function applyProductFilters(\XR\PM\Finder\Product $productFinder, array $filters)
	{
		if (!empty($filters['creator_id']))
		{
			$productFinder->where('user_id', intval($filters['creator_id']));
		}

		$sorts = $this->getAvailableProductSorts();

		if (!empty($filters['order']) && isset($sorts[$filters['order']]))
		{
			$productFinder->order($sorts[$filters['order']], $filters['direction']);
		}
		// else the default order has already been applied
	}

	public function getProductFilterInput()
	{
		$filters = [];

		$input = $this->filter([
			'creator' => 'str',
			'creator_id' => 'uint',
			'order' => 'str',
			'direction' => 'str'
		]);

		if ($input['creator_id'])
		{
			$filters['creator_id'] = $input['creator_id'];
		}
		else if ($input['creator'])
		{
			$user = $this->em()->findOne('XF:User', ['username' => $input['creator']]);
			if ($user)
			{
				$filters['creator_id'] = $user->user_id;
			}
		}

		$sorts = $this->getAvailableProductSorts();

		if ($input['order'] && isset($sorts[$input['order']]))
		{
			if (!in_array($input['direction'], ['asc', 'desc']))
			{
				$input['direction'] = 'desc';
			}

			$defaultOrder = 'last_update';
			$defaultDir = 'desc';

			if ($input['order'] != $defaultOrder || $input['direction'] != $defaultDir)
			{
				$filters['order'] = $input['order'];
				$filters['direction'] = $input['direction'];
			}
		}

		return $filters;
	}

	public function getAvailableProductSorts()
	{
		// maps [name of sort] => field in/relative to ProductItem entity
		return [
			'last_update' => 'last_update',
			'product_date' => 'product_date',
			'title' => 'title'
		];
	}

	public function actionFilters(\XFRM\Entity\Category $category = null)
	{
		$filters = $this->getProductFilterInput();

		if ($this->filter('apply', 'bool'))
		{
			return $this->redirect($this->buildLink(
				$category ? 'products/categories' : 'products',
				$category,
				$filters
			));
		}

		if (!empty($filters['creator_id']))
		{
			$creatorFilter = $this->em()->find('XF:User', $filters['creator_id']);
		}
		else
		{
			$creatorFilter = null;
		}

		$applicableCategories = $this->getCategoryRepo()->getViewableCategories($category);
		$applicableCategoryIds = $applicableCategories->keys();
		if ($category)
		{
			$applicableCategoryIds[] = $category->category_id;
		}

		$defaultOrder = 'last_update';
		$defaultDir = $defaultOrder == 'desc';

		if (empty($filters['order']))
		{
			$filters['order'] = $defaultOrder;
		}
		if (empty($filters['direction']))
		{
			$filters['direction'] = $defaultDir;
		}

		$viewParams = [
			'category' => $category,
			'filters' => $filters,
			'creatorFilter' => $creatorFilter
		];
		return $this->view('XR\PM:Filters', 'xr_pm_filters', $viewParams);
	}

	/**
	 * @return \XR\PM\Repository\Product
	 */
	protected function getProductRepo()
	{
		return $this->repository('XR\PM:Product');
	}

	/**
	 * @return \XR\PM\Repository\Category
	 */
	protected function getCategoryRepo()
	{
		return $this->repository('XR\PM:Category');
	}
}