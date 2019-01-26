<?php

namespace XR\PM\Purchasable;

use XF\Payment\CallbackState;
use XF\Purchasable\AbstractPurchasable;
use XF\Purchasable\Purchase;

class Product extends AbstractPurchasable
{
	public function getTitle()
	{
		return \XF::phrase('xr_pm_xr_product_manager_product_purchase');
	}

	public function getPurchaseFromRequest(\XF\Http\Request $request, \XF\Entity\User $purchaser, &$error = null)
	{
		$profileId = $request->filter('payment_profile_id', 'uint');

		/** @var \XF\Entity\PaymentProfile $paymentProfile */
		$paymentProfile = \XF::em()->find('XF:PaymentProfile', $profileId);
		if (!$paymentProfile || !$paymentProfile->active)
		{
			$error = \XF::phrase('please_choose_valid_payment_profile_to_continue_with_your_purchase');
			return false;
		}

		$purchaseId = $request->filter('purchase_id', 'uint');

		/** @var \XR\PM\Entity\ProductPurchase $productPurchase */
		$productPurchase = \XF::em()->find('XR\PM:ProductPurchase', $purchaseId);
		if (!$productPurchase)
		{
			$error = \XF::phrase('this_item_cannot_be_purchased_at_moment');
			return false;
		}

		$product = $productPurchase->Product;
		if (!$product || !$product->active)
		{
			$error = \XF::phrase('this_item_cannot_be_purchased_at_moment');
			return false;
		}

		if (!in_array($profileId, $product->payment_profile_ids))
		{
			$error = \XF::phrase('selected_payment_profile_is_not_valid_for_this_purchase');
			return false;
		}

		return $this->getPurchaseObject($paymentProfile, $productPurchase, $purchaser);
	}

	protected function getTitleFromPurchasable(\XR\PM\Entity\ProductPurchase $productPurchase)
	{
		$title = \XF::phrase('xr_pm_purchase_x_y', ['purchase_key' => $productPurchase->purchase_key, 'product_title' => $productPurchase->Product->product_title])->render();
		if ($productPurchase->purchase_type == 'renewal')
		{
			$title .= ' - ' . \XF::phrase('xr_pm_renewal_for_x', ['purchase_key' => $productPurchase->parent_purchase_key]);
		}
		else if ($productPurchase->purchase_type == 'extras')
		{
			$title .= ' - ' . \XF::phrase('xr_pm_extras_for_x', ['purchase_key' => $productPurchase->parent_purchase_key]);
		}
		return $title;
	}

	public function getPurchasableFromExtraData(array $extraData)
	{
		$output = [
			'link' => '',
			'title' => '',
			'purchasable' => null
		];

		/** @var \XR\PM\Entity\ProductPurchase $productPurchase */
		$productPurchase = \XF::em()->find('XR\PM:ProductPurchase', $extraData['purchase_id']);
		if ($productPurchase)
		{
			$product = $productPurchase->Product;

			$output['link'] = \XF::app()->router('public')->buildLink('products', $product);
			$output['title'] = $this->getTitleFromPurchasable($productPurchase);
			$output['purchasable'] = $productPurchase;
		}
		return $output;
	}

	public function getPurchaseFromExtraData(array $extraData, \XF\Entity\PaymentProfile $paymentProfile, \XF\Entity\User $purchaser, &$error = null)
	{
		$productPurchase = $this->getPurchasableFromExtraData($extraData);
		if (!$productPurchase['purchasable'])
		{
			$error = \XF::phrase('this_item_cannot_be_purchased_at_moment');
			return false;
		}

		/** @var \XR\PM\Entity\Product $product */
		$product = $productPurchase['purchasable']->Product;
		if (!$product || !$product->active)
		{
			$error = \XF::phrase('this_item_cannot_be_purchased_at_moment');
			return false;
		}

		if (!in_array($paymentProfile->payment_profile_id, $product->payment_profile_ids))
		{
			$error = \XF::phrase('selected_payment_profile_is_not_valid_for_this_purchase');
			return false;
		}

		return $this->getPurchaseObject($paymentProfile, $productPurchase['purchasable'], $purchaser);
	}

	public function getPurchaseObject(\XF\Entity\PaymentProfile $paymentProfile, $purchasable, \XF\Entity\User $purchaser)
	{
		/** @var \XR\PM\Entity\ProductPurchase $purchasable */
		$product = $purchasable->Product;

		$purchase = new Purchase();

		$purchase->title = $this->getTitleFromPurchasable($purchasable);
		$purchase->description = $product->product_tag_line;
		$purchase->cost = $purchasable->total_price;
		$purchase->currency = $purchasable->purchase_currency;
		$purchase->recurring = false;
		$purchase->lengthAmount = $product->duration;
		$purchase->lengthUnit = $product->duration_unit;
		$purchase->purchaser = $purchaser;
		$purchase->paymentProfile = $paymentProfile;
		$purchase->purchasableTypeId = $this->purchasableTypeId;
		$purchase->purchasableId = $purchasable->purchase_id;
		$purchase->purchasableTitle = $product->product_title;
		$purchase->extraData = [
			'purchase_id' => $purchasable->purchase_id
		];

		$router = \XF::app()->router('public');

		if ($purchasable->purchase_type == 'renewal')
		{
			$linkParams = [
				'renewal_purchase' => 1
			];
		}
		else if ($purchasable->purchase_type == 'extras')
		{
			$linkParams = [
				'extras_purchase' => 1
			];
		}
		else
		{
			$linkParams = [];
		}

		$purchase->returnUrl = $router->buildLink('canonical:products/purchase', $purchasable, $linkParams);
		$purchase->cancelUrl = $router->buildLink('canonical:products', $product);

		return $purchase;
	}

	public function completePurchase(CallbackState $state)
	{
		$purchaseRequest = $state->getPurchaseRequest();
		$purchaseId = $purchaseRequest->extra_data['purchase_id'];

		$paymentResult = $state->paymentResult;

		/** @var \XR\PM\Entity\ProductPurchase $productPurchase */
		$productPurchase = \XF::em()->find(
			'XR\PM:ProductPurchase', $purchaseId, 'Product'
		);

		/** @var \XR\PM\Service\Purchase\Updater $updaterService */
		$updaterService = \XF::app()->service('XR\PM:Purchase\Updater', $productPurchase);

		switch ($paymentResult)
		{
			case CallbackState::PAYMENT_RECEIVED:
				if ($productPurchase->purchase_type == 'renewal')
				{
					$updaterService->renewPurchase();
				}
				else if ($productPurchase->purchase_type == 'extras')
				{
					$updaterService->addExtras();
				}
				else
				{
					$updaterService->completePurchase();
				}

				$state->logType = 'payment';
				$state->logMessage = 'Payment received, license enabled/extended.';
				break;

			case CallbackState::PAYMENT_REINSTATED:
				$updaterService->reinstatePurchase();

				$state->logType = 'payment';
				$state->logMessage = 'Reversal cancelled, license reinstated/extended.';
				break;
		}

		if ($purchaseRequest)
		{
			$extraData = $purchaseRequest->extra_data;
			$extraData['purchase_id'] = $productPurchase->purchase_id;
			$purchaseRequest->extra_data = $extraData;
			$purchaseRequest->save();
		}
	}

	public function reversePurchase(CallbackState $state)
	{
		$purchaseRequest = $state->getPurchaseRequest();

		$productPurchase = \XF::em()->find(
			'XR\PM:ProductPurchase', $purchaseRequest->extra_data['purchase_id'], 'Product'
		);

		/** @var \XR\PM\Service\Purchase\Updater $updaterService */
		$updaterService = \XF::app()->service('XR\PM:Purchase\Updater', $productPurchase);
		$updaterService->reversePurchase();

		$state->logType = 'cancel';
		$state->logMessage = 'Payment refunded/reversed, revoked.';
	}

	public function getPurchasablesByProfileId($profileId)
	{
		$db = \XF::db();
		$router = \XF::app()->router();

		try
		{
			$products = $db->fetchPairs('
				SELECT product_id, product_title
				FROM xf_xr_pm_product
				WHERE FIND_IN_SET(?, payment_profile_ids)
			', $profileId);
		}
		catch (\XF\Db\Exception $e)
		{
			return [];
		}

		$output = [];

		foreach ($products AS $productId => $productTitle)
		{
			$output['xr_pm_product_' . $productId] = [
				'title' => $productTitle,
				'link' => $router->buildLink('product-manager/products/edit', [
					'product_id' => $productId,
					'product_title' => $productTitle
				])
			];
		}

		return $output;
	}
}