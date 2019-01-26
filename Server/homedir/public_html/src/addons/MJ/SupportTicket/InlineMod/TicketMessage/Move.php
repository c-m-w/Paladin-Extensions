<?php

namespace MJ\SupportTicket\InlineMod\TicketMessage;

use XF\Mvc\Entity\AbstractCollection;
use XF\Mvc\Entity\Entity;

class Move extends AbstractMoveCopy
{
	public function getTitle()
	{
		return \XF::phrase('mjst_move_messages...');
	}

	protected function canApplyToEntity(Entity $entity, array $options, &$error = null)
	{
		/** @var \MJ\SupportTicket\Entity\TicketMessage $entity */
		return $entity->canMove($error);
	}

	public function applyInternal(AbstractCollection $entities, array $options)
	{
		$ticket = $this->getTargetTicketFromOptions($options);

		/** @var \MJ\SupportTicket\Service\TicketMessage\Mover $mover */
		$mover = $this->app()->service('MJ\SupportTicket:TicketMessage\Mover', $ticket);
		$mover->setExistingTarget($options['ticket_type'] == 'existing' ? true : false);

		if ($options['alert'])
		{
			$mover->setSendAlert(true, $options['alert_reason']);
		}

		if ($options['prefix_id'] !== null && $options['ticket_type'] !== 'existing')
		{
			$mover->setPrefix($options['prefix_id']);
		}

		if (!$mover->move($entities))
		{
			throw new \XF\PrintableException(\XF::phrase('mjst_it_is_not_possible_to_move_any_of_selected_messages_to_specified_target'));
		}

		$this->returnUrl = $this->app()->router('public')->buildLink('support-tickets', $mover->getTarget());
	}

	public function renderForm(AbstractCollection $entities, \XF\Mvc\Controller $controller)
	{
		/** @var \MJ\SupportTicket\Repository\Department $departmentRepo */
		$departmentRepo = $this->app()->repository('MJ\SupportTicket:Department');
		$departments = $departmentRepo->getFullDepartmentList()->filterViewable();

		$viewParams = [
			'messages'    => $entities,
			'total'       => count($entities),
			'departments' => $departments,
			'first'       => $entities->first(),
			'prefixes'    => $entities->first()->Ticket->Department->getUsablePrefixes()
		];
		return $controller->view('MJ\SupportTicket:Public:InlineMod\TicketMessage\Move', 'mjst_inline_mod_message_move', $viewParams);
	}
}
