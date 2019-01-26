<?php

namespace MJ\SupportTicket\Service\Ticket;

use MJ\SupportTicket\Entity\Ticket;
use MJ\SupportTicket\Entity\User;

class Mover extends \XF\Service\AbstractService
{
	/**
	 * @var Ticket
	 */
	protected $ticket;

	protected $alert = false;
	protected $alertReason = '';

	protected $notifyWatchers = false;

	protected $prefixId = null;

	protected $extraSetup = [];

	public function __construct(\XF\App $app, Ticket $ticket)
	{
		parent::__construct($app);

		$this->ticket = $ticket;
	}

	public function getTicket()
	{
		return $this->ticket;
	}

	public function setSendAlert($alert, $reason = null)
	{
		$this->alert = (bool)$alert;
		if ($reason !== null)
		{
			$this->alertReason = $reason;
		}
	}

	public function setPrefix($prefixId)
	{
		$this->prefixId = ($prefixId === null ? $prefixId : intval($prefixId));
	}

	public function setNotifyWatchers($value = true)
	{
		$this->notifyWatchers = (bool)$value;
	}

	public function addExtraSetup(callable $extra)
	{
		$this->extraSetup[] = $extra;
	}

	public function move(\MJ\SupportTicket\Entity\Department $department)
	{
		$actor = \XF::visitor();

		$ticket = $this->ticket;
		$oldDepartment = $ticket->Department;

		$moved = ($ticket->department_id != $department->department_id);

		foreach ($this->extraSetup as $extra)
		{
			call_user_func($extra, $ticket, $department);
		}

		$ticket->department_id = $department->department_id;
		if ($this->prefixId !== null)
		{
			$ticket->prefix_id = $this->prefixId;
		}

		if (!$ticket->preSave())
		{
			throw new \XF\PrintableException($ticket->getErrors());
		}

		$db = $this->db();
		$db->beginTransaction();

		$ticket->save(true, false);

		$db->commit();

		if ($moved
			&& $this->alert
			&& $ticket->user_id != $actor->user_id
		)
		{
			/** @var \MJ\SupportTicket\Repository\Ticket $ticketRepo */
			$ticketRepo = $this->repository('MJ\SupportTicket:Ticket');
			$ticketRepo->sendModeratorActionAlert($ticket, 'move', $this->alertReason);
		}

		if ($moved
			&& $this->notifyWatchers
			&& $ticket->FirstMessage
		)
		{
			/** @var \MJ\SupportTicket\Service\TicketMessage\Notifier $notifier */
			$notifier = $this->service('MJ\SupportTicket:TicketMessage\Notifier', $ticket->FirstMessage, 'ticket');
			if ($oldDepartment)
			{
				$notifier->skipUsersWatchingDepartment($oldDepartment);
			}
			$notifier->notifyAndEnqueue(3);
		}

		return $moved;
	}
}
