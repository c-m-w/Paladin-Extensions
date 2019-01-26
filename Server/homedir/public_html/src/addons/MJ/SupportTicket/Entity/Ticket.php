<?php

namespace MJ\SupportTicket\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

class Ticket extends Entity
{
	const STATUS_OPEN     = 1;
	const STATUS_ANSWERED = 2;
	const STATUS_CUSREPLY = 3;
	const STATUS_CLOSED   = 4;
	const STATUS_AWAITING = 5;

	public function canView(&$error = null)
	{
		if (!$this->Department || !$this->Department->canView())
		{
			return false;
		}

		$visitor = \XF::visitor();
		$departmentId = $this->department_id;

		if (!$visitor->hasTicketDepartmentPermission($departmentId, 'useTicket'))
		{
			return false;
		}

		if ($visitor->hasTicketDepartmentPermission($departmentId, 'viewAnyTicket'))
		{
			return true;
		}

		if(!$visitor->user_id || $visitor->user_id != $this->user_id){
			return false;
		}
		return true;
	}

	public function canViewGuestTicket(&$error = null)
	{
		$visitor = \XF::visitor();
		$departmentId = $this->department_id;

		$password = \XF::app()->request()->getCookie('msjtp_' . $this->support_ticket_id);
		if(!$password){
			$password = \XF::app()->request()->getCookie('ticket_passwords_' . $this->support_ticket_id);
		}

		if($password == $this->guest_password){
			return true;
		}

		if (!$visitor->hasTicketDepartmentPermission($departmentId, 'useTicket'))
		{
			return false;
		}
		if ($visitor->hasTicketDepartmentPermission($departmentId, 'viewAnyTicket'))
		{
			return true;
		}

		if(!$visitor->user_id || $visitor->user_id != $this->user_id){
			return false;
		}

		return true;
	}

	public function canPreview(&$error = null)
	{
		// assumes view check has already been run
		$visitor = \XF::visitor();
		$departmentId = $this->department_id;
		return (
			$this->first_message_id
			&& $this->app()->options()->discussionPreview
			&& ($visitor->user_id == $this->user_id || $visitor->hasNodePermission($departmentId, 'viewAnyTicket'))
		);
	}

	public function canEdit(&$error = null)
	{
		$visitor = \XF::visitor();
		if (!$visitor->user_id)
		{
			return false;
		}

		$departmentId = $this->department_id;

		if ($visitor->hasTicketDepartmentPermission($departmentId, 'manageAnyTicket'))
		{
			return true;
		}

		if ($this->user_id == $visitor->user_id && $visitor->hasTicketDepartmentPermission($departmentId, 'editOwnMessage'))
		{
			$editLimit = $visitor->hasTicketDepartmentPermission($departmentId, 'editOwnMessageTimeLimit');
			if ($editLimit != -1 && (!$editLimit || $this->message_date < \XF::$time - 60 * $editLimit))
			{
				$error = \XF::phraseDeferred('message_edit_time_limit_expired', ['minutes' => $editLimit]);
				return false;
			}
			return $visitor->hasTicketDepartmentPermission($departmentId, 'editOwnTicketTitle');
		}

		return false;
	}

	public function canEditTicketDepartment(&$error = null)
	{
		$visitor = \XF::visitor();
		if (!$visitor->user_id)
		{
			return false;
		}

		if ($visitor->hasTicketDepartmentPermission($this->department_id, 'editTicketDepartment'))
		{
			return true;
		}

		return false;
	}

	public function canChangeOwner(&$error = null)
	{
		$visitor = \XF::visitor();
		if (!$visitor->user_id)
		{
			return false;
		}

		if ($visitor->hasTicketDepartmentPermission($this->department_id, 'changeOwner'))
		{
			return true;
		}

		return false;
	}

	public function canViewAssigned(&$error = null)
	{
		$visitor = \XF::visitor();
		if (!$visitor->user_id)
		{
			return false;
		}

		if ($visitor->hasTicketDepartmentPermission($this->department_id, 'viewAssigned'))
		{
			return true;
		}

		if ($this->canAssignSupportTicket())
		{
			return true;
		}

		return false;
	}

	public function canAssignSupportTicket(&$error = null)
	{
		$visitor = \XF::visitor();
		if (!$visitor->user_id)
		{
			return false;
		}

		if ($visitor->hasTicketDepartmentPermission($this->department_id, 'assignSupportTicket'))
		{
			return true;
		}

		return false;
	}

	public function canEditTicketStatus(&$error = null)
	{
		$visitor = \XF::visitor();
		if (!$visitor->user_id)
		{
			return false;
		}

		if ($visitor->hasTicketDepartmentPermission($this->department_id, 'editTicketStatus'))
		{
			return true;
		}

		return false;
	}

	public function canClose(&$error = null)
	{
		$visitor = \XF::visitor();
		if (!$visitor->user_id)
		{
			return false;
		}

		$departmentId = $this->department_id;

		if ($visitor->hasTicketDepartmentPermission($departmentId, 'manageAnyTicket'))
		{
			return true;
		}

		if ($this->user_id == $visitor->user_id)
		{
			return true;
		}

		return false;
	}

	public function canViewCurrentViewer(&$error = null)
	{
		$visitor = \XF::visitor();
		if (!$visitor->user_id)
		{
			return false;
		}

		if ($visitor->hasTicketDepartmentPermission($this->department_id, 'viewCurrentViewer'))
		{
			return true;
		}

		return false;
	}

	public function canRate(&$error = null)
	{
		$visitor = \XF::visitor();
		if (!$visitor->user_id)
		{
			return false;
		}

		if ($this->user_id == $visitor->user_id)
		{
			return true;
		}

		return false;
	}

	public function canReply(&$error = null)
	{
		$visitor = \XF::visitor();
		$departmentId = $this->department_id;
		if (!$visitor->hasTicketDepartmentPermission($departmentId, 'postReply'))
		{
			return false;
		}

		return true;
	}

	public function canUseInlineModeration(&$error = null)
	{
		$visitor = \XF::visitor();
		return ($visitor->user_id && $visitor->hasTicketDepartmentPermission($this->department_id, 'inlineMod'));
	}

	public function canDelete(&$error = null)
	{
		$visitor = \XF::visitor();
		if (!$visitor->user_id)
		{
			return false;
		}

		$departmentId = $this->department_id;

		if ($visitor->hasTicketDepartmentPermission($departmentId, 'deleteAnyTicket'))
		{
			return true;
		}

		if ($this->user_id == $visitor->user_id && $visitor->hasTicketDepartmentPermission($departmentId, 'deleteOwnTicket'))
		{
			return true;
		}

		return false;
	}

	public function canViewDeletedMessages()
	{
		return \XF::visitor()->hasTicketDepartmentPermission($this->department_id, 'viewDeleted');
	}

	public function canViewModeratedMessages()
	{
		return \XF::visitor()->hasTicketDepartmentPermission($this->department_id, 'viewModerated');
	}

	public function canViewSubmitterIp()
	{
		return \XF::visitor()->hasTicketDepartmentPermission($this->department_id, 'viewSubmitterIp');
	}

	public function canMove(&$error = null)
	{
		$visitor = \XF::visitor();
		return $visitor->user_id && $visitor->hasTicketDepartmentPermission($this->department_id, 'manageAnyTicket');
	}

	public function canCopy(&$error = null)
	{
		$visitor = \XF::visitor();
		return $visitor->user_id && $visitor->hasTicketDepartmentPermission($this->department_id, 'manageAnyTicket');
	}

	public function canMerge(&$error = null)
	{
		$visitor = \XF::visitor();
		return $visitor->user_id && $visitor->hasTicketDepartmentPermission($this->department_id, 'manageAnyTicket');
	}

	public function canUploadAndManageAttachments()
	{
		$visitor = \XF::visitor();

		return ($visitor->user_id && $visitor->hasPermission('mjstSupport', 'uploadAttachment'));
	}

	public function canViewAttachments(&$error = null)
	{
		return \XF::visitor()->hasTicketDepartmentPermission($this->department_id, 'viewAttachment');
	}

	public function canWatch(&$error = null)
	{
		return \XF::visitor()->user_id ? true : false;
	}

	public function canSendModeratorActionAlert()
	{
		return $this->FirstMessage->canSendModeratorActionAlert();
	}

	public function canViewModeratorLogs(&$error = null)
	{
		$visitor = \XF::visitor();
		return $visitor->user_id && $visitor->hasTicketDepartmentPermission($this->department_id, 'manageAnyTicket');
	}

	public function getVisitorReadDate()
	{
		$visitor = \XF::visitor();
		if (!$visitor->user_id)
		{
			return null;
		}

		$ticketRead = $this->Read[$visitor->user_id];

		$dates = [\XF::$time - $this->app()->options()->readMarkingDataLifetime * 86400];
		if ($ticketRead)
		{
			$dates[] = $ticketRead->support_ticket_read_date;
		}

		return max($dates);
	}

	/**
	 * @return \XF\Draft
	 */
	public function getDraftReply()
	{
		return \XF\Draft::createFromEntity($this, 'DraftReplies');
	}

	public function getUrgencyTitle()
	{
		switch ($this->urgency) {
			case 1:
				return \XF::phrase('mjst_high');
				break;
			case 2:
				return \XF::phrase('mjst_medium');
				break;
			case 3:
				return \XF::phrase('mjst_low');
				break;
		}

		return '';
	}

	public function getNewMessage()
	{
		$message = $this->_em->create('MJ\SupportTicket:TicketMessage');

		$message->support_ticket_id = $this->_getDeferredValue(function()
		{
			return $this->support_ticket_id;
		}, 'save');

		return $message;
	}

	public function getFieldEditMode()
	{
		$visitor = \XF::visitor();

		$isSelf = ($visitor->user_id == $this->user_id || !$this->support_ticket_id);
		$isMod = ($visitor->user_id && $visitor->hasTicketDepartmentPermission($this->department_id, 'manageAnyTicket'));

		if ($isMod || !$isSelf)
		{
			return $isSelf ? 'moderator_user' : 'moderator';
		}
		else
		{
			return 'user';
		}
	}

	/**
	 * @return \XF\CustomField\Set
	 */
	public function getCustomFields()
	{
		/** @var \XF\CustomField\DefinitionSet $fieldDefinitions */
		$fieldDefinitions = $this->app()->container('customFields.tickets');

		return new \XF\CustomField\Set($fieldDefinitions, $this);
	}

	/**
	 * @return array
	 */
	public function getMessageIds()
	{
		return $this->db()->fetchAllColumn("
			SELECT message_id
			FROM xf_mjst_ticket_message
			WHERE support_ticket_id = ?
			ORDER BY message_date
		", $this->support_ticket_id);
	}

	/**
	 * @return array
	 */
	public function getLastMessageCache()
	{
		return [
			'message_id'   => $this->last_message_id,
			'user_id'      => $this->last_message_user_id,
			'username'     => $this->last_message_username,
			'message_date' => $this->last_message_date
		];
	}

	public function getBreadcrumbs($includeSelf = true)
	{
		$breadcrumbs = $this->Department ? $this->Department->getBreadcrumbs() : [];
		if ($includeSelf && $this->support_ticket_id)
		{
			$breadcrumbs[] = [
				'href' => $this->app()->router('public')->buildLink('support-tickets', $this),
				'value' => $this->title
			];
		}

		return $breadcrumbs;
	}
	public function getFullTitle($rich = false)
	{
		if($rich){
			return '<span class="ticketId">#' . $this->ticket_id . '</span> ' . $this->title;
		}
		return '[#' . $this->ticket_id . '] ' . $this->title;
	}

	public function isUnread()
	{
		$readDate = $this->getVisitorReadDate();
		if ($readDate === null)
		{
			return false;
		}

		return $readDate < $this->last_message_date;
	}

	public function isClosed()
	{
		return $this->ticket_status_id == self::STATUS_CLOSED;
	}

	public function isIgnored()
	{
		return \XF::visitor()->isIgnoring($this->user_id);
	}

	public function setDataFromDraft($draft)
	{
		$this->title            = $draft->title ?: '';
		$this->prefix_id        = $draft->prefix_id ?: 0;
		$this->urgency          = $draft->urgency ?: 0;
		$this->ticket_status_id = $draft->ticket_status_id ?: 0;
	}

	public function rebuildCounters()
	{
		$this->rebuildFirstMessageInfo();
		$this->rebuildLastMessageInfo();
		$this->rebuildReplyCount();

		return true;
	}

	public function rebuildFirstMessageInfo()
	{
		$firstMessage = $this->db()->fetchRow("
			SELECT message_id, message_date, user_id, username
			FROM xf_mjst_ticket_message
			WHERE support_ticket_id = ?
			ORDER BY message_date
			LIMIT 1
		", $this->support_ticket_id);
		if (!$firstMessage)
		{
			return false;
		}

		// TODO: sanity check first message to make sure it's visible and force it? Might break other counters though

		$this->first_message_id = $firstMessage['message_id'];
		$this->open_date = $firstMessage['message_date'];
		$this->user_id = $firstMessage['user_id'];
		$this->username = $firstMessage['username'] ?: '-';

		return true;
	}

	public function rebuildLastMessageInfo()
	{
		$lastMessage = $this->db()->fetchRow("
			SELECT message_id, message_date, user_id, username
			FROM xf_mjst_ticket_message
			WHERE support_ticket_id = ?
				AND message_state = 'visible'
			ORDER BY message_date DESC
			LIMIT 1
		", $this->support_ticket_id);
		if (!$lastMessage)
		{
			return false;
		}

		$this->last_message_id = $lastMessage['message_id'];
		$this->last_message_date = $lastMessage['message_date'];
		$this->last_message_user_id = $lastMessage['user_id'];
		$this->last_message_username = $lastMessage['username'] ?: '-';

		return true;
	}

	public function rebuildReplyCount()
	{
		$visibleMessages = $this->db()->fetchOne("
			SELECT COUNT(*)
			FROM xf_mjst_ticket_message
			WHERE support_ticket_id = ?
				AND message_state = 'visible'
		", $this->support_ticket_id);
		$this->reply_count = max(0, $visibleMessages - 1);

		return $this->reply_count;
	}

	public function messageAdded(TicketMessage $message)
	{
		if (!$this->first_message_id)
		{
			$this->first_message_id = $message->message_id;
		}
		else
		{
			$this->reply_count++;
		}

		if ($message->message_date >= $this->last_message_date)
		{
			$this->last_message_date = $message->message_date;
			$this->last_message_id = $message->message_id;
			$this->last_message_user_id = $message->user_id;
			$this->last_message_username = $message->username;
		}
		if($message->user_id != $this->user_id){
			$this->ticket_status_id = self::STATUS_ANSWERED;
		}else{
			$this->ticket_status_id = self::STATUS_CUSREPLY;
		}

		unset($this->_getterCache['message_ids']);
	}

	public function messageRemoved(TicketMessage $message)
	{
		$this->reply_count--;

		if ($message->message_id == $this->first_message_id)
		{
			$this->rebuildFirstMessageInfo();
		}

		if ($message->message_id == $this->last_message_id)
		{
			$this->rebuildLastMessageInfo();
		}

		unset($this->_getterCache['message_ids']);
	}

	protected function _preSave()
	{
		if ($this->prefix_id && ($this->isChanged(['prefix_id', 'department_id'])))
		{
			if (!$this->Department->isPrefixValid($this->prefix_id))
			{
				$this->prefix_id = 0;
			}
		}
		if(!$this->ticket_status_id){
			$this->ticket_status_id = self::STATUS_OPEN;
		}

		if($this->isInsert()){
			$this->guest_password = \XF\Util\Random::getRandomString(16);
			$this->ticket_id = $this->repository('MJ\SupportTicket:Ticket')->randomTicketId();
		}
		$this->last_update = \XF::$time;
	}

	protected function _postSave()
	{
		$this->updateDepartmentRecord();

		if ($this->isUpdate() && $this->getOption('log_moderator'))
		{
			$this->app()->logger()->logModeratorChanges('support_ticket', $this);
		}

		if($this->isInsert() && !$this->user_id){
			$this->app()->response()->setCookie('msjtp_' . $this->support_ticket_id, $this->guest_password);
		}
	}

	protected function ticketMadeVisible()
	{
		// TODO: this may need a different process with big tickets
		$this->adjustUserMessageCountIfNeeded(1);
	}

	protected function ticketHidden($hardDelete = false)
	{
		$this->adjustUserMessageCountIfNeeded(-1);
		/** @var \XF\Repository\UserAlert $alertRepo */
		$alertRepo = $this->repository('XF:UserAlert');
		$alertRepo->fastDeleteAlertsForContent('support_ticket_message', $this->message_ids);
	}

	protected function submitHamData()
	{
		/** @var \XF\Spam\ContentChecker $submitter */
		$submitter = $this->app()->container('spam.contentHamSubmitter');
		$submitter->submitHam('support_ticket', $this->support_ticket_id);
	}

	protected function adjustUserMessageCountIfNeeded($direction, $forceChange = false)
	{
		$updates = $this->db()->fetchPairs("
			SELECT user_id, COUNT(*)
			FROM xf_mjst_ticket_message
			WHERE support_ticket_id = ?
				AND user_id > 0
				AND message_state = 'visible'
			GROUP BY user_id
		", $this->support_ticket_id);

		$operator = $direction > 0 ? '+' : '-';
		foreach ($updates as $userId => $adjust)
		{
			$this->db()->query("
				UPDATE xf_user
				SET mjst_ticket_count = GREATEST(0, CAST(mjst_ticket_count AS SIGNED) {$operator} ?)
				WHERE user_id = ?
			", [$adjust, $userId]);
		}
	}

	protected function updateDepartmentRecord()
	{
		if (!$this->Department)
		{
			return;
		}

		/** @var \MJ\SupportTicket\Entity\Department $department */
		$department = $this->Department;

		list($activeIds, $waitReplyIds) = $this->repository('MJ\SupportTicket:TicketStatus')->getStatusTypesCache();
		$statusId = $this->ticket_status_id;

		$isActive = in_array($statusId, $activeIds) ? true : false;
		$isWaitReply = in_array($statusId, $waitReplyIds) ? true : false;
		$updated = true;

		if ($this->isUpdate())
		{
			$oldStatusId = $this->getExistingValue('ticket_status_id');
			$isOldActive = in_array($oldStatusId, $activeIds) ? true : false;
			$isOldWaitReply = in_array($oldStatusId, $waitReplyIds) ? true : false;

			if($this->isChanged('department_id')){
				$department->ticketAdded($this);
				if($isActive){
					$department->activeAdded($this);
				}
				if($isWaitReply){
					$department->awaitReplyAdded($this);
				}
				$department->save();

				/** @var Department $oldDepartment */
				$oldDepartment = $this->getExistingRelation('Department');
				$oldDepartment->ticketRemoved($this);
				if($isOldActive){
					$oldDepartment->activeRemoved($this);
				}
				if($isOldWaitReply){
					$oldDepartment->awaitReplyRemoved($this);
				}
				$oldDepartment->save();
			}else if($this->isChanged('ticket_status_id')){
				if($isOldActive && !$isActive){
					$department->activeRemoved($this);
				}else if(!$isOldActive && $isActive){
					$department->activeAdded($this);
				}
				if($isOldWaitReply && !$isWaitReply){
					$department->awaitReplyRemoved($this);
				}else if(!$isOldWaitReply && $isWaitReply){
					$department->awaitReplyAdded($this);
				}
				if($department->hasChanges()){
					$department->save();
				}
			}
			return;
		}

		if($this->isInsert()){
			$department->ticketAdded($this);
			if($isActive){
				$department->activeAdded($this);
			}
			if($isWaitReply){
				$department->awaitReplyAdded($this);
			}
			$department->save();
		}
	}

	protected function _postDelete()
	{
		$this->ticketHidden(true);

		if ($this->Department)
		{
			$department = $this->Department;
			list($activeIds, $waitReplyIds) = $this->repository('MJ\SupportTicket:TicketStatus')->getStatusTypesCache();
			$statusId = $this->ticket_status_id;

			$isActive = in_array($statusId, $activeIds) ? true : false;
			$isWaitReply = in_array($statusId, $waitReplyIds) ? true : false;
			if($isActive){
				$department->activeRemoved($this);
			}
			if($isWaitReply){
				$department->awaitReplyRemoved($this);
			}
			$department->ticketRemoved($this);
			$department->save();
		}

		if ($this->getOption('log_moderator'))
		{
			$this->app()->logger()->logModeratorAction('support_ticket', $this, 'delete');
		}

		$db = $this->db();

		$messageIds = $this->message_ids;
		if ($messageIds)
		{
			$this->_postDeleteMessages($messageIds);
		}
	}

	protected function _postDeleteMessages(array $messageIds)
	{
		$db = $this->db();

		/** @var \XF\Repository\Attachment $attachRepo */
		$attachRepo = $this->repository('XF:Attachment');
		$attachRepo->fastDeleteContentAttachments('support_ticket_message', $messageIds);

		$db->delete('xf_mjst_ticket_message', 'message_id IN (' . $db->quote($messageIds) . ')');

		$db->delete('xf_deletion_log', 'content_id IN (' . $db->quote($messageIds) . ') AND content_type = ?', 'support_ticket_message');
		$db->delete('xf_edit_history', 'content_id IN (' . $db->quote($messageIds) . ') AND content_type = ?', 'support_ticket_message');
	}

	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_mjst_ticket';
		$structure->shortName = 'MJ\SupportTicket:Ticket';
		$structure->primaryKey = 'support_ticket_id';
		$structure->contentType = 'support_ticket';
		$structure->columns = [
			'support_ticket_id'     => ['type' => self::UINT, 'nullable' => true, 'autoIncrement' => true],
			'ticket_id'             => ['type' => self::STR, 'maxLength' => 25, 'default' => ''],
			'title'                 => ['type' => self::STR, 'required' => true],
			'user_id'               => ['type' => self::UINT, 'required' => true],
			'username'              => ['type' => self::STR, 'required' => true, 'maxLength' => 50],
			'user_email'            => ['type' => self::STR, 'default' => '', 'maxLength' => 120],
			'user_name'             => ['type' => self::STR, 'default' => '', 'maxLength' => 50],
			'creator_user_id'       => ['type' => self::UINT, 'default' => 0],
			'creator_username'      => ['type' => self::STR, 'default' => '', 'maxLength' => 50],
			'open_date'             => ['type' => self::UINT, 'default' => \XF::$time],
			'urgency'               => ['type' => self::STR, 'default' => 2, 'allowedValues' => ['1', '2', '3']],
			'guest_password'        => ['type' => self::STR, 'maxLength' => 50, 'default' => ''],
			'reply_count'           => ['type' => self::UINT, 'default' => 0],
			'participant_count'     => ['type' => self::UINT, 'default' => 0],
			'department_id'         => ['type' => self::UINT, 'required' => true],
			'assigned_user_id'      => ['type' => self::UINT, 'default' => 0],
			'ticket_status_id'      => ['type' => self::UINT, 'required' => true],
			'is_primary_close'      => ['type' => self::BOOL, 'default' => 0],
			'first_message_id'      => ['type' => self::UINT, 'default' => 0],
			'last_update'           => ['type' => self::UINT, 'default' => \XF::$time],
			'last_message_date'     => ['type' => self::UINT, 'default' => \XF::$time],
			'last_message_id'       => ['type' => self::UINT, 'default' => 0],
			'last_message_user_id'  => ['type' => self::UINT, 'default' => 0],
			'last_message_username' => ['type' => self::STR, 'maxLength' => 50, 'default' => ''],
			'submitter_rating'      => ['type' => self::FLOAT, 'default' => 0],
			'prefix_id'             => ['type' => self::UINT, 'default' => 0],
			'custom_fields'         => ['type' => self::JSON_ARRAY, 'default' => []],
			'participants'          => ['type' => self::JSON_ARRAY, 'default' => []],
			'is_piping_email'       => ['type' => self::BOOL, 'default' => 0]
		];

		$structure->behaviors = [
			'XF:CustomFieldsHolder' => [
				'valueTable' => 'xf_mjst_ticket_field_value',
				'checkForUpdates' => ['department_id'],
				'getAllowedFields' => function($ticket)
				{
					return $ticket->Department ? $ticket->Department->field_cache : [];
				}
			]
		];

		$structure->getters = [
			'draft_reply'        => true,
			'message_ids'        => true,
			'last_message_cache' => true,
			'custom_fields'      => true,
			'full_title'         => true,
			'urgency_title'      => true,
		];

		$structure->relations = [
			'Department' => [
				'entity'     => 'MJ\SupportTicket:Department',
				'type'       => self::TO_ONE,
				'conditions' => 'department_id',
				'primary'    => true
			],
			'User' => [
				'entity'     => 'XF:User',
				'type'       => self::TO_ONE,
				'conditions' => 'user_id',
				'primary'    => true
			],
			'Creator' => [
				'entity' => 'XF:User',
				'type' => self::TO_ONE,
				'conditions' => [
					['user_id', '=', '$creator_user_id']
				],
				'primary' => true
			],
			'Status' => [
				'entity'     => 'MJ\SupportTicket:TicketStatus',
				'type'       => self::TO_ONE,
				'conditions' => 'ticket_status_id',
				'primary'    => true
			],
			'FirstMessage' => [
				'entity' => 'MJ\SupportTicket:TicketMessage',
				'type' => self::TO_ONE,
				'conditions' => [['message_id', '=', '$first_message_id']],
				'primary' => true
			],
			'AssignedUser' => [
				'entity'     => 'XF:User',
				'type'       => self::TO_ONE,
				'conditions' => [['message_id', '=', '$assigned_user_id']],
				'primary' => true
			],
			'LastMessage' => [
				'entity' => 'MJ\SupportTicket:TicketMessage',
				'type' => self::TO_ONE,
				'conditions' => [['message_id', '=', '$last_message_id']],
				'primary' => true
			],
			'LastMessager' => [
				'entity' => 'XF:User',
				'type' => self::TO_ONE,
				'conditions' => [['user_id', '=', '$last_message_user_id']],
				'primary' => true
			],
			'Prefix' => [
				'entity' => 'MJ\SupportTicket:TicketPrefix',
				'type' => self::TO_ONE,
				'conditions' => 'prefix_id',
				'primary' => true
			],
			'Read' => [
				'entity' => 'MJ\SupportTicket:TicketRead',
				'type' => self::TO_MANY,
				'conditions' => 'support_ticket_id',
				'key' => 'user_id'
			],
			'Watch' => [
				'entity'     => 'MJ\SupportTicket:TicketWatch',
				'type'       => self::TO_MANY,
				'conditions' => 'support_ticket_id',
				'key'        => 'user_id'
			],
			'EscalationLog' => [
				'entity'     => 'MJ\SupportTicket:TicketEscalationLog',
				'type'       => self::TO_MANY,
				'conditions' => 'support_ticket_id',
				'key'        => 'escalation_id'
			],
			'DraftReplies' => [
				'entity' => 'XF:Draft',
				'type' => self::TO_MANY,
				'conditions' => [
					['draft_key', '=', 'mjst-ticket-', '$support_ticket_id']
				],
				'key' => 'user_id'
			],
		];

		$structure->options = [
			'log_moderator' => true
		];

		return $structure;
	}
}
