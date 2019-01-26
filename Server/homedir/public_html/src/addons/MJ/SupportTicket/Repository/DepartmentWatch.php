<?php

namespace MJ\SupportTicket\Repository;

use XF\Mvc\Entity\Repository;

class DepartmentWatch extends Repository
{
	public function setWatchState(\MJ\SupportTicket\Entity\Department $department, \XF\Entity\User $user, $notifyType = null, $sendAlert = null, $sendEmail = null)
	{
		if (!$department->department_id || !$user->user_id)
		{
			throw new \InvalidArgumentException("Invalid department or user");
		}

		$watch = $this->em->find('MJ\SupportTicket:DepartmentWatch', [
			'department_id' => $department->department_id,
			'user_id' => $user->user_id
		]);

		switch ($notifyType)
		{
			case 'message':
			case 'ticket':
			case '':
			case null:
				if (!$watch)
				{
					$watch = $this->em->create('MJ\SupportTicket:DepartmentWatch');
					$watch->department_id = $department->department_id;
					$watch->user_id = $user->user_id;
				}
				if ($notifyType !== null)
				{
					$watch->notify_on = $notifyType;
				}
				if ($sendAlert !== null)
				{
					$watch->send_alert = $sendAlert;
				}
				if ($sendEmail !== null)
				{
					$watch->send_email = $sendEmail;
				}
				$watch->save();
				break;

			case 'delete':
				if ($watch)
				{
					$watch->delete();
				}
				break;

			default:
				throw new \InvalidArgumentException("Unknown notify type '$notifyType'");
		}
	}

	public function setWatchStateForAll(\XF\Entity\User $user, $state)
	{
		if (!$user->user_id)
		{
			throw new \InvalidArgumentException("Invalid user");
		}

		$db = $this->db();

		switch ($state)
		{
			case 'watch_email':
			case 'email':
				return $db->update('xf_mjst_department_watch', ['send_email' => 1], 'user_id = ?', $user->user_id);

			case 'watch_no_email':
			case 'no_email':
				return $db->update('xf_mjst_department_watch', ['send_email' => 0], 'user_id = ?', $user->user_id);

			case 'watch_alert':
			case 'alert':
				return $db->update('xf_mjst_department_watch', ['send_alert' => 1], 'user_id = ?', $user->user_id);

			case 'watch_no_alert':
			case 'no_alert':
				return $db->update('xf_mjst_department_watch', ['send_alert' => 0], 'user_id = ?', $user->user_id);

			case 'delete':
			case 'stop':
			case '':
				return $db->delete('xf_mjst_department_watch', 'user_id = ?', $user->user_id);

			default:
				throw new \InvalidArgumentException("Unknown state '$state'");
		}
	}

	public function isValidWatchState($state)
	{
		switch ($state)
		{
			case 'watch_email':
			case 'email':
			case 'watch_no_email':
			case 'no_email':
			case 'watch_alert':
			case 'alert':
			case 'watch_no_alert':
			case 'no_alert':
			case 'delete':
			case 'stop':
			case '':
				return true;

			default:
				return false;
		}
	}
}
