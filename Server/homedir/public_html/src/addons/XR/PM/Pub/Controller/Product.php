<?php

namespace XR\PM\Pub\Controller;

use XF\Mvc\ParameterBag;
use XF\Mvc\Reply\AbstractReply;
use XF\Pub\Controller\AbstractController;

class Product extends AbstractController
{
	protected function preDispatchController($action, ParameterBag $params)
	{
		/** @var \XR\PM\XF\Entity\User $visitor */
		$visitor = \XF::visitor();

		if (!$visitor->canViewProducts($error))
		{
			throw $this->exception($this->noPermission($error));
		}
	}

	public function actionIndex(ParameterBag $params)
	{
		if ($params->product_id)
		{
			return $this->rerouteController(__CLASS__, 'view', $params);
		}

		/** @var \XR\PM\ControllerPlugin\ProductList $listPlugin */
		$listPlugin = $this->plugin('XR\PM:ProductList');

		$categoryParams = $listPlugin->getCategoryListData();
		$viewableCategoryIds = $categoryParams['categories']->keys();

		$listParams = $listPlugin->getCoreListData($viewableCategoryIds);

		$this->assertValidPage($listParams['page'], $listParams['perPage'], $listParams['total'], 'products');
		$this->assertCanonicalUrl($this->buildLink('products', null, ['page' => $listParams['page']]));

		$viewParams = $categoryParams + $listParams;
		return $this->view('XR\PM:Product\Overview', 'xr_pm_overview', $viewParams);
	}

	public function actionFilters()
	{
		/** @var \XR\PM\ControllerPlugin\ProductList $listPlugin */
		$listPlugin = $this->plugin('XR\PM:ProductList');

		return $listPlugin->actionFilters();
	}

	public function actionView(ParameterBag $params)
	{
		$attachRepo = $this->repository('XF:Attachment');

		$product = $this->assertViewableProduct($params->product_id, ['Category', 'Version']);
		$product = $attachRepo->addAttachmentsToContent($product, 'xr_pm_product_image', 'attach_count', 'Images');

		$viewParams = [
			'product' => $product
		];
		return $this->view('XR\PM:Product\View', 'xr_pm_product_view', $viewParams);
	}

	public function actionUpdates(ParameterBag $params)
	{
		$product = $this->assertViewableProduct($params->product_id);

		$versionRepo = $this->getVersionRepo();
		$versions = $versionRepo->findVersionsForProduct($product)->fetch();

		$viewParams = [
			'product' => $product,
			'versions' => $versions
		];
		return $this->view('XR\PM:Product\Updates', 'xr_pm_product_updates', $viewParams);
	}

	public function actionVersion(ParameterBag $params)
	{
		$product = $this->assertViewableProduct($params->product_id);
		$version = $this->assertVersionExists($params->product_version_id);

		if ($version->product_id != $product->product_id)
		{
			return $this->noPermission();
		}

		return $this->redirectPermanently($this->buildLink('products/updates', $product) . '#version-' . $version->product_version_id);
	}

	public function actionProductPurchases(ParameterBag $params)
	{
		$visitor = \XF::visitor();
		$product = $this->assertViewableProduct($params->product_id);

		$purchaseRepo = $this->getPurchaseRepo();
		$purchases = $purchaseRepo->findPurchasesForUser($visitor)
			->with('Product')
			->where('product_id', $product->product_id)
			->fetch();
		$purchasesGrouped = $purchaseRepo->groupPurchasesByState($purchases);

		$viewParams = [
			'product' => $product,
			'purchasesGrouped' => $purchasesGrouped,
			'purchaseStates' => $purchaseRepo->getPurchaseStates()
		];
		return $this->view('XR\PM:Product\ProductPurchases', 'xr_pm_product_product_purchases', $viewParams);
	}

	public function actionTerms(ParameterBag $params)
	{
		$product = $this->assertViewableProduct($params->product_id);

		$terms = $product->terms_conditions ?: $this->options()->xr_pm_default_terms;

		$viewParams = [
			'product' => $product,
			'terms' => strtr($terms, [
				'{board_title}' => $this->options()->boardTitle
			])
		];
		return $this->view('XR\PM:Product\Terms', 'xr_pm_product_terms', $viewParams);
	}

	public function actionDownload(ParameterBag $params)
	{
		$product = $this->assertViewableProduct($params->product_id);

		if (!$product->canDownload($error))
		{
			return $this->error($error);
		}

		$visitor = \XF::visitor();

		if ($this->isPost())
		{
			$confirmed = $this->filter('confirmed', 'bool');
			if ($product->confirm_license && !$confirmed)
			{
				return $this->error(\XF::phrase('xr_pm_you_must_agree_to_terms_and_conditions_before_downloading'));
			}

			$purchaseVersion = $this->filter('purchase_version', 'str');
			list ($purchaseId, $versionId) = explode('|', $purchaseVersion, 2);

			/** @var \XR\PM\Entity\ProductPurchase $purchase */
			$purchase = $this->em()->find('XR\PM:ProductPurchase', $purchaseId);
			if (!$purchase)
			{
				return $this->notFound();
			}

			if (!$purchase->isDownloadable($error))
			{
				return $this->noPermission();
			}

			/** @var \XR\PM\Entity\Version $version */
			$version = $this->em()->find('XR\PM:Version', $versionId);
			if (!$version)
			{
				return $this->notFound();
			}

			$product = $purchase->Product;

			/** @var \XR\PM\Entity\Version[]|\XF\Mvc\Entity\ArrayCollection $versions */
			$versions = $product->Versions;
			$versions = $this->getVersionRepo()->filterAllowedVersionsForPurchase($versions, $purchase);

			if (!isset($versions[$version->product_version_id]))
			{
				return $this->noPermission();
			}

			$this->repository('XR\PM:Version')->logDownload($version, $purchase);

			/** @var \XF\ControllerPlugin\Attachment $attachPlugin */
			$attachPlugin = $this->plugin('XF:Attachment');

			return $attachPlugin->displayAttachment($version->Version);
		}
		else
		{
			$purchases = $this->repository('XR\PM:ProductPurchase')
				->findPurchasesForUser($visitor)
				->where('product_id', $product->product_id)
				->order('expiry_date', 'DESC')
				->fetch();

			if ($purchases->count() == 1)
			{
				return $this->rerouteController(__CLASS__, 'purchase-download', [
					'purchase_id' => $purchases->first()->purchase_id
				]);
			}
			else
			{
				$viewParams = [
					'product' => $product,
					'purchases' => $purchases
				];
				return $this->view('XR\PM:Product\Download', 'xr_pm_product_download', $viewParams);
			}
		}
	}

	/**
	 * @param \XR\PM\Entity\Product $product
	 *
	 * @return \XR\PM\Service\Purchase\Creator
	 */
	protected function setupPurchaseCreatorService(\XR\PM\Entity\Product $product)
	{
		return $this->service('XR\PM:Purchase\Creator', $product);
	}

	protected function finalizePurchaseCreatorService(\XR\PM\Service\Purchase\Creator $builder)
	{
	}

	public function actionBuy(ParameterBag $params)
	{
		$product = $this->assertViewableProduct($params->product_id);

		if (!$product->canPurchase($error))
		{
			return $this->noPermission($error);
		}

		$visitor = \XF::visitor();

		if (!$visitor->user_id)
		{
			return $this->rerouteController('XF:Register', 'index');
		}

		if ($visitor->user_state != 'valid')
		{
			return $this->noPermission();
		}

		if ($this->isPost())
		{
			$creator = $this->setupPurchaseCreatorService($product);

			$creator->setProductPrice($product->price, $product->currency);
			$creator->setPurchasableType('product');

			$extras = $this->filter('extras', 'array-uint');
			if ($extras)
			{
				$creator->setExtras($extras);
			}

			if ($product->canUseCoupons())
			{
				/** @var \XR\PM\ControllerPlugin\Coupon $couponPlugin */
				$couponPlugin = $this->plugin('XR\PM:Coupon');
				$couponData = $couponPlugin->getAppliedCouponsData($product, ['extra', 'product', 'purchase']);

				foreach ($couponData['newCoupons'] AS $coupon)
				{
					$creator->applyCoupon($coupon);
				}
			}

			if (!$creator->validate($errors))
			{
				return $this->error($errors);
			}

			$purchase = $creator->save();

			$this->finalizePurchaseCreatorService($creator);

			if ($purchase->total_price > 0.00)
			{
				$this->request->set('purchase_id', $purchase->purchase_id);
				$this->request->set('payment_profile_id', $this->filter('payment_profile_id', 'uint'));

				return $this->rerouteController('XF:Purchase', 'index', [
					'purchasable_type_id' => 'xr_pm_product'
				]);
			}
			else
			{
				/** @var \XR\PM\Service\Purchase\Updater $updater */
				$updater = $this->service('XR\PM:Purchase\Updater', $purchase);
				$updater->completePurchase();

				return $this->redirect($this->buildLink('products/purchase', $purchase));
			}
		}
		else
		{
			$profiles = $this->repository('XF:Payment')->getPaymentProfileOptionsData();

			if ($product->canUseCoupons())
			{
				/** @var \XR\PM\Repository\Coupon $couponRepo */
				$couponRepo = $this->repository('XR\PM:Coupon');

				$coupons = $couponRepo->findUsableCoupons(['product', 'purchase'])->fetch();
				$coupons = $couponRepo->filterUsable($coupons);

				if ($coupons->count())
				{
					$coupons = $coupons->filter(function(\XR\PM\Entity\Coupon $coupon) use ($product)
					{
						if (!$coupon->isAutoApplied())
						{
							return false;
						}

						if ($coupon->coupon_type == 'product' && !in_array($product->product_id, $coupon->coupon_product_ids))
						{
							return false;
						}

						return true;
					});
				}

				$couponIds = array_combine($coupons->keys(), $coupons->keys());
			}
			else
			{
				$coupons = [];
				$couponIds = [];
			}

			$viewParams = [
				'product' => $product,
				'profiles' => $profiles,
				'coupons' => $coupons,
				'couponIds' => $couponIds
			];
			return $this->view('XR\PM:Product\Buy', 'xr_pm_product_buy', $viewParams);
		}
	}

	public function actionBuyCouponChecker(ParameterBag $params)
	{
		$this->assertPostOnly();

		$product = $this->assertViewableProduct($params->product_id);

		/** @var \XR\PM\ControllerPlugin\Coupon $couponPlugin */
		$couponPlugin = $this->plugin('XR\PM:Coupon');
		$couponData = $couponPlugin->getAppliedCouponsData($product, ['extra', 'product', 'purchase']);

		$viewParams = [
			'newCoupons' => $couponData['newCoupons']
		];
		$reply = $this->view('XR\PM:Product\BuyCouponChecker', 'xr_pm_applied_coupons', $viewParams);

		$reply->setJsonParams([
			'coupons' => array_combine(array_keys($couponData['newCoupons']), array_keys($couponData['newCoupons'])),
			'discount' => $couponData['discount']
		]);

		return $reply;
	}

	protected function finalizeCouponCheckerReply(AbstractReply $reply)
	{
		$reply->setJsonParam('name', $this->filter('name', 'str'));
		return $reply;
	}

	public function actionField(ParameterBag $params)
	{
		$product = $this->assertProductExists($params->product_id);

		if (!$product->getValue('custom_fields'))
		{
			return $this->redirect($this->buildLink('products', $product));
		}

		/** @var \XF\CustomField\Set $fieldSet */
		$fieldSet = $product->custom_fields;
		$definitionSet = $fieldSet->getDefinitionSet()
			->filterGroup('tab_content')
			->filterWithValue($fieldSet);

		$fieldId = $this->filter('field', 'str');

		if (!isset($definitionSet[$fieldId]))
		{
			return $this->redirect($this->buildLink('products', $product));
		}

		$definition = $fieldSet->getDefinition($fieldId);
		$fieldValue = $fieldSet->getFieldValue($fieldId);

		$viewParams = [
			'product' => $product,

			'fieldId' => $fieldId,
			'fieldDefinition' => $definition,
			'fieldValue' => $fieldValue
		];
		return $this->view('XR\PM:Product\Field', 'xr_pm_product_field', $viewParams);
	}

	public function actionPurchases()
	{
		$visitor = \XF::visitor();

		$purchaseRepo = $this->getPurchaseRepo();
		$purchases = $purchaseRepo->findPurchasesForUser($visitor)->fetch();
		$purchasesGrouped = $purchaseRepo->groupPurchasesByState($purchases);

		$productRepo = $this->getProductRepo();
		$products = $purchases->pluckNamed('Product');
		$products = $productRepo->addExtrasToProducts($products);

		$viewParams = [
			'products' => $products,
			'purchasesGrouped' => $purchasesGrouped,
			'purchaseStates' => $purchaseRepo->getPurchaseStates()
		];
		return $this->view('XR\PM:Product\Purchases', 'xr_pm_product_purchases', $viewParams);
	}

	public function actionPurchase(ParameterBag $params)
	{
		$purchase = $this->assertPurchaseExists($params->purchase_id);

		if ($purchase->parent_purchase_key)
		{
			$purchase = $this->em()->findOne('XR\PM:ProductPurchase', [
				'purchase_key' => $purchase->parent_purchase_key
			]);
		}

		if ($purchase->purchase_state == 'pending')
		{
			return $this->message(\XF::phrase('xr_pm_if_you_have_recently_paid_for_this_purchase_thank_you'));
		}
		else if ($purchase->purchase_state == 'revoked')
		{
			return $this->noPermission();
		}

		$linkParams = [];

		$renewPurchase = $this->filter('renewal_purchase', 'bool');
		if ($renewPurchase)
		{
			$linkParams = [
				'renewal_purchase' => 1
			];
		}

		$extrasPurchase = $this->filter('extras_purchase', 'bool');
		if ($extrasPurchase)
		{
			$linkParams = [
				'extras_purchase' => 1
			];
			$renewPurchase = false;
		}

		$this->assertCanonicalUrl($this->buildLink('products/purchase', $purchase, $linkParams));

		$viewParams = [
			'purchase' => $purchase,
			'purchaseStates' => $this->getPurchaseRepo()->getPurchaseStates(),
			'renewPurchase' => $renewPurchase,
			'extrasPurchase' => $extrasPurchase
		];
		return $this->view('XR\PM:Purchase\View', 'xr_pm_purchase_view', $viewParams);
	}

	public function actionPurchaseDownload(ParameterBag $params)
	{
		$purchase = $this->assertPurchaseExists($params->purchase_id);
		if (!$purchase->isDownloadable($error))
		{
			return $this->noPermission($error);
		}

		$product = $purchase->Product;

		/** @var \XR\PM\Entity\Version[]|\XF\Mvc\Entity\ArrayCollection $versions */
		$versions = $product->Versions;
		$versions = $this->getVersionRepo()->filterAllowedVersionsForPurchase($versions, $purchase);

		if (!$versions->count())
		{
			return $this->error(\XF::phrase('xr_pm_there_no_valid_versions_available_for_this_purchase'));
		}

		if ($this->isPost())
		{
			$confirmed = $this->filter('confirmed', 'bool');
			if ($product->confirm_license && !$confirmed)
			{
				return $this->error(\XF::phrase('xr_pm_you_must_agree_to_terms_and_conditions_before_downloading'));
			}

			$versionId = $this->filter('product_version_id', 'uint');
			if (!isset($versions[$versionId]))
			{
				return $this->noPermission();
			}

			$version = $versions[$versionId];

			$this->repository('XR\PM:Version')->logDownload($version, $purchase);

			/** @var \XF\ControllerPlugin\Attachment $attachPlugin */
			$attachPlugin = $this->plugin('XF:Attachment');

			return $attachPlugin->displayAttachment($version->Version);
		}
		else
		{
			$firstVersionId = $versions->first()->product_version_id;
			$versions = $versions->pluckNamed('version_string', 'product_version_id');

			$viewParams = [
				'purchase' => $purchase,
				'product' => $product,
				'versions' => $versions,
				'firstVersionId' => $firstVersionId
			];
			return $this->view('XR\PM:Purchase\Download', 'xr_pm_purchase_download', $viewParams);
		}
	}

	/**
	 * @param \XR\PM\Entity\ProductPurchase $purchase
	 *
	 * @return \XR\PM\Service\Purchase\Activator
	 */
	protected function setupActivatorService(\XR\PM\Entity\ProductPurchase $purchase)
	{
		/** @var \XR\PM\Service\Purchase\Activator $activator */
		$activator = $this->service('XR\PM:Purchase\Activator', $purchase);

		$activator->setLicenseDetails(
			$this->filter('license_name', 'str'),
			$this->filter('license_url', 'str')
		);

		return $activator;
	}

	protected function finalizeActivatorService(\XR\PM\Service\Purchase\Activator $activator)
	{
	}

	public function actionPurchaseActivate(ParameterBag $params)
	{
		$purchase = $this->assertPurchaseExists($params->purchase_id);
		$product = $this->assertViewableProduct($purchase->product_id);

		if (!$purchase->isActivatable($error))
		{
			return $this->noPermission($error);
		}

		if ($this->isPost())
		{
			$activator = $this->setupActivatorService($purchase);

			if (!$activator->validate($errors))
			{
				return $this->error($errors);
			}

			$activator->save();

			$this->finalizeActivatorService($activator);

			return $this->redirect($this->buildLink('products/purchase', $purchase));
		}
		else
		{
			$viewParams = [
				'purchase' => $purchase,
				'product' => $product
			];
			return $this->view('XR\PM:Purchase\Activate', 'xr_pm_purchase_activate', $viewParams);
		}
	}

	public function actionPurchaseRenew(ParameterBag $params)
	{
		$purchase = $this->assertPurchaseExists($params->purchase_id);
		$product = $this->assertViewableProduct($purchase->product_id);

		if (!$purchase->doesRequireRenewal($error) && !$purchase->isRenewableEarly())
		{
			return $this->noPermission($error);
		}

		if ($this->isPost())
		{
			$creator = $this->setupPurchaseCreatorService($product);

			$creator->setPurchasableType('renewal', $purchase->purchase_key);
			$creator->setProductPrice($purchase->renew_price, $purchase->purchase_currency);

			if ($product->canUseCoupons())
			{
				/** @var \XR\PM\ControllerPlugin\Coupon $couponPlugin */
				$couponPlugin = $this->plugin('XR\PM:Coupon');
				$couponData = $couponPlugin->getAppliedCouponsData($product, ['renewal', 'purchase'], $purchase->renew_price, $purchase->purchase_currency);

				foreach ($couponData['newCoupons'] AS $coupon)
				{
					$creator->applyCoupon($coupon);
				}
			}

			if (!$creator->validate($errors))
			{
				return $this->error($errors);
			}

			/** @var \XR\PM\Entity\ProductPurchase $purchase */
			$purchase = $creator->save();

			$this->finalizePurchaseCreatorService($creator);

			if ($purchase->total_price > 0.00)
			{
				$this->request->set('purchase_id', $purchase->purchase_id);
				$this->request->set('payment_profile_id', $this->filter('payment_profile_id', 'uint'));

				return $this->rerouteController('XF:Purchase', 'index', [
					'purchasable_type_id' => 'xr_pm_product'
				]);
			}
			else
			{
				/** @var \XR\PM\Service\Purchase\Updater $updater */
				$updater = $this->service('XR\PM:Purchase\Updater', $purchase);
				$updater->renewPurchase();

				return $this->redirect($this->buildLink('products/purchase', $purchase, [
					'renewal_purchase' => 1
				]));
			}
		}
		else
		{
			$profiles = $this->repository('XF:Payment')->getPaymentProfileOptionsData();

			if ($product->canUseCoupons())
			{
				/** @var \XR\PM\Repository\Coupon $couponRepo */
				$couponRepo = $this->repository('XR\PM:Coupon');

				$coupons = $couponRepo->findUsableCoupons(['renewal', 'purchase'])->fetch();
				$coupons = $couponRepo->filterUsable($coupons);

				if ($coupons->count())
				{
					$coupons = $coupons->filter(function(\XR\PM\Entity\Coupon $coupon) use ($product)
					{
						if (!$coupon->isAutoApplied())
						{
							return false;
						}

						if ($coupon->coupon_type == 'renewal' && !in_array($product->product_id, $coupon->coupon_product_ids))
						{
							return false;
						}

						return true;
					});
				}

				$couponIds = array_combine($coupons->keys(), $coupons->keys());
			}
			else
			{
				$coupons = [];
				$couponIds = [];
			}

			$viewParams = [
				'purchase' => $purchase,
				'product' => $product,
				'profiles' => $profiles,
				'coupons' => $coupons,
				'couponIds' => $couponIds
			];
			return $this->view('XR\PM:Purchase\Renew', 'xr_pm_purchase_renew', $viewParams);
		}
	}

	public function actionPurchaseRenewCouponChecker(ParameterBag $params)
	{
		$this->assertPostOnly();

		$purchase = $this->assertPurchaseExists($params->purchase_id);
		$product = $purchase->Product;

		/** @var \XR\PM\ControllerPlugin\Coupon $couponPlugin */
		$couponPlugin = $this->plugin('XR\PM:Coupon');
		$couponData = $couponPlugin->getAppliedCouponsData($product, ['renewal', 'purchase'], $purchase->renew_price, $purchase->purchase_currency, array_keys($purchase->extras));

		$viewParams = [
			'newCoupons' => $couponData['newCoupons']
		];
		$reply = $this->view('XR\PM:Purchase\RenewCouponChecker', 'xr_pm_applied_coupons', $viewParams);

		$reply->setJsonParams([
			'coupons' => array_combine(array_keys($couponData['newCoupons']), array_keys($couponData['newCoupons'])),
			'discount' => $couponData['discount']
		]);

		return $reply;
	}

	public function actionPurchaseExtras(ParameterBag $params)
	{
		$purchase = $this->assertPurchaseExists($params->purchase_id);
		$product = $this->assertViewableProduct($purchase->product_id);

		if (!$purchase->canPurchaseExtras($error))
		{
			return $this->noPermission($error);
		}

		if ($this->isPost())
		{
			$creator = $this->setupPurchaseCreatorService($product);

			$creator->setProductPrice(0.00, $product->currency);
			$creator->setPurchasableType('extras', $purchase->purchase_key);

			$extras = $this->filter('extras', 'array-uint');
			if ($extras)
			{
				$creator->setExtras($extras);
			}

			if ($product->canUseCoupons())
			{
				/** @var \XR\PM\ControllerPlugin\Coupon $couponPlugin */
				$couponPlugin = $this->plugin('XR\PM:Coupon');
				$couponData = $couponPlugin->getAppliedCouponsData($product, ['extra', 'purchase'], 0.00, $purchase->purchase_currency);

				foreach ($couponData['newCoupons'] AS $coupon)
				{
					$creator->applyCoupon($coupon);
				}
			}

			if (!$creator->validate($errors))
			{
				return $this->error($errors);
			}

			/** @var \XR\PM\Entity\ProductPurchase $purchase */
			$purchase = $creator->save();

			$this->finalizePurchaseCreatorService($creator);

			if ($purchase->total_price > 0.00)
			{
				$this->request->set('purchase_id', $purchase->purchase_id);
				$this->request->set('payment_profile_id', $this->filter('payment_profile_id', 'uint'));

				return $this->rerouteController('XF:Purchase', 'index', [
					'purchasable_type_id' => 'xr_pm_product'
				]);
			}
			else
			{
				/** @var \XR\PM\Service\Purchase\Updater $updater */
				$updater = $this->service('XR\PM:Purchase\Updater', $purchase);
				$updater->addExtras();

				return $this->redirect($this->buildLink('products/purchase', $purchase, [
					'extras_purchase' => 1
				]));
			}
		}
		else
		{
			$profiles = $this->repository('XF:Payment')->getPaymentProfileOptionsData();
			$extraId = $this->filter('extra_id', 'uint');

			if ($product->canUseCoupons())
			{
				/** @var \XR\PM\Repository\Coupon $couponRepo */
				$couponRepo = $this->repository('XR\PM:Coupon');

				$coupons = $couponRepo->findUsableCoupons(['extra', 'purchase'])->fetch();
				$coupons = $couponRepo->filterUsable($coupons);

				if ($coupons->count())
				{
					$coupons = $coupons->filter(function(\XR\PM\Entity\Coupon $coupon) use ($extraId)
					{
						if (!$coupon->isAutoApplied())
						{
							return false;
						}

						if ($coupon->coupon_type == 'extra' && !in_array($extraId, $coupon->coupon_extra_ids))
						{
							return false;
						}

						return true;
					});
				}

				$couponIds = array_combine($coupons->keys(), $coupons->keys());
			}
			else
			{
				$coupons = [];
				$couponIds = [];
			}

			$viewParams = [
				'purchase' => $purchase,
				'product' => $product,
				'profiles' => $profiles,
				'extraId' => $extraId,
				'coupons' => $coupons,
				'couponIds' => $couponIds
			];
			return $this->view('XR\PM:Purchase\Extras', 'xr_pm_purchase_extras', $viewParams);
		}
	}

	public function actionPurchaseExtrasCouponChecker(ParameterBag $params)
	{
		$this->assertPostOnly();

		$purchase = $this->assertPurchaseExists($params->purchase_id);
		$product = $purchase->Product;

		/** @var \XR\PM\ControllerPlugin\Coupon $couponPlugin */
		$couponPlugin = $this->plugin('XR\PM:Coupon');

		// note: price passed in as string rather than float so it doesn't get overwritten
		$couponData = $couponPlugin->getAppliedCouponsData(
			$product, ['extra', 'purchase'], '0.00', $purchase->purchase_currency
		);

		$viewParams = [
			'newCoupons' => $couponData['newCoupons']
		];
		$reply = $this->view('XR\PM:Purchase\ExtrasCouponChecker', 'xr_pm_applied_coupons', $viewParams);

		$reply->setJsonParams([
			'coupons' => array_combine(array_keys($couponData['newCoupons']), array_keys($couponData['newCoupons'])),
			'discount' => $couponData['discount']
		]);

		return $reply;
	}

	/**
	 * @return \XR\PM\Repository\Product
	 */
	protected function getProductRepo()
	{
		return $this->repository('XR\PM:Product');
	}

	/**
	 * @return \XR\PM\Repository\ProductPurchase
	 */
	protected function getPurchaseRepo()
	{
		return $this->repository('XR\PM:ProductPurchase');
	}

	/**
	 * @return \XR\PM\Repository\Version
	 */
	protected function getVersionRepo()
	{
		return $this->repository('XR\PM:Version');
	}

	/**
	 * @param $id
	 * @param null $with
	 * @param null $phraseKey
	 *
	 * @return \XR\PM\Entity\Product
	 *
	 * @throws \XF\Mvc\Reply\Exception
	 */
	protected function assertProductExists($id, $with = null, $phraseKey = null)
	{
		return $this->assertRecordExists('XR\PM:Product', $id, $with, $phraseKey);
	}

	protected function assertViewableProduct($id, $with = null, $phraseKey = null)
	{
		$product = $this->assertProductExists($id, $with, $phraseKey);

		if (!$product->canView($error))
		{
			throw $this->exception($this->error($error));
		}

		return $product;
	}

	/**
	 * @param $id
	 * @param null $with
	 * @param null $phraseKey
	 *
	 * @return \XR\PM\Entity\Category
	 *
	 * @throws \XF\Mvc\Reply\Exception
	 */
	protected function assertCategoryExists($id, $with = null, $phraseKey = null)
	{
		return $this->assertRecordExists('XR\PM:Category', $id, $with, $phraseKey);
	}

	/**
	 * @param $id
	 * @param null $with
	 * @param null $phraseKey
	 *
	 * @return \XR\PM\Entity\ProductPurchase
	 *
	 * @throws \XF\Mvc\Reply\Exception
	 */
	protected function assertPurchaseExists($id, $with = null, $phraseKey = null)
	{
		/** @var \XR\PM\Entity\ProductPurchase $purchase */
		$purchase = $this->assertRecordExists('XR\PM:ProductPurchase', $id, $with, $phraseKey);

		if (!$purchase->canView($error))
		{
			throw $this->exception($this->noPermission($error));
		}

		$this->getPurchaseRepo()->expirePurchaseIfNeeded($purchase);

		return $purchase;
	}

	protected function assertVersionExists($id, $with = null, $phraseKey = null)
	{
		return $this->assertRecordExists('XR\PM:Version', $id, $with, $phraseKey);
	}

	public static function getActivityDetails(array $activities)
	{
		return self::getActivityDetailsForContent(
			$activities, \XF::phrase('xr_pm_viewing_product'), 'product_id',
			function(array $ids)
			{
				$products = \XF::em()->findByIds(
					'XR\PM:Product',
					$ids,
					['Category', 'Category.Permissions|' . \XF::visitor()->permission_combination_id]
				);

				$router = \XF::app()->router('public');
				$data = [];

				foreach ($products->filterViewable() AS $id => $product)
				{
					$data[$id] = [
						'title' => $product->product_title,
						'url' => $router->buildLink('products', $products)
					];
				}

				return $data;
			}
		);
	}
}