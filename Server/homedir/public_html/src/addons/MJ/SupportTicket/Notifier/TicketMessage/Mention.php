<?php

namespace MJ\SupportTicket\Notifier\TicketMessage;

use XF\Notifier\AbstractNotifier;

class Mention extends AbstractNotifier
{
	/**
	 * @var \MJ\SupportTicket\Entity\TicketMessage
	 */
	protected $message;

	public function __construct(\XF\App $app, \MJ\SupportTicket\Entity\TicketMessage $message)
	{
		parent::__construct($app);

		$this->message = $message;
	}

	public function canNotify(\XF\Entity\User $user)
	{
		return ($user->user_id != $this->message->user_id);
	}

	public function sendAlert(\XF\Entity\User $user)
	{
		$message = $this->message;
		return $this->basicAlert($user, $message->user_id, $message->username, 'support_ticket_message', $message->message_id, 'mention');
	}
}
