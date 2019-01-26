<?php

namespace MJ\SupportTicket\Notifier\TicketMessage;

use XF\Notifier\AbstractNotifier;

abstract class AbstractWatch extends AbstractNotifier
{
	/**
	 * @var \MJ\SupportTicket\Entity\TicketMessage
	 */
	protected $message;

	protected $actionType;
	protected $isApplicable;

	protected $userReadDates = [];
	protected $previousMessages = null;

	abstract protected function getDefaultWatchNotifyData();
	abstract protected function getApplicableActionTypes();
	abstract protected function getWatchEmailTemplateName();

	public function __construct(\XF\App $app, \MJ\SupportTicket\Entity\TicketMessage $message, $actionType)
	{
		parent::__construct($app);

		$this->message = $message;
		$this->actionType = $actionType;
		$this->isApplicable = $this->isApplicable();
	}

	protected function isApplicable()
	{
		if (!in_array($this->actionType, $this->getApplicableActionTypes()))
		{
			return false;
		}

		if (!$this->message->isVisible())
		{
			return false;
		}

		return true;
	}

	public function canNotify(\XF\Entity\User $user)
	{
		if (!$this->isApplicable)
		{
			return false;
		}

		if (!isset($this->userReadDates[$user->user_id]))
		{
			// this should have a record for every user, so generally shouldn't happen
			return false;
		}

		$userReadDate = $this->userReadDates[$user->user_id];
		$message = $this->message;

		if ($user->user_id == $message->user_id || $user->isIgnoring($message->user_id))
		{
			return false;
		}

		if ($userReadDate > $message->Ticket->last_message_date)
		{
			return false;
		}

		if ($this->actionType == 'reply')
		{
			$previousVisibleMessage = null;
			foreach ($this->getPreviousMessages() as $previousMessage)
			{
				if (!$user->isIgnoring($previousMessage->user_id))
				{
					$previousVisibleMessage = $previousMessage;
					break;
				}
			}

			$autoReadDate = \XF::$time - $this->app()->options()->readMarkingDataLifetime * 86400;
			if (!$previousVisibleMessage || $previousVisibleMessage->message_date < $autoReadDate)
			{
				// always alert
			}
			else if ($previousVisibleMessage->message_date > $userReadDate)
			{
				return false;
			}
		}

		return true;
	}

	public function sendAlert(\XF\Entity\User $user)
	{
		$message = $this->message;

		return $this->basicAlert($user, $message->user_id, $message->username, 'support_ticket_message', $message->message_id, 'insert');
	}

	public function sendEmail(\XF\Entity\User $user)
	{
		if (!$user->email || $user->user_state != 'valid')
		{
			return false;
		}

		$message = $this->message;

		$params = [
			'message'    => $message,
			'ticket'     => $message->Ticket,
			'department' => $message->Ticket->Department,
			'receiver'   => $user
		];

		$template = $this->getWatchEmailTemplateName();

		$this->app()->mailer()->newMail()
			->setToUser($user)
			->setTemplate($template, $params)
			->queue();

		return true;
	}

	public function getDefaultNotifyData()
	{
		if (!$this->isApplicable)
		{
			return [];
		}

		return $this->getDefaultWatchNotifyData();
	}

	public function getUserData(array $userIds)
	{
		$users = parent::getUserData($userIds);
		$this->userReadDates = $this->getUserReadDates($userIds);

		return $users;
	}

	protected function getUserReadDates(array $userIds)
	{
		if (!$userIds)
		{
			return [];
		}

		$autoReadDate = \XF::$time - $this->app()->options()->readMarkingDataLifetime * 86400;
		$message = $this->message;

		$db = $this->app()->db();
		$readDates = $db->fetchPairs("
			SELECT user.user_id,
				GREATEST(
					COALESCE(ticket_read.support_ticket_read_date, 0),
					?
				)
			FROM xf_user AS user
			LEFT JOIN xf_mjst_ticket_read AS ticket_read ON
				(ticket_read.user_id = user.user_id AND ticket_read.support_ticket_id = ?)
			WHERE user.user_id IN (" . $db->quote($userIds) . ")
		", [$autoReadDate, $message->support_ticket_id]);

		foreach ($userIds as $userId)
		{
			if (!isset($readDates[$userId]))
			{
				$readDates[$userId] = $autoReadDate;
			}
		}

		return $readDates;
	}

	protected function getPreviousMessages()
	{
		if ($this->previousMessages === null)
		{
			$autoReadDate = \XF::$time - $this->app()->options()->readMarkingDataLifetime * 86400;

			$finder = $this->app()->finder('MJ\SupportTicket:TicketMessage')
				->where('support_ticket_id', $this->message->support_ticket_id)
				->where('message_state', 'visible')
				->where('message_date', '<', $this->message->message_date)
				->where('message_date', '>=', $autoReadDate)
				->order('message_date', 'desc');

			$this->previousMessages = $finder->fetch(15);
		}

		return $this->previousMessages;
	}
}
