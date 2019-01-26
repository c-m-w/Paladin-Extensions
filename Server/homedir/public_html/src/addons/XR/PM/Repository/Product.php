<?php

namespace XR\PM\Repository;

use XF\Mvc\Entity\ArrayCollection;
use XF\Mvc\Entity\Repository;

class Product extends Repository
{
	public function findProductsForList(array $viewableCategoryIds = null, $visibilityLimit = true)
	{
		/** @var \XR\PM\Finder\Product $productFinder */
		$productFinder = $this->finder('XR\PM:Product');

		if ($viewableCategoryIds)
		{
			$productFinder->where('category_id', $viewableCategoryIds);
		}

		// TODO: For full view
		// TODO: More sort options
		$productFinder
			->with('Category')
			->setDefaultOrder('product_date', 'desc');

		if ($visibilityLimit)
		{
			$productFinder->where('active', true);
		}

		return $productFinder;
	}

	public function findProductsForAdminList()
	{
		return $this->findProductsForList(null, false);
	}

	/**
	 * @param ArrayCollection|\XR\PM\Entity\Product[] $products
	 */
	public function addExtrasToProducts(ArrayCollection $products)
	{
		$ids = [];
		foreach ($products AS $productId => $product)
		{
			foreach ($product->optional_extras AS $extraId)
			{
				$ids[] = $extraId;
			}
		}

		if ($ids)
		{
			$extras = $this->em->findByIds('XR\PM:Extra', $ids);

			foreach ($products AS $productId => $product)
			{
				$set = [];

				foreach ($product->optional_extras AS $id)
				{
					if (isset($extras[$id]))
					{
						$set[$id] = $extras[$id];
					}
				}

				$product->setExtras($this->em->getBasicCollection($set));
			}
		}

		return $products;
	}

	public function rebuildProductCurrentVersion($productId)
	{
		$version = $this->finder('XR\PM:Version')
			->where('product_id', $productId)
			->order('release_date', 'DESC')
			->where('is_unsupported', 0)
			->fetchOne();

		if ($version)
		{
			$this->db()->update('xf_xr_pm_product', [
				'current_version_id' => $version->product_version_id
			], 'product_id = ?', $productId);
		}
	}
}