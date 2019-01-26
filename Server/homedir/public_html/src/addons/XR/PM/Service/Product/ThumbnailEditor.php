<?php

namespace XR\PM\Service\Product;

use XF\Service\AbstractService;
use XF\Service\ValidateAndSavableTrait;

class ThumbnailEditor extends AbstractService
{
	use ValidateAndSavableTrait;

	/**
	 * @var \XR\PM\Entity\Product
	 */
	protected $product;

	/**
	 * @var \XR\PM\Service\Product\Preparer
	 */
	protected $productPreparer;

	public function __construct(\XF\App $app, \XR\PM\Entity\Product $product)
	{
		parent::__construct($app);
		$this->product = $product;
		$this->productPreparer = $this->service('XR\PM:Product\Preparer', $this->product);
	}

	public function setThumbAttachmentHash($hash)
	{
		$this->productPreparer->setThumbAttachmentHash($hash);
	}

	protected function finalSetup()
	{
	}

	public function _validate()
	{
		$this->finalSetup();

		return [];
	}

	public function _save()
	{
		if ($this->productPreparer->hasNewThumbnails())
		{
			$this->deleteExistingAttachment();
		}
		$this->productPreparer->afterUpdate();
	}

	public function deleteExistingAttachment()
	{
		$product = $this->product;

		$existing = $this->em()->findOne('XF:Attachment', [
			'content_type' => 'xr_pm_product_thumb',
			'content_id' => $product->product_id
		]);

		if ($existing)
		{
			$existing->delete();
		}
	}
}