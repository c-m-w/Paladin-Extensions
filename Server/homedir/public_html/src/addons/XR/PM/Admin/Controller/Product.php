<?php

namespace XR\PM\Admin\Controller;

use XF\Admin\Controller\AbstractController;
use XF\Mvc\ParameterBag;

class Product extends AbstractController
{
	protected function preDispatchController($action, ParameterBag $params)
	{
		$this->assertAdminPermission('xr_pm_products');
	}

	public function actionIndex(ParameterBag $params)
	{
		$productRepo = $this->repository('XR\PM:Product');
		$productFinder = $productRepo->findProductsForList(null, false);

		// TODO: Pagination

		$viewParams = [
			'products' => $productFinder->fetch(),
			'total' => $productFinder->total()
		];
		return $this->view('XR\PM:Product\Index', 'xr_pm_product_index', $viewParams);
	}

	protected function productAddEdit(\XR\PM\Entity\Product $product)
	{
		$categoryRepo = $this->repository('XR\PM:Category');
		$categories = $categoryRepo->getCategoryOptionsData();
		if (!$categories)
		{
			throw $this->exception($this->error(\XF::phrase('xr_pm_please_create_at_least_one_category_before_continuing')));
		}

		$paymentRepo = $this->repository('XF:Payment');
		$paymentProfiles = $paymentRepo->findPaymentProfilesForList()->fetch();
		if (!$paymentProfiles)
		{
			throw $this->exception($this->error(\XF::phrase('please_create_at_least_one_payment_profile_before_continuing')));
		}

		/** @var \XF\Repository\Attachment $attachmentRepo */
		$attachmentRepo = $this->repository('XF:Attachment');
		$imageAttachData = $attachmentRepo->getEditorData('xr_pm_product_image', $product ?: null);

		$extraRepo = $this->getExtraRepo();
		$extras = $extraRepo->findExtrasForList()->fetch();

		$viewParams = [
			'categories' => $categories,
			'product' => $product,
			'version' => $product->isInsert()
				? $product->getNewVersion()
				: $product->getRelationOrDefault('Version'),
			'imageAttachData' => $imageAttachData,
			'profiles' => $paymentProfiles,
			'totalProfiles' => $paymentProfiles->count(),
			'userGroups' => $this->repository('XF:UserGroup')->getUserGroupTitlePairs(),
			'extras' => $extras
		];
		if ($product->isInsert())
		{
			$productAttachData = $attachmentRepo->getEditorData('xr_pm_product_version', $product->Version ?: null);
			$thumbAttachData = $attachmentRepo->getEditorData('xr_pm_product_thumb', $product ?: null);
			$viewParams['productAttachData'] = $productAttachData;
			$viewParams['thumbAttachData'] = $thumbAttachData;
		}
		return $this->view('XR\PM:Product\Edit', 'xr_pm_product_edit', $viewParams);
	}

	public function actionEdit(ParameterBag $params)
	{
		$product = $this->assertProductExists($params->product_id);
		return $this->productAddEdit($product);
	}

	public function actionAdd()
	{
		/** @var \XR\PM\Entity\Product $product */
		$product = $this->em()->create('XR\PM:Product');
		return $this->productAddEdit($product);
	}

	protected function getProductInput()
	{
		$input = $this->filter([
			'product' => [
				'product_title' => 'str',
				'category_id' => 'uint',
				'product_tag_line' => 'str',
				'features' => 'array-str',
				'price' => 'str',
				'currency' => 'str',
				'renew_price' => 'str',
				'duration' => 'uint',
				'duration_unit' => 'str',
				'allow_early_extension' => 'bool',
				'payment_profile_ids' => 'array-uint',
				'user_group_ids' => 'array-str',
				'optional_extras' => 'array-uint',
				'confirm_license' => 'bool',
				'requires_activation' => 'bool',
				'active' => 'bool'
			],
			'version' => [
				'version_string' => 'str'
			],
			'custom_fields' => 'array'
		]);

		$input['product']['product_details'] = $this->plugin('XF:Editor')->fromInput('product.product_details');
		$input['product']['terms_conditions'] = $this->plugin('XF:Editor')->fromInput('product.terms_conditions');

		$input['product_attach_hash'] = $this->filter('product_attach_hash', 'str');
		$input['thumb_attach_hash'] = $this->filter('thumb_attach_hash', 'str');
		$input['image_attach_hash'] = $this->filter('image_attach_hash', 'str');

		return $input;
	}

	protected function setupProductCreate()
	{
		$input = $this->getProductInput();
		$product = $input['product'];
		$version = $input['version'];

		$category = $this->em()->find('XR\PM:Category', $product['category_id']);
		if (!$category)
		{
				throw $this->exception($this->error(\XF::phrase('xr_pm_please_select_category')));
		}

		/** @var \XR\PM\Service\Product\Creator $creator */
		$creator = $this->service('XR\PM:Product\Creator', $category);

		$creator->setVersion($version['version_string']);
		$creator->setVersionAttachmentHash($input['product_attach_hash']);

		$creator->setThumbAttachmentHash($input['thumb_attach_hash']);
		$creator->setImageAttachmentHash($input['image_attach_hash']);
		$creator->setProductDetails(
			$product['product_title'],
			$product['product_details'],
			$product['product_tag_line']
		);

		$creator->setFeatures($product['features']);

		$creator->setPurchasePrice($product['price'], $product['currency']);
		$creator->setRenewalPrice($product['renew_price']);
		$creator->setSupportDuration($product['duration'], $product['duration_unit']);
		$creator->setEarlyExtension($product['allow_early_extension']);

		$creator->setAllowedPaymentProfiles($product['payment_profile_ids']);

		$creator->setUserGroups($product['user_group_ids']);

		$creator->setOptionalExtras($product['optional_extras']);

		$creator->setLicenseOptions(
			$product['terms_conditions'],
			$product['confirm_license'],
			$product['requires_activation']
		);

		$creator->setActive($product['active']);

		$creator->setCustomFields($input['custom_fields']);

		return $creator;
	}

	protected function finalizeProductCreate(\XR\PM\Service\Product\Creator $creator)
	{
	}

	protected function setupProductEdit(\XR\PM\Entity\Product $product)
	{
		$input = $this->getProductInput();

		$category = $this->em()->find('XR\PM:Category', $input['product']['category_id']);
		if (!$category)
		{
				throw $this->exception($this->error(\XF::phrase('xr_pm_please_select_category')));
		}

		/** @var \XR\PM\Service\Product\Editor $editor */
		$editor = $this->service('XR\PM:Product\Editor', $product);

		$editor->setCategory($category);

		$editor->setVersion($input['version']['version_string']);

		$editor->setImageAttachmentHash($input['image_attach_hash']);
		$editor->setProductDetails(
			$input['product']['product_title'],
			$input['product']['product_details'],
			$input['product']['product_tag_line']
		);

		$editor->setFeatures($input['product']['features']);

		$editor->setPurchasePrice($input['product']['price'], $input['product']['currency']);
		$editor->setRenewalPrice($input['product']['renew_price']);
		$editor->setSupportDuration($input['product']['duration'], $input['product']['duration_unit']);
		$editor->setEarlyExtension($input['product']['allow_early_extension']);

		$editor->setAllowedPaymentProfiles($input['product']['payment_profile_ids']);

		$editor->setUserGroups($input['product']['user_group_ids']);

		$editor->setOptionalExtras($input['product']['optional_extras']);

		$editor->setLicenseOptions(
			$input['product']['terms_conditions'],
			$input['product']['confirm_license'],
			$input['product']['requires_activation']
		);

		$editor->setActive($input['product']['active']);

		$editor->setCustomFields($input['custom_fields']);

		return $editor;
	}

	protected function finalizeProductEdit(\XR\PM\Service\Product\Editor $editor)
	{
	}

	public function actionSave(ParameterBag $params)
	{
		$this->assertPostOnly();

		if ($params->product_id)
		{
			$product = $this->assertProductExists($params->product_id);

			$editor = $this->setupProductEdit($product);

			if (!$editor->validate($errors))
			{
				return $this->error($errors);
			}

			$editor->save();
			$this->finalizeProductEdit($editor);
		}
		else
		{
			$creator = $this->setupProductCreate();

			if (!$creator->validate($errors))
			{
				return $this->error($errors);
			}

			$creator->save();
			$this->finalizeProductCreate($creator);
		}

		return $this->redirect($this->buildLink('product-manager/products'));
	}

	/**
	 * @param \XR\PM\Entity\Product $product
	 *
	 * @return \XR\PM\Service\Version\Creator
	 */
	protected function setupVersionCreator(\XR\PM\Entity\Product $product)
	{
		/** @var \XR\PM\Service\Version\Creator $creator */
		$creator = $this->service('XR\PM:Version\Creator', $product);

		$versionString = $this->filter('version_string', 'str');
		$versionDetails = $this->plugin('XF:Editor')->fromInput('version_details');

		$creator->setVersionDetails($versionString, $versionDetails);

		$attachmentHash = $this->filter('product_attach_hash', 'str');
		$creator->setVersionAttachmentHash($attachmentHash);

		$changelogs = $this->filter('changelog', 'array-str');
		$creator->setChangelogItems($changelogs);

		$isUnsupported = $this->filter('is_unsupported', 'bool');
		$creator->setIsUnsupported($isUnsupported);

		$sendNotifications = $this->filter('send_notifications', 'array-str');
		$creator->setSendNotifications($sendNotifications);

		$nodeId = $this->filter('node_id', 'uint');
		if ($nodeId)
		{
			$forum = $this->assertRecordExists('XF:Forum', $nodeId);
			$creator->setForum($forum);
		}

		return $creator;
	}

	protected function finalizeVersionCreator(\XR\PM\Service\Version\Creator $creator)
	{
		$creator->sendNotifications();
	}

	public function actionAddVersion(ParameterBag $params)
	{
		$product = $this->assertProductExists($params->product_id);

		if ($this->isPost())
		{
			$creator = $this->setupVersionCreator($product);

			if (!$creator->validate($errors))
			{
				return $this->error($errors);
			}

			$creator->save();

			$this->finalizeVersionCreator($creator);

			return $this->redirect($this->buildLink('product-manager/products/versions'));
		}
		else
		{
			$productAttachData = $this->repository('XF:Attachment')->getEditorData('xr_pm_product_version');

			$viewParams = [
				'product' => $product,
				'productAttachData' => $productAttachData,
				'forums' => $this->repository('XF:Node')->getNodeOptionsData(true, 'Forum')
			];
			return $this->view('XR\PM:Product\AddVersion', 'xr_pm_product_add_version', $viewParams);
		}
	}

	/**
	 * @param \XR\PM\Entity\Product $product
	 *
	 * @return \XR\PM\Service\Product\ThumbnailEditor
	 */
	protected function setupThumbnailEditorService(\XR\PM\Entity\Product $product)
	{
		return $this->service('XR\PM:Product\ThumbnailEditor', $product);
	}

	public function actionEditThumbnail(ParameterBag $params)
	{
		$product = $this->assertProductExists($params->product_id);

		if ($this->isPost())
		{
			$editor = $this->setupThumbnailEditorService($product);

			if ($this->request->exists('delete'))
			{
				$editor->deleteExistingAttachment();
			}
			else
			{
				$thumbAttachHash = $this->filter('thumb_attach_hash', 'str');
				if (!$thumbAttachHash)
				{
					return $this->error('No thumbnail attachment hash found. Try again.');
				}
				$editor->setThumbAttachmentHash($thumbAttachHash);
				$editor->save();
			}

			return $this->redirect($this->getDynamicRedirect());
		}
		else
		{
			$thumbAttachData = $this->repository('XF:Attachment')->getEditorData('xr_pm_product_thumb');

			$viewParams = [
				'product' => $product,
				'thumbAttachData' => $thumbAttachData
			];
			return $this->view('XR\PM:Product\EditThumbnail', 'xr_pm_product_edit_thumbnail', $viewParams);
		}
	}

	public function actionDelete(ParameterBag $params)
	{
		$product = $this->assertProductExists($params->product_id);
		if (!$product->preDelete())
		{
			return $this->error($product->getErrors());
		}

		if ($this->isPost())
		{
			$product->delete();
			return $this->redirect($this->buildLink('product-manager/products'));
		}
		else
		{
			$viewParams = [
				'product' => $product
			];
			return $this->view('XR\PM:Product\Delete', 'xr_pm_product_delete', $viewParams);
		}
	}

	public function actionToggle()
	{
		/** @var \XF\ControllerPlugin\Toggle $plugin */
		$plugin = $this->plugin('XF:Toggle');
		return $plugin->actionToggle('XR\PM:Product');
	}

	public function actionVersion(ParameterBag $params)
	{
		$versionRepo = $this->getVersionRepo();

		$versions = $versionRepo->findVersionsForList()->fetch();
		$products = $versions->pluckNamed('product_title', 'product_id');
		$groupedVersions = $versions->groupBy('product_id');

		$viewParams = [
			'products' => $products,
			'groupedVersions' => $groupedVersions
		];
		return $this->view('XR\PM:Version\List', 'xr_pm_version_list', $viewParams);
	}

	/**
	 * @param \XR\PM\Entity\Version $version
	 *
	 * @return \XR\PM\Service\Version\Editor
	 */
	protected function setupVersionEditorService(\XR\PM\Entity\Version $version)
	{
		return $this->service('XR\PM:Version\Editor', $version);
	}


	public function actionVersionEdit(ParameterBag $params)
	{
		$version = $this->assertVersionExists($params->product_version_id);

		if ($this->isPost())
		{
			$editor = $this->setupVersionEditorService($version);

			$versionString = $this->filter('version_string', 'str');
			$versionDetails = $this->plugin('XF:Editor')->fromInput('version_details');

			$editor->setVersionDetails($versionString, $versionDetails);

			$attachmentHash = $this->filter('product_attach_hash', 'str');
			if (!$attachmentHash)
			{
				return $this->error('No product attachment hash found. Try again.');
			}
			$editor->setVersionAttachmentHash($attachmentHash);

			$changelogs = $this->filter('changelog', 'array-str');
			$editor->setChangelogItems($changelogs);

			$isUnsupported = $this->filter('is_unsupported', 'bool');
			$editor->setIsUnsupported($isUnsupported);

			$editor->save();

			return $this->redirect($this->getDynamicRedirect());
		}
		else
		{
			$productAttachData = $this->repository('XF:Attachment')->getEditorData('xr_pm_product_version');

			$viewParams = [
				'version' => $version,
				'productAttachData' => $productAttachData
			];
			return $this->view('XR\PM:Version\Edit', 'xr_pm_version_edit', $viewParams);
		}
	}

	public function actionVersionDelete(ParameterBag $params)
	{
		$version = $this->assertVersionExists($params->product_version_id);
		if (!$version->preDelete())
		{
			return $this->error($version->getErrors());
		}

		if ($this->isPost())
		{
			$version->delete();
			return $this->redirect($this->buildLink('product-manager/products/versions'));
		}
		else
		{
			$viewParams = [
				'version' => $version
			];
			return $this->view('XR\PM:Version\Delete', 'xr_pm_version_delete', $viewParams);
		}
	}

	public function actionVersionDownloadLog(ParameterBag $params)
	{
		$version = $this->assertVersionExists($params->product_version_id);

		$page = $this->filterPage();
		$perPage = 20;

		$versionRepo = $this->getVersionRepo();
		$downloads = $versionRepo
			->findDownloadLogsForVersion($version->product_version_id)
			->limitByPage($page, $perPage, 1)
			->fetch();

		$hasNext = false;
		if ($downloads->count() > $perPage)
		{
			$hasNext = true;
			$downloads = $downloads->slice(0, $perPage);
		}

		if (!$downloads->count())
		{
			return $this->message(\XF::phrase('xr_pm_no_one_has_downloaded_this_version_yet'));
		}

		$viewParams = [
			'version' => $version,
			'downloads' => $downloads,
			'hasNext' => $hasNext,
			'page' => $page
		];
		return $this->view('XR\PM:Version\DownloadLog', 'xr_pm_version_download_log', $viewParams);
	}

	public function actionExtra()
	{
		$extraRepo = $this->getExtraRepo();

		$extras = $extraRepo->findExtrasForList()->fetch();

		$viewParams = [
			'extras' => $extras
		];
		return $this->view('XR\PM:Extra\List', 'xr_pm_extra_list', $viewParams);
	}

	protected function extraAddEdit(\XR\PM\Entity\Extra $extra)
	{
		$extraAttachData = $this->repository('XF:Attachment')->getEditorData('xr_pm_product_extra');

		$products = $this->getProductRepo()->findProductsForList()->fetch()->pluckNamed('product_title', 'product_id');

		$productIds = [];
		$productExtras = $extra->ProductExtras;
		if ($productExtras)
		{
			$productIds = $productExtras->pluckNamed('product_id');
		}

		$viewParams = [
			'extra' => $extra,
			'userGroups' => $this->repository('XF:UserGroup')->getUserGroupTitlePairs(),
			'extraAttachData' => $extraAttachData,
			'products' => $products,
			'productIds' => $productIds
		];
		return $this->view('XR\PM:Extra\Edit', 'xr_pm_extra_edit', $viewParams);
	}

	public function actionExtraEdit(ParameterBag $params)
	{
		$extra = $this->assertExtraExists($params->extra_id);
		return $this->extraAddEdit($extra);
	}

	public function actionExtraAdd()
	{
		$extra = $this->em()->create('XR\PM:Extra');
		return $this->extraAddEdit($extra);
	}

	protected function getExtraInput()
	{
		$input = $this->filter([
			'extra_title' => 'str',
			'extra_description' => 'str',
			'extra_price' => 'str',
			'extra_renew_price' => 'str',
			'extra_reward' => 'str',
			'extra_user_group_id' => 'str',
			'extra_attach_hash' => 'str',
			'product_ids' => 'array-uint'
		]);

		if ($input['extra_reward'] == 'instructions')
		{
			$input['instructions'] = $this->plugin('XF:Editor')->fromInput('instructions');
		}

		return $input;
	}

	protected function setupExtraEditorService(\XR\PM\Entity\Extra $extra)
	{
		$input = $this->getExtraInput();

		/** @var \XR\PM\Service\Extra\Editor $editor */
		$editor = $this->service('XR\PM:Extra\Editor', $extra);

		$editor->setDetails($input['extra_title'], $input['extra_description']);
		$editor->setPrice($input['extra_price']);

		if ($input['extra_renew_price'])
		{
			$editor->setRenewPrice($input['extra_renew_price']);
		}

		$editor->setRewardType($input['extra_reward']);
		switch ($input['extra_reward'])
		{
			case 'user_group':
				$editor->setRewardUserGroup($input['extra_user_group_id']);
				break;

			case 'file':
				$editor->setRewardFile($input['extra_attach_hash']);
				break;

			case 'instructions':
				$editor->setRewardInstructions($input['instructions']);
				break;
		}

		$editor->setProductIds($input['product_ids']);

		return $editor;
	}

	protected function finalizeExtraEditorService()
	{
	}

	protected function setupExtraCreatorService(\XR\PM\Entity\Extra $extra)
	{
		$input = $this->getExtraInput();

		/** @var \XR\PM\Service\Extra\Creator $creator */
		$creator = $this->service('XR\PM:Extra\Creator', $extra);

		$creator->setDetails($input['extra_title'], $input['extra_description']);
		$creator->setPrice($input['extra_price']);

		if ($input['extra_renew_price'])
		{
			$creator->setRenewPrice($input['extra_renew_price']);
		}

		$creator->setRewardType($input['extra_reward']);
		switch ($input['extra_reward'])
		{
			case 'user_group':
				$creator->setRewardUserGroup($input['extra_user_group_id']);
				break;

			case 'file':
				$creator->setRewardFile($input['extra_attach_hash']);
				break;

			case 'instructions':
				$creator->setRewardInstructions($input['instructions']);
				break;
		}

		$creator->setProductIds($input['product_ids']);

		return $creator;
	}

	protected function finalizeExtraCreatorService()
	{
	}

	public function actionExtraSave(ParameterBag $params)
	{
		$this->assertPostOnly();

		if ($params->extra_id)
		{
			$extra = $this->assertExtraExists($params->extra_id);
			$editor = $this->setupExtraEditorService($extra);
			
			if (!$editor->validate($errors))
			{
				return $this->error($errors);
			}
			
			$editor->save();
			
			$this->finalizeExtraEditorService();
		}
		else
		{
			$extra = $this->em()->create('XR\PM:Extra');
			$creator = $this->setupExtraCreatorService($extra);

			if (!$creator->validate($errors))
			{
				return $this->error($errors);
			}

			$creator->save();

			$this->finalizeExtraCreatorService();
		}

		return $this->redirect($this->buildLink('product-manager/products/extras'));
	}

	public function actionExtraDelete(ParameterBag $params)
	{
		$extra = $this->assertExtraExists($params->extra_id);
		if (!$extra->preDelete())
		{
			return $this->error($extra->getErrors());
		}

		if ($this->isPost())
		{
			$extra->delete();
			return $this->redirect($this->buildLink('product-manager/products/extras'));
		}
		else
		{
			$viewParams = [
				'extra' => $extra
			];
			return $this->view('XR\PM:Extra\Delete', 'xr_pm_extra_delete', $viewParams);
		}
	}

	public function actionCoupon()
	{
		$couponRepo = $this->getCouponRepo();

		$coupons = $couponRepo->findCouponsForList()->fetch();

		$viewParams = [
			'coupons' => $coupons
		];
		return $this->view('XR\PM:Coupon\List', 'xr_pm_coupon_list', $viewParams);
	}

	protected function couponAddEdit(\XR\PM\Entity\Coupon $coupon)
	{
		$products = $this->getProductRepo()->findProductsForList()->fetch()->pluckNamed('product_title', 'product_id');
		$extras = $this->getExtraRepo()->findExtrasForList()->fetch()->pluckNamed('extra_title', 'extra_id');

		$viewParams = [
			'coupon' => $coupon,
			'userGroups' => $this->repository('XF:UserGroup')->getUserGroupTitlePairs(),
			'products' => $products,
			'extras' => $extras
		];
		return $this->view('XR\PM:Coupon\Edit', 'xr_pm_coupon_edit', $viewParams);
	}

	public function actionCouponEdit(ParameterBag $params)
	{
		$coupon = $this->assertCouponExists($params->coupon_id);
		return $this->couponAddEdit($coupon);
	}

	public function actionCouponAdd()
	{
		$coupon = $this->em()->create('XR\PM:Coupon');
		return $this->couponAddEdit($coupon);
	}

	protected function getCouponInput()
	{
		return $this->filter([
			'coupon_title' => 'str',
			'coupon_description' => 'str',
			'coupon_code' => 'str',
			'coupon_type' => 'str',
			'renewal_coupon_type' => 'str',
			'coupon_usable_by' => 'str',
			'coupon_usable_by_ids' => 'array-int',
			'coupon_auto_assign_to' => 'str',
			'coupon_auto_assign_to_ids' => 'array-int',
			'coupon_product_ids' => 'array-uint',
			'coupon_extra_ids' => 'array-uint',
			'coupon_reduction' => 'uint',
			'coupon_unit' => 'str',
			'coupon_valid_to' => 'datetime',
			'coupon_set_limit' => 'bool',
			'coupon_limit' => 'uint',
			'active' => 'bool'
		]);
	}

	protected function setupCouponEditorService(\XR\PM\Entity\Coupon $coupon)
	{
		$input = $this->getCouponInput();

		/** @var \XR\PM\Service\Coupon\Editor $editor */
		$editor = $this->service('XR\PM:Coupon\Editor', $coupon);

		$editor->setDetails($input['coupon_title'], $input['coupon_description'], $input['coupon_code']);

		$ids = [];
		if ($input['coupon_type'] == 'product')
		{
			$ids = $input['coupon_product_ids'];
		}
		else if ($input['coupon_type'] == 'extra')
		{
			$ids = $input['coupon_extra_ids'];
		}
		else if ($input['coupon_type'] == 'renewal')
		{
			if ($input['renewal_coupon_type'] == 'all')
			{
				$ids = [];
			}
			else
			{
				$ids = $input['coupon_product_ids'];
			}
		}
		$editor->setCouponType($input['coupon_type'], $ids);

		$editor->setUsableBy($input['coupon_usable_by'], $input['coupon_usable_by_ids']);
		$editor->setAutoAssignTo($input['coupon_auto_assign_to'], $input['coupon_auto_assign_to_ids']);

		$editor->setDiscount($input['coupon_reduction'], $input['coupon_unit']);

		$editor->setLimit($input['coupon_set_limit'], $input['coupon_limit']);

		$editor->setDateLimit($input['coupon_valid_to']);

		$editor->setActive($input['active']);

		return $editor;
	}

	protected function finalizeCouponEditorService()
	{
	}

	protected function setupCouponCreatorService(\XR\PM\Entity\Coupon $coupon)
	{
		$input = $this->getCouponInput();

		/** @var \XR\PM\Service\Coupon\Creator $creator */
		$creator = $this->service('XR\PM:Coupon\Creator', $coupon);

		$creator->setDetails($input['coupon_title'], $input['coupon_description'], $input['coupon_code']);

		$ids = [];
		if ($input['coupon_type'] == 'product')
		{
			$ids = $input['coupon_product_ids'];
		}
		else if ($input['coupon_type'] == 'extra')
		{
			$ids = $input['coupon_extra_ids'];
		}
		else if ($input['coupon_type'] == 'renewal')
		{
			if ($input['renewal_coupon_type'] == 'all')
			{
				$ids = [];
			}
			else
			{
				$ids = $input['coupon_product_ids'];
			}
		}
		$creator->setCouponType($input['coupon_type'], $ids);

		$creator->setUsableBy($input['coupon_usable_by'], $input['coupon_usable_by_ids']);
		$creator->setAutoAssignTo($input['coupon_auto_assign_to'], $input['coupon_auto_assign_to_ids']);

		$creator->setDiscount($input['coupon_reduction'], $input['coupon_unit']);

		$creator->setLimit($input['coupon_set_limit'], $input['coupon_limit']);

		$creator->setDateLimit($input['coupon_valid_to']);

		$creator->setActive($input['active']);

		return $creator;
	}

	protected function finalizeCouponCreatorService()
	{
	}

	public function actionCouponSave(ParameterBag $params)
	{
		$this->assertPostOnly();

		if ($params->coupon_id)
		{
			$coupon = $this->assertCouponExists($params->coupon_id);
			$editor = $this->setupCouponEditorService($coupon);

			if (!$editor->validate($errors))
			{
				return $this->error($errors);
			}

			$editor->save();

			$this->finalizeCouponEditorService();
		}
		else
		{
			$coupon = $this->em()->create('XR\PM:Coupon');
			$creator = $this->setupCouponCreatorService($coupon);

			if (!$creator->validate($errors))
			{
				return $this->error($errors);
			}

			$creator->save();

			$this->finalizeCouponCreatorService();
		}

		return $this->redirect($this->buildLink('product-manager/products/coupons'));
	}

	public function actionCouponDelete(ParameterBag $params)
	{
		$coupon = $this->assertCouponExists($params->coupon_id);
		if (!$coupon->preDelete())
		{
			return $this->error($coupon->getErrors());
		}

		if ($this->isPost())
		{
			$coupon->delete();
			return $this->redirect($this->buildLink('product-manager/products/coupons'));
		}
		else
		{
			$viewParams = [
				'coupon' => $coupon
			];
			return $this->view('XR\PM:Coupon\Delete', 'xr_pm_coupon_delete', $viewParams);
		}
	}

	public function actionCouponToggle()
	{
		/** @var \XF\ControllerPlugin\Toggle $plugin */
		$plugin = $this->plugin('XF:Toggle');
		return $plugin->actionToggle('XR\PM:Coupon');
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
	 * @return \XR\PM\Entity\Version
	 *
	 * @throws \XF\Mvc\Reply\Exception
	 */
	protected function assertVersionExists($id, $with = null, $phraseKey = null)
	{
		return $this->assertRecordExists('XR\PM:Version', $id, $with, $phraseKey);
	}

	/**
	 * @param $id
	 * @param null $with
	 * @param null $phraseKey
	 *
	 * @return \XR\PM\Entity\Extra
	 *
	 * @throws \XF\Mvc\Reply\Exception
	 */
	protected function assertExtraExists($id, $with = null, $phraseKey = null)
	{
		return $this->assertRecordExists('XR\PM:Extra', $id, $with, $phraseKey);
	}

	/**
	 * @param $id
	 * @param null $with
	 * @param null $phraseKey
	 *
	 * @return \XR\PM\Entity\Coupon
	 *
	 * @throws \XF\Mvc\Reply\Exception
	 */
	protected function assertCouponExists($id, $with = null, $phraseKey = null)
	{
		return $this->assertRecordExists('XR\PM:Coupon', $id, $with, $phraseKey);
	}

	/**
	 * @return \XR\PM\Repository\Product
	 */
	protected function getProductRepo()
	{
		return $this->repository('XR\PM:Product');
	}

	/**
	 * @return \XR\PM\Repository\Version
	 */
	protected function getVersionRepo()
	{
		return $this->repository('XR\PM:Version');
	}

	/**
	 * @return \XR\PM\Repository\Extra
	 */
	protected function getExtraRepo()
	{
		return $this->repository('XR\PM:Extra');
	}

	/**
	 * @return \XR\PM\Repository\Coupon
	 */
	protected function getCouponRepo()
	{
		return $this->repository('XR\PM:Coupon');
	}
}