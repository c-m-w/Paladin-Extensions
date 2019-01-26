<?php

namespace XR\PM\Repository;

use XF\Mvc\Entity\ArrayCollection;
use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Repository;

class Version extends Repository
{
	/**
	 * @return Finder
	 */
	public function findVersionsForList()
	{
		$finder = $this->finder('XR\PM:Version')
			->with('Product')
			->setDefaultOrder('release_date', 'DESC');

		return $finder;
	}

	/**
	 * @param \XR\PM\Entity\Product $product
	 *
	 * @return Finder
	 */
	public function findVersionsForProduct(\XR\PM\Entity\Product $product)
	{
		$finder = $this->finder('XR\PM:Version')
			->with('Product')
			->where('product_id', $product->product_id)
			->setDefaultOrder('release_date', 'DESC');

		return $finder;
	}

	public function filterAllowedVersionsForPurchase(ArrayCollection $versions, \XR\PM\Entity\ProductPurchase $purchase)
	{
		return $versions->filter(function(\XR\PM\Entity\Version $version) use($purchase)
		{
			if ($purchase->expiry_date > 0 && $version->release_date > $purchase->expiry_date)
			{
				return false;
			}
			else
			{
				return true;
			}
		});
	}

	public function getVersionAttachmentConstraints()
	{
		$options = $this->options();

		return [
			'extensions' => preg_split('/\s+/', trim($options->xr_pm_versionExtensions), -1, PREG_SPLIT_NO_EMPTY),
			'size' => $options->xr_pm_versionMaxSize * 1024,
			'width' => 0, 'height' => 0, 'count' => 1
		];
	}

	public function logDownload(\XR\PM\Entity\Version $version, \XR\PM\Entity\ProductPurchase $purchase)
	{
		$visitor = \XF::visitor();

		$hasDownloaded = $this->db()->fetchOne("
			SELECT 1
			FROM xf_xr_pm_download
			WHERE user_id = ?
				AND product_id = ?
				AND purchase_key = ?
			LIMIT 1
		", [$visitor->user_id, $version->product_id, $purchase->purchase_key]);

		$result = $this->db()->insert('xf_xr_pm_download', [
			'purchase_key' => $purchase->purchase_key,
			'version_id' => $version->product_version_id,
			'user_id' => $visitor->user_id,
			'product_id' => $version->product_id,
			'last_download_date' => \XF::$time
		], false, 'last_download_date = VALUES(last_download_date)');

		if (!$hasDownloaded)
		{
			$this->db()->query("
				UPDATE xf_xr_pm_product
				SET download_count = download_count + 1
				WHERE product_id = ?
			", $version->product_id);
		}

		if ($result == 1)
		{
			$this->db()->query("
				UPDATE xf_xr_pm_version
				SET download_count = download_count + 1
				WHERE product_version_id = ?
			", $version->product_version_id);
		}
	}

	/**
	 * @param $versionId
	 * @return Finder
	 */
	public function findDownloadLogsForVersion($versionId)
	{
		$finder = $this->finder('XR\PM:Download');

		$finder
			->where('version_id', $versionId)
			->with([
				'Product',
				'Purchase',
				'Version',
				'User'
			], true)
			->order('last_download_date', 'DESC');

		return $finder;
	}
}