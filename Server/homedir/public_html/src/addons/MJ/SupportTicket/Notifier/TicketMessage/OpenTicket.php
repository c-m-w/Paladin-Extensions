<?php

namespace MJ\SupportTicket\Notifier\TicketMessage;

use XF\Notifier\AbstractNotifier;

class OpenTicket extends AbstractNotifier
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
		return ($user->user_id == $this->message->user_id);
	}

	public function sendAlert(\XF\Entity\User $user)
	{
		$message = $this->message;
		if(!$message->user_id){
			return false;
		}

		return $this->basicAlert($user, $message->user_id, $message->username, 'support_ticket_message', $message->message_id, 'open');
	}

	public function sendEmail(\XF\Entity\User $user)
	{
		if (!$user->email || ($user->user_id && $user->user_state != 'valid'))
		{
			return false;
		}

		$message = $this->message;

		$params = [
			'message'    => $message,
			'ticket'     => $message->Ticket,
			'department' => $message->Ticket->Department,
			'receiver'   => $user,
			'creator'    => $message->Ticket->Creator,
		];

		$template = $this->getWatchEmailTemplateName();
		$mail = $this->app()->mailer()->newMail()
			->setToUser($user)
			->setTemplate($template, $params);
		$result = $mail->queue();
		return true;
	}

	protected function getWatchEmailTemplateName()
	{
		return 'mjst_new_ticket';
	}
}
