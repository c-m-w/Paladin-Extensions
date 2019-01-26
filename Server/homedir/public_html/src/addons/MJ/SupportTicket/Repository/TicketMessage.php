<?php

namespace MJ\SupportTicket\Repository;

use XF\Mvc\Entity\Repository;

class TicketMessage extends Repository
{
	public function findMessagesForTicketView(\MJ\SupportTicket\Entity\Ticket $ticket, array $limits = [])
	{
		/** @var \MJ\SupportTicket\Finder\TicketMessage $finder */
		$finder = $this->finder('MJ\SupportTicket:TicketMessage');
		$finder
			->inTicket($ticket, $limits)
			->orderByDate()
			->forFullView();

		return $finder;
	}

	public function findNewestMessagesInTicket(\MJ\SupportTicket\Entity\Ticket $ticket, $newerThan, array $limits = [])
	{
		/** @var \MJ\SupportTicket\Finder\TicketMessage $finder */
		$finder = $this->finder('MJ\SupportTicket:TicketMessage');
		$finder
			->inTicket($ticket, $limits)
			->orderByDate('DESC')
			->newerThan($newerThan);

		return $finder;
	}

	public function findNextMessagesInTicket(\MJ\SupportTicket\Entity\Ticket $ticket, $newerThan, array $limits = [])
	{
		/** @var \MJ\SupportTicket\Finder\TicketMessage $finder */
		$finder = $this->finder('MJ\SupportTicket:TicketMessage');
		$finder
			->inTicket($ticket, $limits)
			->orderByDate()
			->newerThan($newerThan);

		return $finder;
	}

	public function sendModeratorActionAlert(\MJ\SupportTicket\Entity\TicketMessage $message, $action, $reason = '', array $extra = [])
	{
		if (!$message->user_id || !$message->User)
		{
			return false;
		}

		$extra = array_merge([
			'title'      => $message->Ticket->title,
			'prefix_id'  => $message->Ticket->prefix_id,
			'link'       => $this->app()->router('public')->buildLink('nopath:support-tickets/messages', $message),
			'ticketLink' => $this->app()->router('public')->buildLink('nopath:support-tickets/messages', $message->Ticket),
			'reason'     => $reason
		], $extra);

		/** @var \XF\Repository\UserAlert $alertRepo */
		$alertRepo = $this->repository('XF:UserAlert');
		$alertRepo->alert(
			$message->User,
			0,
			'',
			'user',
			$message->user_id,
			"mjst_message_{$action}",
			$extra
		);
		return true;
	}
}
