<?php

namespace MJ\SupportTicket\Service\TicketMessage;

use MJ\SupportTicket\Entity\TicketMessage;

class Approver extends \XF\Service\AbstractService
{
	/**
	 * @var TicketMessage
	 */
	protected $message;

	protected $notifyRunTime = 3;

	public function __construct(\XF\App $app, TicketMessage $message)
	{
		parent::__construct($app);
		$this->message = $message;
	}

	public function getMessage()
	{
		return $this->message;
	}

	public function setNotifyRunTime($time)
	{
		$this->notifyRunTime = $time;
	}

	public function approve()
	{
		if ($this->message->message_state == 'moderated')
		{
			$this->message->message_state = 'visible';
			$this->message->save();

			$this->onApprove();
			return true;
		}
		else
		{
			return false;
		}
	}

	protected function onApprove()
	{
		/** @var \MJ\SupportTicket\Service\TicketMessage\Notifier $notifier */
		$notifier = $this->service('MJ\SupportTicket:TicketMessage\Notifier', $this->message, 'reply');
		$notifier->notifyAndEnqueue($this->notifyRunTime);
	}
}
