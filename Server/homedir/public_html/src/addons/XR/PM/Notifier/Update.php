<?php

namespace XR\PM\Notifier;

use XF\Notifier\AbstractNotifier;
use XR\PM\Entity\Version;

class Update extends AbstractNotifier
{
	/**
	 * @var Version
	 */
	protected $version;

	protected $sendEmail = false;

	protected $sendAlert = false;

	public function __construct(\XF\App $app, Version $version, $sendEmail, $sendAlert)
	{
		parent::__construct($app);

		$this->version = $version;
		$this->sendEmail = $sendEmail;
		$this->sendAlert = $sendAlert;
	}

	public function sendAlert(\XF\Entity\User $user)
	{
		$version = $this->version;

		return $this->basicAlert(
			$user, 0, '', 'xr_pm_product_version', $version->product_version_id, 'release'
		);
	}

	public function sendEmail(\XF\Entity\User $user)
	{
		if (!$user->email || $user->user_state != 'valid' || !$user->Option->xr_pm_receive_update_email)
		{
			return false;
		}

		$version = $this->version;

		$params = [
			'version' => $version,
			'product' => $version->Product,
			'receiver' => $user
		];

		$this->app()->mailer()->newMail()
			->setToUser($user)
			->setTemplate('xr_pm_version_released', $params)
			->queue();

		return true;
	}

	public function getDefaultNotifyData()
	{
		$product = $this->version->Product;

		if (!$product)
		{
			return [];
		}

		if (!$this->sendEmail && !$this->sendAlert)
		{
			return [];
		}

		$finder = $product->getRelationFinder('Purchases');
		$finder->where('purchase_state', ['inactive', 'active', 'expired'])
			->where('purchase_type', 'product')
			->with(['User'], true)
			->pluckFrom('User', 'user_id');

		$notifyData = [];
		foreach ($finder->fetchColumns(['user_id']) AS $purchase)
		{
			$notifyData[$purchase['user_id']] = [
				'alert' => $this->sendAlert,
				'email' => $this->sendEmail
			];
		}

		return $notifyData;
	}
}