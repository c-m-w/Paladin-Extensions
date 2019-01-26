<?php

namespace MJ\SupportTicket\InlineMod;

use XF\Mvc\Entity\Entity;

class TicketMessage extends \XF\InlineMod\AbstractHandler
{
	public function getPossibleActions()
	{
		$actions = [];

		$actions['delete'] = $this->getActionHandler('MJ\SupportTicket:TicketMessage\Delete');

		$actions['undelete'] = $this->getSimpleActionHandler(
			\XF::phrase('mjst_undelete_messages'),
			'canUndelete',
			function(Entity $entity)
			{
				/** @var \MJ\SupportTicket\Entity\TicketMessage $entity */
				if ($entity->message_state == 'deleted')
				{
					$entity->message_state = 'visible';
					$entity->save();
				}
			}
		);

		$actions['move'] = $this->getActionHandler('MJ\SupportTicket:TicketMessage\Move');
		//$actions['copy'] = $this->getActionHandler('MJ\SupportTicket:TicketMessage\Copy');
		$actions['merge'] = $this->getActionHandler('MJ\SupportTicket:TicketMessage\Merge');

		return $actions;
	}

	public function getEntityWith()
	{
		$visitor = \XF::visitor();

		return ['Ticket', 'Ticket.Department', 'Ticket.Department.Permissions|' . $visitor->permission_combination_id];
	}
}
