<?php

namespace MJ\SupportTicket\Service\Ticket;

use MJ\SupportTicket\Entity\Ticket;

class Editor extends \XF\Service\AbstractService
{
	use \XF\Service\ValidateAndSavableTrait;

	/**
	 * @var Ticket
	 */
	protected $ticket;

	protected $department;

	protected $performValidations = true;

	public function __construct(\XF\App $app, Ticket $ticket)
	{
		parent::__construct($app);
		$this->ticket = $ticket;
		$this->setDepartment($ticket->Department);
	}

	public function getTicket()
	{
		return $this->ticket;
	}

	public function setPerformValidations($perform)
	{
		$this->performValidations = (bool)$perform;
	}

	public function getPerformValidations()
	{
		return $this->performValidations;
	}

	public function setTitle($title)
	{
		$this->ticket->title = $title;
	}

	public function setPrefix($prefixId)
	{
		$this->ticket->prefix_id = $prefixId;
	}

	public function setDepartment($department)
	{
		$this->department = $department;
		if($department->department_id != $this->ticket->department_id){
			$this->ticket->department_id = $department->department_id;
		}
	}

	public function setStatus($ticketStatusId)
	{
		$this->ticket->ticket_status_id = $ticketStatusId;
	}

	public function setUrgency($urgency)
	{
		$this->ticket->urgency = $urgency;
	}

	public function setCustomFields(array $customFields)
	{
		$ticket = $this->ticket;

		$editMode = $ticket->getFieldEditMode();

		/** @var \XF\CustomField\Set $fieldSet */
		$fieldSet = $ticket->custom_fields;
		$fieldDefinition = $fieldSet->getDefinitionSet()
			->filterEditable($fieldSet, $editMode)
			->filterOnly($ticket->Department->field_cache);

		$customFieldsShown = array_keys($fieldDefinition->getFieldDefinitions());

		if ($customFieldsShown)
		{
			$fieldSet->bulkSet($customFields, $customFieldsShown, $editMode);
		}
	}

	public function setOwner($userId, $username)
	{
		$this->ticket->user_id = $userId;
		$this->ticket->username = $username;
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
	}

	protected function _validate()
	{
		$this->finalSetup();

		$ticket = $this->ticket;

		$ticket->preSave();
		$errors = $ticket->getErrors();

		if ($this->performValidations)
		{
			if (!$ticket->prefix_id
				&& $ticket->Department->require_prefix
				&& $ticket->Department->getUsablePrefixes()
				&& !$ticket->canMove()
			)
			{
				$errors[] = \XF::phraseDeferred('please_select_a_prefix');
			}

			// the canMove check allows moderators to bypass this requirement when editing; they're likely editing
			// another user's ticket so don't force them to add a prefix
		}

		return $errors;
	}

	protected function _save()
	{
		$ticket = $this->ticket;

		$ticket->save(true, false);

		return $ticket;
	}
}
