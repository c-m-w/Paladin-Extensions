<?php

namespace MJ\SupportTicket\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

class KnowledgeBaseCategory extends Entity
{
	public function canView(&$error = null)
	{
		return \XF::visitor()->canViewKb();
	}

	protected function _postSave()
	{
		if ($this->isChanged('display_order'))
		{
			$this->rebuildKbCaches();
		}
	}

	protected function _postDelete()
	{
		if ($this->KnowledgeBases)
		{
			foreach ($this->KnowledgeBases as $kb)
			{
				$kb->kb_category_id = 0;
				$kb->save();
			}
		}

		$this->rebuildKbCaches();
	}

	protected function rebuildKbCaches()
	{
		$repo = $this->getKbRepo();

		\XF::runOnce('mjstKbCategoryCaches', function() use ($repo)
		{
			$repo->rebuildKnowledgeBaseMaterializedOrder();
		});
	}

	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_mjst_kb_category';
		$structure->shortName = 'MJ\SupportTicket:KnowledgeBaseCategory';
		$structure->primaryKey = 'kb_category_id';
		$structure->contentType = 'support_kb_category';
		$structure->columns = [
			'kb_category_id' => ['type' => self::UINT, 'nullable' => true, 'autoIncrement' => true],
			'title'          => ['type' => self::STR, 'required' => true],
			'display_order'  => ['type' => self::UINT, 'default' => 0],
			'description'    => ['type' => self::STR, 'default' => '']
		];
		$structure->relations = [
			'KnowledgeBases' => [
				'entity'     => 'MJ\SupportTicket:KnowledgeBase',
				'type'       => self::TO_MANY,
				'conditions' => 'kb_category_id'
			]
		];
		$structure->getters = [];

		return $structure;
	}

	/**
	 * @return \MJ\SupportTicket\Repository\KnowledgeBase
	 */
	protected function getKbRepo()
	{
		return $this->repository('MJ\SupportTicket:KnowledgeBase');
	}
}
