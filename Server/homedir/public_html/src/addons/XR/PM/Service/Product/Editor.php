<?php

namespace XR\PM\Service\Product;

use XF\Service\AbstractService;
use XF\Service\ValidateAndSavableTrait;
use XR\PM\Entity\Category;
use XR\PM\Entity\Product;
use XR\PM\Entity\Version;

class Editor extends AbstractService
{
	use ValidateAndSavableTrait;
	/**
	 * @var Product
	 */
	protected $product;

	/**
	 * @var Version
	 */
	protected $version;

	protected $extras = [];

	/**
	 * @var \XR\PM\Service\Product\Preparer
	 */
	protected $productPreparer;

	/**
	 * @var \XR\PM\Service\Version\Preparer
	 */
	protected $versionPreparer;

	protected $performValidations = true;

	public function __construct(\XF\App $app, Product $product)
	{
		parent::__construct($app);
		$this->product = $product;
		$this->version = $product->Version;

		$this->productPreparer = $this->service('XR\PM:Product\Preparer', $this->product);
		$this->versionPreparer = $this->service('XR\PM:Version\Preparer', $this->version);
		$this->product->addCascadedSave($this->version);
	}

	public function setPerformValidations($perform)
	{
		$this->performValidations = (bool)$perform;
	}

	public function getPerformValidations()
	{
		return $this->performValidations;
	}

	public function setCategory(Category $category)
	{
		$this->product->category_id = $category->category_id;
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
		$this->product->user_group_ids = $userGroupIds;
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

		$db = $this->db();
		$db->beginTransaction();

		$product->save(true, false);
		// version will also be saved

		$this->productPreparer->afterInsert();
		$this->versionPreparer->afterInsert();

		$db->commit();

		/** @var \XR\PM\Repository\Extra $repo */
		$repo = $this->repository('XR\PM:Extra');
		$repo->updateProductAssociations($this->product->product_id, $this->extras);

		return $product;
	}
}