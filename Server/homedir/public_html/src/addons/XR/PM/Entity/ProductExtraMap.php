<?php

namespace XR\PM\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

/**
 * COLUMNS
 * @property int product_id
 * @property int extra_id
 *
 * RELATIONS
 * @property \XR\PM\Entity\Extra Extra
 * @property \XR\PM\Entity\Product Product
 */
class ProductExtraMap extends Entity
{
	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_xr_pm_product_extra_map';
		$structure->shortName = 'XR\PM:ProductExtraMap';
		$structure->primaryKey = ['product_id', 'extra_id'];
		$structure->columns = [
			'product_id' => ['type' => self::UINT, 'required' => true],
			'extra_id' => ['type' => self::UINT, 'required' => true]
		];
		$structure->getters = [];
		$structure->relations = [
			'Extra' => [
				'entity' => 'XR\PM:Extra',
				'type' => self::TO_ONE,
				'conditions' => 'extra_id',
				'primary' => true
			],
			'Product' => [
				'entity' => 'XR\PM:Product',
				'type' => self::TO_ONE,
				'conditions' => 'product_id',
				'primary' => true
			]
		];

		return $structure;
	}
}