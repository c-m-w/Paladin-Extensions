<?php

namespace MJ\SupportTicket\Service\Ticket;

use MJ\SupportTicket\Entity\Ticket;

class Closer extends \XF\Service\AbstractService
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

	public function setSendAlert($alert)
	{
		$this->alert = (bool)$alert;
	}

	public function close()
	{
		$user = $this->user ?: \XF::visitor();

		$ticket = $this->ticket;
		$ticket->ticket_status_id = Ticket::STATUS_CLOSED;
		$ticket->save();
		return true;
	}
}
