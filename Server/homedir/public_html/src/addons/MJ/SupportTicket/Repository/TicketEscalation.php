<?php

namespace MJ\SupportTicket\Repository;

use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Repository;

class TicketEscalation extends Repository
{
	/**
	 * @return Finder
	 */
	public function findTicketEscalationForList()
	{
		return $this->finder('MJ\SupportTicket:TicketEscalation');
	}

	public function logEscalationRun($escalationId, $ticketId)
	{
		$escalationId = intval($escalationId);
		if (!$escalationId)
		{
			return null;
		}
		$ticketId = intval($ticketId);
		if (!$ticketId)
		{
			return null;
		}

		$this->db()->insert('xf_mjst_ticket_escalation_log', [
			'escalation_id' => $escalationId,
			'support_ticket_id' => $ticketId,
			'log_date' => \XF::$time,
		]);

		return $this->db()->lastInsertId();
	}
}
