<?php

namespace XR\PM\Service\Coupon;

use XF\Service\AbstractService;
use XF\Service\ValidateAndSavableTrait;

class Editor extends AbstractService
{
	use ValidateAndSavableTrait;

	/**
	 * @var \XR\PM\Entity\Coupon
	 */
	protected $coupon;

	public function __construct(\XF\App $app, \XR\PM\Entity\Coupon $coupon)
	{
		parent::__construct($app);
		$this->coupon = $coupon;
	}

	public function setDetails($title, $description, $code)
	{
		$this->coupon->coupon_title = $title;
		$this->coupon->coupon_description = $description;
		$this->coupon->coupon_code = $code;
	}

	public function setCouponType($type, $ids = [])
	{
		$this->coupon->coupon_type = $type;

		switch ($type)
		{
			case 'product':
				$this->coupon->coupon_product_ids = $ids;
				$this->coupon->coupon_extra_ids = [];
				break;
			case 'extra':
				$this->coupon->coupon_extra_ids = $ids;
				$this->coupon->coupon_product_ids = [];
				break;
			case 'renewal':
				$this->coupon->coupon_product_ids = $ids;
				$this->coupon->coupon_extra_ids = [];
				break;
			default:
				$this->coupon->coupon_product_ids = [];
				$this->coupon->coupon_extra_ids = [];
				break;
		}
	}

	public function setUsableBy($type, array $ids)
	{
		if ($type == 'all')
		{
			$this->coupon->coupon_usable_by = [-1];
		}
		else
		{
			$this->coupon->coupon_usable_by = $ids;
		}
	}

	public function setAutoAssignTo($type, array $ids)
	{
		if ($type == 'all')
		{
			$this->coupon->coupon_auto_assign_to = [-1];
		}
		else
		{
			$this->coupon->coupon_auto_assign_to = $ids;
		}
	}

	public function setDiscount($reduction, $unit)
	{
		$this->coupon->coupon_reduction = $reduction;
		$this->coupon->coupon_unit = $unit;
	}

	public function setLimit($setLimit, $limit)
	{
		if ($setLimit)
		{
			$this->coupon->coupon_set_limit = true;
			$this->coupon->coupon_limit = $limit;
		}
		else
		{
			$this->coupon->coupon_set_limit = false;
			$this->coupon->coupon_limit = 0;
		}
	}

	public function setDateLimit($date)
	{
		$this->coupon->coupon_valid_to = $date;
	}

	public function setActive($active)
	{
		$this->coupon->active = $active;
	}

	protected function finalSetup()
	{
	}

	protected function _validate()
	{
		$this->finalSetup();

		$this->coupon->preSave();
		return $this->coupon->getErrors();
	}

	protected function _save()
	{
		$coupon = $this->coupon;

		$db = $this->db();
		$db->beginTransaction();

		$coupon->save(true, false);

		$db->commit();

		return $coupon;
	}
}