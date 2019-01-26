<?php

namespace MJ\SupportTicket\Service\TicketMessage;

use MJ\SupportTicket\Entity\TicketMessage;
use MJ\SupportTicket\Entity\Ticket;

class Copier extends \XF\Service\AbstractService
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

	public function copy($sourceMessagesRaw)
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

		foreach ($sourceMessagesRaw as $sourceMessage)
		{
			$sourceMessage->setOption('log_moderator', false);
			$sourceMessages[$sourceMessage->message_id] = $sourceMessage;

			/** @var Ticket $sourceTicket */
			$sourceTicket = $sourceMessage->Ticket;
			if (!isset($sourceTickets[$sourceTicket->support_ticket_id]))
			{
				$sourceTicket->setOption('log_moderator', false);
				$sourceTickets[$sourceTicket->support_ticket_id] = $sourceTicket;
			}
		}

		$sourceMessages = \XF\Util\Arr::columnSort($sourceMessages, 'message_date');

		$this->sourceTickets = $sourceTickets;
		$this->sourceMessages = $sourceMessages;

		$target = $this->target;
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

		$this->copyDataToTarget();
		$this->updateTargetData();

		if ($this->alert)
		{
			$this->sendAlert();
		}

		$this->finalActions();

		$db->commit();

		return true;
	}

	protected function copyDataToTarget()
	{
		$resetValues = $this->getResetMessageData();

		$position = 0;
		$firstMessage = null;

		// messages are sorted in date order
		foreach ($this->sourceMessages as $sourceMessage)
		{
			/** @var \MJ\SupportTicket\Entity\TicketMessage $newMessage */
			$newMessage = $this->em()->create('MJ\SupportTicket:TicketMessage');

			$values = $sourceMessage->toArray(false);
			foreach ($resetValues as $key)
			{
				unset($values[$key]);
			}

			$newMessage->support_ticket_id = $this->target->support_ticket_id;
			$newMessage->bulkSet($values);

			$newMessage->position = $position;
			if (!$firstMessage)
			{
				// first message is always visible, set $firstMessage later
				$newMessage->message_state = 'visible';
			}

			$newMessage->save();

			if (!$firstMessage)
			{
				$firstMessage = $newMessage;

				$this->target->fastUpdate('first_message_id', $newMessage->message_id);
			}

			$embedMetadata = $sourceMessage->embed_metadata;
			$newMessage->embed_metadata = $this->updateEmbeds($sourceMessage, $newMessage, $embedMetadata ?: []);
			$newMessage->saveIfChanged();

			if ($newMessage->message_state == 'visible')
			{
				$position++;
			}
		}
	}

	protected function getResetMessageData()
	{
		return  [
			'message_id',
			'support_ticket_id',
			'position',
			'last_edit_date',
			'last_edit_user_id',
			'edit_count'
		];
	}

	protected function updateEmbeds(Message $sourceMessage, Message $newMessage, array $embedMetadata)
	{
		$attachEmbed = isset($embedMetadata['attachments']) ? $embedMetadata['attachments'] : [];

		foreach ($sourceMessage->Attachments as $sourceAttachment)
		{
			/** @var \XF\Entity\Attachment $newAttachment */
			$newAttachment = $this->em()->create('XF:Attachment');

			$values = $sourceAttachment->toArray(false);
			unset($values['attachment_id'], $values['content_id'], $values['view_count']);

			$newAttachment->content_id = $newMessage->message_id;
			$newAttachment->bulkSet($values);
			$newAttachment->save();

			$newMessage->message = preg_replace(
				'#(\[attach(=[^]]+)?\])' . $sourceAttachment->attachment_id . '(\[/attach\])#i',
				'${1}' . $newAttachment->attachment_id . '${3}',
				$newMessage->message
			);

			if (isset($attachEmbed[$sourceAttachment->attachment_id]))
			{
				unset($attachEmbed[$sourceAttachment->attachment_id]);
				$attachEmbed[$newAttachment->attachment_id] = $newAttachment->attachment_id;
			}
		}

		if ($attachEmbed)
		{
			$embedMetadata['attachments'] = $attachEmbed;
		}
		else
		{
			unset($embedMetadata['attachments']);
		}

		return $embedMetadata;
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

		$target->Forum->rebuildCounters();
		$target->Forum->save();

		/** @var \MJ\SupportTicket\Repository\Ticket $ticketRepo */
		$ticketRepo = $this->repository('MJ\SupportTicket:Ticket');
		$ticketRepo->rebuildTicketMessagePositions($target->support_ticket_id);
		$ticketRepo->rebuildTicketUserMessageCounters($target->support_ticket_id);
	}

	protected function sendAlert()
	{
		$target = $this->target;

		/** @var \MJ\SupportTicket\Repository\Message $messageRepo */
		$messageRepo = $this->repository('MJ\SupportTicket:Message');

		$alertExtras = [
			'targetTitle' => $target->full_title,
			'targetLink' => $this->app->router('public')->buildLink('nopath:support-tickets', $target)
		];

		foreach ($this->sourceMessages as $sourceMessage)
		{
			if ($sourceMessage->message_state == 'visible'
				&& $sourceMessage->user_id != \XF::visitor()->user_id
			)
			{
				$messageRepo->sendModeratorActionAlert($sourceMessage, 'copy', $this->alertReason, $alertExtras);
			}
		}
	}

	protected function finalActions()
	{
		$target = $this->target;
		$messageIds = array_keys($this->sourceMessages);

		if ($this->log)
		{
			$this->app->logger()->logModeratorAction('support_ticket', $target, 'message_copy_target'  . ($this->existingTarget ? '_exist' : ''),
				['ids' => implode(', ', $messageIds)]
			);

			foreach ($this->sourceTickets as $sourceTicket)
			{
				$this->app->logger()->logModeratorAction('support_ticket', $sourceTicket, 'message_copy_source', [
					'url' => $this->app->router('public')->buildLink('nopath:support-tickets', $sourceTicket),
					'title' => $target->title
				]);
			}
		}
	}
}
