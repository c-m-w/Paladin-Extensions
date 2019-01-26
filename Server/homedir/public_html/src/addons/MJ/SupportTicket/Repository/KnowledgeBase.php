<?php

namespace MJ\SupportTicket\Repository;

use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Repository;

class KnowledgeBase extends Repository
{
	public function getDefaultCategory()
	{
		$kbCategory = $this->em->create('MJ\SupportTicket:KnowledgeBaseCategory');
		$kbCategory->setTrusted('kb_category_id', 0);
		$kbCategory->setTrusted('display_order', 0);
		$kbCategory->setReadOnly(true);

		return $kbCategory;
	}

	public function findKnowledgeBaseCategories($getDefault = false)
	{
		$categories = $this->finder('MJ\SupportTicket:KnowledgeBaseCategory')
			->order('display_order');

		if ($getDefault)
		{
			$categories = $categories->fetch();

			$defaultCategory = $this->getDefaultCategory();
			$kbCategories = $categories->toArray();
			$kbCategories = $kbCategories + [$defaultCategory];
			$categories = $this->em->getBasicCollection($kbCategories);
		}
		return $categories;
	}

	public function getKbCategories()
	{
		$categories = $this->finder('MJ\SupportTicket:KnowledgeBaseCategory')
			->order('display_order');

		return $categories->fetch();
	}

	public function getKnowledgeBaseListData()
	{
		$kbs = $this->findKbsForList()->fetch();
		$kbCategories = $this->findKnowledgeBaseCategories(true);
		return [
			'kbCategories' => $kbCategories,
			'kbsGrouped'   => $kbs->groupBy('kb_category_id'),
			'kbTotal'      => count($kbs)
		];
	}

	/**
	 * @return Finder
	 */
	public function findKbsForList()
	{
		return $this->finder('MJ\SupportTicket:KnowledgeBase')
			->order(['materialized_order']);
	}

	public function logKbView($kbId)
	{
		$db = $this->db();
		$db->query('
			UPDATE `xf_mjst_kb`
			SET `view_count`=`view_count` + 1
			WHERE kb_id = ?
		', $kbId);
	}

	public function rebuildKnowledgeBaseMaterializedOrder()
	{
		$kbs = $this->finder('MJ\SupportTicket:KnowledgeBase')
			->with('Category')
			->order([
				'Category.display_order',
				'display_order'
			]);

		$db = $this->db();
		$ungroupedKbs = [];
		$updates = [];
		$i = 0;

		foreach ($kbs as $kbId => $kb)
		{
			if ($kb->kb_category_id)
			{
				if (++$i != $kb->materialized_order)
				{
					$updates[$kbId] = 'WHEN ' . $db->quote($kbId) . ' THEN ' . $db->quote($i);
				}
			}
			else
			{
				$ungroupedKbs[$kbId] = $kb;
			}
		}

		foreach ($ungroupedKbs as $kbId => $kb)
		{
			if (++$i != $kb->materialized_order)
			{
				$updates[$kbId] = 'WHEN ' . $db->quote($kbId) . ' THEN ' . $db->quote($i);
			}
		}

		if (!empty($updates))
		{
			$structure = $this->em->getEntityStructure('MJ\SupportTicket:KnowledgeBase');
			$table = $structure->table;

			$db->query('
				UPDATE `' . $table . '` SET materialized_order = CASE kb_id
				' . implode(' ', $updates) . '
				END
				WHERE kb_id IN(' . $db->quote(array_keys($updates)) . ')
			');
		}
	}
}
