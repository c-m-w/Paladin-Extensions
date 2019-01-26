<?php

namespace MJ\SupportTicket\Job;

use XF\Job\AbstractRebuildJob;

class Ticket extends AbstractRebuildJob
{
	protected $defaultData = [
		'position_rebuild' => false
	];

	protected function getNextIds($start, $batch)
	{
		$db = $this->app->db();

		return $db->fetchAllColumn($db->limit(
			"
				SELECT support_ticket_id
				FROM xf_mjst_ticket
				WHERE support_ticket_id > ?
				ORDER BY support_ticket_id
			", $batch
		), $start);
	}

	protected function rebuildById($id)
	{
		/** @var \MJ\SupportTicket\Entity\Ticket $ticket */
		$ticket = $this->app->em()->find('MJ\SupportTicket:Ticket', $id);
		if (!$ticket)
		{
			return;
		}

		$updated = false;

		if ($ticket->rebuildCounters())
		{
			$ticket->save();
			$updated = true;
		}
		// note: don't delete the ticket if this fails; a redirect has no posts for example

		/** @var \MJ\SupportTicket\Repository\Ticket $ticketRepo */
		$ticketRepo = $this->app->repository('MJ\SupportTicket:Ticket');

		if ($updated && $this->data['position_rebuild'])
		{
			$ticketRepo->rebuildTicketMessagePositions($id);
		}
	}

	protected function getStatusType()
	{
		return \XF::phrase('mjst_tickets');
	}
}
