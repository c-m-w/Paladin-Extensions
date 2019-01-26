<?php

namespace XR\PM\Repository;

use XF\Repository\AbstractCategoryTree;

class Category extends AbstractCategoryTree
{
	protected function getClassName()
	{
		return 'XR\PM:Category';
	}

	public function mergeCategoryListExtras(array $extras, array $childExtras)
	{
		$output = array_merge([
			'childCount' => 0,
			'product_count' => 0,
			'last_update' => 0,
			'last_product_title' => '',
			'last_product_id' => 0
		], $extras);

		foreach ($childExtras AS $child)
		{
			if (!empty($child['product_count']))
			{
				$output['product_count'] += $child['product_count'];
			}

			if (!empty($child['last_update']) && $child['last_update'] > $output['last_update'])
			{
				$output['last_update'] = $child['last_update'];
				$output['last_product_title'] = $child['last_product_title'];
				$output['last_product_id'] = $child['last_product_id'];
			}

			$output['childCount'] += 1 + (!empty($child['childCount']) ? $child['childCount'] : 0);
		}

		return $output;
	}
}