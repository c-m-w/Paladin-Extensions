<?php

namespace MJ\SupportTicket\Service\TicketMessage;

use MJ\SupportTicket\Entity\TicketMessage;

class Preparer extends \XF\Service\AbstractService
{
	/**
	 * @var TicketMessage
	 */
	protected $message;

	protected $attachmentHash;

	protected $logIp = true;

	protected $quotedMessages = [];

	protected $mentionedUsers = [];

	public function __construct(\XF\App $app, TicketMessage $message)
	{
		parent::__construct($app);
		$this->message = $message;
	}

	public function getMessage()
	{
		return $this->message;
	}

	public function logIp($logIp)
	{
		$this->logIp = $logIp;
	}

	public function getQuotedMessages()
	{
		return $this->quotedMessages;
	}

	public function getQuotedUserIds()
	{
		if (!$this->quotedMessages)
		{
			return [];
		}

		$messageIds = array_keys($this->quotedMessages);
		$quotedUserIds = [];

		$db = $this->db();
		$messageUserMap = $db->fetchPairs("
			SELECT message_id, user_id
			FROM xf_mjst_ticket_message
			WHERE message_id IN (" . $db->quote($messageIds) .")
		");
		foreach ($messageUserMap as $messageId => $userId)
		{
			if (!isset($this->quotedMessages[$messageId]) || !$userId)
			{
				continue;
			}

			$quote = $this->quotedMessages[$messageId];
			if (!isset($quote['member']) || $quote['member'] == $userId)
			{
				$quotedUserIds[] = $userId;
			}
		}

		return $quotedUserIds;
	}

	public function getMentionedUsers($limitPermissions = true)
	{
		if ($limitPermissions && $this->message)
		{
			/** @var \XF\Entity\User $user */
			$user = $this->message->User ?: $this->repository('XF:User')->getGuestUser();
			return $user->getAllowedUserMentions($this->mentionedUsers);
		}
		else
		{
			return $this->mentionedUsers;
		}
	}

	public function getMentionedUserIds($limitPermissions = true)
	{
		return array_keys($this->getMentionedUsers($limitPermissions));
	}

	public function setMessage($message, $format = true, $checkValidity = true)
	{
		$preparer = $this->getMessagePreparer($format);
		$this->message->message = $preparer->prepare($message, $checkValidity);
		$this->message->embed_metadata = $preparer->getEmbedMetadata();

		$this->quotedMessages = $preparer->getQuotesKeyed('message');
		$this->mentionedUsers = $preparer->getMentionedUsers();

		return $preparer->pushEntityErrorIfInvalid($this->message);
	}

	/**
	 * @param bool $format
	 *
	 * @return \MJ\SupportTicket\Service\TicketMessage\Preparer
	 */
	protected function getMessagePreparer($format = true)
	{
		/** @var \MJ\SupportTicket\Service\TicketMessage\Preparer $preparer */
		$preparer = $this->service('XF:Message\Preparer', 'support_ticket_message', $this->message);
		if (!$format)
		{
			$preparer->disableAllFilters();
		}

		return $preparer;
	}

	public function setAttachmentHash($hash)
	{
		$this->attachmentHash = $hash;
	}

	public function checkForSpam()
	{
		$message = $this->message;
		$ticket = $this->message->Ticket;

		/** @var \XF\Entity\User $user */
		$user = $message->User ?: $this->repository('XF:User')->getGuestUser($message->username);

		if ($message->isFirstMessage())
		{
			$message = $ticket->title . "\n" . $message->message;
			$contentType = 'support_ticket';
		}
		else
		{
			$message = $message->message;
			$contentType = 'support_ticket_message';
		}

		$checker = $this->app->spam()->contentChecker();
		$checker->check($user, $message, [
			'permalink' => $this->app->router('public')->buildLink('canonical:support-tickets', $ticket),
			'content_type' => $contentType
		]);

		$decision = $checker->getFinalDecision();
		switch ($decision)
		{
			case 'moderated':
				$message->message_state = 'moderated';
				break;

			case 'denied':
				$checker->logSpamTrigger($message->isFirstMessage() ? 'support_ticket' : 'support_ticket_message', null);
				$message->error(\XF::phrase('your_content_cannot_be_submitted_try_later'));
				break;
		}
	}

	public function afterInsert()
	{
		if ($this->attachmentHash)
		{
			$this->associateAttachments($this->attachmentHash);
		}

		if ($this->logIp)
		{
			$ip = ($this->logIp === true ? $this->app->request()->getIp() : $this->logIp);
			$this->writeIpLog($ip);
		}

		$message = $this->message;
		$checker = $this->app->spam()->contentChecker();

		if ($message->isFirstMessage())
		{
			$checker->logContentSpamCheck('support_ticket', $message->support_ticket_id);
			$checker->logSpamTrigger('support_ticket', $message->support_ticket_id);
		}
		else
		{
			$checker->logContentSpamCheck('support_ticket_message', $message->message_id);
			$checker->logSpamTrigger('support_ticket_message', $message->message_id);
		}
	}

	public function afterUpdate()
	{
		if ($this->attachmentHash)
		{
			$this->associateAttachments($this->attachmentHash);
		}

		$message = $this->message;
		$checker = $this->app->spam()->contentChecker();

		if ($message->isFirstMessage())
		{
			$checker->logSpamTrigger('support_ticket', $message->support_ticket_id);
		}
		else
		{
			$checker->logSpamTrigger('support_ticket_message', $message->message_id);
		}
	}

	protected function associateAttachments($hash)
	{
		$message = $this->message;

		/** @var \XF\Service\Attachment\Preparer $inserter */
		$inserter = $this->service('XF:Attachment\Preparer');
		$associated = $inserter->associateAttachmentsWithContent($hash, 'support_ticket_message', $message->message_id);
		if ($associated)
		{
			$message->fastUpdate('attach_count', $message->attach_count + $associated);
		}
	}

	protected function writeIpLog($ip)
	{
		$message = $this->message;

		/** @var \XF\Repository\IP $ipRepo */
		$ipRepo = $this->repository('XF:Ip');
		$ipEnt = $ipRepo->logIp($message->user_id, $ip, 'support_ticket_message', $message->message_id);
		if ($ipEnt)
		{
			$message->fastUpdate('ip_id', $ipEnt->ip_id);
		}
	}
}
