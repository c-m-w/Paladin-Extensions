<?php

namespace XR\PM\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

/**
 * COLUMNS
 * @property int|null download_id
 * @property string purchase_key
 * @property int version_id
 * @property int user_id
 * @property int product_id
 * @property int last_download_date
 *
 * RELATIONS
 * @property \XR\PM\Entity\Product Product
 * @property \XR\PM\Entity\ProductPurchase Purchase
 * @property \XR\PM\Entity\Version Version
 * @property \XF\Entity\User User
 */
class Download extends Entity
{
	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_xr_pm_download';
		$structure->shortName = 'XR\PM:Download';
		$structure->primaryKey = 'download_id';
		$structure->columns = [
			'download_id' => ['type' => self::UINT, 'autoIncrement' => true, 'nullable' => true],
			'purchase_key' => ['type' => self::STR, 'required' => true],
			'version_id' => ['type' => self::UINT, 'required' => true],
			'user_id' => ['type' => self::UINT, 'required' => true],
			'product_id' => ['type' => self::UINT, 'required' => true],
			'last_download_date' => ['type' => self::UINT, 'default' => \XF::$time]
		];
		$structure->getters = [];
		$structure->relations = [
			'Product' => [
				'entity' => 'XR\PM:Product',
				'type' => self::TO_ONE,
				'conditions' => 'product_id',
				'primary' => true
			],
			'Purchase' => [
				'entity' => 'XR\PM:ProductPurchase',
				'type' => self::TO_ONE,
				'conditions' => 'purchase_key'
			],
			'Version' => [
				'entity' => 'XR\PM:Version',
				'type' => self::TO_ONE,
				'conditions' => [
					['product_version_id', '=', '$version_id']
				],
				'primary' => true
			],
			'User' => [
				'entity' => 'XF:User',
				'type' => self::TO_ONE,
				'conditions' => 'user_id',
				'primary' => true
			],
		];

		return $structure;
	}
}