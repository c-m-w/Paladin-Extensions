<?php

namespace MJ\SupportTicket\Finder;

use XF\Mvc\Entity\Finder;

class TicketMessage extends Finder
{
	public function inTicket(\MJ\SupportTicket\Entity\Ticket $ticket, array $limits = [])
	{
		$limits = array_replace([
			'visibility' => true,
			'allowOwnPending' => true
		], $limits);

		$this->where('support_ticket_id', $ticket->support_ticket_id);

		if ($limits['visibility'])
		{
			$this->applyVisibilityChecksInTicket($ticket, $limits['allowOwnPending']);
		}

		return $this;
	}

	public function applyVisibilityChecksInTicket(\MJ\SupportTicket\Entity\Ticket $ticket, $allowOwnPending = true)
	{
		$conditions = [];
		$viewableStates = ['visible'];

		if ($ticket->canViewDeletedMessages())
		{
			$viewableStates[] = 'deleted';

			$this->with('DeletionLog');
		}

		$visitor = \XF::visitor();
		if ($ticket->canViewModeratedMessages())
		{
			$viewableStates[] = 'moderated';
		}
		else if ($visitor->user_id && $allowOwnPending)
		{
			$conditions[] = [
				'message_state' => 'moderated',
				'user_id' => $visitor->user_id
			];
		}

		$conditions[] = ['message_state', $viewableStates];

		$this->whereOr($conditions);

		return $this;
	}

	public function onPage($page, $perPage = null)
	{
		$page = max(1, intval($page));
		if ($perPage === null)
		{
			$perPage = $this->app()->options()->messagesPerPage;
		}
		$perPage = max(1, intval($perPage));

		$start = ($page - 1) * $perPage;
		$end = $start + $perPage;

		$this->where('position', '>=', $start)->where('position', '<', $end);

		return $this;
	}

	public function newerThan($date)
	{
		$this->where('message_date', '>', $date);

		return $this;
	}

	public function orderByDate($direction = 'ASC')
	{
		$this->order('position', $direction)->order('message_date', $direction);

		return $this;
	}

	public function skipIgnored(\XF\Entity\User $user = null)
	{
		if (!$user)
		{
			$user = \XF::visitor();
		}

		if (!$user->user_id)
		{
			return $this;
		}

		if ($user->Profile && $user->Profile->ignored)
		{
			$this->where('user_id', '<>', array_keys($user->Profile->ignored));
		}

		return $this;
	}

	public function isNotFirstMessage()
	{
		$this->where($this->expression(
			'%s <> %s',
			'Ticket.first_message_id',
			'message_id'
		));

		return $this;
	}

	public function forFullView()
	{
		$this->with(['User', 'User.Profile', 'User.Privacy']);

		if ($this->app()->options()->showMessageOnlineStatus)
		{
			$this->with('User.Activity');
		}
		return $this;
	}
}
