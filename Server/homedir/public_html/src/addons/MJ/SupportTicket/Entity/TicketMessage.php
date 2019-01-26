<?php

namespace MJ\SupportTicket\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;
use XF\Entity\QuotableInterface;

class TicketMessage extends Entity implements QuotableInterface, \XF\BbCode\RenderableContentInterface
{
	public function canView(&$error = null)
	{
		if (!$this->Ticket ||
			(!$this->Ticket->canView($error) &&
				($this->Ticket->user_id || !$this->Ticket->canViewGuestTicket())
			)
		)
		{
			return false;
		}

		$visitor = \XF::visitor();
		$departmentId = $this->Ticket->department_id;

		if ($this->message_state == 'deleted')
		{
			if (!$visitor->hasTicketDepartmentPermission($departmentId, 'viewDeleted'))
			{
				$error = \XF::phraseDeferred('requested_message_not_found');
				return false;
			}
		}

		return true;
	}

	public function canEdit(&$error = null)
	{
		$ticket = $this->Ticket;
		$visitor = \XF::visitor();
		if (!$visitor->user_id || !$ticket)
		{
			return false;
		}

		$departmentId = $ticket->department_id;

		if ($visitor->hasTicketDepartmentPermission($departmentId, 'editAnyMessage'))
		{
			return true;
		}

		if ($this->user_id == $visitor->user_id && $visitor->hasTicketDepartmentPermission($departmentId, 'editOwnMessage'))
		{
			return true;
		}

		return false;
	}

	public function canEditSilently(&$error = null)
	{
		$ticket = $this->Ticket;
		$visitor = \XF::visitor();
		if (!$visitor->user_id || !$ticket)
		{
			return false;
		}

		$departmentId = $ticket->department_id;

		if ($visitor->hasTicketDepartmentPermission($departmentId, 'editAnyMessage'))
		{
			return true;
		}

		return false;
	}

	public function canUseInlineModeration(&$error = null)
	{
		return $this->Ticket->canUseInlineModeration($error);
	}

	public function canViewHistory(&$error = null)
	{
		$visitor = \XF::visitor();
		if (!$visitor->user_id)
		{
			return false;
		}

		if (!$this->app()->options()->editHistory['enabled'])
		{
			return false;
		}

		if ($visitor->hasTicketDepartmentPermission($this->Ticket->department_id, 'editAnyMessage'))
		{
			return true;
		}

		return false;
	}

	public function canDelete($type = 'soft', &$error = null)
	{
		$ticket = $this->Ticket;
		$visitor = \XF::visitor();
		if (!$visitor->user_id || !$ticket)
		{
			return false;
		}

		$departmentId = $ticket->department_id;

		if ($type != 'soft' && !$visitor->hasTicketDepartmentPermission($departmentId, 'hardDeleteAnyMessage'))
		{
			return false;
		}

		if ($this->isFirstMessage())
		{
			return $ticket->canDelete($error);
		}

		if ($visitor->hasTicketDepartmentPermission($departmentId, 'deleteAnyMessage'))
		{
			return true;
		}

		if ($this->user_id == $visitor->user_id && $visitor->hasTicketDepartmentPermission($departmentId, 'deleteOwnMessage'))
		{
			return true;
		}

		return false;
	}

	public function canUndelete(&$error = null)
	{
		$ticket = $this->Ticket;
		$visitor = \XF::visitor();
		if (!$visitor->user_id || !$ticket)
		{
			return false;
		}

		return $visitor->hasTicketDepartmentPermission($ticket->department_id, 'undelete');
	}

	public function canMove(&$error = null)
	{
		return $this->Ticket->canMove($error);
	}

	public function canCopy(&$error = null)
	{
		return $this->Ticket->canCopy($error);
	}

	public function canMerge(&$error = null)
	{
		return $this->Ticket->canMerge($error);
	}

	public function canCleanSpam()
	{
		return (\XF::visitor()->canCleanSpam() && $this->User && $this->User->isPossibleSpammer());
	}

	public function canSendModeratorActionAlert()
	{
		$visitor = \XF::visitor();

		if (!$visitor->user_id || ($visitor->user_id == $this->user_id && $visitor->user_id == $this->Ticket->user_id))
		{
			return false;
		}

		if ($this->message_state != 'visible')
		{
			return false;
		}

		return true;
	}

	public function isVisible()
	{
		return (
			$this->message_state == 'visible'
			&& $this->Ticket
		);
	}

	public function isFirstMessage()
	{
		$ticket = $this->Ticket;
		if (!$ticket)
		{
			return false;
		}

		if ($this->message_id == $ticket->first_message_id)
		{
			return true;
		}

		// this can be called during an insert where the ticket hasn't actually been updated yet
		// just assume it's the first post
		if (!$ticket->support_ticket_id)
		{
			return true;
		}

		if (!$ticket->first_message_id && $this->message_date == $ticket->message_date)
		{
			return true;
		}

		return false;
	}

	public function isLastMessage()
	{
		$ticket = $this->Ticket;
		if (!$ticket)
		{
			return false;
		}

		return ($this->message_id == $ticket->last_message_id);
	}

	public function isUnread()
	{
		if (!$this->Ticket)
		{
			return false;
		}

		$readDate = $this->Ticket->getVisitorReadDate();
		if ($readDate === null)
		{
			return false;
		}

		return $readDate < $this->message_date;
	}

	public function isAttachmentEmbedded($attachmentId)
	{
		if (!$this->embed_metadata)
		{
			return false;
		}

		if ($attachmentId instanceof \XF\Entity\Attachment)
		{
			$attachmentId = $attachmentId->attachment_id;
		}
		return isset($this->embed_metadata['attachments'][$attachmentId]);
	}

	public function isIgnored()
	{
		return \XF::visitor()->isIgnoring($this->user_id);
	}

	public function getQuoteWrapper($inner)
	{
		return '[QUOTE="'
			. ($this->User ? $this->User->username : $this->username)
			. ', brstsMessage: ' . $this->message_id
			. ($this->User ? ", member: $this->user_id" : '')
			. '"]'
			. $inner
			. "[/QUOTE]\n";
	}

	public function getBbCodeRenderOptions($context, $type)
	{
		return [
			'entity'          => $this,
			'user'            => $this->User,
			'attachments'     => $this->attach_count ? $this->Attachments : [],
			'viewAttachments' => $this->Ticket ? $this->Ticket->canViewAttachments() : false
		];
	}

	protected function _postSave()
	{
		$visibilityChange = $this->isStateChanged('message_state', 'visible');
		$deletionChange = $this->isStateChanged('message_state', 'deleted');

		if ($this->isUpdate())
		{
			if ($visibilityChange == 'enter')
			{
				$this->messageMadeVisible();
			}
			else if ($visibilityChange == 'leave')
			{
				$this->messageHidden();
			}

			if ($deletionChange == 'leave' && $this->DeletionLog)
			{
				$this->DeletionLog->delete();
			}
		}
		else
		{
			// insert
			if ($this->message_state == 'visible')
			{
				$this->messageInsertedVisible();
			}
		}

		if ($deletionChange == 'enter' && !$this->DeletionLog)
		{
			$delLog = $this->getRelationOrDefault('DeletionLog', false);
			$delLog->setFromVisitor();
			$delLog->save();
		}

		$this->updateTicketRecord();

		if ($this->isUpdate() && $this->getOption('log_moderator'))
		{
			$this->app()->logger()->logModeratorChanges('support_ticket_message', $this);
		}
	}

	protected function updateTicketRecord()
	{
		if (!$this->Ticket || !$this->Ticket->exists())
		{
			// inserting a ticket, don't try to write to it
			return;
		}

		$visibilityChange = $this->isStateChanged('message_state', 'visible');
		if ($visibilityChange == 'enter')
		{
			$this->Ticket->messageAdded($this);
			$this->Ticket->save();
		}
		else if ($visibilityChange == 'leave')
		{
			$this->Ticket->messageRemoved($this);
			$this->Ticket->save();
		}
	}

	protected function adjustUserMessageCountIfNeeded($amount)
	{
		return;
		if ($this->user_id)
		{
			return;
			$this->db()->query("
				UPDATE xf_user
				SET mjst_message_count = GREATEST(0, mjst_message_count + ?)
				WHERE user_id = ?
			", [$amount, $this->user_id]);
		}
	}

	protected function adjustTicketUserMessageCount($amount)
	{
		if ($this->user_id)
		{
			$db = $this->db();

			if ($amount > 0)
			{
				$db->insert('xf_mjst_ticket_user_message', [
					'support_ticket_id' => $this->support_ticket_id,
					'user_id' => $this->user_id,
					'message_count' => $amount
				], false, 'message_count = message_count + VALUES(message_count)');
			}
			else
			{
				$existingValue = $db->fetchOne("
					SELECT message_count
					FROM xf_mjst_ticket_user_message
					WHERE support_ticket_id = ?
						AND user_id = ?
				", [$this->support_ticket_id, $this->user_id]);
				if ($existingValue !== null)
				{
					$newValue = $existingValue + $amount;
					if ($newValue <= 0)
					{
						$this->db()->delete(
							'xf_mjst_ticket_user_message',
							'support_ticket_id = ? AND user_id = ?',
							[$this->support_ticket_id, $this->user_id]
						);
					}
					else
					{
						$this->db()->update(
							'xf_mjst_ticket_user_message',
							['message_count' => $newValue],
							'support_ticket_id = ? AND user_id = ?',
							[$this->support_ticket_id, $this->user_id]
						);
					}
				}
			}
		}
	}

	protected function messageInsertedVisible()
	{
		$this->adjustUserMessageCountIfNeeded(1);
		$this->adjustTicketUserMessageCount(1);
	}

	protected function messageMadeVisible()
	{
		if ($this->isChanged('position'))
		{
			// if we've updated the position, we need to trust what we had is accurate...
			$basePosition = $this->getExistingValue('position');
		}
		else
		{
			// ...otherwise, we should always double check the DB for the latest position since this function won't
			// update cached entities
			$basePosition = $this->db()->fetchOne("
				SELECT position
				FROM xf_mjst_ticket_message
				WHERE message_id = ?
			", $this->message_id);
			if ($basePosition === null || $basePosition === false)
			{
				$basePosition = $this->getExistingValue('position');
			}

			// also, since we haven't changed the position yet, we need to update that
			$this->fastUpdate('position', $basePosition + 1);
		}

		$this->db()->query("
			UPDATE xf_mjst_ticket_message
			SET position = position + 1
			WHERE support_ticket_id = ?
				AND (
					position > ?
					OR (position = ? AND message_date > ?)
				)
				AND message_id <> ?
		", [$this->support_ticket_id, $basePosition, $basePosition, $this->message_date, $this->message_id]);

		$this->adjustUserMessageCountIfNeeded(1);
		$this->adjustTicketUserMessageCount(1);
	}

	protected function messageHidden($hardDelete = false)
	{
		if ($hardDelete || $this->isChanged('position'))
		{
			// if we've deleted the post or updated the position, we need to trust what we had is accurate...
			$basePosition = $this->getExistingValue('position');
		}
		else
		{
			// ...otherwise, we should always double check the DB for the latest position since this function won't
			// update cached entities
			$basePosition = $this->db()->fetchOne("
				SELECT position
				FROM xf_mjst_ticket_message
				WHERE message_id = ?
			", $this->message_id);
			if ($basePosition === null || $basePosition === false)
			{
				$basePosition = $this->getExistingValue('position');
			}

			// also, since we haven't changed the position yet, we need to update that
			$this->fastUpdate('position', $basePosition - 1);
		}

		$this->db()->query("
			UPDATE xf_mjst_ticket_message
			SET position = IF(position > 0, position - 1, 0)
			WHERE support_ticket_id = ?
				AND position >= ?
				AND message_id <> ?
		", [$this->support_ticket_id, $basePosition, $this->message_id]);

		//$this->adjustUserMessageCountIfNeeded(-1);
		$this->adjustTicketUserMessageCount(-1);

		/** @var \XF\Repository\UserAlert $alertRepo */
		$alertRepo = $this->repository('XF:UserAlert');
		$alertRepo->fastDeleteAlertsForContent('support_ticket_message', $this->message_id);
	}

	protected function submitHamData()
	{
		/** @var \XF\Spam\ContentChecker $submitter */
		$submitter = $this->app()->container('spam.contentHamSubmitter');
		$submitter->submitHam('support_ticket_message', $this->message_id);
	}

	protected function _preDelete()
	{
		// if we're deleting multiple posts, the position value we base the position recalc on in messageHidden
		// will be from when the entity was originally loaded, rather than what is in the database.
		// we therefore need to check what the expected position is before the record is gone and ensure we use that.
		$expectedPosition = $this->db()->fetchOne('SELECT position FROM xf_mjst_ticket_message WHERE message_id = ?', $this->message_id);

		if ($expectedPosition != $this->position)
		{
			$this->setAsSaved('position', $expectedPosition);
		}
	}

	protected function _postDelete()
	{
		if ($this->message_state == 'visible')
		{
			$this->messageHidden(true);
		}

		if ($this->Ticket && $this->message_state == 'visible')
		{
			$this->Ticket->messageRemoved($this);
			$this->Ticket->save();
		}

		if ($this->message_state == 'deleted' && $this->DeletionLog)
		{
			$this->DeletionLog->delete();
		}

		if ($this->getOption('log_moderator'))
		{
			$this->app()->logger()->logModeratorAction('support_ticket_message', $this, 'delete_hard');
		}

		$this->db()->delete('xf_edit_history', 'content_type = ? AND content_id = ?', ['support_ticket_message', $this->message_id]);

		/** @var \XF\Repository\Attachment $attachRepo */
		$attachRepo = $this->repository('XF:Attachment');
		$attachRepo->fastDeleteContentAttachments('support_ticket_message', $this->message_id);
	}

	public function softDelete($reason = '', \XF\Entity\User $byUser = null)
	{
		$byUser = $byUser ?: \XF::visitor();

		if ($this->message_state == 'deleted')
		{
			return false;
		}

		$this->message_state = 'deleted';

		/** @var \XF\Entity\DeletionLog $deletionLog */
		$deletionLog = $this->getRelationOrDefault('DeletionLog');
		$deletionLog->setFromUser($byUser);
		$deletionLog->delete_reason = $reason;

		$this->save();

		return true;
	}

	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_mjst_ticket_message';
		$structure->shortName = 'MJ\SupportTicket:TicketMessage';
		$structure->primaryKey = 'message_id';
		$structure->contentType = 'support_ticket_message';
		$structure->columns = [
			'message_id'        => ['type' => self::UINT, 'nullable' => true, 'autoIncrement' => true],
			'support_ticket_id' => ['type' => self::UINT, 'required' => true],
			'user_id'           => ['type' => self::UINT, 'required' => true],
			'username' => ['type' => self::STR, 'maxLength' => 50,
				'required' => 'please_enter_valid_name'
			],
			'user_email'        => ['type' => self::STR, 'default' => '', 'maxLength' => 120],
			'user_name'         => ['type' => self::STR, 'default' => '', 'maxLength' => 50],
			'message_date'      => ['type' => self::UINT, 'default' => \XF::$time],
			'message' => ['type' => self::STR,
				'required' => 'please_enter_valid_message'
			],
			'ip_id'             => ['type' => self::UINT, 'default' => 0],
			'message_state'     => ['type' => self::STR, 'default' => 'visible',
				'allowedValues' => ['visible', 'moderated', 'deleted']
			],
			'attach_count'      => ['type' => self::UINT, 'default' => 0],
			'position'          => ['type' => self::UINT, 'default' => 0],
			'last_edit_date'    => ['type' => self::UINT, 'default' => 0],
			'last_edit_user_id' => ['type' => self::UINT, 'default' => 0],
			'edit_count'        => ['type' => self::UINT, 'default' => 0],
			'embed_metadata'    => ['type' => self::JSON_ARRAY, 'nullable' => true, 'default' => null]
		];
		$structure->behaviors = [
			'XF:Indexable' => [
				'checkForUpdates' => ['message', 'user_id', 'support_ticket_id', 'message_date', 'message_state']
			]
		];
		$structure->getters = [];
		$structure->relations = [
			'Ticket' => [
				'entity' => 'MJ\SupportTicket:Ticket',
				'type' => self::TO_ONE,
				'conditions' => 'support_ticket_id',
				'primary' => true,
				'with' => ['Department']
			],
			'User' => [
				'entity' => 'XF:User',
				'type' => self::TO_ONE,
				'conditions' => 'user_id',
				'primary' => true
			],
			'Ip' => [
				'entity' => 'XF:Ip',
				'type' => self::TO_ONE,
				'conditions' => 'ip_id',
				'primary' => true
			],
			'Attachments' => [
				'entity' => 'XF:Attachment',
				'type' => self::TO_MANY,
				'conditions' => [
					['content_type', '=', 'support_ticket_message'],
					['content_id', '=', '$message_id']
				],
				'with' => 'Data',
				'order' => 'attach_date'
			],
			'DeletionLog' => [
				'entity' => 'XF:DeletionLog',
				'type' => self::TO_ONE,
				'conditions' => [
					['content_type', '=', 'support_ticket_message'],
					['content_id', '=', '$message_id']
				],
				'primary' => true
			]
		];
		$structure->options = [
			'log_moderator' => true
		];

		return $structure;
	}
}
