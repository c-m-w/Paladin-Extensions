<?php

namespace XR\PM\Repository;

use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Repository;

class Extra extends Repository
{
	/**
	 * @return Finder
	 */
	public function findExtrasForList()
	{
		$finder = $this->finder('XR\PM:Extra')
			->setDefaultOrder('extra_id');

		return $finder;
	}

	public function updateExtraAssociations(\XR\PM\Entity\Extra $extra, array $productIds)
	{
		$emptyKey = array_search(0, $productIds);
		if ($emptyKey !== false)
		{
			unset($productIds[$emptyKey]);
		}
		$productIds = array_unique($productIds);

		$existingAssociations = $extra->ProductExtras;
		if (!count($existingAssociations) && !$productIds)
		{
			return;
		}

		$db = $this->db();
		$db->beginTransaction();

		$db->delete('xf_xr_pm_product_extra_map', 'extra_id = ?', $extra->extra_id);

		$map = [];

		foreach ($productIds AS $id)
		{
			$map[] = [
				'product_id' => $id,
				'extra_id' => $extra->extra_id
			];
		}
		if ($map)
		{
			$db->insertBulk('xf_xr_pm_product_extra_map', $map);
		}

		$rebuildIds = $productIds;

		foreach ($existingAssociations AS $association)
		{
			$rebuildIds[] = $association->product_id;
		}

		$rebuildIds = array_unique($rebuildIds);
		$this->rebuildProductAssociationCache($rebuildIds);

		$db->commit();
	}

	public function removeExtraAssociations(\XR\PM\Entity\Extra $extra)
	{
		$rebuildIds = $this->db()->fetchAllColumn("
			SELECT product_id
			FROM xf_xr_pm_product_extra_map
			WHERE extra_id = ?
		", $extra->extra_id);

		if (!$rebuildIds)
		{
			return;
		}

		$db = $this->db();
		$db->beginTransaction();

		$db->delete('xf_xr_pm_product_extra_map', 'extra_id = ?', $extra->extra_id);

		$this->rebuildProductAssociationCache($rebuildIds);

		$db->commit();
	}

	public function updateProductAssociations($productId, array $extraIds)
	{
		$db = $this->db();
		$db->beginTransaction();

		$db->delete('xf_xr_pm_product_extra_map', 'product_id = ?', $productId);

		$map = [];

		foreach ($extraIds AS $extraId)
		{
			$map[] = [
				'product_id' => $productId,
				'extra_id' => $extraId
			];
		}

		if ($map)
		{
			$db->insertBulk('xf_xr_pm_product_extra_map', $map);
		}

		$this->rebuildProductAssociationCache($productId);

		$db->commit();
	}

	public function rebuildProductAssociationCache($productIds)
	{
		if (!is_array($productIds))
		{
			$productIds = [$productIds];
		}
		if (!$productIds)
		{
			return;
		}

		$newCache = [];

		$extraAssociations = $this->finder('XR\PM:ProductExtraMap')
			->with('Extra')
			->where('product_id', $productIds)
			->order('product_id');
		foreach ($extraAssociations->fetch() AS $extraMap)
		{
			$key = $extraMap->product_id;
			$newCache[$key][$extraMap->extra_id] = $extraMap->extra_id;
		}

		foreach ($productIds AS $productId)
		{
			if (!isset($newCache[$productId]))
			{
				$newCache[$productId] = [];
			}
		}

		$this->updateAssociationCache($newCache);
	}

	protected function updateAssociationCache(array $cache)
	{
		$productIds = array_keys($cache);
		$products = $this->em->findByIds('XR\PM:Product', $productIds);

		foreach ($products AS $product)
		{
			/** @var \XR\PM\Entity\Product $product */
			$product->optional_extras = $cache[$product->product_id];
			$product->saveIfChanged();
		}
	}
}