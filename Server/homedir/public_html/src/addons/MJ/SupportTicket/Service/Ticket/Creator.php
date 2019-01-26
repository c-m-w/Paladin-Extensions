<?php

namespace MJ\SupportTicket\Service\Ticket;

use MJ\SupportTicket\Entity\Department;
use MJ\SupportTicket\Entity\TicketMessage;
use MJ\SupportTicket\Entity\Ticket;
use XF\Entity\User;

class Creator extends \XF\Service\AbstractService
{
	use \XF\Service\ValidateAndSavableTrait;

	/**
	 * @var Department
	 */
	protected $department;

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
	 * @var \XF\Service\TicketMessage\Preparer
	 */
	protected $messagePreparer;

	protected $performValidations = true;

	public function __construct(\XF\App $app, Department $department)
	{
		parent::__construct($app);
		$this->department = $department;
		$this->setupDefaults();
	}

	protected function setupDefaults()
	{
		$this->ticket = $this->department->getNewTicket();
		$this->message = $this->ticket->getNewMessage();

		$this->messagePreparer = $this->service('MJ\SupportTicket:TicketMessage\Preparer', $this->message);

		$this->ticket->addCascadedSave($this->message);
		$this->message->hydrateRelation('Ticket', $this->ticket);

		$user = \XF::visitor();
		$this->setUser($user);

		$this->ticket->ticket_status_id = Ticket::STATUS_OPEN;

		$this->message->message_state = 'visible';
	}

	public function getDepartment()
	{
		return $this->department;
	}

	public function getTicket()
	{
		return $this->ticket;
	}

	public function getMessage()
	{
		return $this->message;
	}

	public function getUser()
	{
		return $this->user;
	}

	public function getTicketMessagePreparer()
	{
		return $this->messagePreparer;
	}

	public function setEmail($email, &$error = null)
	{
		if (!$this->validateEmail($email, $error))
		{
			return false;
		}
		$this->ticket->user_email = $email;
		return true;
	}

	public function setOwner($userId, $username)
	{
		$this->ticket->user_id = $userId;
		$this->ticket->username = $username;
	}

	protected function setUser(\XF\Entity\User $user)
	{
		$this->user = $user;

		$this->ticket->user_id = $user->user_id;
		$this->ticket->username = $user->username;

		$this->ticket->creator_user_id = $user->user_id;
		if($user->email){
			$this->ticket->user_email = $user->email;
		}
		$this->ticket->creator_username = $user->username;

		$this->message->user_id = $user->user_id;
		$this->message->username = $user->username;
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

	public function logIp($logIp)
	{
		$this->messagePreparer->logIp($logIp);
	}

	public function setContent($title, $message, $format = true)
	{
		$this->ticket->set(
			'title',
			$title,
			['forceConstraint' => $this->performValidations ? false : true]
		);

		return $this->messagePreparer->setMessage($message, $format, $this->performValidations);
	}

	public function setUrgency($urgency)
	{
		$this->ticket->urgency = $urgency;
	}

	public function setPrefix($prefixId)
	{
		$this->ticket->prefix_id = $prefixId;
	}

	public function setAttachmentHash($hash)
	{
		$this->messagePreparer->setAttachmentHash($hash);
	}

	public function setCustomFields(array $customFields)
	{
		/** @var \XF\CustomField\Set $fieldSet */
		$fieldSet = $this->ticket->custom_fields;
		$fieldDefinition = $fieldSet->getDefinitionSet()
			->filterEditable($fieldSet, 'user')
			->filterOnly($this->department->field_cache);

		$customFieldsShown = array_keys($fieldDefinition->getFieldDefinitions());

		if ($customFieldsShown)
		{
			$fieldSet->bulkSet($customFields, $customFieldsShown);
		}
	}

	public function checkForSpam()
	{
		if ($this->user->isSpamCheckRequired())
		{
			$this->messagePreparer->checkForSpam();
		}
	}

	protected function validateEmail(&$email, &$error = null)
	{
		$validator = $this->app->validator('Email');
		$email = $validator->coerceValue($email);
		if (!$validator->isValid($email))
		{
			$error = \XF::phrase('please_enter_valid_email');
			return false;
		}
		return true;
	}

	protected function finalSetup()
	{
		$date = time();

		$this->ticket->open_date = $date;
		$this->ticket->last_message_date = $date;
		$this->ticket->last_message_user_id = $this->ticket->creator_user_id;
		$this->ticket->last_message_username = $this->ticket->creator_username;

		$this->message->message_date = $date;
		$this->message->position = 0;

		if($this->ticket->user_id != $this->ticket->creator_user_id){
			$this->ticket->ticket_status_id = Ticket::STATUS_AWAITING;
		}else{
			$this->ticket->ticket_status_id = Ticket::STATUS_OPEN;
		}
	}

	protected function _validate()
	{
		$this->finalSetup();

		$ticket = $this->ticket;

		if (!$ticket->user_id)
		{
			/** @var \XF\Validator\Username $validator */
			$validator = $this->app->validator('Username');
			$ticket->username = $validator->coerceValue($ticket->username);
			$this->message->username = $ticket->username;

			if ($this->performValidations && !$validator->isValid($ticket->username, $error))
			{
				return [
					$validator->getPrintableErrorValue($error)
				];
			}
		}

		$ticket->preSave();
		$errors = $ticket->getErrors();

		if ($this->performValidations)
		{
			if (!$ticket->prefix_id
				&& $this->department->require_prefix
				&& $this->department->getUsablePrefixes()
			)
			{
				$errors[] = \XF::phraseDeferred('please_select_a_prefix');
			}
		}

		return $errors;
	}

	protected function _save()
	{
		$department = $this->department;
		$ticket = $this->ticket;
		$message = $this->message;

		$db = $this->db();
		$db->beginTransaction();

		$ticket->save(true, false);
		// message will also be saved now

		$ticket->fastUpdate([
			'first_message_id' => $message->message_id,
			'last_message_id' => $message->message_id
		]);

		$this->messagePreparer->afterInsert();

		$db->commit();

		return $ticket;
	}

	public function sendNotifications()
	{
		/** @var \MJ\SupportTicket\Service\TicketMessage\Notifier $notifier */
		$notifier = $this->service('MJ\SupportTicket:TicketMessage\Notifier', $this->message, 'ticket');
		$notifier->setMentionedUserIds($this->messagePreparer->getMentionedUserIds());
		$notifier->setQuotedUserIds($this->messagePreparer->getQuotedUserIds());

		if($this->ticket->user_id){
			$notifier->addNotifications('openTicket', [$this->ticket->user_id], true, true);
		}else{
			$notifier->addGuestNotification('openTicket', $this->ticket->username, $this->ticket->user_email, true);
		}


		$notifier->notifyAndEnqueue(3);
	}
}
