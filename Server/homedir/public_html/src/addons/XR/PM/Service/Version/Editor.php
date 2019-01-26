<?php

namespace XR\PM\Service\Version;

use XF\Service\AbstractService;
use XF\Service\ValidateAndSavableTrait;

class Editor extends AbstractService
{
	use ValidateAndSavableTrait;

	/**
	 * @var \XR\PM\Entity\Version
	 */
	protected $version;

	/**
	 * @var \XR\PM\Service\Version\Preparer
	 */
	protected $versionPreparer;

	protected $performValidations = true;

	public function __construct(\XF\App $app, \XR\PM\Entity\Version $version)
	{
		parent::__construct($app);
		$this->version = $version;
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

	protected function finalSetup()
	{
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

		$db = $this->db();
		$db->beginTransaction();

		$version->save(true, false);

		if ($this->versionPreparer->hasNewAttachments())
		{
			$this->deleteExistingAttachment();
		}
		$this->versionPreparer->afterInsert();

		$db->commit();

		return $version;
	}

	public function deleteExistingAttachment()
	{
		$version = $this->version;

		$existing = $this->em()->findOne('XF:Attachment', [
			'content_type' => 'xr_pm_product_version',
			'content_id' => $version->product_version_id
		]);

		if ($existing)
		{
			$existing->delete();
		}
	}
}