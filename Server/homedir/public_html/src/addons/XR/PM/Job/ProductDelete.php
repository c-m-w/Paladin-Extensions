<?php

namespace XR\PM\Job;

use XF\Job\AbstractJob;

class ProductDelete extends AbstractJob
{
	protected $defaultData = [
		'product_id' => null,
		'count' => 0,
		'total' => null
	];

	public function run($maxRunTime)
	{
		$s = microtime(true);

		if (!$this->data['product_id'])
		{
			throw new \InvalidArgumentException('Cannot delete purchases without a product_id.');
		}

		$purchaseFinder = $this->app->finder('XR\PM:ProductPurchase')
			->where('product_id', $this->data['product_id']);

		if ($this->data['total'] === null)
		{
			$this->data['total'] = $purchaseFinder->total();
			if (!$this->data['total'])
			{
				return $this->complete();
			}
		}

		$purchaseIds = $purchaseFinder->pluckFrom('purchase_id')->fetch(1000);
		if (!$purchaseIds)
		{
			return $this->complete();
		}

		$continue = count($purchaseIds) < 1000 ? false : true;

		foreach ($purchaseIds AS $purchaseId)
		{
			$this->data['count']++;

			$purchase = $this->app->find('XR\PM:ProductPurchase', $purchaseId);
			if (!$purchase)
			{
				continue;
			}
			$purchase->delete(false);

			if ($maxRunTime && microtime(true) - $s > $maxRunTime)
			{
				$continue = true;
				break;
			}
		}

		if ($continue)
		{
			return $this->resume();
		}
		else
		{
			return $this->complete();
		}
	}

	public function getStatusMessage()
	{
		$actionPhrase = \XF::phrase('deleting');
		$typePhrase = \XF::phrase('xr_pm_purchases');
		return sprintf('%s... %s (%s/%s)', $actionPhrase, $typePhrase,
			\XF::language()->numberFormat($this->data['count']), \XF::language()->numberFormat($this->data['total'])
		);
	}

	public function canCancel()
	{
		return true;
	}

	public function canTriggerByChoice()
	{
		return false;
	}
}