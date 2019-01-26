<?php

namespace MJ\SupportKnowledgeBase\Search\Data;

use XF\Mvc\Entity\Entity;
use XF\Search\IndexRecord;
use XF\Search\MetadataStructure;

class KnowledgeBase extends \XF\Search\Data\AbstractData
{
	public function getEntityWith($forView = false)
	{
		$get = ['Category'];
		if ($forView)
		{
			$get[] = 'User';
		}

		return $get;
	}

	public function getIndexData(Entity $entity)
	{
		/** @var \MJ\SupportKnowledgeBase\Entity\KnowledgeBase $entity */

		if (!$entity->Department)
		{
			return null;
		}

		/** @var \MJ\SupportKnowledgeBase\Entity\KnowledgeBase|null $firstMessage */
		$firstMessage = $entity->FirstMessage;

		$index = IndexRecord::create('support_kb', $entity->kb_id, [
			'title'         => $entity->title_,
			'message'       => $entity->message_,
			'date'          => $entity->kb_date,
			'user_id'       => $entity->user_id,
			'discussion_id' => $entity->kb_id,
			'metadata'      => $this->getMetaData($entity)
		]);

		return $index;
	}

	protected function getMetaData(\MJ\SupportKnowledgeBase\Entity\KnowledgeBase $entity)
	{
		$metadata = [
			'kb_category' => $entity->kb_category_id,
			'kb' => $entity->kb_id
		];

		return $metadata;
	}

	public function setupMetadataStructure(MetadataStructure $structure)
	{
		$structure->addField('kb_category', MetadataStructure::INT);
		$structure->addField('kb', MetadataStructure::INT);
	}

	public function getResultDate(Entity $entity)
	{
		return $entity->kb_date;
	}

	public function getTemplateData(Entity $entity, array $options = [])
	{
		return [
			'kb'      => $entity,
			'options' => $options
		];
	}

	public function getSearchFormTab()
	{
		return [
			'title' => \XF::phrase('mjst_search_kb'),
			'order' => 10
		];
	}

	public function getSectionContext()
	{
		return 'mjstKb';
	}
}
