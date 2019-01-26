<?php

namespace XR\PM\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

/**
 * COLUMNS
 * @property int|null product_version_id
 * @property int product_id
 * @property string version_string_
 * @property string version_details
 * @property bool is_unsupported
 * @property int release_date
 * @property array changelog
 * @property int download_count
 *
 * GETTERS
 * @property mixed version_string
 * @property mixed product_title
 *
 * RELATIONS
 * @property \XR\PM\Entity\Product Product
 * @property \XF\Entity\Attachment Version
 */
class Version extends Entity
{
	public function canViewVersionFile()
	{
		$visitor = \XF::visitor();

		$purchaseRepo = $this->repository('XR\PM:ProductPurchase');

		/** @var \XR\PM\Entity\ProductPurchase[] $purchases */
		$purchases = $purchaseRepo->findPurchasesForUser($visitor)
			->fetch();

		if (!$purchases)
		{
			return false;
		}

		$canView = false;

		foreach ($purchases AS $purchase)
		{
			if ($purchase->purchase_type != 'product')
			{
				continue;
			}

			if ($purchase->isDownloadable())
			{
				if (!$purchase->expiry_date)
				{
					$canView = true;
					break;
				}

				if ($purchase->expiry_date > $this->release_date)
				{
					$canView = true;
					break;
				}
			}
		}

		return $canView;
	}

	public function getVersionString()
	{
		if ($this->is_unsupported)
		{
			return $this->version_string_ . ' ' . \XF::phrase('(xr_pm_unsupported)');
		}
		else
		{
			return $this->version_string_;
		}
	}

	public function getProductTitle()
	{
		return $this->Product ? $this->Product->product_title : '';
	}

	protected function _postSave()
	{
		if ($this->isInsert())
		{
			$this->rebuildProductCurrentVersion();
		}
		else if ($this->isUpdate() && $this->isChanged('is_unsupported'))
		{
			$this->rebuildProductCurrentVersion();
		}
	}

	protected function _postDelete()
	{
		$this->rebuildProductCurrentVersion();

		/** @var \XF\Repository\Attachment $attachRepo */
		$attachRepo = $this->repository('XF:Attachment');
		$attachRepo->fastDeleteContentAttachments('xr_pm_version', $this->product_version_id);

		$this->db()->delete('xf_xr_pm_download', 'version_id = ?', $this->product_version_id);
	}

	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_xr_pm_version';
		$structure->shortName = 'XR\PM:Version';
		$structure->primaryKey = 'product_version_id';
		$structure->columns = [
			'product_version_id' => ['type' => self::UINT, 'autoIncrement' => true, 'nullable' => true],
			'product_id' => ['type' => self::UINT],
			'version_string' => ['type' => self::STR, 'required' => true, 'maxLength' => 25],
			'version_details' => ['type' => self::STR, 'default' => ''],
			'is_unsupported' => ['type' => self::BOOL, 'default' => 0],
			'release_date' => ['type' => self::UINT, 'required' => true, 'default' => \XF::$time],
			'changelog' => ['type' => self::JSON_ARRAY, 'default' => ''],
			'download_count' => ['type' => self::UINT, 'default' => '0']
		];
		$structure->getters = [
			'version_string' => true,
			'product_title' => true
		];
		$structure->relations = [
			'Product' => [
				'entity' => 'XR\PM:Product',
				'type' => self::TO_ONE,
				'conditions' => 'product_id',
				'primary' => true
			],
			'Version' => [
				'entity' => 'XF:Attachment',
				'type' => self::TO_ONE,
				'conditions' => [
					['content_type', '=', 'xr_pm_product_version'],
					['content_id', '=', '$product_version_id']
				],
				'order' => ['attach_date', 'DESC'] // should only be one but ensure we get the latest
			]
		];

		return $structure;
	}

	protected function rebuildProductCurrentVersion()
	{
		\XF::runOnce('xrpmCurrentVersionRebuild' . $this->product_id, function()
		{
			$repo = $this->repository('XR\PM:Product');
			$repo->rebuildProductCurrentVersion($this->product_id);
		});
	}
}