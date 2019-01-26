<?php

namespace XR\PM\Service\Version;

use XF\Entity\Forum;
use XF\Service\AbstractService;
use XF\Service\ValidateAndSavableTrait;

class Creator extends AbstractService
{
	use ValidateAndSavableTrait;

	/**
	 * @var \XR\PM\Entity\Product
	 */
	protected $product;

	/**
	 * @var \XR\PM\Entity\Version
	 */
	protected $version;

	/**
	 * @var \XR\PM\Service\Version\Preparer
	 */
	protected $versionPreparer;

	protected $performValidations = true;

	protected $sendEmail = false;

	protected $sendAlert = false;

	/**
	 * @var Forum
	 */
	protected $forum;

	public function __construct(\XF\App $app, \XR\PM\Entity\Product $product)
	{
		parent::__construct($app);

		$this->product = $product;
		$this->version = $product->getNewVersion();
		$this->version->addCascadedSave($this->product);
		$this->versionPreparer = $this->service('XR\PM:Version\Preparer', $this->version);
	}

	public function setPerformValidations($perform)
	{
		$this->performValidations = (bool)$perform;
	}

	public function getPerformValidations()
	{
		return $this->performValidations;
	}

	public function setVersionDetails($versionString, $versionDetails, $format = true)
	{
		$this->version->version_string = $versionString;

		return $this->versionPreparer->setVersionDetails($versionDetails, $format, $this->performValidations);
	}

	public function setVersionAttachmentHash($hash)
	{
		$this->versionPreparer->setVersionAttachmentHash($hash);
	}

	public function setChangelogItems(array $changelogs)
	{
		$changelogs = array_filter($changelogs);
		$this->version->changelog = $changelogs;
	}

	public function setIsUnsupported($unsupported)
	{
		$this->version->is_unsupported = $unsupported;
	}

	public function setSendNotifications($sendNotifications)
	{
		foreach ((array)$sendNotifications AS $notification)
		{
			switch ($notification)
			{
				case 'email':
					$this->sendEmail = true;
					break;

				case 'alert':
					$this->sendAlert = true;
					break;
			}
		}
	}

	public function setForum(Forum $forum)
	{
		$this->forum = $forum;
	}

	protected function finalSetup()
	{
		$this->version->release_date = time();
	}

	protected function _validate()
	{
		$this->finalSetup();

		$this->version->preSave();
		return $this->version->getErrors();
	}

	protected function _save()
	{
		$version = $this->version;
		$product = $this->product;

		$db = $this->db();
		$db->beginTransaction();

		$version->save(true, false);
		// product will also be saved

		if (!$version->is_unsupported)
		{
			$product->fastUpdate('current_version_id', $version->product_version_id);
			$product->fastUpdate('last_update', $version->release_date);
		}

		$this->versionPreparer->afterInsert();

		if ($this->forum)
		{
			try
			{
				/** @var \XF\Service\Thread\Creator $threadCreator */
				$threadCreator = $this->service('XF:Thread\Creator', $this->forum);
				$threadCreator->setIsAutomated();

				$title = \XF::phrase('xr_pm_product_x_version_y_released', [
					'product' => $product->product_title,
					'version' => $version->version_string
				]);

				$message = $version->version_details;
				if ($version->changelog)
				{
					$message .= "\n" . "[LIST]\n[*]" . implode("\n[*]", $version->changelog) . "\n[/LIST]";
				}

				$threadCreator->setContent($title, $message);
				$threadCreator->save();
			}
			catch (\Exception $e)
			{
				$db->rollbackAll();
				throw $e;
			}
		}

		$db->commit();

		return $version;
	}

	public function sendNotifications()
	{
		if (!$this->sendEmail && !$this->sendAlert)
		{
			return;
		}

		/** @var \XR\PM\Service\Purchase\Notifier $notifier */
		$notifier = $this->service('XR\PM:Purchase\Notifier', $this->version);

		if ($this->sendEmail)
		{
			$notifier->setSendEmail(true);
		}

		if ($this->sendAlert)
		{
			$notifier->setSendAlert(true);
		}

		$notifier->notifyAndEnqueue(3);
	}
}