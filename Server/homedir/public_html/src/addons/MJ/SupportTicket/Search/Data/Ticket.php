<?php

namespace MJ\SupportTicket\Search\Data;

use XF\Mvc\Entity\Entity;
use XF\Search\IndexRecord;
use XF\Search\MetadataStructure;

class Ticket extends \XF\Search\Data\AbstractData
{
	public function getEntityWith($forView = false)
	{
		$get = ['Department', 'FirstMessage'];
		if ($forView)
		{
			$get[] = 'User';

			$visitor = \XF::visitor();
			$get[] = 'Department.Permissions|' . $visitor->permission_combination_id;
		}

		return $get;
	}

	public function getIndexData(Entity $entity)
	{
		/** @var \MJ\SupportTicket\Entity\Ticket $entity */

		if (!$entity->Department)
		{
			return null;
		}

		/** @var \MJ\SupportTicket\Entity\TicketMessage|null $firstMessage */
		$firstMessage = $entity->FirstMessage;

		$index = IndexRecord::create('support_ticket', $entity->support_ticket_id, [
			'title'         => $entity->title_,
			'message'       => $firstMessage ? $firstMessage->message_ : '',
			'date'          => $entity->open_date,
			'user_id'       => $entity->user_id,
			'discussion_id' => $entity->support_ticket_id,
			'metadata'      => $this->getMetaData($entity)
		]);

		return $index;
	}

	protected function getMetaData(\MJ\SupportTicket\Entity\Ticket $entity)
	{
		$metadata = [
			'department' => $entity->department_id,
			'ticket' => $entity->support_ticket_id
		];
		if ($entity->prefix_id)
		{
			$metadata['prefix'] = $entity->prefix_id;
		}

		return $metadata;
	}

	public function setupMetadataStructure(MetadataStructure $structure)
	{
		$structure->addField('department', MetadataStructure::INT);
		$structure->addField('ticket', MetadataStructure::INT);
		$structure->addField('prefix', MetadataStructure::INT);
	}

	public function getResultDate(Entity $entity)
	{
		return $entity->open_date;
	}

	public function getTemplateData(Entity $entity, array $options = [])
	{
		return [
			'ticket' => $entity,
			'options' => $options
		];
	}

	public function canUseInlineModeration(Entity $entity, &$error = null)
	{
		/** @var \MJ\SupportTicket\Entity\Ticket $entity */
		return $entity->canUseInlineModeration($error);
	}
}
