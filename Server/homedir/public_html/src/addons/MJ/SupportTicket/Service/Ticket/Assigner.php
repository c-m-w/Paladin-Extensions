<?php

namespace MJ\SupportTicket\Service\Ticket;

use MJ\SupportTicket\Entity\Ticket;

class Assigner extends \XF\Service\AbstractService
{
	/**
	 * @var Ticket
	 */
	protected $ticket;

	protected $user;

	protected $alert = true;

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

	public function assign()
	{
		$visitor = \XF::visitor();
		$user = $this->user ?: $visitor;

		$ticket = $this->ticket;
		if(!$user->mjst_department_ids || !in_array($ticket->department_id, $user->mjst_department_ids)){
			throw new \XF\PrintableException(\XF::phrase('mjst_this_user_not_member_of_this_department'));
		}

		$ticket->assigned_user_id = $user->user_id;
		$ticket->save();

		if ($this->alert
			&& $visitor->user_id != $user->user_id
		)
		{
			/** @var \XF\Repository\UserAlert $alertRepo */
			$alertRepo = $this->repository('XF:UserAlert');
			$alertRepo->alert(
				$user,
				$visitor->user_id,
				$visitor->username,
				'support_ticket',
				$this->ticket->support_ticket_id,
				'assign'
			);
		}
		return true;
	}
}
