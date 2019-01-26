<?php

namespace XR\PM\Service\Purchase;

use XF\Service\AbstractNotifier;
use XR\PM\Entity\Version;

class Notifier extends AbstractNotifier
{
	/**
	 * @var Version
	 */
	protected $version;

	protected $sendEmail = false;

	protected $sendAlert = false;

	public function __construct(\XF\App $app, Version $version)
	{
		parent::__construct($app);

		$this->version = $version;
	}

	public function setSendEmail($sendEmail)
	{
		$this->sendEmail = $sendEmail;
	}

	public function setSendAlert($sendAlert)
	{
		$this->sendAlert = $sendAlert;
	}

	public static function createForJob(array $extraData)
	{
		$version = \XF::app()->find('XR\PM:Version', $extraData['versionId']);
		if (!$version)
		{
			return null;
		}

		return \XF::service('XR\PM:Purchase\Notifier', $version);
	}

	protected function getExtraJobData()
	{
		return [
			'versionId' => $this->version->product_version_id,
			'sendEmail' => $this->sendEmail,
			'sendAlert' => $this->sendAlert
		];
	}

	protected function loadNotifiers()
	{
		return [
			'update' => $this->app->notifier('XR\PM:Update', $this->version, $this->sendEmail, $this->sendAlert)
		];
	}

	protected function loadExtraUserData(array $users)
	{
		$permCombinationIds = [];
		foreach ($users AS $user)
		{
			$id = $user->permission_combination_id;
			$permCombinationIds[$id] = $id;
		}

		$this->app->permissionCache()->cacheMultipleContentPermsForContent(
			$permCombinationIds,
			'xr_pm_category', $this->version->Product->Category->category_id
		);
	}

	protected function canUserViewContent(\XF\Entity\User $user)
	{
		return (
			$this->version->Product->canView()
			&& !$user->is_banned
		);
	}
}