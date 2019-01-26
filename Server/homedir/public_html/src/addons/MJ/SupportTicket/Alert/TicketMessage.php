<?php

namespace MJ\SupportTicket\Alert;

use XF\Mvc\Entity\Entity;

class TicketMessage extends \XF\Alert\AbstractHandler
{
	public function getEntityWith()
	{
		$visitor = \XF::visitor();

		return ['Ticket', 'Ticket.Department', 'Ticket.Department.Permissions|' . $visitor->permission_combination_id];
	}

	public function getOptOutActions()
	{
		return [
			'insert',
			'quote',
			'mention',
		];
	}

	public function getTemplateName($action)
	{
		return 'public:mjst_alert_' . $this->contentType . '_' . $action;
	}

	public function getOptOutDisplayOrder()
	{
		return 30105;
	}
}
