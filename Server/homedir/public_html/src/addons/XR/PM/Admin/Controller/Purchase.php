<?php

namespace XR\PM\Admin\Controller;

use XF\Admin\Controller\AbstractController;
use XF\Mvc\FormAction;
use XF\Mvc\ParameterBag;
use XR\PM\Entity\ProductPurchase;

class Purchase extends AbstractController
{
	protected function preDispatchController($action, ParameterBag $params)
	{
		$this->assertAdminPermission('xr_pm_products');
	}

	public function actionIndex()
	{
		$criteria = $this->filter('criteria', 'array');
		$order = $this->filter('order', 'str');
		$direction = $this->filter('direction', 'str');

		$page = $this->filterPage();
		$perPage = 20;

		$searcher = $this->searcher('XR\PM:ProductPurchase', $criteria);

		if ($order && !$direction)
		{
			$direction = $searcher->getRecommendedOrderDirection($order);
		}

		$searcher->setOrder($order, $direction);

		$finder = $searcher->getFinder();
		$finder->with('Product', true);
		$finder->limitByPage($page, $perPage);

		$filter = $this->filter('_xfFilter', [
			'text' => 'str',
			'prefix' => 'bool'
		]);
		if (strlen($filter['text']))
		{
			$query = $finder->escapeLike($filter['text'], $filter['prefix'] ? '?%' : '%?%');

			$finder->whereOr([
				['purchase_key', 'LIKE', $query],
				['Product.product_title', 'LIKE', $query],
				['User.username', 'LIKE', $query],
				['username', 'LIKE', $query],
				['old_cart_key', 'LIKE', $query],
				['parent_purchase_key', 'LIKE', $query],
				['license_name', 'LIKE', $query],
				['license_url', 'LIKE', $query]
			]);
		}

		$total = $finder->total();
		$purchases = $finder->fetch();

		$this->assertValidPage($page, $perPage, $total, 'product-manager/purchases');

		$viewParams = [
			'purchases' => $purchases,

			'total' => $total,
			'page' => $page,
			'perPage' => $perPage,

			'criteria' => $searcher->getFilteredCriteria(),
			'filter' => $filter['text'],
			'sortOptions' => $searcher->getOrderOptions(),
			'order' => $order,
			'direction' => $direction
		];
		return $this->view('XR\PM:Purchase\List', 'xr_pm_purchase_list', $viewParams);
	}

	public function actionTransfer(ParameterBag $params)
	{
		$purchase = $this->assertPurchaseExists($params->purchase_id, 'Product');

		if (!$purchase->isTransferrable())
		{
			return $this->noPermission();
		}

		if ($this->isPost())
		{
			$username = $this->filter('username', 'str');

			$user = $this->em()->findOne('XF:User', ['username' => $username]);
			if (!$user)
			{
				return $this->notFound(\XF::phrase('no_matching_users_were_found'));
			}

			if ($purchase->user_id == $user->user_id)
			{
				return $this->error(\XF::phrase('xr_pm_this_purchase_is_already_assigned_to_that_user'));
			}

			$oldUser = $purchase->User;

			$purchase->user_id = $user->user_id;
			$purchase->username = $user->username;

			$purchase->save();

			if ($oldUser && $oldUser->user_state == 'valid' && !$oldUser->is_banned)
			{
				$params = [
					'receiver' => $oldUser,
					'purchase' => $purchase,
					'product' => $purchase->Product
				];

				$this->app()->mailer()->newMail()
					->setToUser($oldUser)
					->setTemplate('xr_pm_purchase_transferred_from', $params)
					->queue();
			}

			if ($user->user_state == 'valid' && !$user->is_banned)
			{
				$params = [
					'receiver' => $user,
					'purchase' => $purchase,
					'product' => $purchase->Product
				];

				$this->app()->mailer()->newMail()
					->setToUser($user)
					->setTemplate('xr_pm_purchase_transferred_to', $params)
					->queue();
			}

			return $this->redirect($this->buildLink('product-manager/purchases/edit', $purchase));
		}
		else
		{
			$viewParams = [
				'purchase' => $purchase
			];
			return $this->view('XR\PM:Purchase\Transfer', 'xr_pm_purchase_transfer', $viewParams);
		}
	}

	protected function purchaseAddEdit(ProductPurchase $purchase)
	{
		$purchaseRepo = $this->getPurchaseRepo();

		$products = $this->getProductRepo()->findProductsForAdminList()->fetch()->pluckNamed('product_title', 'product_id');
		$coupons = $purchase->coupons ? $this->em()->findByIds('XR\PM:Coupon', $purchase->coupons) : [];
		$extras = $this->repository('XR\PM:Extra')->findExtrasForList()->fetch()->pluckNamed('extra_title', 'extra_id');

		$viewParams = [
			'purchase' => $purchase,
			'products' => $products,
			'coupons' => $coupons,
			'extras' => $extras,
			'purchaseStates' => $purchaseRepo->getPurchaseStates(),
			'purchaseTypes' => $purchaseRepo->getPurchaseTypes(),
			'parentPurchase' => $this->em()->findOne('XR\PM:ProductPurchase', [
				'purchase_key' => $purchase->parent_purchase_key
			], 'Product')
		];
		return $this->view('XR\PM:Purchase\Edit', 'xr_pm_purchase_edit', $viewParams);
	}

	public function actionEdit(ParameterBag $params)
	{
		$purchase = $this->assertPurchaseExists($params->purchase_id, 'Product');
		return $this->purchaseAddEdit($purchase);
	}

	public function actionAdd()
	{
		$purchase = $this->em()->create('XR\PM:ProductPurchase');
		return $this->purchaseAddEdit($purchase);
	}

	protected function purchaseSaveProcess(ProductPurchase $purchase)
	{
		$form = $this->formAction();

		$input = $this->filter([
			'purchase_date' => 'datetime',
			'expiry_date' => 'datetime',
			'purchase_state' => 'str',
			'license_name' => 'str',
			'license_url' => 'str',
			'purchase_currency' => 'str',
			'product_price' => 'str',
			'extras_price' => 'str',
			'discount_total' => 'str',
			'total_price' => 'str',
			'extras' => 'array',
			'coupons' => 'array-uint'
		]);

		$input['extras'] = $this->getPurchaseRepo()->getExtrasForPurchaseCache($input['extras']);

		$productId = $this->filter('product_id', 'uint');
		$username = $this->filter('username', 'str');
		$purchaseType = $this->filter('purchase_type', 'str');

		if ($purchase->isInsert())
		{
			$input['product_id'] = $productId;
			$input['purchase_type'] = $purchaseType;

			$input['username'] = $username;
			$form->validate(function(FormAction $form) use ($username, $purchase)
			{
				if ($username)
				{
					$user = $this->finder('XF:User')
						->where('username', $username)
						->fetchOne();
				}
				else
				{
					$user = \XF::visitor();
				}

				if ($user)
				{
					$purchase->username = $user->username;
					$purchase->user_id = $user->user_id;
				}
				else
				{
					$form->logError(\XF::phrase('requested_user_not_found'));
				}
			});
 		}

 		$form->basicEntitySave($purchase, $input);

		return $form;
	}

	public function actionSave(ParameterBag $params)
	{
		$this->assertPostOnly();

		if ($params->purchase_id)
		{
			$purchase = $this->assertPurchaseExists($params->purchase_id);
		}
		else
		{
			$purchase = $this->em()->create('XR\PM:ProductPurchase');
		}

		$purchase->setOption('admin_add_or_edit', true);

		$this->purchaseSaveProcess($purchase)->run();

		return $this->redirect($this->buildLink('product-manager/purchases/edit', $purchase));
	}

	public function actionGetStateExplain()
	{
		$this->assertPostOnly();

		$state = $this->filter('id', 'str');
		$states = $this->getPurchaseRepo()->getPurchaseStates();

		if (!$state || !isset($states[$state]))
		{
			return $this->notFound();
		}

		$explain = $states[$state]['explain'];

		$view = $this->view('XF:DescLoader');
		$view->setJsonParam('description', $explain);
		return $view;
	}

	public function actionSearch()
	{
		$this->setSectionContext('xr_pm_purchases_search');

		$searcher = $this->searcher('XR\PM:ProductPurchase');

		$viewParams = $searcher->getFormData() + [
			'criteria' => $searcher->getFormCriteria(),
			'sortOrders' => $searcher->getOrderOptions()
		];
		return $this->view('XR\PM:Purchases\Search', 'xr_pm_purchase_search', $viewParams);
	}

	/**
	 * @return \XR\PM\Repository\ProductPurchase
	 */
	protected function getPurchaseRepo()
	{
		return $this->repository('XR\PM:ProductPurchase');
	}

	/**
	 * @return \XR\PM\Repository\Product
	 */
	protected function getProductRepo()
	{
		return $this->repository('XR\PM:Product');
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

		if (!$purchase->Product)
		{
			throw $this->exception($this->notFound());
		}

		$this->getPurchaseRepo()->expirePurchaseIfNeeded($purchase);

		return $purchase;
	}
}