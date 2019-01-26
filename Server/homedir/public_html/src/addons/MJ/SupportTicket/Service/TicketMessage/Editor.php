<?php

namespace MJ\SupportTicket\Service\TicketMessage;

use MJ\SupportTicket\Entity\TicketMessage;

class Editor extends \XF\Service\AbstractService
{
	use \XF\Service\ValidateAndSavableTrait;

	/**
	 * @var TicketMessage
	 */
	protected $message;

	/**
	 * @var \XF\Service\TicketMessage\Preparer
	 */
	protected $messagePreparer;

	protected $oldMessage;

	protected $logDelay;
	protected $logEdit = true;
	protected $logHistory = true;

	protected $alert = false;
	protected $alertReason = '';

	protected $performValidations = true;

	public function __construct(\XF\App $app, TicketMessage $message)
	{
		parent::__construct($app);
		$this->setTicketMessage($message);
	}

	protected function setTicketMessage(TicketMessage $message)
	{
		$this->message = $message;
		$this->messagePreparer = $this->service('MJ\SupportTicket:TicketMessage\Preparer', $this->message);
	}

	public function getTicketMessage()
	{
		return $this->message;
	}

	public function logDelay($logDelay)
	{
		$this->logDelay = $logDelay;
	}

	public function logEdit($logEdit)
	{
		$this->logEdit = $logEdit;
	}

	public function logHistory($logHistory)
	{
		$this->logHistory = $logHistory;
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
		$this->setPerformValidations(false);
	}

	public function getTicketMessagePreparer()
	{
		return $this->messagePreparer;
	}

	protected function setupEditHistory($oldMessage)
	{
		$message = $this->message;

		$message->edit_count++;

		$options = $this->app->options();
		if ($options->editLogDisplay['enabled'] && $this->logEdit)
		{
			$delay = is_null($this->logDelay) ? $options->editLogDisplay['delay'] * 60 : $this->logDelay;
			if ($message->message_date + $delay <= \XF::$time)
			{
				$message->last_edit_date = \XF::$time;
				$message->last_edit_user_id = \XF::visitor()->user_id;
			}
		}

		if ($options->editHistory['enabled'] && $this->logHistory)
		{
			$this->oldMessage = $oldMessage;
		}
	}

	public function setMessage($message, $format = true)
	{
		$setupHistory = !$this->message->isChanged('message');
		$oldMessage = $this->message->message;

		$result = $this->messagePreparer->setMessage($message, $format, $this->performValidations);

		if ($setupHistory && $result && $this->message->isChanged('message'))
		{
			$this->setupEditHistory($oldMessage);
		}

		return $result;
	}

	public function setAttachmentHash($hash)
	{
		$this->messagePreparer->setAttachmentHash($hash);
	}

	public function setSendAlert($alert, $reason = null)
	{
		$this->alert = (bool)$alert;
		if ($reason !== null)
		{
			$this->alertReason = $reason;
		}
	}

	public function checkForSpam()
	{
		if ($this->message->message_state == 'visible' && \XF::visitor()->isSpamCheckRequired())
		{
			$this->messagePreparer->checkForSpam();
		}
	}

	protected function finalSetup()
	{
	}

	protected function _validate()
	{
		$this->finalSetup();

		$this->message->preSave();
		return $this->message->getErrors();
	}

	protected function _save()
	{
		$message = $this->message;
		$visitor = \XF::visitor();

		$db = $this->db();
		$db->beginTransaction();

		$message->save(true, false);

		$this->messagePreparer->afterUpdate();

		if ($this->oldMessage)
		{
			/** @var \XF\Repository\EditHistory $repo */
			$repo = $this->repository('XF:EditHistory');
			$repo->insertEditHistory('support_ticket_message', $message, $visitor, $this->oldMessage, $this->app->request()->getIp());
		}

		if ($message->message_state == 'visible' && $this->alert && $message->user_id != $visitor->user_id)
		{
			/** @var \MJ\SupportTicket\Repository\TicketMessage $messageRepo */
			$messageRepo = $this->repository('MJ\SupportTicket:TicketMessage');
			$messageRepo->sendModeratorActionAlert($message, 'edit', $this->alertReason);
		}

		$db->commit();

		return $message;
	}
}
