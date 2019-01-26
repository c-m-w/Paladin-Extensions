<?php

namespace XR\PM\Service\Version;

use XF\Service\AbstractService;
use XR\PM\Entity\Version;

class Preparer extends AbstractService
{
	/**
	 * @var Version
	 */
	protected $version;

	protected $versionAttachmentHash;

	public function __construct(\XF\App $app, Version $version)
	{
		parent::__construct($app);
		$this->version = $version;
	}

	public function getVersion()
	{
		return $this->version;
	}

	public function setVersionDetails($versionDetails, $format = true, $checkValidity = true)
	{
		$preparer = $this->getMessagePreparer($format);
		$this->version->version_details = $preparer->prepare($versionDetails, $checkValidity);

		return $preparer->pushEntityErrorIfInvalid($this->version);
	}

	/**
	 * @param bool $format
	 *
	 * @return \XF\Service\Message\Preparer
	 */
	protected function getMessagePreparer($format = true)
	{
		/** @var \XF\Service\Message\Preparer $preparer */
		$preparer = $this->service('XF:Message\Preparer', 'xr_pm_product_version', $this->version);
		if (!$format)
		{
			$preparer->disableAllFilters();
		}

		return $preparer;
	}

	public function getVersionAttachmentHash()
	{
		return $this->versionAttachmentHash;
	}

	public function setVersionAttachmentHash($hash)
	{
		$this->versionAttachmentHash = $hash;
	}

	public function hasNewAttachments()
	{
		if (!$this->versionAttachmentHash)
		{
			return false;
		}

		$attachments = $this->repository('XF:Attachment')
			->findAttachmentsByTempHash($this->versionAttachmentHash);

		return (bool)$attachments->fetch()->count();
	}

	public function afterInsert()
	{
		$this->associateAttachments($this->versionAttachmentHash);
	}

	public function afterUpdate()
	{
		$this->associateAttachments($this->versionAttachmentHash);
	}

	protected function associateAttachments($hash)
	{
		$version = $this->version;

		/** @var \XF\Service\Attachment\Preparer $inserter */
		$inserter = $this->service('XF:Attachment\Preparer');
		$inserter->associateAttachmentsWithContent($hash, 'xr_pm_product_version', $version->product_version_id);
	}
}