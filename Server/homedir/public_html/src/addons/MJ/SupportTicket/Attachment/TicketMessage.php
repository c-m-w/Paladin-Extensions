<?php

namespace MJ\SupportTicket\Attachment;

use XF\Entity\Attachment;
use XF\Mvc\Entity\Entity;

class TicketMessage extends \XF\Attachment\AbstractHandler
{
	public function getContainerWith()
	{
		$visitor = \XF::visitor();

		return ['Ticket', 'Ticket.Department', 'Ticket.Department.Permissions|' . $visitor->permission_combination_id];
	}

	public function canView(Attachment $attachment, Entity $container, &$error = null)
	{
		/** @var \MJ\SupportTicket\Entity\TicketMessage $container */
		if (!$container->canView())
		{
			return false;
		}

		/** @var \MJ\SupportTicket\Entity\Ticket $ticket */
		$ticket = $container->Ticket;
		return $ticket->canViewAttachments($error);
	}

	public function canManageAttachments(array $context, &$error = null)
	{
		$em = \XF::em();

		if (!empty($context['message_id']))
		{
			/** @var \MJ\SupportTicket\Entity\TicketMessage $message */
			$message = $em->find('MJ\SupportTicket:TicketMessage', intval($context['message_id']), ['Ticket', 'Ticket.Department']);
			if (!$message || !$message->canView() || !$message->canEdit())
			{
				return false;
			}

			$department = $message->Ticket->Department;
		}
		else if (!empty($context['support_ticket_id']))
		{
			/** @var \MJ\SupportTicket\Entity\Ticket $ticket */
			$ticket = $em->find('MJ\SupportTicket:Ticket', intval($context['support_ticket_id']), ['Department']);
			if (!$ticket || !$ticket->canView())
			{
				return false;
			}

			$department = $ticket->Department;
		}
		else if (!empty($context['department_id']))
		{
			/** @var \MJ\SupportTicket\Entity\Department $department */
			$department = $em->find('MJ\SupportTicket:Department', intval($context['department_id']));
			if (!$department || !$department->canView())
			{
				return false;
			}
		}
		else
		{
			return false;
		}

		return $department->canUploadAndManageAttachments();
	}

	public function onAttachmentDelete(Attachment $attachment, Entity $container = null)
	{
		if (!$container)
		{
			return;
		}

		/** @var \MJ\SupportTicket\Entity\TicketMessage $container */
		$container->attach_count--;
		$container->save();
	}

	public function getConstraints(array $context)
	{
		return \XF::repository('XF:Attachment')->getDefaultAttachmentConstraints();
	}

	public function getContainerIdFromContext(array $context)
	{
		return isset($context['message_id']) ? intval($context['message_id']) : null;
	}

	public function getContainerLink(Entity $container, array $extraParams = [])
	{
		return \XF::app()->router('public')->buildLink('support-tickets/messages', $container, $extraParams);
	}

	public function getContext(Entity $entity = null, array $extraContext = [])
	{
		if ($entity instanceof \MJ\SupportTicket\Entity\TicketMessage)
		{
			$extraContext['message_id'] = $entity->message_id;
		}
		else if ($entity instanceof \MJ\SupportTicket\Entity\Ticket)
		{
			$extraContext['support_ticket_id'] = $entity->support_ticket_id;
		}
		else if ($entity instanceof \MJ\SupportTicket\Entity\Department)
		{
			$extraContext['department_id'] = $entity->department_id;
		}
		else if (!$entity)
		{
			// need nothing
		}
		else
		{
			throw new \InvalidArgumentException("Entity must be post, ticket or department");
		}

		return $extraContext;
	}
}
