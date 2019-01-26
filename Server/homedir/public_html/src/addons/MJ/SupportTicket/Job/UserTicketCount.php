<?php

namespace MJ\SupportTicket\Job;

use XF\Job\AbstractRebuildJob;

class UserTicketCount extends AbstractRebuildJob
{
	protected function getNextIds($start, $batch)
	{
		$db = $this->app->db();

		return $db->fetchAllColumn($db->limit(
			"
				SELECT user_id
				FROM xf_user
				WHERE user_id > ?
				ORDER BY user_id
			", $batch
		), $start);
	}

	protected function rebuildById($id)
	{
		/** @var \MJ\SupportTicket\Repository\Ticket $repo */
		$repo = $this->app->repository('MJ\SupportTicket:Ticket');
		$count = $repo->getTicketResourceCount($id);

		$this->app->db()->update('xf_user', ['mjst_ticket_count' => $count], 'user_id = ?', $id);
	}

	protected function getStatusType()
	{
		return \XF::phrase('mjst_ticket_counts');
	}
}
