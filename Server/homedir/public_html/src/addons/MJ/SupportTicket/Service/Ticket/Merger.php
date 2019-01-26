<?php

namespace MJ\SupportTicket\Service\Ticket;

use MJ\SupportTicket\Entity\Ticket;
use XF\Entity\User;

class Merger extends \XF\Service\AbstractService
{
	/**
	 * @var Ticket
	 */
	protected $target;

	protected $alert = false;
	protected $alertReason = '';

	protected $redirect = false;
	protected $redirectLength = 0;

	protected $log = true;

	protected $sourceTickets = [];
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

	public function merge($sourceTicketsRaw)
	{
		if ($sourceTicketsRaw instanceof \XF\Mvc\Entity\AbstractCollection)
		{
			$sourceTicketsRaw = $sourceTicketsRaw->toArray();
		}
		else if ($sourceTicketsRaw instanceof Ticket)
		{
			$sourceTicketsRaw = [$sourceTicketsRaw];
		}
		else if (!is_array($sourceTicketsRaw))
		{
			throw new \InvalidArgumentException('Tickets must be provided as collection, array or entity');
		}

		if (!$sourceTicketsRaw)
		{
			return false;
		}

		$db = $this->db();

		/** @var Ticket[] $sourceTickets */
		$sourceTickets = [];
		foreach ($sourceTicketsRaw as $sourceTicket)
		{
			$sourceTicket->setOption('log_moderator', false);
			$sourceTickets[$sourceTicket->support_ticket_id] = $sourceTicket;
		}

		$messages = $db->fetchAllKeyed("
			SELECT message_id, support_ticket_id, user_id, message_state
			FROM xf_mjst_ticket_message
			WHERE support_ticket_id IN (" . $db->quote(array_keys($sourceTickets)) . ")
		", 'message_id');

		$this->sourceTickets = $sourceTickets;
		$this->sourceMessages = $messages;

		$target = $this->target;
		$target->setOption('log_moderator', false);

		$db->beginTransaction();

		$this->moveDataToTarget();
		$this->updateTargetData();

		if ($this->alert)
		{
			$this->sendAlert();
		}

		foreach ($sourceTickets as $sourceTicket)
		{
			$sourceTicket->delete();
		}

		$this->finalActions();

		$db->commit();

		return true;
	}

	protected function moveDataToTarget()
	{
		$db = $this->db();
		$target = $this->target;
		$sourceTicketIds = array_keys($this->sourceTickets);
		$sourceIdsQuoted = $db->quote($sourceTicketIds);

		$db->update(
			'xf_mjst_ticket_message',
			['support_ticket_id' => $target->support_ticket_id],
			"support_ticket_id IN ($sourceIdsQuoted)"
		);
		$db->update(
			'xf_mjst_ticket_watch',
			['support_ticket_id' => $target->support_ticket_id],
			"support_ticket_id IN ($sourceIdsQuoted)",
			[],
			'IGNORE'
		);
	}

	protected function updateTargetData()
	{
		$target = $this->target;

		$target->rebuildCounters();
		$target->save();

		/** @var \MJ\SupportTicket\Repository\Ticket $ticketRepo */
		$ticketRepo = $this->repository('MJ\SupportTicket:Ticket');
		$ticketRepo->rebuildTicketMessagePositions($target->support_ticket_id);
	}

	protected function sendAlert()
	{
		$target = $this->target;
		$actor = \XF::visitor();

		/** @var \MJ\SupportTicket\Repository\Ticket $ticketRepo */
		$ticketRepo = $this->repository('MJ\SupportTicket:Ticket');

		$alertExtras = [
			'targetTitle' => $target->full_title,
			'targetLink' => $this->app->router('public')->buildLink('nopath:support-tickets', $target)
		];

		foreach ($this->sourceTickets as $sourceTicket)
		{
			if ($sourceTicket->user_id != $actor->user_id
			)
			{
				$ticketRepo->sendModeratorActionAlert($sourceTicket, 'merge', $this->alertReason, $alertExtras);
			}
		}
	}

	protected function convertSourcesToRedirects()
	{
		$target = $this->target;

		/** @var \MJ\SupportTicket\Repository\TicketRedirect $redirectRepo */
		$redirectRepo = $this->repository('MJ\SupportTicket:TicketRedirect');

		foreach ($this->sourceTickets as $sourceTicket)
		{
			$sourceTicket->discussion_type = 'redirect';
			$redirectRepo->createRedirectionRecordForTicket($sourceTicket, $target, $this->redirectLength, false);
			$sourceTicket->save();
		}
	}

	protected function finalActions()
	{
		$target = $this->target;
		$sourceTicketIds = array_keys($this->sourceTickets);
		$messageIds = array_keys($this->sourceMessages);

		if ($messageIds)
		{
			$this->app->jobManager()->enqueue('XF:SearchIndex', [
				'content_type' => 'message',
				'content_ids' => $messageIds
			]);
		}

		if ($this->log)
		{
			$this->app->logger()->logModeratorAction('support_ticket', $target, 'merge_target',
				['ids' => implode(', ', $sourceTicketIds)]
			);
		}
	}
}
