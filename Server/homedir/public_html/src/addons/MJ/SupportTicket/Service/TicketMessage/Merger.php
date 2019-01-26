<?php

namespace MJ\SupportTicket\Service\TicketMessage;

use MJ\SupportTicket\Entity\TicketMessage;
use XF\Entity\User;

class Merger extends \XF\Service\AbstractService
{
	/**
	 * @var TicketMessage
	 */
	protected $target;

	protected $originalTargetMessage;

	/**
	 * @var \MJ\SupportTicket\Service\TicketMessage\Preparer
	 */
	protected $messagePreparer;

	protected $alert = false;
	protected $alertReason = '';

	protected $log = true;

	/**
	 * @var \MJ\SupportTicket\Entity\Ticket[]
	 */
	protected $sourceTickets = [];

	/**
	 * @var \MJ\SupportTicket\Entity\TicketMessage[]
	 */
	protected $sourceMessages = [];

	public function __construct(\XF\App $app, TicketMessage $target)
	{
		parent::__construct($app);

		$this->target = $target;
		$this->originalTargetMessage = $target->message;
		$this->messagePreparer = $this->service('MJ\SupportTicket:TicketMessage\Preparer', $this->target);
	}

	public function getTarget()
	{
		return $this->target;
	}

	public function setSendAlert($alert, $reason = null)
	{
		$this->alert = (bool)$alert;
		if ($reason !== null)
		{
			$this->alertReason = $reason;
		}
	}

	public function setLog($log)
	{
		$this->log = (bool)$log;
	}

	public function setMessage($message, $format = true)
	{
		return $this->messagePreparer->setMessage($message, $format);
	}

	public function merge($sourceMessagesRaw)
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

		/** @var Message[] $sourceMessages */
		$sourceMessages = [];

		/** @var \XF\Entity\Ticket[] $sourceTickets */
		$sourceTickets = [];

		foreach ($sourceMessagesRaw as $sourceMessage)
		{
			$sourceMessage->setOption('log_moderator', false);
			$sourceMessages[$sourceMessage->message_id] = $sourceMessage;

			/** @var \XF\Entity\Ticket $sourceTicket */
			$sourceTicket = $sourceMessage->Ticket;
			if (!isset($sourceTickets[$sourceTicket->support_ticket_id]))
			{
				$sourceTicket->setOption('log_moderator', false);
				$sourceTickets[$sourceTicket->support_ticket_id] = $sourceTicket;
			}
		}

		$this->sourceTickets = $sourceTickets;
		$this->sourceMessages = $sourceMessages;

		$target = $this->target;
		$target->setOption('log_moderator', false);

		$db->beginTransaction();

		$this->moveDataToTarget();
		$this->updateTargetData();
		$this->updateSourceData();

		if ($this->alert)
		{
			$this->sendAlert();
		}

		$this->finalActions();

		$target->save();

		$db->commit();

		return true;
	}

	protected function moveDataToTarget()
	{
		$db = $this->db();
		$target = $this->target;

		$sourceMessages = $this->sourceMessages;
		$sourceMessageIds = array_keys($sourceMessages);
		$sourceIdsQuoted = $db->quote($sourceMessageIds);

		$rows = $db->update(
			'xf_attachment',
			['content_id' => $target->message_id],
			"content_id IN ($sourceIdsQuoted) AND content_type = 'support_ticket_message'"
		);

		$target->attach_count += $rows;

		foreach ($sourceMessages as $sourceMessage)
		{
			$sourceMessage->delete();
		}
	}

	protected function updateTargetData()
	{
		/** @var \MJ\SupportTicket\Entity\Ticket $targetTicket */
		$targetTicket = $this->target->Ticket;

		$targetTicket->rebuildCounters();
		$targetTicket->save();

		/** @var \MJ\SupportTicket\Repository\Ticket $ticketRepo */
		$ticketRepo = $this->repository('MJ\SupportTicket:Ticket');
		$ticketRepo->rebuildTicketMessagePositions($targetTicket->support_ticket_id);
		$ticketRepo->rebuildTicketUserMessageCounters($targetTicket->support_ticket_id);
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
		/** @var \XF\Repository\Message $messageRepo */
		$messageRepo = $this->repository('XF:Message');

		$alerted = [];
		foreach ($this->sourceMessages as $sourceMessage)
		{
			if (isset($alerted[$sourceMessage->user_id]))
			{
				continue;
			}

			if ($sourceMessage->message_state == 'visible' && $sourceMessage->user_id != \XF::visitor()->user_id)
			{
				$messageRepo->sendModeratorActionAlert($sourceMessage, 'merge', $this->alertReason);
				$alerted[$sourceMessage->user_id] = true;
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
			$this->app->logger()->logModeratorAction('support_ticket_message', $target, 'merge_target',
				['ids' => implode(', ', $messageIds)]
			);
		}

		$preEditMergeMessage = $this->originalTargetMessage;
		foreach ($this->sourceMessages as $s)
		{
			$preEditMergeMessage .= "\n\n" . $s->message;
		}
		$preEditMergeMessage = trim($preEditMergeMessage);

		$options = $this->app->options();
		if ($options->editLogDisplay['enabled'] && $this->log && $target->message != $preEditMergeMessage)
		{
			$target->last_edit_date = \XF::$time;
			$target->last_edit_user_id = \XF::visitor()->user_id;
		}

		if ($options->editHistory['enabled'])
		{
			$visitor = \XF::visitor();
			$ip = $this->app->request()->getIp();

			/** @var \XF\Repository\EditHistory $editHistoryRepo */
			$editHistoryRepo = $this->app->repository('XF:EditHistory');

			// Log an edit history record for the target message's original message then log a further record
			// for the pre-merge result of all the source and target messages. These two entries should ensure
			// there is no context loss as a result of merging a series of messages.
			$editHistoryRepo->insertEditHistory('support_ticket_message', $target, $visitor, $this->originalTargetMessage, $ip);
			$target->edit_count++;

			if ($target->message != $preEditMergeMessage)
			{
				$editHistoryRepo->insertEditHistory('support_ticket_message', $target, $visitor, $preEditMergeMessage, $ip);
				$target->edit_count++;
			}
		}
	}
}
