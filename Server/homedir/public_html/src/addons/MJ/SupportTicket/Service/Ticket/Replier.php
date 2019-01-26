<?php

namespace MJ\SupportTicket\Service\Ticket;

use MJ\SupportTicket\Entity\TicketMessage;
use MJ\SupportTicket\Entity\Ticket;
use XF\Entity\User;

class Replier extends \XF\Service\AbstractService
{
	use \XF\Service\ValidateAndSavableTrait;

	/**
	 * @var Ticket
	 */
	protected $ticket;

	/**
	 * @var TicketMessage
	 */
	protected $message;

	/**
	 * @var User
	 */
	protected $user;

	/**
	 * @var \MJ\SupportTicket\Service\TicketMessage\Preparer
	 */
	protected $messagePreparer;

	protected $performValidations = true;

	public function __construct(\XF\App $app, Ticket $ticket, User $user = null)
	{
		parent::__construct($app);
		$this->setTicket($ticket);
		if($user){
			$this->setUser($user);
		}else{
			$this->setUser(\XF::visitor());
		}

		$this->setMessageDefaults();
	}

	protected function setTicket(Ticket $ticket)
	{
		$this->ticket = $ticket;
		$this->message = $ticket->getNewMessage();
		$this->messagePreparer = $this->service('MJ\SupportTicket:TicketMessage\Preparer', $this->message);
	}

	public function getTicket()
	{
		return $this->ticket;
	}

	public function getMessage()
	{
		return $this->message;
	}

	public function getMessagePreparer()
	{
		return $this->messagePreparer;
	}

	public function setUser(\XF\Entity\User $user)
	{
		$this->user = $user;
	}

	public function logIp($logIp)
	{
		$this->messagePreparer->logIp($logIp);
	}

	public function setPerformValidations($perform)
	{
		$this->performValidations = (bool)$perform;
	}

	public function getPerformValidations()
	{
		return $this->performValidations;
	}

	public function setIsAutomated()
	{
		$this->logIp(false);
		$this->setPerformValidations(false);
	}

	protected function setMessageDefaults()
	{
		$department = $this->ticket->Department;
		$this->message->message_state = $department->getNewContentState($this->ticket);
		$this->message->user_id = $this->user->user_id;
		$this->message->username = $this->user->username;
	}

	public function setMessage($message, $format = true)
	{
		return $this->messagePreparer->setMessage($message, $format, $this->performValidations);
	}

	public function setAttachmentHash($hash)
	{
		$this->messagePreparer->setAttachmentHash($hash);
	}

	public function checkForSpam()
	{
		if ($this->message->message_state == 'visible' && $this->user->isSpamCheckRequired())
		{
			$this->messagePreparer->checkForSpam();
		}
	}

	protected function finalSetup()
	{
		$this->message->message_date = time();
	}

	protected function _validate()
	{
		$this->finalSetup();

		$message = $this->message;

		if (!$message->user_id)
		{
			/** @var \XF\Validator\Username $validator */
			$validator = $this->app->validator('Username');
			$message->username = $validator->coerceValue($message->username);
			if ($this->performValidations && !$validator->isValid($message->username, $error))
			{
				return [$validator->getPrintableErrorValue($error)];
			}
		}

		$message->preSave();
		$errors = $message->getErrors();

		return $errors;
	}

	protected function _save()
	{
		$message = $this->message;

		$db = $this->db();
		$db->beginTransaction();

		$ticketLatest = $this->db()->fetchRow("
			SELECT *
			FROM xf_mjst_ticket
			WHERE support_ticket_id = ?
			FOR UPDATE
		", $this->ticket->support_ticket_id);

		$this->setMessagePosition($ticketLatest);

		$message->save(true, false);

		$this->messagePreparer->afterInsert();

		$db->commit();

		return $message;
	}

	protected function setMessagePosition(array $ticketInfo)
	{
		$message = $this->message;

		if ($message->message_date < $ticketInfo['last_message_date'])
		{
			throw new \LogicException("Replier can only add messages at the end of a ticket");
		}

		if ($message->message_state == 'visible')
		{
			$position = $ticketInfo['reply_count'] + 1;
		}
		else
		{
			$position = $ticketInfo['reply_count'];
		}

		$message->set('position', $position, ['forceSet' => true]);
	}

	public function sendNotifications()
	{
		if ($this->message->isVisible())
		{
			/** @var \MJ\SupportTicket\Service\TicketMessage\Notifier $notifier */
			$notifier = $this->service('MJ\SupportTicket:TicketMessage\Notifier', $this->message, 'reply');
			$notifier->setMentionedUserIds($this->messagePreparer->getMentionedUserIds());
			$notifier->setQuotedUserIds($this->messagePreparer->getQuotedUserIds());
			$notifier->notifyAndEnqueue(3);
		}
	}
}
