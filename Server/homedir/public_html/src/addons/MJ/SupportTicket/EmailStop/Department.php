<?php

namespace MJ\SupportTicket\EmailStop;

class Department extends \XF\EmailStop\AbstractHandler
{
	public function getStopOneText(\XF\Entity\User $user, $contentId)
	{
		/** @var \MJ\SupportTicket\Entity\Department|null $department */
		$department = \XF::em()->find('MJ\SupportTicket:Department', $contentId);
		$canView = \XF::asVisitor(
			$user,
			function() use ($department)
			{
				return $department && $department->canView();
			}
		);

		if ($canView)
		{
			return \XF::phrase('stop_notification_emails_from_x', ['title' => $department->title]);
		}
		else
		{
			return null;
		}
	}

	public function getStopAllText(\XF\Entity\User $user)
	{
		return \XF::phrase('mjst_stop_notification_emails_from_all_tickets');
	}

	public function stopOne(\XF\Entity\User $user, $contentId)
	{
		/** @var \MJ\SupportTicket\Entity\Department $department */
		$department = \XF::em()->find('MJ\SupportTicket:Department', $contentId);
		if ($department)
		{
			/** @var \MJ\SupportTicket\Repository\DepartmentWatch $departmentWatchRepo */
			$departmentWatchRepo = \XF::repository('MJ\SupportTicket:DepartmentWatch');
			$departmentWatchRepo->setWatchState($department, $user, null, null, false);
		}
	}

	public function stopAll(\XF\Entity\User $user)
	{
		// Note that we stop all ticket and department notifications here, as the distinction of the source is unlikely
		// to be clear and they've chosen to stop all emails of this type.

		/** @var \MJ\SupportTicket\Repository\TicketWatch $ticketWatchRepo */
		$ticketWatchRepo = \XF::repository('MJ\SupportTicket:TicketWatch');
		$ticketWatchRepo->setWatchStateForAll($user, 'no_email');

		/** @var \MJ\SupportTicket\Repository\DepartmentWatch $departmentWatchRepo */
		$departmentWatchRepo = \XF::repository('MJ\SupportTicket:DepartmentWatch');
		$departmentWatchRepo->setWatchStateForAll($user, 'no_email');
	}
}
