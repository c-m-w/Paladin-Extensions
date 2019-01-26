<?php

namespace MJ\SupportTicket\InlineMod;

use XF\Mvc\Entity\Entity;

class Ticket extends \XF\InlineMod\AbstractHandler
{
	public function getPossibleActions()
	{
		$actions = [];

		$actions['delete']       = $this->getActionHandler('MJ\SupportTicket:Ticket\Delete');

		$actions['move']         = $this->getActionHandler('MJ\SupportTicket:Ticket\Move');
		$actions['merge']        = $this->getActionHandler('MJ\SupportTicket:Ticket\Merge');
		$actions['apply_prefix'] = $this->getActionHandler('MJ\SupportTicket:Ticket\ApplyPrefix');

		return $actions;
	}

	public function getEntityWith()
	{
		$visitor = \XF::visitor();

		return ['Department', 'Department.Permissions|' . $visitor->permission_combination_id];
	}
}
