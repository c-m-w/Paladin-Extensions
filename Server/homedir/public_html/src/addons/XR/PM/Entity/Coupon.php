<?php

namespace XR\PM\Entity;

use XF\Entity\Attachment;
use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

/**
 * COLUMNS
 * @property int coupon_id
 * @property string coupon_code
 * @property string coupon_title
 * @property string coupon_description
 * @property string coupon_type
 * @property array coupon_usable_by
 * @property array coupon_auto_assign_to
 * @property array coupon_product_ids
 * @property array coupon_extra_ids
 * @property int coupon_reduction
 * @property string coupon_unit
 * @property int coupon_valid_to
 * @property bool coupon_set_limit
 * @property int coupon_limit
 * @property bool active
 */
class Coupon extends Entity
{
	public function canUse(&$error = null)
	{
		$visitor = \XF::visitor();

		if (!in_array(-1, $this->coupon_usable_by) && !$visitor->isMemberOf($this->coupon_usable_by))
		{
			$error = \XF::phrase('xr_pm_you_do_not_have_permission_to_use_selected_coupon_x', ['coupon_code' => $this->coupon_code]);
			return false;
		}

		if ($this->coupon_set_limit && !$this->coupon_limit)
		{
			$error = \XF::phrase('xr_pm_selected_coupon_x_is_no_longer_available', ['coupon_code' => $this->coupon_code]);
			return false;
		}

		if ($this->coupon_valid_to && time() > $this->coupon_valid_to)
		{
			$error = \XF::phrase('xr_pm_selected_coupon_x_has_now_expired', ['thiscoupon_code' => $this->coupon_code]);
			return false;
		}

		return true;
	}

	public function isAutoApplied(&$error = null)
	{
		$visitor = \XF::visitor();

		return $this->canUse($error)
			&& (in_array(-1, $this->coupon_auto_assign_to)
				|| $visitor->isMemberOf($this->coupon_auto_assign_to)
			);
	}

	public function getDiscountAmount($price)
	{
		$discount = $this->coupon_reduction;

		if ($this->coupon_unit == 'percent')
		{
			$sellingPrice = $price - ($price * ($discount / 100));
			$discount = $price - $sellingPrice;
		}

		// just a sanity check
		if ($discount < 0)
		{
			$discount = 0;
		}
		if ($discount > $price)
		{
			$discount = $price;
		}

		return $discount;
	}

	protected function _preSave()
	{
		if ($this->coupon_type == 'product' && !$this->coupon_product_ids)
		{
			$this->error(\XF::phrase('xr_pm_you_must_select_at_least_one_product_for_product_coupon'));
			return;
		}

		if ($this->coupon_type == 'extra' && !$this->coupon_extra_ids)
		{
			$this->error(\XF::phrase('xr_pm_you_must_select_at_least_one_extra_for_extra_coupon'));
			return;
		}
	}

	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_xr_pm_coupon';
		$structure->shortName = 'XR\PM:Coupon';
		$structure->primaryKey = 'coupon_id';
		$structure->columns = [
			'coupon_id' => ['type' => self::UINT, 'autoIncrement' => true],
			'coupon_code' => ['type' => self::STR,
				'required' => 'xr_pm_please_enter_valid_coupon_code', 'maxLength' => 50
			],
			'coupon_title' => ['type' => self::STR,
				'required' => 'xr_pm_please_enter_valid_coupon_title', 'maxLength' => 100
			],
			'coupon_description' => ['type' => self::STR, 'default' => ''],
			'coupon_type' => ['type' => self::STR, 'default' => 'purchase'],
			'coupon_usable_by' => ['type' => self::LIST_COMMA, 'default' => [],
				'list' => ['unique' => true, 'sort' => SORT_NUMERIC]
			],
			'coupon_auto_assign_to' => ['type' => self::LIST_COMMA, 'default' => [],
				'list' => ['unique' => true, 'sort' => SORT_NUMERIC]
			],
			'coupon_product_ids' => ['type' => self::JSON_ARRAY, 'default' => []],
			'coupon_extra_ids' => ['type' => self::JSON_ARRAY, 'default' => []],
			'coupon_reduction' => ['type' => self::UINT, 'default' => 10],
			'coupon_unit' => ['type' => self::STR, 'default' => 'percent'],
			'coupon_valid_to' => ['type' => self::UINT, 'default' => 0],
			'coupon_set_limit' => ['type' => self::BOOL, 'default' => false],
			'coupon_limit' => ['type' => self::UINT, 'default' => 0, 'forced' => true],
			'active' => ['type' => self::BOOL, 'default' => true]
		];
		$structure->getters = [];
		$structure->relations = [];

		return $structure;
	}
}