<?php

namespace MJ\SupportTicket\Service\TicketMessage;

use MJ\SupportTicket\Entity\TicketMessage;
use XF\Entity\User;

class Deleter extends \XF\Service\AbstractService
{
	/**
	 * @var TicketMessage
	 */
	protected $message;

	/**
	 * @var User
	 */
	protected $user;

	protected $alert = false;
	protected $alertReason = '';

	protected $ticketDeleted = false;

	public function __construct(\XF\App $app, TicketMessage $message)
	{
		parent::__construct($app);
		$this->message = $message;
		$this->setUser(\XF::visitor());
	}

	public function getMessage()
	{
		return $this->message;
	}

	protected function setUser(\XF\Entity\User $user)
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

	public function delete($type, $reason = '')
	{
		$deleteTicket = $this->isTicketDeleteRequired($type);

		$user = $this->user;

		/** @var \MJ\SupportTicket\Entity\Ticket $ticket */
		$ticket = $this->message->Ticket;

		$result = null;
		$this->ticketDeleted = $deleteTicket;

		$wasVisible = $this->message->message_state == 'visible';

		if ($type == 'soft')
		{
			if ($deleteTicket)
			{
				if ($ticket)
				{
					$result = $ticket->delete();
				}
			}
			else
			{
				$result = $this->message->softDelete($reason, $user);
			}
		}
		else
		{
			if ($deleteTicket)
			{
				if ($ticket)
				{
					$result = $ticket->delete();
				}
			}
			else
			{
				$result = $this->message->delete();
			}
		}

		if ($result && $wasVisible && $this->alert && $this->message->user_id != $user->user_id)
		{
			/** @var \MJ\SupportTicket\Repository\TicketMessage $messageRepo */
			$messageRepo = $this->repository('MJ\SupportTicket:TicketMessage');
			$messageRepo->sendModeratorActionAlert($this->message, 'delete', $this->alertReason);
		}

		return $result;
	}

	public function wasTicketDeleted()
	{
		return $this->ticketDeleted;
	}

	protected function isTicketDeleteRequired($type)
	{
		return $this->message->isFirstMessage();
	}
}
