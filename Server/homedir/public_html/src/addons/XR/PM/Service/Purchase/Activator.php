<?php

namespace XR\PM\Service\Purchase;

use XF\Service\AbstractService;
use XF\Service\ValidateAndSavableTrait;

class Activator extends AbstractService
{
	use ValidateAndSavableTrait;

	/**
	 * @var \XR\PM\Entity\ProductPurchase
	 */
	protected $purchase;

	public function __construct(\XF\App $app, \XR\PM\Entity\ProductPurchase $purchase)
	{
		parent::__construct($app);

		$this->purchase = $purchase;
	}

	/**
	 * @return \XR\PM\Entity\ProductPurchase
	 */
	public function getPurchase()
	{
		return $this->purchase;
	}

	public function setLicenseDetails($name, $url)
	{
		$this->purchase->license_name = $name;
		$this->purchase->license_url = $url;
		$this->purchase->purchase_state = 'active';
	}

	protected function _validate()
	{
		$errors = [];

		if (!$this->purchase->license_name || !$this->purchase->license_url)
		{
			$errors[] = \XF::phrase('please_complete_required_fields');
		}

		if (!$this->purchase->isActivatable())
		{
			$errors[] = \XF::phrase('xr_pm_purchase_cannot_be_activated_as_it_is_in_invalid_state');
		}

		/** @var \XF\Validator\Url $validator */
		$validator = $this->app->validator('Url');
		$this->purchase->license_url = $validator->coerceValue($this->purchase->license_url);
		if (!$validator->isValid($this->purchase->license_url))
		{
			$errors[] = \XF::phrase('please_enter_valid_url');
		}

		return $errors;
	}

	protected function _save()
	{
		return $this->purchase->save();
	}
}