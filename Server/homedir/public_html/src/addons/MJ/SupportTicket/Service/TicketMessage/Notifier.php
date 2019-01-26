<?php

namespace MJ\SupportTicket\Service\TicketMessage;

use MJ\SupportTicket\Entity\TicketMessage;
use XF\Service\AbstractNotifier;

class Notifier extends AbstractNotifier
{
	/**
	 * @var TicketMessage
	 */
	protected $message;

	protected $actionType;

	public function __construct(\XF\App $app, TicketMessage $message, $actionType)
	{
		parent::__construct($app);

		switch ($actionType)
		{
			case 'reply':
			case 'ticket':
				break;

			default:
				throw new \InvalidArgumentException("Unknown action type '$actionType'");
		}

		$this->actionType = $actionType;
		$this->message = $message;
	}

	public static function createForJob(array $extraData)
	{
		$message = \XF::app()->find('MJ\SupportTicket:TicketMessage', $extraData['messageId'], ['Ticket', 'Ticket.Department']);
		if (!$message)
		{
			return null;
		}

		return \XF::service('MJ\SupportTicket:TicketMessage\Notifier', $message, $extraData['actionType']);
	}

	protected function getExtraJobData()
	{
		return [
			'messageId' => $this->message->message_id,
			'actionType' => $this->actionType
		];
	}

	protected function loadNotifiers()
	{
		$notifiers = [
			'quote'           => $this->app->notifier('MJ\SupportTicket:TicketMessage\Quote', $this->message),
			'mention'         => $this->app->notifier('MJ\SupportTicket:TicketMessage\Mention', $this->message),
			'departmentWatch' => $this->app->notifier('MJ\SupportTicket:TicketMessage\DepartmentWatch', $this->message, $this->actionType),
		];

		// if this is not the last message, then another notification would have been triggered already
		if ($this->message->isFirstMessage())
		{
			$notifiers['openTicket'] = $this->app->notifier(
				'MJ\SupportTicket:TicketMessage\OpenTicket',
				$this->message
			);
		}
		if ($this->message->isLastMessage())
		{
			$notifiers['ticketWatch'] = $this->app->notifier(
				'MJ\SupportTicket:TicketMessage\TicketWatch',
				$this->message,
				$this->actionType
			);
		}

		return $notifiers;
	}

	protected function loadExtraUserData(array $users)
	{
		$permCombinationIds = [];
		foreach ($users as $user)
		{
			$id = $user->permission_combination_id;
			$permCombinationIds[$id] = $id;
		}

		$this->app->permissionCache()->cacheMultipleContentPermsForContent(
			$permCombinationIds,
			'department',
			$this->message->Ticket->department_id
		);
	}

	protected function canUserViewContent(\XF\Entity\User $user)
	{
		return \XF::asVisitor(
			$user,
			function() {
				return $this->message->canView();
			}
		);
	}

	protected function notifyType(\XF\Notifier\AbstractNotifier $notifier, array $data, $endTime = null)
	{
		$userRepo = $this->repository('XF:User');
		$disableEmail = \XF::options()->mjstDisableEmail;
		do
		{
			$notifyUsers = array_slice($data, 0, self::USERS_PER_CYCLE, true);

			$users = $notifier->getUserData(array_keys($notifyUsers));

			$this->loadExtraUserData($users);

			foreach ($notifyUsers as $userId => $notify)
			{
				unset($data[$userId]);

				$sendEmail = true;

				if(strpos($userId, '@') !== false){
					$user = $userRepo->getGuestUser($notify['username']);
					$user->setReadOnly(false);
					$user->setAsSaved('email', $notify['userEmail']);
					$user->setReadOnly(true);

					$sendEmail = !$disableEmail;
				}else{
					if (!isset($users[$userId]))
					{
						continue;
					}

					$user = $users[$userId];
					if (!$this->canUserViewContent($user) || !$notifier->canNotify($user))
					{
						continue;
					}

					$alert = ($notify['alert'] && empty($this->alerted[$userId]));
					if ($alert && $notifier->sendAlert($user))
					{
						$this->alerted[$userId] = true;
					}
					if(!$disableEmail && !$user->Option->email_on_support_ticket ||
						$disableEmail && $user->Option->disable_email_on_support_ticket){
						$sendEmail = false;
					}
				}

				if($sendEmail){
					$email = ($notify['email'] && empty($this->emailed[$userId]));
					if ($email && $notifier->sendEmail($user))
					{
						$this->emailed[$userId] = true;
					}
				}

				if ($endTime && microtime(true) >= $endTime)
				{
					return $data;
				}
			}
		}
		while ($data);

		return $data;
	}

	public function addGuestNotification($type, $username, $userEmail, $email = false)
	{
		$notifiers = $this->getNotifiers();

		if (!isset($notifiers[$type]))
		{
			throw new \InvalidArgumentException("Unknown notification type '$type'");
		}

		$this->notifyData[$type][$userEmail] = [
			'userEmail' => $userEmail,
			'username'  => $username,
			'alert'     => false,
			'email'     => $email
		];
	}

	public function skipUsersWatchingDepartment(\MJ\SupportTicket\Entity\Department $department)
	{
		$watchers = $this->db()->fetchAll("
			SELECT user_id, send_alert, send_email
			FROM xf_mjst_department_watch
			WHERE department_id = ?
				AND (send_alert = 1 OR send_email = 1)
		", $department->department_id);

		foreach ($watchers as $watcher)
		{
			if ($watcher['send_alert'])
			{
				$this->setUserAsAlerted($watcher['user_id']);
			}
			if ($watcher['send_email'])
			{
				$this->setUserAsEmailed($watcher['user_id']);
			}
		}
	}
}
