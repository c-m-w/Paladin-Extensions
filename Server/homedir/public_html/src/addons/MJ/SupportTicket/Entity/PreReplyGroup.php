<?php

namespace MJ\SupportTicket\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

class PreReplyGroup extends Entity
{
	protected function _postSave()
	{
		if ($this->isChanged('display_order'))
		{
			$this->rebuildPreReplyCaches();
		}
	}

	protected function _postDelete()
	{
		if ($this->Replies)
		{
			foreach ($this->Replies as $reply)
			{
				$reply->reply_group_id = 0;
				$reply->save();
			}
		}

		$this->rebuildPreReplyCaches();
	}

	protected function rebuildPreReplyCaches()
	{
		$repo = $this->getPreReplyRepo();

		\XF::runOnce('mjstReplyGroupCaches', function() use ($repo)
		{
			$repo->rebuildPreReplyMaterializedOrder();
		});
	}

	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_mjst_pre_reply_group';
		$structure->shortName = 'MJ\SupportTicket:PreReplyGroup';
		$structure->primaryKey = 'reply_group_id';
		$structure->columns = [
			'reply_group_id' => ['type' => self::UINT, 'nullable' => true, 'autoIncrement' => true],
			'title'          => ['type' => self::STR, 'required' => true],
			'display_order'  => ['type' => self::UINT, 'default' => 0]
		];
		$structure->relations = [
			'Replies' => [
				'entity'     => 'MJ\SupportTicket:PreReply',
				'type'       => self::TO_MANY,
				'conditions' => 'reply_group_id'
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
