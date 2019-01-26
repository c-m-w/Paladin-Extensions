<?php

namespace MJ\SupportTicket\Service\TicketMessage;

use MJ\SupportTicket\Entity\TicketMessage;
use MJ\SupportTicket\Entity\Ticket;
use XF\Entity\User;

class Mover extends \XF\Service\AbstractService
{
	/**
	 * @var Ticket
	 */
	protected $target;

	protected $existingTarget = false;

	protected $alert = false;
	protected $alertReason = '';

	protected $prefixId = null;

	protected $log = true;

	/**
	 * @var Ticket[]
	 */
	protected $sourceTickets = [];

	/**
	 * @var TicketMessage[]
	 */
	protected $sourceMessages = [];

	public function __construct(\XF\App $app, Ticket $target)
	{
		parent::__construct($app);
		$this->target = $target;
	}

	public function getTarget()
	{
		return $this->target;
	}

	public function setExistingTarget($existing)
	{
		$this->existingTarget = (bool)$existing;
	}

	public function setLog($log)
	{
		$this->log = (bool)$log;
	}

	public function setSendAlert($alert, $reason = null)
	{
		$this->alert = (bool)$alert;
		if ($reason !== null)
		{
			$this->alertReason = $reason;
		}
	}

	public function setPrefix($prefixId)
	{
		$this->prefixId = ($prefixId === null ? $prefixId : intval($prefixId));
	}

	public function move($sourceMessagesRaw)
	{
		if ($sourceMessagesRaw instanceof \XF\Mvc\Entity\AbstractCollection)
		{
			$sourceMessagesRaw = $sourceMessagesRaw->toArray();
		}
		else if ($sourceMessagesRaw instanceof TicketMessage)
		{
			$sourceMessagesRaw = [$sourceMessagesRaw];
		}
		else if (!is_array($sourceMessagesRaw))
		{
			throw new \InvalidArgumentException('Messages must be provided as collection, array or entity');
		}

		if (!$sourceMessagesRaw)
		{
			return false;
		}

		$db = $this->db();

		/** @var TicketMessage[] $sourceMessages */
		/** @var Ticket[] $sourceTickets */
		$sourceMessages = [];
		$sourceTickets = [];

		$target = $this->target;

		foreach ($sourceMessagesRaw as $sourceMessage)
		{
			if ($sourceMessage->support_ticket_id == $target->support_ticket_id)
			{
				continue;
			}

			$sourceMessage->setOption('log_moderator', false);
			$sourceMessages[$sourceMessage->message_id] = $sourceMessage;

			/** @var Ticket $sourceTicket */
			$sourceTicket = $sourceMessage->Ticket;
			if ($sourceTicket && !isset($sourceTickets[$sourceTicket->support_ticket_id]))
			{
				$sourceTicket->setOption('log_moderator', false);
				$sourceTickets[$sourceTicket->support_ticket_id] = $sourceTicket;
			}
		}

		if (!$sourceMessages)
		{
			return false; // nothing to do
		}

		$sourceMessages = \XF\Util\Arr::columnSort($sourceMessages, 'message_date');

		$this->sourceTickets = $sourceTickets;
		$this->sourceMessages = $sourceMessages;

		$target->setOption('log_moderator', false);

		if (!$target->support_ticket_id)
		{
			$firstMessage = reset($sourceMessages);

			$target->user_id = $firstMessage->user_id;
			$target->username = $firstMessage->username;
			$target->open_date = $firstMessage->message_date;
		}

		$db->beginTransaction();

		$target->save();

		$this->moveDataToTarget();
		$this->updateTargetData();
		$this->updateSourceData();

		if ($this->alert)
		{
			$this->sendAlert();
		}

		$this->finalActions();

		$db->commit();

		return true;
	}

	protected function moveDataToTarget()
	{
		$db = $this->db();
		$target = $this->target;
		$sourceMessageIds = array_keys($this->sourceMessages);
		$sourceIdsQuoted = $db->quote($sourceMessageIds);

		$db->update(
			'xf_mjst_ticket_message',
			['support_ticket_id' => $target->support_ticket_id],
			"message_id IN ($sourceIdsQuoted)"
		);

		$firstMessage = reset($this->sourceMessages);
		if ($firstMessage->message_state != 'visible'
			&& (!$this->existingTarget || $firstMessage->message_date <= $this->target->message_date)
		)
		{
			// need to do this change on a clone, as we need the source message version to be unchanged
			$clone = clone $firstMessage;
			$clone->setAsSaved('support_ticket_id', $target->support_ticket_id);
			$clone->message_state = 'visible';
			$clone->save();
		}
	}

	protected function updateTargetData()
	{
		$target = $this->target;

		if ($this->prefixId !== null)
		{
			$target->prefix_id = $this->prefixId;
		}
		$target->rebuildCounters();
		$target->save();

		$target->Department->rebuildCounters();
		$target->Department->save();

		/** @var \MJ\SupportTicket\Repository\Ticket $ticketRepo */
		$ticketRepo = $this->repository('MJ\SupportTicket:Ticket');
		$ticketRepo->rebuildTicketMessagePositions($target->support_ticket_id);
	}

	protected function updateSourceData()
	{
		/** @var \MJ\SupportTicket\Repository\Ticket $ticketRepo */
		$ticketRepo = $this->repository('MJ\SupportTicket:Ticket');

		foreach ($this->sourceTickets as $sourceTicket)
		{
			$sourceTicket->rebuildCounters();

			$sourceTicket->save(); // has to be saved for the delete to work (if needed).

			if (array_key_exists($sourceTicket->first_message_id, $this->sourceMessages) && $sourceTicket->reply_count == 0)
			{
				$sourceTicket->delete(); // first message has been moved out, no other replies, ticket now empty
			}
			else
			{
				$ticketRepo->rebuildTicketMessagePositions($sourceTicket->support_ticket_id);
			}

			$sourceTicket->Department->rebuildCounters();
			$sourceTicket->Department->save();
		}
	}

	protected function sendAlert()
	{
		$target = $this->target;

		/** @var \MJ\SupportTicket\Repository\TicketMessage $messageRepo */
		$messageRepo = $this->repository('MJ\SupportTicket:TicketMessage');

		$alertExtras = [
			'targetTitle' => $target->full_title,
			'targetLink' => $this->app->router('public')->buildLink('nopath:support-tickets', $target)
		];

		foreach ($this->sourceMessages as $sourceMessage)
		{
			if ($sourceMessage->message_state == 'visible')
			{
				$messageRepo->sendModeratorActionAlert($sourceMessage, 'move', $this->alertReason, $alertExtras);
			}
		}
	}

	protected function finalActions()
	{
		$target = $this->target;
		$messageIds = array_keys($this->sourceMessages);

		if ($messageIds)
		{
			$this->app->jobManager()->enqueue('XF:SearchIndex', [
				'content_type' => 'support_ticket_message',
				'content_ids' => $messageIds
			]);
		}

		if ($this->log)
		{
			$this->app->logger()->logModeratorAction(
				'support_ticket',
				$target,
				'message_move_target' . ($this->existingTarget ? '_exist' : ''),
				['ids' => implode(', ', $messageIds)]
			);
			//'message_move_target_exist';

			foreach ($this->sourceTickets as $sourceTicket)
			{
				$this->app->logger()->logModeratorAction('support_ticket', $sourceTicket, 'message_move_source', [
					'url' => $this->app->router('public')->buildLink('nopath:support-tickets', $sourceTicket),
					'title' => $target->title
				]);
			}
		}
	}
}
