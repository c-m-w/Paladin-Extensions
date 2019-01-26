<?php

namespace MJ\SupportTicket\Service\Ticket;

use MJ\SupportTicket\Entity\Ticket;

class Deleter extends \XF\Service\AbstractService
{
	/**
	 * @var Ticket
	 */
	protected $ticket;

	protected $user;

	protected $alert = false;
	protected $alertReason = '';

	public function __construct(\XF\App $app, Ticket $ticket)
	{
		parent::__construct($app);
		$this->ticket = $ticket;
	}

	public function getTicket()
	{
		return $this->ticket;
	}

	public function setUser(\XF\Entity\User $user = null)
	{
		$this->user = $user;
	}

	public function getUser()
	{
		return $this->user;
	}

	public function setSendAlert($alert, $reason = null)
	{
		$this->alert = (bool)$alert;
		if ($reason !== null)
		{
			$this->alertReason = $reason;
		}
	}

	public function delete($reason = '')
	{
		$user = $this->user ?: \XF::visitor();

		$result = $this->ticket->delete();

		if ($result
			&& $this->alert
			&& $this->ticket->user_id != $user->user_id
		)
		{
			/** @var \MJ\SupportTicket\Repository\Ticket $ticketRepo */
			$ticketRepo = $this->repository('MJ\SupportTicket:Ticket');
			$ticketRepo->sendModeratorActionAlert($this->ticket, 'delete', $this->alertReason);
		}
		return $result;
	}
}
