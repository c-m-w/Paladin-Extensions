<?php

namespace MJ\SupportTicket\Search\Data;

use XF\Mvc\Entity\Entity;
use XF\Search\IndexRecord;
use XF\Search\MetadataStructure;
use XF\Search\Query\MetadataConstraint;

class TicketMessage extends \XF\Search\Data\AbstractData
{
	public function getEntityWith($forView = false)
	{
		$get = ['Ticket', 'Ticket.Department'];
		if ($forView)
		{
			$get[] = 'User';

			$visitor = \XF::visitor();
			$get[] = 'Ticket.Department.Permissions|' . $visitor->permission_combination_id;
		}

		return $get;
	}

	public function getIndexData(Entity $entity)
	{
		/** @var \MJ\SupportTicket\Entity\TicketMessage $entity */

		if (!$entity->Ticket || !$entity->Ticket->Department)
		{
			return null;
		}

		/** @var \MJ\SupportTicket\Entity\Ticket $ticket */
		$ticket = $entity->Ticket;

		if ($entity->isFirstMessage())
		{
			return $this->searcher->handler('support_ticket')->getIndexData($ticket);
		}

		$index = IndexRecord::create('support_ticket_message', $entity->message_id, [
			'message' => $entity->message_,
			'date' => $entity->message_date,
			'user_id' => $entity->user_id,
			'discussion_id' => $entity->support_ticket_id,
			'metadata' => $this->getMetaData($entity)
		]);

		if (!$entity->isVisible())
		{
			$index->setHidden();
		}

		return $index;
	}

	protected function getMetaData(\MJ\SupportTicket\Entity\TicketMessage $entity)
	{
		/** @var \MJ\SupportTicket\Entity\Ticket $ticket */
		$ticket = $entity->Ticket;

		$metadata = [
			'department' => $ticket->department_id,
			'ticket'     => $entity->support_ticket_id
		];
		if ($ticket->prefix_id)
		{
			$metadata['prefix'] = $ticket->prefix_id;
		}

		return $metadata;
	}

	public function setupMetadataStructure(MetadataStructure $structure)
	{
		$structure->addField('department', MetadataStructure::INT);
		$structure->addField('ticket', MetadataStructure::INT);
		$structure->addField('prefix', MetadataStructure::INT);
	}

	public function canIncludeInResults(Entity $entity, array $resultIds)
	{
		/** @var \MJ\SupportTicket\Entity\TicketMessage $entity */
		if (isset($resultIds['ticket-' . $entity->support_ticket_id]) && $entity->isFirstMessage())
		{
			return false;
		}

		return true;
	}

	public function getResultDate(Entity $entity)
	{
		return $entity->message_date;
	}

	public function getTemplateData(Entity $entity, array $options = [])
	{
		return [
			'message' => $entity,
			'options' => $options
		];
	}

	public function getSearchableContentTypes()
	{
		return ['support_ticket_message', 'support_ticket'];
	}

	public function getSearchFormTab()
	{
		return [
			'title' => \XF::phrase('mjst_search_tickets'),
			'order' => 10
		];
	}

	public function getSectionContext()
	{
		return 'mjstSupportTicket';
	}

	public function getSearchFormData()
	{
		$prefixListData = $this->getPrefixListData();

		return [
			'prefixGroups'    => $prefixListData['prefixGroups'],
			'prefixesGrouped' => $prefixListData['prefixesGrouped'],

			'departments'     => $this->getSearchableDepartments()
		];
	}

	/**
	 * @return \XF\Tree
	 */
	protected function getSearchableDepartments()
	{
		/** @var \MJ\SupportTicket\Repository\Department $departmentRepo */
		$departmentRepo = \XF::repository('MJ\SupportTicket:Department');
		return $departmentRepo->getViewableDepartments();
	}

	protected function getPrefixListData()
	{
		/** @var \MJ\SupportTicket\Repository\TicketPrefix $prefixRepo */
		$prefixRepo = \XF::repository('MJ\SupportTicket:TicketPrefix');
		return $prefixRepo->getPrefixListData();
	}

	public function applyTypeConstraintsFromInput(\XF\Search\Query\Query $query, \XF\Http\Request $request, array &$urlConstraints)
	{
		$minReplyCount = $request->filter('c.min_reply_count', 'uint');
		if ($minReplyCount)
		{
			$query->withSql(new \XF\Search\Query\SqlConstraint(
				'ticket.reply_count >= %s',
				$minReplyCount,
				$this->getTicketQueryTableReference()
			));
		}
		else
		{
			unset($urlConstraints['min_reply_count']);
		}

		$prefixes = $request->filter('c.prefixes', 'array-uint');
		$prefixes = array_unique($prefixes);
		if ($prefixes && reset($prefixes))
		{
			$query->withMetadata('prefix', $prefixes);
		}
		else
		{
			unset($urlConstraints['prefixes']);
		}

		$ticketId = $request->filter('c.ticket', 'uint');
		if ($ticketId)
		{
			$query->withMetadata('ticket', $ticketId)
				->inTitleOnly(false);
		}
		else
		{
			unset($urlConstraints['ticket']);

			$departmentIds = $request->filter('c.departments', 'array-uint');
			$departmentIds = array_unique($departmentIds);
			if ($departmentIds && reset($departmentIds))
			{
				$query->withMetadata('department', $departmentIds);
			}
			else
			{
				unset($urlConstraints['departments']);
			}
		}
	}

	public function getTypePermissionConstraints(\XF\Search\Query\Query $query, $isOnlyType)
	{
		/** @var \MJ\SupportTicket\Repository\Department $departmentRepo */
		$departmentRepo = \XF::repository('MJ\SupportTicket:Department');
		$departments = $departmentRepo->getFullDepartmentList();

		$skip = [];
		foreach ($departments as $department)
		{
			if (!$department->canView())
			{
				$skip[] = $department->department_id;
			}
		}

		if ($skip)
		{
			return [
				new MetadataConstraint('department', $skip, MetadataConstraint::MATCH_NONE)
			];
		}
		else
		{
			return [];
		}
	}

	public function getTypeOrder($order)
	{
		if ($order == 'replies')
		{
			return new \XF\Search\Query\SqlOrder('ticket.reply_count DESC', $this->getTicketQueryTableReference());
		}
		else
		{
			return null;
		}
	}

	protected function getTicketQueryTableReference()
	{
		return new \XF\Search\Query\TableReference(
			'support_ticket',
			'xf_mjst_ticket',
			'ticket.support_ticket_id = search_index.discussion_id'
		);
	}

	public function getGroupByType()
	{
		return 'support_ticket';
	}

	public function canUseInlineModeration(Entity $entity, &$error = null)
	{
		/** @var \MJ\SupportTicket\Entity\TicketMessage $entity */
		return $entity->canUseInlineModeration($error);
	}
}
