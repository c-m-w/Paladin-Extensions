<?php

namespace MJ\SupportTicket\Repository;

use XF\Mvc\Entity\Repository;

class TicketWatch extends Repository
{
	public function autoWatchTicket(\MJ\SupportTicket\Entity\Ticket $ticket, \XF\Entity\User $user, $onCreation = false)
	{
		$userField = $onCreation ? 'creation_watch_state' : 'interaction_watch_state';

		if (!$ticket->support_ticket_id || !$user->user_id || !$user->Option->getValue($userField))
		{
			return null;
		}

		$watch = $this->em->find('MJ\SupportTicket:TicketWatch', [
			'support_ticket_id' => $ticket->support_ticket_id,
			'user_id' => $user->user_id
		]);
		if ($watch)
		{
			return null;
		}

		$watch = $this->em->create('MJ\SupportTicket:TicketWatch');
		$watch->support_ticket_id      = $ticket->support_ticket_id;
		$watch->user_id         = $user->user_id;
		$watch->email_subscribe = ($user->Option->getValue($userField) == 'watch_email');
		try
		{
			$watch->save();
		}
		catch (\XF\Db\DuplicateKeyException $e)
		{
			return null;
		}

		return $watch;
	}

	public function setWatchState(\MJ\SupportTicket\Entity\Ticket $ticket, \XF\Entity\User $user, $action, array $config = [])
	{
		if (!$ticket->support_ticket_id || !$user->user_id)
		{
			throw new \InvalidArgumentException("Invalid ticket or user");
		}

		$watch = $this->em->find('MJ\SupportTicket:TicketWatch', [
			'support_ticket_id' => $ticket->support_ticket_id,
			'user_id' => $user->user_id
		]);

		switch ($action)
		{
			case 'watch_email':
			case 'watch_no_email':
			case 'no_email':
				if (!$watch)
				{
					$watch = $this->em->create('MJ\SupportTicket:TicketWatch');
					$watch->support_ticket_id = $ticket->support_ticket_id;
					$watch->user_id = $user->user_id;
				}
				$watch->email_subscribe = ($action == 'watch_email');
				try
				{
					$watch->save();
				}
				catch (\XF\Db\DuplicateKeyException $e) {}
				break;

			case 'delete':
			case 'stop':
			case '':
				if ($watch)
				{
					$watch->delete();
				}
				break;

			default:
				throw new \InvalidArgumentException("Unknown action '$action' (expected: delete/watch)");
		}
	}

	public function setWatchStateForAll(\XF\Entity\User $user, $action, array $updates = [])
	{
		if (!$user->user_id)
		{
			throw new \InvalidArgumentException("Invalid user");
		}

		$db = $this->db();

		switch ($action)
		{
			case 'watch_email':
				return $db->update('xf_mjst_ticket_watch', ['email_subscribe' => 1], 'user_id = ?', $user->user_id);

			case 'watch_no_email':
			case 'no_email':
				return $db->update('xf_mjst_ticket_watch', ['email_subscribe' => 0], 'user_id = ?', $user->user_id);

			case 'update':
				unset($updates['support_ticket_id'], $updates['user_id']);
				return $db->update('xf_mjst_ticket_watch', $updates, 'user_id = ?', $user->user_id);

			case 'delete':
			case 'stop':
			case '':
				return $db->delete('xf_mjst_ticket_watch', 'user_id = ?', $user->user_id);

			default:
				throw new \InvalidArgumentException("Unknown action '$action'");
		}
	}

	public function isValidWatchState($state)
	{
		switch ($state)
		{
			case 'watch_email':
			case 'watch_no_email':
			case 'no_email':
			case 'delete':
			case 'stop':
			case '':
				return true;

			default:
				return false;
		}
	}
}
