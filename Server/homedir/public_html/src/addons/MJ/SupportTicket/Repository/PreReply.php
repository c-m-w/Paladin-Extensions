<?php

namespace MJ\SupportTicket\Repository;

use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\AbstractCollection;
use XF\Mvc\Entity\Repository;

class PreReply extends Repository
{
	public function getDefaultGroup()
	{
		$replyGroup = $this->em->create('MJ\SupportTicket:PreReplyGroup');
		$replyGroup->setTrusted('reply_group_id', 0);
		$replyGroup->setTrusted('display_order', 0);
		$replyGroup->setReadOnly(true);

		return $replyGroup;
	}

	public function findPreReplyGroups($getDefault = false)
	{
		$groups = $this->finder('MJ\SupportTicket:PreReplyGroup')
			->order('display_order');

		if ($getDefault)
		{
			$groups = $groups->fetch();

			$defaultGroup = $this->getDefaultGroup();
			$replyGroups = $groups->toArray();
			$replyGroups = $replyGroups + [$defaultGroup];
			$groups = $this->em->getBasicCollection($replyGroups);
		}

		return $groups;
	}

	public function getPreReplyListData($adminView = false)
	{
		$replies = $this->findPreRepliesForList()->fetch();
		if(!$adminView){
			$replies = $replies->filterViewable();
		}
		$replyGroups = $this->findPreReplyGroups(true);

		return [
			'replyGroups' => $replyGroups,
			'repliesGrouped' => $replies->groupBy('reply_group_id'),
			'replyTotal' => count($replies)
		];
	}

	/**
	 * @return Finder
	 */
	public function findPreRepliesForList()
	{
		return $this->finder('MJ\SupportTicket:PreReply')
			->order(['materialized_order']);
	}

	public function rebuildPreReplyMaterializedOrder()
	{
		$replies = $this->finder('MJ\SupportTicket:PreReply')
			->with('Group')
			->order([
				'Group.display_order',
				'display_order'
			]);

		$db = $this->db();
		$ungroupedPreReplies = [];
		$updates = [];
		$i = 0;

		foreach ($replies as $replyId => $reply)
		{
			if ($reply->reply_group_id)
			{
				if (++$i != $reply->materialized_order)
				{
					$updates[$replyId] = 'WHEN ' . $db->quote($replyId) . ' THEN ' . $db->quote($i);
				}
			}
			else
			{
				$ungroupedPreReplies[$replyId] = $reply;
			}
		}

		foreach ($ungroupedPreReplies as $replyId => $reply)
		{
			if (++$i != $reply->materialized_order)
			{
				$updates[$replyId] = 'WHEN ' . $db->quote($replyId) . ' THEN ' . $db->quote($i);
			}
		}

		if (!empty($updates))
		{
			$structure = $this->em->getEntityStructure('MJ\SupportTicket:PreReply');
			$table = $structure->table;

			$db->query('
				UPDATE `' . $table . '` SET materialized_order = CASE reply_id
				' . implode(' ', $updates) . '
				END
				WHERE reply_id IN(' . $db->quote(array_keys($updates)) . ')
			');
		}
	}
}
