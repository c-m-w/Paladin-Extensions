<?php

namespace XR\PM\Service\Product;

use XF\Service\AbstractService;
use XF\Service\ValidateAndSavableTrait;
use XR\PM\Entity\Category;
use XR\PM\Entity\Product;
use XR\PM\Entity\Version;

class Creator extends AbstractService
{
	use ValidateAndSavableTrait;

	/**
	 * @var Category
	 */
	protected $category;

	/**
	 * @var Product
	 */
	protected $product;

	protected $extras = [];

	/**
	 * @var Version
	 */
	protected $version;

	/**
	 * @var \XR\PM\Service\Product\Preparer
	 */
	protected $productPreparer;

	/**
	 * @var \XR\PM\Service\Version\Preparer
	 */
	protected $versionPreparer;

	protected $createNewUserGroup = false;

	protected $performValidations = true;

	public function __construct(\XF\App $app, Category $category)
	{
		parent::__construct($app);
		$this->category = $category;
		$this->product = $category->getNewProduct();
		$this->version = $this->product->getNewVersion();

		$this->setProductDefaults();
	}

	public function setPerformValidations($perform)
	{
		$this->performValidations = (bool)$perform;
	}

	public function getPerformValidations()
	{
		return $this->performValidations;
	}

	protected function setProductDefaults()
	{
		$this->productPreparer = $this->service('XR\PM:Product\Preparer', $this->product);
		$this->versionPreparer = $this->service('XR\PM:Version\Preparer', $this->version);

		$visitor = \XF::visitor();
		$this->product->user_id = $visitor->user_id;
		$this->product->username = $visitor->username;

		$this->product->product_date = time();
		$this->product->active = true;

		$this->product->addCascadedSave($this->version);
		$this->version->hydrateRelation('Product', $this->product);
	}

	public function setVersion($version)
	{
		$this->version->version_string = $version;
	}

	public function setProductDetails($title, $details, $tagLine, $format = true)
	{
		$this->product->product_title = $title;
		$this->product->product_tag_line = $tagLine;

		return $this->productPreparer->setProductDetails($details, $format, $this->performValidations);
	}

	public function setImageAttachmentHash($hash)
	{
		$this->productPreparer->setImageAttachmentHash($hash);
	}

	public function setThumbAttachmentHash($hash)
	{
		$this->productPreparer->setThumbAttachmentHash($hash);
	}

	public function setVersionAttachmentHash($hash)
	{
		$this->versionPreparer->setVersionAttachmentHash($hash);
	}

	public function setFeatures(array $features)
	{
		$features = array_filter($features);
		$this->product->features = $features;
	}

	public function setPurchasePrice($price, $currency)
	{
		$this->product->price = $price;
		$this->product->currency = $currency;
	}

	public function setRenewalPrice($price)
	{
		$this->product->renew_price = $price;
	}

	public function setSupportDuration($length, $unit)
	{
		$this->product->duration = $length;
		$this->product->duration_unit = $unit;
	}

	public function setEarlyExtension($earlyExtension)
	{
		$this->product->allow_early_extension = $earlyExtension;
	}

	public function setUserGroups(array $userGroupIds)
	{
		$value = [];

		foreach ($userGroupIds AS $userGroupId)
		{
			if ($userGroupId == '__new')
			{
				$this->createNewUserGroup = true;
			}
			else
			{
				$value[] = $userGroupId;
			}
		}

		$this->product->user_group_ids = $value;
	}

	public function setOptionalExtras(array $extraIds)
	{
		$this->extras = $extraIds;
	}

	public function setLicenseOptions($terms, $confirmTerms, $requiresActivation, $format = true)
	{
		$this->product->confirm_license = $confirmTerms;
		$this->product->requires_activation = $requiresActivation;

		return $this->productPreparer->setTermsConditions($terms, $format, $this->performValidations);
	}

	public function setActive($active)
	{
		$this->product->active = $active;
	}

	public function setCustomFields(array $customFields)
	{
		$product = $this->product;

		/** @var \XF\CustomField\Set $fieldSet */
		$fieldSet = $product->custom_fields;
		$fieldDefinition = $fieldSet->getDefinitionSet();

		$customFieldsShown = array_keys($fieldDefinition->getFieldDefinitions());

		if ($customFieldsShown)
		{
			$fieldSet->bulkSet($customFields, $customFieldsShown);
		}
	}

	public function setAllowedPaymentProfiles(array $profileIds)
	{
		$this->product->payment_profile_ids = $profileIds;
	}

	protected function finalSetup()
	{
	}

	protected function _validate()
	{
		$this->finalSetup();

		$this->product->preSave();
		return $this->product->getErrors();
	}

	protected function _save()
	{
		$product = $this->product;
		$version = $this->version;

		$db = $this->db();
		$db->beginTransaction();

		$product->save(true, false);
		// version will also be saved

		if ($this->createNewUserGroup)
		{
			$userGroupIds = $product->user_group_ids;

			/** @var \XF\Entity\UserGroup $userGroup */
			$userGroup = $this->em()->create('XF:UserGroup');
			$userGroup->title = \XF::phrase('xr_pm_licensed_user_group_title_prefix:') . ' ' . $product->product_title;
			if ($userGroup->save(false, false))
			{
				$userGroupIds[] = $userGroup->user_group_id;
				$product->fastUpdate('user_group_ids', $userGroupIds);
			}
		}

		$product->fastUpdate('current_version_id', $version->product_version_id);

		$this->productPreparer->afterInsert();
		$this->versionPreparer->afterInsert();

		$db->commit();

		/** @var \XR\PM\Repository\Extra $repo */
		$repo = $this->repository('XR\PM:Extra');
		$repo->updateProductAssociations($this->product->product_id, $this->extras);

		return $product;
	}
}