<?php

namespace MJ\SupportTicket\Job;

use XF\Job\AbstractRebuildJob;

class TicketEscalation extends AbstractRebuildJob
{
	protected $defaultData = [
		'position_rebuild' => false
	];

	protected function getNextIds($start, $batch)
	{
		$db = $this->app->db();

		return $db->fetchAllColumn($db->limit(
			"
				SELECT ticket_escalation_id
				FROM xf_mjst_ticket_escalation
				WHERE ticket_escalation_id > ?
				ORDER BY ticket_escalation_id
			", $batch
		), $start);
	}

	protected function rebuildById($id)
	{
		/** @var \MJ\SupportTicket\Entity\TicketEscalation $ticketEscalation */
		$ticketEscalation = $this->app->em()->find('MJ\SupportTicket:TicketEscalation', $id);
		if (!$ticketEscalation)
		{
			return;
		}

		$updated = false;

		if ($ticketEscalation->rebuildCounters())
		{
			$ticketEscalation->save();
			$updated = true;
		}
	}

	protected function getStatusType()
	{
		return \XF::phrase('mjst_ticket_escalations');
	}
}
