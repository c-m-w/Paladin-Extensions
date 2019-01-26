<?php

namespace XR\PM\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

/**
 * COLUMNS
 * @property int|null purchase_id
 * @property string purchase_key
 * @property string old_cart_key
 * @property int product_id
 * @property int purchase_date
 * @property int expiry_date
 * @property string purchase_state
 * @property string purchase_type
 * @property string parent_purchase_key
 * @property int user_id
 * @property string username
 * @property string license_name
 * @property string license_url
 * @property string purchase_currency
 * @property float product_price_
 * @property float extras_price_
 * @property float discount_total_
 * @property float total_price_
 * @property array extras
 * @property array coupons
 *
 * GETTERS
 * @property mixed displayable_extras
 * @property mixed renew_price
 * @property mixed product_price
 * @property mixed extras_price
 * @property mixed discount_total
 * @property mixed total_price
 * @property mixed change_key
 * @property mixed downloadable_versions
 *
 * RELATIONS
 * @property \XR\PM\Entity\Product Product
 * @property \XF\Entity\User User
 */
class ProductPurchase extends Entity
{
	public function canView(&$error = null)
	{
		return (\XF::visitor()->user_id && $this->user_id === \XF::visitor()->user_id && $this->Product);
	}

	public function canPurchaseExtras(&$error = null)
	{
		return (!$this->isExpired() && $this->hasUnpurchasedExtras() && $this->isProductActive());
	}

	public function isProductActive()
	{
		$product = $this->Product;
		if (!$product)
		{
			return false;
		}

		return $product->active;
	}

	public function isDownloadable(&$error = null)
	{
		$product = $this->Product;

		if (!$product)
		{
			return false;
		}

		if (!$this->isProductActive())
		{
			return false;
		}

		if (!$this->canView($error))
		{
			return false;
		}

		if ($this->doesRequireActivation())
		{
			return false;
		}

		if (in_array($this->purchase_state, ['inactive', 'pending', 'revoked', 'complete']))
		{
			return false;
		}

		return true;
	}

	public function isExpired()
	{
		return (in_array($this->purchase_state, ['active', 'inactive', 'expired']) && $this->expiry_date > 0 && time() > $this->expiry_date);
	}

	public function isActivatable(&$error = null)
	{
		return (
			$this->Product->requires_activation
			&& $this->isProductActive()
			&& !in_array($this->purchase_state, ['pending', 'revoked', 'renewal', 'expired'])
			&& !$this->isExpired()
		);
	}

	public function isRenewableEarly()
	{
		$product = $this->Product;
		return (!$this->isExpired() && $product && $product->isRenewable() && $product->allow_early_extension);
	}

	public function isVeryEarlyRenewal()
	{
		if ($this->isExpired())
		{
			return false;
		}

		$product = $this->Product;
		$duration = $product->duration;
		$durationUnit = $product->duration_unit;

		$now = new \DateTime();

		$expiry = clone $now;
		$expiry->modify("+ $duration $durationUnit");

		$diff = $expiry->getTimestamp() - $now->getTimestamp();

		$halfDiff = intval($diff / 2);
		$currentDiff = $this->expiry_date - $now->getTimestamp();

		return ($currentDiff > $halfDiff);
	}

	/**
	 * "Valid" in this context is a purchase which is not expired or otherwise not usable
	 *
	 * @return bool
	 */
	public function isValidPurchase()
	{
		return in_array($this->purchase_state, ['active', 'inactive']);
	}

	public function isTransferrable()
	{
		return ($this->exists() && $this->purchase_type === 'product');
	}

	public function doesRequireActivation()
	{
		return ($this->isActivatable() && !$this->hasLicenseDetails());
	}

	public function doesRequireRenewal(&$error = null)
	{
		return ($this->isExpired() && $this->Product->isRenewable());
	}

	public function hasLicenseDetails()
	{
		return ($this->license_name && $this->license_url);
	}

	public function hasCoupons()
	{
		return ($this->coupons && !empty(floatval($this->discount_total)));
	}

	public function hasUnpurchasedExtras()
	{
		return (bool)count($this->getUnpurchasedExtras()) && $this->isProductActive();
	}

	public function getUnpurchasedExtras()
	{
		if (!$this->isProductActive())
		{
			return [];
		}

		$productExtras = $this->Product->optional_extras;
		$purchaseExtras = $this->extras;
		return array_diff_key($productExtras, $purchaseExtras);
	}

	public function getDisplayableExtras()
	{
		$output = [];

		$extras = $this->Product->extras;

		foreach ($this->extras AS $extraId => $extra)
		{
			if (empty($extras[$extraId]))
			{
				continue;
			}

			$output[$extraId] = $extras[$extraId]->toArray() + [
				'extra_id' => $extraId,
				'extra_price' => $extra['extra_price']
			];
		}

		return $output;
	}

	public function getRenewPrice()
	{
		$renewPrice = $this->Product->renew_price;
		$extras = $this->Product->extras;

		foreach (array_keys($this->extras) AS $extraId)
		{
			if (isset($extras[$extraId]))
			{
				$extra = $extras[$extraId];
				if ($extra['extra_renew_price'])
				{
					$renewPrice += $extra['extra_renew_price'];
				}
			}
		}

		return round(floatval($renewPrice), 2);
	}

	public function getProductPrice()
	{
		return round(floatval($this->product_price_), 2);
	}

	public function getExtrasPrice()
	{
		return round(floatval($this->extras_price_), 2);
	}

	public function getDiscountTotal()
	{
		return round(floatval($this->discount_total_), 2);
	}

	public function getTotalPrice()
	{
		return round(floatval($this->total_price_), 2);
	}

	public function getChangeKey()
	{
		return "xr_pm_purchase_{$this->purchase_key}";
	}

	public function getExtraChangeKey($extraId)
	{
		return "xr_pm_extra_{$extraId}_{$this->purchase_key}";
	}

	public function getDownloadableVersions()
	{
		$product = $this->Product;

		if (!$product)
		{
			return null;
		}

		$versions = $product->Versions;

		if (!$versions)
		{
			return null;
		}

		return $versions->filter(function(Version $version)
		{
			return (!$version->is_unsupported && (!$this->expiry_date || $version->release_date <= $this->expiry_date));
		});
	}

	public function getBreadcrumbs($includeSelf = false)
	{
		$router = $this->app()->router();

		$breadcrumbs = [
			[
				'value' => \XF::phrase('nav.xr_pm_your_purchases'),
				'href' => $router->buildLink('products/purchases')
			]
		];

		if ($includeSelf)
		{
			$breadcrumbs[] = [
				'value' => "{$this->purchase_key} - {$this->Product->product_title}",
				'href' => $router->buildLink('products/purchase', $this),
				'purchase_id' => $this->purchase_id
			];
		}

		return $breadcrumbs;
	}

	protected function _preSave()
	{
		if ($this->isInsert() && !$this->purchase_key)
		{
			$this->purchase_key = $this->generatePurchaseKey();
		}

		// sanity check - never ensure the discount is more than the total purchase price
		if ($this->discount_total > ($this->product_price + $this->extras_price))
		{
			$this->discount_total = $this->product_price + $this->extras_price;
		}
	}

	protected function _postSave()
	{
		$this->rebuildTempUserChanges();
	}

	protected function rebuildTempUserChanges()
	{
		\XF::runOnce('xrpmProductPurchaseRebuildTempChanges-' . $this->purchase_key, function()
		{
			if ($this->purchase_type == 'product')
			{
				if ($this->isUpdate())
				{
					$this->expireAllTempUserChanges();
				}

				if ($this->isValidPurchase())
				{
					if ($this->Product->valid_user_group_ids)
					{
						$this->applyTempUserChange();
					}

					$extraIds = array_keys($this->extras);
					if ($extraIds)
					{
						/** @var Extra[] $extras */
						$extras = $this->_em->findByIds(
							'XR\PM:Extra', $extraIds
						);
						foreach ($extraIds AS $extraId)
						{
							$extra = $extras[$extraId];
							if ($extra->extra_reward == 'user_group' && $extra->extra_user_group_id)
							{
								$this->applyTempUserChange(
									$this->getExtraChangeKey($extra->extra_id), $extra->extra_user_group_id
								);
							}
						}
					}
				}
			}
		});
	}

	protected function applyTempUserChange($changeKey = null, $addGroups = null, $expiryDate = null, \XF\Entity\User $user = null)
	{
		$changeKey = $changeKey ?: $this->change_key;
		$addGroups = $addGroups ?: $this->Product->valid_user_group_ids;
		$expiryDate = $expiryDate ?: $this->expiry_date;
		$user = $user ?: $this->User;

		if (!is_array($addGroups))
		{
			$addGroups = [$addGroups];
		}

		$tempChange = $this->app()->service('XF:User\TempChange');

		$tempChange->applyGroupChange(
			$user,
			$changeKey,
			$addGroups,
			$changeKey,
			$expiryDate ?: null
		);
	}

	protected function expireAllTempUserChanges()
	{
		/** @var \XF\Entity\UserChangeTemp[] $changeTemp */
		$changeTemp = $this->finder('XF:UserChangeTemp')
			->where('change_key', 'LIKE', '%_' . $this->purchase_key)
			->fetch();

		foreach ($changeTemp AS $change)
		{
			$tempChange = $this->app()->service('XF:User\TempChange');
			$tempChange->expireChange($change);
		}
	}

	protected function generatePurchaseKey($length = 12)
	{
		return strtoupper(substr(md5(uniqid(mt_rand() . microtime(), true)), 0, $length));
	}

	protected function _postDelete()
	{
		$this->expireAllTempUserChanges();
	}

	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_xr_pm_product_purchase';
		$structure->shortName = 'XR\PM:ProductPurchase';
		$structure->primaryKey = 'purchase_id';
		$structure->columns = [
			'purchase_id' => ['type' => self::UINT, 'autoIncrement' => true, 'nullable' => true],
			'purchase_key' => ['type' => self::STR, 'required' => true, 'unique' => true],
			'old_cart_key' => ['type' => self::STR, 'default' => ''],
			'product_id' => ['type' => self::UINT],
			'purchase_date' => ['type' => self::UINT, 'default' => \XF::$time],
			'expiry_date' => ['type' => self::UINT, 'default' => 0],
			'purchase_state' => ['type' => self::STR, 'default' => 'pending',
				'allowedValues' => array_keys(
					\XF::repository('XR\PM:ProductPurchase')->getPurchaseStates()
				)
			],
			'purchase_type' => ['type' => self::STR, 'default' => 'product',
				'allowedValues' => array_keys(
					\XF::repository('XR\PM:ProductPurchase')->getPurchaseTypes()
				)
			],
			'parent_purchase_key' => ['type' => self::STR, 'default' => ''],
			'user_id' => ['type' => self::UINT, 'default' => '0'],
			'username' => ['type' => self::STR, 'maxLength' => 50],
			'license_name' => ['type' => self::STR, 'default' => '', 'maxLength' => 100],
			'license_url' => ['type' => self::STR, 'default' => ''],
			'purchase_currency' => ['type' => self::STR, 'required' => true],
			'product_price' => ['type' => self::FLOAT, 'default' => '0', 'min' => 0, 'forced' => true],
			'extras_price' => ['type' => self::FLOAT, 'default' => '0', 'min' => 0, 'forced' => true],
			'discount_total' => ['type' => self::FLOAT, 'default' => '0', 'min' => 0, 'forced' => true],
			'total_price' => ['type' => self::FLOAT, 'default' => '0', 'min' => 0, 'forced' => true],
			'extras' => ['type' => self::JSON_ARRAY, 'default' => []],
			'coupons' => ['type' => self::JSON_ARRAY, 'default' => []]
		];
		$structure->getters = [
			'displayable_extras' => true,
			'renew_price' => true,
			'product_price' => true,
			'extras_price' => true,
			'discount_total' => true,
			'total_price' => true,
			'change_key' => true,
			'downloadable_versions' => true
		];
		$structure->relations = [
			'Product' => [
				'entity' => 'XR\PM:Product',
				'type' => self::TO_ONE,
				'conditions' => 'product_id',
				'primary' => true
			],
			'User' => [
				'entity' => 'XF:User',
				'type' => self::TO_ONE,
				'conditions' => 'user_id',
				'primary' => true
			]
		];
		$structure->options = [
			'admin_add_or_edit' => false
		];

		return $structure;
	}
}