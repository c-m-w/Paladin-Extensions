<?php

namespace MJ\SupportTicket\InlineMod\TicketMessage;

use XF\Mvc\Entity\AbstractCollection;
use XF\Mvc\Entity\Entity;

class Copy extends AbstractMoveCopy
{
	public function getTitle()
	{
		return \XF::phrase('mjst_copy_messages...');
	}

	protected function canApplyToEntity(Entity $entity, array $options, &$error = null)
	{
		/** @var \MJ\SupportTicket\Entity\TicketMessage $entity */
		return $entity->canCopy($error);
	}

	public function applyInternal(AbstractCollection $entities, array $options)
	{
		$ticket = $this->getTargetTicketFromOptions($options);

		/** @var \MJ\SupportTicket\Service\TicketMessage\Copier $copier */
		$copier = $this->app()->service('MJ\SupportTicket:TicketMessage\Copier', $ticket);
		$copier->setExistingTarget($options['ticket_type'] == 'existing' ? true : false);

		if ($options['alert'])
		{
			$copier->setSendAlert(true, $options['alert_reason']);
		}

		if ($options['prefix_id'] !== null && $options['ticket_type'] !== 'existing')
		{
			$copier->setPrefix($options['prefix_id']);
		}

		$copier->copy($entities);

		$this->returnUrl = $this->app()->router('public')->buildLink('support-tickets', $copier->getTarget());
	}

	public function renderForm(AbstractCollection $entities, \XF\Mvc\Controller $controller)
	{
		/** @var \MJ\SupportTicket\Repository\Department $departmentRepo */
		$departmentRepo = $this->app()->repository('MJ\SupportTicket:Department');
		$departments = $departmentRepo->getDepartmentList();

		$viewParams = [
			'messages'    => $entities,
			'total'       => count($entities),
			'departments' => $departments,
			'first'       => $entities->first(),
			'prefixes'    => $entities->first()->Ticket->Department->getUsablePrefixes()
		];
		return $controller->view('MJ\SupportTicket:Public:InlineMod\TicketMessage\Copy', 'mjst_inline_mod_message_copy', $viewParams);
	}
}
