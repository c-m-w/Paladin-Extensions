<?php

namespace XR\PM\Service\Extra;

use XF\Service\AbstractService;
use XR\PM\Entity\Extra;

class Preparer extends AbstractService
{
	/**
	 * @var Extra
	 */
	protected $extra;

	protected $extraAttachmentHash;

	public function __construct(\XF\App $app, Extra $extra)
	{
		parent::__construct($app);
		$this->extra = $extra;
	}

	public function getExtra()
	{
		return $this->extra;
	}

	public function setExtraInstructions($instructions, $format = true, $checkValidity = true)
	{
		$preparer = $this->getMessagePreparer($format);
		$this->extra->instructions = $preparer->prepare($instructions, $checkValidity);

		return $preparer->pushEntityErrorIfInvalid($this->extra);
	}

	/**
	 * @param bool $format
	 *
	 * @return \XF\Service\Message\Preparer
	 */
	protected function getMessagePreparer($format = true)
	{
		/** @var \XF\Service\Message\Preparer $preparer */
		$preparer = $this->service('XF:Message\Preparer', 'xr_pm_product_extra', $this->extra);
		if (!$format)
		{
			$preparer->disableAllFilters();
		}

		return $preparer;
	}

	public function getExtraAttachmentHash()
	{
		return $this->extraAttachmentHash;
	}

	public function setExtraAttachmentHash($hash)
	{
		$this->extraAttachmentHash = $hash;
	}

	public function hasNewAttachments()
	{
		if (!$this->extraAttachmentHash)
		{
			return false;
		}

		$attachments = $this->repository('XF:Attachment')
			->findAttachmentsByTempHash($this->extraAttachmentHash);

		return (bool)$attachments->fetch()->count();
	}

	public function afterInsert()
	{
		$this->associateAttachments($this->extraAttachmentHash);
	}

	public function afterUpdate()
	{
		$this->associateAttachments($this->extraAttachmentHash);
	}

	protected function associateAttachments($hash)
	{
		$extra = $this->extra;

		/** @var \XF\Service\Attachment\Preparer $inserter */
		$inserter = $this->service('XF:Attachment\Preparer');
		$inserter->associateAttachmentsWithContent($hash, 'xr_pm_product_extra', $extra->extra_id);
	}
}