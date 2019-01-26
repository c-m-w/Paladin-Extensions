<?php

namespace XR\PM\Service\Product;

use XF\Service\AbstractService;
use XF\Util\File;
use XR\PM\Entity\Product;

class Thumbnailer extends AbstractService
{
	/**
	 * @var Product
	 */
	protected $product;

	/**
	 * @var \XF\Entity\Attachment
	 */
	protected $thumbAttachment;

	public function __construct(\XF\App $app, Product $product)
	{
		parent::__construct($app);
		$this->product = $product;
		$this->thumbAttachment = $product->Thumbnail;
	}

	public function thumbnail()
	{
		$data = $this->thumbAttachment->Data;
		$dataPath = $data->getAbstractedDataPath();
		$tempFile = File::copyAbstractedPathToTempFile($dataPath);
		$thumbPath = $this->product->getAbstractedThumbnailPath();

		if (!$data->width || !$data->height || !$this->app->imageManager()->canResize($data->width, $data->height))
		{
			\XF\Util\File::deleteFromAbstractedPath($thumbPath);
			return;
		}

		$image = $this->app->imageManager()->imageFromFile($tempFile);

		$thumbWidth = $thumbHeight = $this->app->options()->xr_pm_thumbnail_size;

		$image->resizeAndCrop($thumbWidth, $thumbHeight)
			->unsharpMask();

		$newTemp = File::getTempFile();
		if ($newTemp && $image->save($newTemp))
		{
			try
			{
				\XF\Util\File::copyFileToAbstractedPath($newTemp, $thumbPath);
				$this->product->fastUpdate('thumbnail_date', time());
			}
			catch (\Exception $e)
			{
				\XF\Util\File::deleteFromAbstractedPath($thumbPath);

				throw $e;
			}
		}
	}
}