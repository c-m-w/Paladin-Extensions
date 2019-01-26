<?php

namespace XR\PM\Entity;

use XF\Entity\Attachment;
use XF\Mvc\Entity\ArrayCollection;
use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

/**
 * COLUMNS
 * @property int product_id
 * @property string product_hash
 * @property int category_id
 * @property string product_title
 * @property string product_tag_line
 * @property string product_details
 * @property array features
 * @property array optional_extras
 * @property int product_date
 * @property int last_update
 * @property int user_id
 * @property string username
 * @property bool active
 * @property int|null current_version_id
 * @property float price_
 * @property string currency
 * @property float renew_price_
 * @property int duration
 * @property string duration_unit
 * @property bool allow_early_extension
 * @property array user_group_ids
 * @property string terms_conditions
 * @property bool confirm_license
 * @property bool requires_activation
 * @property int download_count
 * @property int attach_count
 * @property array|null embed_metadata
 * @property int thumbnail_date
 * @property array payment_profile_ids
 * @property array|null custom_fields_
 *
 * GETTERS
 * @property string|null thumbnail_url
 * @property mixed has_thumbnail
 * @property array product_version_ids
 * @property mixed extras
 * @property mixed price
 * @property mixed renew_price
 * @property mixed valid_user_group_ids
 * @property \XF\CustomField\Set custom_fields
 *
 * RELATIONS
 * @property \XR\PM\Entity\Category Category
 * @property \XR\PM\Entity\Version Version
 * @property \XR\PM\Entity\Version[] Versions
 * @property \XF\Entity\Attachment Thumbnail
 * @property \XF\Entity\User User
 * @property \XF\Entity\Attachment[] Images
 * @property \XR\PM\Entity\ProductPurchase[] Purchases
 */
class Product extends Entity implements \XF\BbCode\RenderableContentInterface
{
	public function canView(&$error = null)
	{
		if (!$this->category_id)
		{
			return \XF::visitor()->canViewProducts();
		}
		return $this->Category->canView($error);
	}

	public function canViewProductImages()
	{
		return $this->hasPermission('view_product_image');
	}

	public function canPurchase(&$error = null)
	{
		return $this->canView($error) && $this->hasPermission('buy');
	}

	/**
	 * @return bool|int
	 */
	public function canUseCoupons($bool = true, &$error = null)
	{
		$useCoupons = $this->hasPermission('use_coupons');
		if ($useCoupons)
		{
			/** @var int $couponLimit */
			$couponLimit = $this->hasPermission('use_coupons_limit');
			return ($bool ? true : $couponLimit);
		}

		$error = \XF::phrase('xr_pm_you_do_not_have_permission_to_use_coupons');
		return ($bool ? false : 0);
	}

	/**
	 * Attempts to ascertain whether the visitor has any downloadable purchases for this product.
	 *
	 * @param null $error
	 *
	 * @return bool
	 */
	public function canDownload(&$error = null)
	{
		$visitor = \XF::visitor();

		if (!$visitor->user_id)
		{
			return false;
		}

		$purchases = $this->repository('XR\PM:ProductPurchase')
			->findPurchasesForUser($visitor)
			->where('product_id', $this->product_id)
			->fetch();

		$canDownload = false;

		foreach ($purchases AS $purchase)
		{
			if ($purchase->isDownloadable())
			{
				$canDownload = true;
				break;
			}
		}

		return $canDownload;
	}

	public function getNewVersion()
	{
		/** @var Version $version */
		$version = $this->em()->create('XR\PM:Version');

		$version->product_id = $this->_getDeferredValue(function()
		{
			return $this->product_id;
		}, 'save');

		return $version;
	}

	public function isAttachmentEmbedded($attachmentId)
	{
		if (!$this->embed_metadata)
		{
			return false;
		}

		if ($attachmentId instanceof Attachment)
		{
			$attachmentId = $attachmentId->attachment_id;
		}

		return isset($this->embed_metadata['attachments'][$attachmentId]);
	}

	public function hasPermission($permission)
	{
		/** @var \XR\PM\XF\Entity\User $visitor */
		$visitor = \XF::visitor();
		return $visitor->hasXrPmCategoryPermission($this->category_id, $permission);
	}

	public function hasThumbnail()
	{
		return (bool)$this->thumbnail_date;
	}

	/**
	 * @param bool $canonical
	 *
	 * @return string|null
	 */
	public function getThumbnailUrl($canonical = false)
	{
		if (!$this->thumbnail_date)
		{
			return null;
		}

		$productId = $this->product_id;

		$path = sprintf("xrpm/thumbnail/%d/%d-%s.jpg?{$this->thumbnail_date}",
			floor($productId / 1000),
			$productId,
			$this->product_hash
		);
		return $this->app()->applyExternalDataUrl($path, $canonical);
	}

	public function getAbstractedThumbnailPath()
	{
		$productId = $this->product_id;

		return sprintf('data://xrpm/thumbnail/%d/%d-%s.jpg',
			floor($productId / 1000),
			$productId,
			$this->product_hash
		);
	}

	/**
	 * @return array
	 */
	public function getProductVersionIds()
	{
		return $this->db()->fetchAllColumn("
			SELECT product_version_id
			FROM xf_xr_pm_version
			WHERE product_id = ?
			ORDER BY release_date
		", $this->product_id);
	}

	public function getExtras()
	{
		if (!$this->optional_extras)
		{
			return $this->_em->getEmptyCollection();
		}

		$extras = $this->finder('XR\PM:Extra')
			->where('extra_id', $this->optional_extras)
			->order('extra_id')
			->fetch();

		return $extras;
	}

	public function setExtras(ArrayCollection $extras)
	{
		$this->_getterCache['extras'] = $extras;
	}

	public function getExtraDescription($extra)
	{
		return strtr($extra['extra_description'], [
			'{product}' => $this->product_title
		]);
	}

	public function getPrice()
	{
		return round(floatval($this->price_), 2);
	}

	public function getRenewPrice()
	{
		return round(floatval($this->renew_price_), 2);
	}

	public function getValidUserGroupIds()
	{
		$userGroupIds = $this->_em->findByIds(
			'XF:UserGroup', $this->user_group_ids
		)->keys();

		return $userGroupIds;
	}

	/**
	 * @return \XF\CustomField\Set
	 */
	public function getCustomFields()
	{
		/** @var \XF\CustomField\DefinitionSet $fieldDefinitions */
		$fieldDefinitions = $this->app()->container('customFields.xr_pm_products');

		return new \XF\CustomField\Set($fieldDefinitions, $this);
	}

	public function getBbCodeRenderOptions($context, $type)
	{
		return [
			'entity' => $this,
			'user' => $this->User,
			'attachments' => $this->attach_count ? $this->Images : [],
			'viewAttachments' => $this->canViewProductImages()
		];
	}

	public function isRenewable()
	{
		return ($this->duration && $this->active);
	}

	protected function _preSave()
	{
		if ($this->isInsert() && !$this->product_hash)
		{
			$this->product_hash = md5(microtime(true) . \XF::generateRandomString(8, true));
		}
	}

	protected function _postSave()
	{
		if ($this->isUpdate())
		{
			if ($this->active)
			{
				$this->productMadeVisible();
			}
			else
			{
				$this->productHidden();
			}

			if ($this->isChanged('category_id'))
			{
				/** @var Category $oldCategory */
				$oldCategory = $this->getExistingRelation('Category');
				if ($oldCategory && $this->Category)
				{
					$this->productMoved($oldCategory, $this->Category);
				}
			}
		}
		else
		{
			// insert
			if ($this->active)
			{
				$this->productInsertedVisible();
			}
		}

		$this->updateCategoryRecord();
	}

	protected function productMadeVisible()
	{
	}

	protected function productHidden($hardDelete = false)
	{
//		TODO: Delete license alerts
//		/** @var \XF\Repository\UserAlert $alertRepo */
//		$alertRepo = $this->repository('XF:UserAlert');
//		$alertRepo->fastDeleteAlertsForContent('xr_pm_license', $this->product_license_ids;
	}

	protected function productInsertedVisible()
	{
	}

	protected function productMoved(Category $from, Category $to)
	{
	}

	protected function updateCategoryRecord()
	{
		if (!$this->Category)
		{
			return;
		}

		$category = $this->Category;

		if ($this->isUpdate() && $this->isChanged('category_id'))
		{
			if ($this->active)
			{
				$category->productAdded($this);
				$category->save();

				/** @var Category $oldCategory */
				$oldCategory = $this->getExistingRelation('Category');
				if ($oldCategory)
				{
					$oldCategory->productRemoved($this);
					$oldCategory->save();
				}
			}

			return;
		}

		$activeChange = $this->isStateChanged('active', true);
		if ($activeChange == 'enter' && $category)
		{
			$category->productAdded($this);
			$category->save();
		}
		else if ($activeChange == 'leave' && $category)
		{
			$category->productRemoved($this);
			$category->save();
		}
		else if ($this->isUpdate() && $this->active)
		{
			$category->productDataChanged($this);
			$category->save();
		}
	}
	
	protected function _postDelete()
	{
		if ($this->active)
		{
			$this->productHidden(true);
		}

		if ($this->Category && $this->active)
		{
			$this->Category->productRemoved($this);
			$this->Category->save();
		}

		/** @var \XF\Repository\Attachment $attachRepo */
		$attachRepo = $this->repository('XF:Attachment');
		$attachRepo->fastDeleteContentAttachments('xr_pm_product_image', $this->product_id);
		$attachRepo->fastDeleteContentAttachments('xr_pm_product_thumb', $this->product_id);

		$versionIds = $this->product_version_ids;
		if ($versionIds)
		{
			$this->_postDeleteVersions($versionIds);
		}

		$this->app()->jobManager()->enqueueUnique('xrpmProductDelete' . $this->product_id, 'XR\PM:ProductDelete', [
			'product_id' => $this->product_id
		]);
	}

	protected function _postDeleteVersions(array $versionIds)
	{
		$db = $this->db();

		/** @var \XF\Repository\Attachment $attachRepo */
		$attachRepo = $this->repository('XF:Attachment');
		$attachRepo->fastDeleteContentAttachments('xr_pm_version', $versionIds);

		$db->delete('xf_xr_pm_version', 'product_version_id IN (' . $db->quote($versionIds) . ')');
		$db->delete('xf_xr_pm_download', 'version_id IN (' . $db->quote($versionIds) . ')');
	}

	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_xr_pm_product';
		$structure->shortName = 'XR\PM:Product';
		$structure->primaryKey = 'product_id';
		$structure->columns = [
			'product_id' => ['type' => self::UINT, 'autoIncrement' => true],
			'product_hash' => ['type' => self::STR, 'maxLength' => 32, 'required' => true],
			'category_id' => ['type' => self::UINT,
				'required' => 'xr_pm_name_only_please_choose_valid_category'
			],
			'product_title' => ['type' => self::STR, 
				'required' => 'xr_pm_name_only_please_enter_valid_product_title', 'maxLength' => 100
			],
			'product_tag_line' => ['type' => self::STR,
				'required' => 'xr_pm_name_only_please_enter_valid_product_tag_line', 'maxLength' => 100
			],
			'product_details' => ['type' => self::STR,
				'required' => 'xr_pm_name_only_please_enter_some_product_details'
			],
			'features' => ['type' => self::JSON_ARRAY],
			'optional_extras' => ['type' => self::JSON_ARRAY, 'default' => []],
			'product_date' => ['type' => self::UINT, 'default' => \XF::$time],
			'last_update' => ['type' => self::UINT, 'default' => \XF::$time],
			'user_id' => ['type' => self::UINT, 'default' => '0'],
			'username' => ['type' => self::STR, 'maxLength' => 50],
			'active' => ['type' => self::BOOL, 'default' => true],
			'current_version_id' => ['type' => self::UINT, 'default' => 0, 'nullable' => true],
			'price' => ['type' => self::FLOAT, 'default' => '0'],
			'currency' => ['type' => self::STR, 'required' => true],
			'renew_price' => ['type' => self::FLOAT, 'default' => '0'],
			'duration' => ['type' => self::UINT, 'default' => 12],
			'duration_unit' => ['type' => self::STR, 'required' => true, 'default' => 'months', 
				'allowedValues' => ['days', 'months', 'years']
			],
			'allow_early_extension' => ['type' => self::BOOL, 'default' => true],
			'user_group_ids' => ['type' => self::JSON_ARRAY, 'default' => []],
			'terms_conditions' => ['type' => self::STR, 'default' => ''],
			'confirm_license' => ['type' => self::BOOL, 'default' => false],
			'requires_activation' => ['type' => self::BOOL, 'default' => true],
			'download_count' => ['type' => self::UINT, 'default' => 0],
			'attach_count' => ['type' => self::UINT, 'default' => 0],
			'embed_metadata' => ['type' => self::JSON_ARRAY, 'nullable' => true, 'default' => null],
			'thumbnail_date' => ['type' => self::UINT, 'default' => 0],
			'payment_profile_ids' => ['type' => self::LIST_COMMA,
				'required' => 'please_select_at_least_one_payment_profile',
				'list' => ['type' => 'posint', 'unique' => true, 'sort' => SORT_NUMERIC]
			],
			'custom_fields' => ['type' => self::JSON_ARRAY, 'nullable' => true, 'default' => []]
		];
		$structure->getters = [
			'thumbnail_url' => true,
			'has_thumbnail' => ['getter' => 'hasThumbnail', 'cache' => false],
			'product_version_ids' => true,
			'extras' => true,
			'price' => true,
			'renew_price' => true,
			'valid_user_group_ids' => true,
			'custom_fields' => true
		];
		$structure->relations = [
			'Category' => [
				'entity' => 'XR\PM:Category',
				'type' => self::TO_ONE,
				'conditions' => 'category_id',
				'primary' => true
			],
			'Version' => [
				'entity' => 'XR\PM:Version',
				'type' => self::TO_ONE,
				'conditions' => [
					['product_version_id', '=', '$current_version_id']
				],
				'primary' => true
			],
			'Versions' => [
				'entity' => 'XR\PM:Version',
				'type' => self::TO_MANY,
				'conditions' => 'product_id',
				'order' => ['release_date', 'DESC']
			],
			'Thumbnail' => [
				'entity' => 'XF:Attachment',
				'type' => self::TO_ONE,
				'conditions' => [
					['content_type', '=', 'xr_pm_product_thumb'],
					['content_id', '=', '$product_id']
				],
				'order' => ['attach_date', 'DESC'] // should only be one but ensure we get the latest
			],
			'User' => [
				'entity' => 'XF:User',
				'type' => self::TO_ONE,
				'conditions' => 'user_id',
				'primary' => true
			],
			'Images' => [
				'entity' => 'XF:Attachment',
				'type' => self::TO_MANY,
				'conditions' => [
					['content_type', '=', 'xr_pm_product_image'],
					['content_id', '=', '$product_id']
				],
				'with' => 'Data',
				'order' => 'attach_date'
			],
			'Purchases' => [
				'entity' => 'XR\PM:ProductPurchase',
				'type' => self::TO_MANY,
				'conditions' => 'product_id',
				'order' => 'purchase_date'
			]
		];

		return $structure;
	}
}