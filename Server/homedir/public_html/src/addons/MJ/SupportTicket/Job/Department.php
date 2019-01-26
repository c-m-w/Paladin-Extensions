<?php

namespace MJ\SupportTicket\Job;

use XF\Job\AbstractRebuildJob;

class Department extends AbstractRebuildJob
{
	protected function getNextIds($start, $batch)
	{
		$db = $this->app->db();

		return $db->fetchAllColumn($db->limit(
			"
				SELECT department_id
				FROM xf_mjst_department
				WHERE department_id > ?
				ORDER BY department_id
			", $batch
		), $start);
	}

	protected function rebuildById($id)
	{
		/** @var \MJ\SupportTicket\Entity\Department $department */
		$department = $this->app->em()->find('MJ\SupportTicket:Department', $id);
		if ($department)
		{
			$department->rebuildCounters();
			$department->save();
		}
	}

	protected function getStatusType()
	{
		return \XF::phrase('mjst_ticket_departments');
	}
}
