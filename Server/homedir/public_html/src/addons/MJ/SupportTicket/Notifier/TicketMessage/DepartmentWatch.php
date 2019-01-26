<?php

namespace MJ\SupportTicket\Notifier\TicketMessage;

class DepartmentWatch extends AbstractWatch
{
	protected function getApplicableActionTypes()
	{
		return ['reply', 'ticket'];
	}

	public function getDefaultWatchNotifyData()
	{
		$message = $this->message;

		$finder = $this->app()->finder('MJ\SupportTicket:DepartmentWatch');

		$finder->where('department_id', $message->Ticket->department_id)
			->where('User.user_state', '=', 'valid')
			->where('User.is_banned', '=', 0)
			->whereOr(
				['send_alert', '>', 0],
				['send_email', '>', 0]
			);

		if ($this->actionType == 'reply')
		{
			$finder->where('notify_on', 'message');
		}
		else
		{
			$finder->where('notify_on', ['ticket', 'message']);
		}

		$activeLimit = $this->app()->options()->watchAlertActiveOnly;
		if (!empty($activeLimit['enabled']))
		{
			$finder->where('User.last_activity', '>=', \XF::$time - 86400 * $activeLimit['days']);
		}

		$notifyData = [];
		foreach ($finder->fetchColumns(['user_id', 'send_alert', 'send_email']) as $watch)
		{
			$notifyData[$watch['user_id']] = [
				'alert' => (bool)$watch['send_alert'],
				'email' => (bool)$watch['send_email']
			];
		}

		return $notifyData;
	}

	protected function getWatchEmailTemplateName()
	{
		return 'mjst_watched_department_' . ($this->actionType == 'ticket' ? 'ticket' : 'reply');
	}
}
