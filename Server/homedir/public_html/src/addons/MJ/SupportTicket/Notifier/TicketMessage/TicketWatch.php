<?php

namespace MJ\SupportTicket\Notifier\TicketMessage;

class TicketWatch extends AbstractWatch
{
	protected function getApplicableActionTypes()
	{
		return ['reply'];
	}

	public function getDefaultWatchNotifyData()
	{
		$message = $this->message;

		if ($message->isFirstMessage())
		{
			return [];
		}

		$finder = $this->app()->finder('MJ\SupportTicket:TicketWatch');

		$finder->where('support_ticket_id', $message->support_ticket_id)
			->where('User.user_state', '=', 'valid')
			->where('User.is_banned', '=', 0);

		$activeLimit = $this->app()->options()->watchAlertActiveOnly;
		if (!empty($activeLimit['enabled']))
		{
			$finder->where('User.last_activity', '>=', \XF::$time - 86400 * $activeLimit['days']);
		}

		$notifyData = [];
		foreach ($finder->fetchColumns(['user_id', 'email_subscribe']) as $watch)
		{
			$notifyData[$watch['user_id']] = [
				'alert' => true,
				'email' => (bool)$watch['email_subscribe']
			];
		}
		if($this->app()->options->mjstGuestNotify &&
			!$message->Ticket->user_id &&
			$message->Ticket->user_email
		){
			$notifyData[$message->Ticket->user_email] = [
				'userEmail' => $message->Ticket->user_email,
				'username'  => $message->Ticket->username,
				'alert'     => false,
				'email'     => true
			];
		}
		return $notifyData;
	}

	protected function getWatchEmailTemplateName()
	{
		return 'mjst_watched_ticket_reply';
	}
}
