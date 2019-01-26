<?php

namespace MJ\SupportTicket\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

class PreReply extends Entity
{
	public function canView(&$error = null)
	{
		return $this->isUsableByUser();
	}

	public function isUsableByUser(\XF\Entity\User $user = null)
	{
		$user = $user ?: \XF::visitor();

		foreach ($this->allowed_user_group_ids as $userGroupId)
		{
			if ($userGroupId == -1 || $user->isMemberOf($userGroupId))
			{
				return true;
			}
		}

		return false;
	}

	protected function _postSave()
	{
		$this->rebuildPreReplyCaches();
	}

	protected function _postDelete()
	{
		$this->rebuildPreReplyCaches();
	}

	protected function rebuildPreReplyCaches()
	{
		$repo = $this->getPreReplyRepo();

		\XF::runOnce('mjstReplyCaches', function() use ($repo)
		{
			$repo->rebuildPreReplyMaterializedOrder();
		});
	}

	protected function _setupDefaults()
	{
		$this->is_active = true;
	}

	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_mjst_pre_reply';
		$structure->shortName = 'MJ\SupportTicket:PreReply';
		$structure->primaryKey = 'reply_id';
		$structure->contentType = 'support_pre_reply';
		$structure->columns = [
			'reply_id'               => ['type' => self::UINT, 'nullable' => true, 'autoIncrement' => true],
			'title'                  => ['type' => self::STR, 'required' => true],
			'message'                => ['type' => self::STR, 'required' => true],
			'reply_group_id'         => ['type' => self::UINT, 'default' => 0],
			'display_order'          => ['type' => self::UINT, 'default' => 0],
			'is_active'              => ['type' => self::BOOL, 'default' => 1],
			'materialized_order'     => ['type' => self::UINT, 'forced' => true, 'default' => 0],
			'allowed_user_group_ids' => ['type' => self::JSON_ARRAY, 'default' => []]
		];
		$structure->relations = [
			'Group' => [
				'entity' => 'MJ\SupportTicket:PreReplyGroup',
				'type' => self::TO_ONE,
				'conditions' => 'reply_group_id',
				'primary' => true
			]
		];
		$structure->getters = [];

		return $structure;
	}

	/**
	 * @return \MJ\SupportTicket\Repository\PreReply
	 */
	protected function getPreReplyRepo()
	{
		return $this->repository('MJ\SupportTicket:PreReply');
	}
}
