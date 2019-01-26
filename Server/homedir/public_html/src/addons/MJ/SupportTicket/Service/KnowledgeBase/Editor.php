<?php

namespace MJ\SupportTicket\Service\KnowledgeBase;

use MJ\SupportTicket\Entity\KnowledgeBase;

class Editor extends \XF\Service\AbstractService
{
	use \XF\Service\ValidateAndSavableTrait;

	/**
	 * @var KnowledgeBase
	 */
	protected $kb;

	protected $attachmentHash;

	protected $performValidations = true;

	public function __construct(\XF\App $app, KnowledgeBase $kb)
	{
		parent::__construct($app);
		$this->kb = $kb;
	}

	public function getKb()
	{
		return $this->kb;
	}

	public function setPerformValidations($perform)
	{
		$this->performValidations = (bool)$perform;
	}

	public function getPerformValidations()
	{
		return $this->performValidations;
	}

	public function setAttachmentHash($hash)
	{
		$this->attachmentHash = $hash;
	}

	protected function finalSetup()
	{
	}

	protected function _validate()
	{
		$this->finalSetup();

		$kb = $this->kb;

		$kb->preSave();
		$errors = $kb->getErrors();

		if ($this->performValidations)
		{
		}

		return $errors;
	}

	protected function _save()
	{
		$kb = $this->kb;

		$kb->save(true, false);

		if ($this->attachmentHash)
		{
			$this->associateAttachments($this->attachmentHash);
		}
		return $kb;
	}

	protected function associateAttachments($hash)
	{
		$kb = $this->kb;

		/** @var \XF\Service\Attachment\Preparer $inserter */
		$inserter = $this->service('XF:Attachment\Preparer');
		$associated = $inserter->associateAttachmentsWithContent($hash, 'support_kb', $kb->kb_id);
		if ($associated)
		{
			$kb->fastUpdate('attach_count', $kb->attach_count + $associated);
		}
	}
}
