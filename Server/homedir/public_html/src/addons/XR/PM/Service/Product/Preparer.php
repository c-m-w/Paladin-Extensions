<?php

namespace XR\PM\Service\Product;

use XF\Service\AbstractService;
use XR\PM\Entity\Product;

class Preparer extends AbstractService
{
	/**
	 * @var Product
	 */
	protected $product;

	protected $imageAttachmentHash;
	protected $thumbAttachmentHash;

	public function __construct(\XF\App $app, Product $product)
	{
		parent::__construct($app);
		$this->product = $product;
	}

	public function getProduct()
	{
		return $this->product;
	}

	public function setProductDetails($productDetails, $format = true, $checkValidity = true)
	{
		$preparer = $this->getMessagePreparer($format);
		$this->product->product_details = $preparer->prepare($productDetails, $checkValidity);
		$this->product->embed_metadata = $preparer->getEmbedMetadata();

		return $preparer->pushEntityErrorIfInvalid($this->product);
	}

	public function setTermsConditions($termsConditions, $format = true, $checkValidity = true)
	{
		$preparer = $this->getMessagePreparer($format);
		$preparer->setConstraint('allowEmpty', true);
		$this->product->terms_conditions = $preparer->prepare($termsConditions, $checkValidity);
		
		return $preparer->pushEntityErrorIfInvalid($this->product);
	}

	/**
	 * @param bool $format
	 *
	 * @return \XF\Service\Message\Preparer
	 */
	protected function getMessagePreparer($format = true)
	{
		/** @var \XF\Service\Message\Preparer $preparer */
		$preparer = $this->service('XF:Message\Preparer', 'xr_pm_product', $this->product);
		if (!$format)
		{
			$preparer->disableAllFilters();
		}

		return $preparer;
	}

	public function setImageAttachmentHash($hash)
	{
		$this->imageAttachmentHash = $hash;
	}

	public function setThumbAttachmentHash($hash)
	{
		$this->thumbAttachmentHash = $hash;
	}

	public function hasNewThumbnails()
	{
		if (!$this->thumbAttachmentHash)
		{
			return false;
		}

		$attachments = $this->repository('XF:Attachment')
			->findAttachmentsByTempHash($this->thumbAttachmentHash);

		return (bool)$attachments->fetch()->count();
	}

	public function afterInsert()
	{
		$this->_associateAttachments('insert');
	}

	public function afterUpdate()
	{
		$this->_associateAttachments('update');
	}

	protected function _associateAttachments($context)
	{
		if ($this->imageAttachmentHash)
		{
			$this->associateAttachments($this->imageAttachmentHash, 'xr_pm_product_image', $context, true);
		}

		if ($this->thumbAttachmentHash)
		{
			$this->associateAttachments($this->thumbAttachmentHash, 'xr_pm_product_thumb', $context);
		}
	}

	protected function associateAttachments($hash, $contentType, $context, $increaseAttachCount = false)
	{
		$product = $this->product;

		/** @var \XF\Service\Attachment\Preparer $inserter */
		$inserter = $this->service('XF:Attachment\Preparer');
		$associated = $inserter->associateAttachmentsWithContent($hash, $contentType, $product->product_id);
		if ($associated && $increaseAttachCount)
		{
			$product->fastUpdate('attach_count', $product->attach_count + $associated);
		}
	}
}