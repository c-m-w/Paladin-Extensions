<?php

namespace XR\PM\Entity;

use XF\Entity\Attachment;
use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

/**
 * COLUMNS
 * @property int extra_id
 * @property string extra_title
 * @property string extra_description
 * @property float extra_price_
 * @property float extra_renew_price_
 * @property string extra_reward
 * @property int extra_user_group_id
 * @property string instructions
 *
 * GETTERS
 * @property mixed extra_price
 * @property mixed extra_renew_price
 *
 * RELATIONS
 * @property \XF\Entity\Attachment Extra
 * @property \XR\PM\Entity\ProductExtraMap[] ProductExtras
 */
class Extra extends Entity
{
	public function canViewExtraFile()
	{
		$visitor = \XF::visitor();

		$purchaseRepo = $this->repository('XR\PM:ProductPurchase');
		$purchases = $purchaseRepo->findPurchasesForUser($visitor)
			->fetch();

		if (!$purchases)
		{
			return false;
		}

		$canView = false;

		foreach ($purchases AS $purchase)
		{
			if (isset($purchase->extras[$this->extra_id]))
			{
				$canView = true;
				break;
			}
		}

		return $canView;
	}

	public function getExtraPrice()
	{
		return round(floatval($this->extra_price_), 2);
	}

	public function getExtraRenewPrice()
	{
		return round(floatval($this->extra_renew_price_), 2);
	}

	public function getInstructions($product)
	{
		return strtr($this->instructions_, [
			'{product}' => $product
		]);
	}

	protected function _postDelete()
	{
		$this->repository('XR\PM:Extra')->removeExtraAssociations($this);
	}

	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_xr_pm_optional_extra';
		$structure->shortName = 'XR\PM:Extra';
		$structure->primaryKey = 'extra_id';
		$structure->columns = [
			'extra_id' => ['type' => self::UINT, 'autoIncrement' => true],
			'extra_title' => ['type' => self::STR,
				'required' => 'xr_pm_please_enter_valid_extra_title', 'maxLength' => 100
			],
			'extra_description' => ['type' => self::STR, 'default' => ''],
			'extra_price' => ['type' => self::FLOAT, 'default' => '0'],
			'extra_renew_price' => ['type' => self::FLOAT, 'default' => '0'],
			'extra_reward' => ['type' => self::STR, 'default' => 'user_group',
				'allowedValues' => ['user_group', 'file', 'instructions']
			],
			'extra_user_group_id' => ['type' => self::UINT, 'default' => 0],
			'instructions' => ['type' => self::STR, 'default' => '']
		];
		$structure->getters = [
			'extra_price' => true,
			'extra_renew_price' => true,
			'change_key' => true
		];
		$structure->relations = [
			'Extra' => [
				'entity' => 'XF:Attachment',
				'type' => self::TO_ONE,
				'conditions' => [
					['content_type', '=', 'xr_pm_product_extra'],
					['content_id', '=', '$extra_id']
				],
				'order' => ['attach_date', 'DESC'] // should only be one but ensure we get the latest
			],
			'ProductExtras' => [
				'entity' => 'XR\PM:ProductExtraMap',
				'type' => self::TO_MANY,
				'conditions' => 'extra_id'
			]
		];

		return $structure;
	}
}