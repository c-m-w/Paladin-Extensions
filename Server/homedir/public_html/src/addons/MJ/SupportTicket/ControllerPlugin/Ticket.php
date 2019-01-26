<?php

namespace MJ\SupportTicket\ControllerPlugin;

use XF\ControllerPlugin\AbstractPlugin;

use XF\Mvc\Entity\Entity;
use XF\Mvc\FormAction;

class Ticket extends AbstractPlugin
{
	public function getMessageLink(\MJ\SupportTicket\Entity\TicketMessage $message)
	{
		$ticket = $message->Ticket;
		if (!$ticket)
		{
			throw new \LogicException("Message has no ticket");
		}

		$page = floor($message->position / $this->options()->messagesPerPage) + 1;

		return $this->buildLink('support-tickets', $ticket, ['page' => $page]) . '#message-' . $message->message_id;
	}
}
