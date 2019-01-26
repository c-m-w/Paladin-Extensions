<?php

namespace XR\PM\Service\Extra;

use XF\Service\AbstractService;
use XF\Service\ValidateAndSavableTrait;

class Editor extends AbstractService
{
	use ValidateAndSavableTrait;

	/**
	 * @var \XR\PM\Entity\Extra
	 */
	protected $extra;

	protected $productIds = [];

	/**
	 * @var Preparer
	 */
	protected $extraPreparer;

	protected $performValidations = true;

	public function __construct(\XF\App $app, \XR\PM\Entity\Extra $extra)
	{
		parent::__construct($app);
		$this->extra = $extra;
		$this->extraPreparer = $this->service('XR\PM:Extra\Preparer', $extra);
	}

	public function setPerformValidations($performValidations)
	{
		$this->performValidations = $performValidations;
	}

	public function setDetails($title, $description)
	{
		$this->extra->extra_title = $title;
		$this->extra->extra_description = $description;
	}

	public function setPrice($price)
	{
		$this->extra->extra_price = $price;
	}

	public function setRenewPrice($price)
	{
		$this->extra->extra_renew_price = $price;
	}

	public function setRewardType($reward)
	{
		$this->extra->extra_reward = $reward;
	}

	public function setRewardUserGroup($userGroupId)
	{
		$this->extra->extra_user_group_id = $userGroupId;
	}

	public function setRewardFile($hash)
	{
		$this->extraPreparer->setExtraAttachmentHash($hash);
	}

	public function setRewardInstructions($instructions, $format = true)
	{
		$this->extraPreparer->setExtraInstructions($instructions, $format, $this->performValidations);
	}

	public function setProductIds($productIds)
	{
		$this->productIds = $productIds;
	}

	protected function finalSetup()
	{
	}

	protected function _validate()
	{
		$this->finalSetup();

		$this->extra->preSave();
		return $this->extra->getErrors();
	}

	protected function _save()
	{
		$extra = $this->extra;

		$db = $this->db();
		$db->beginTransaction();

		$extra->save(true, false);

		if ($this->extraPreparer->hasNewAttachments())
		{
			$this->deleteExistingAttachment();
		}
		$this->extraPreparer->afterInsert();

		$db->commit();

		$repo = $this->repository('XR\PM:Extra');
		$repo->updateExtraAssociations($extra, $this->productIds);

		return $extra;
	}

	public function deleteExistingAttachment()
	{
		$extra = $this->extra;

		$existing = $this->em()->findOne('XF:Attachment', [
			'content_type' => 'xr_pm_product_extra',
			'content_id' => $extra->extra_id
		]);

		if ($existing)
		{
			$existing->delete();
		}
	}
}