<?php

namespace MJ\SupportTicket\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

class Department extends Entity
{
	public function canView(&$error = null)
	{
		return $this->hasPermission('useTicket');
	}

	public function canOpenTicket(&$error = null)
	{
		$visitor = \XF::visitor();

		return $this->hasPermission('openSupportTicket');
	}

	public function canOpenTicketForMember(&$error = null)
	{
		$visitor = \XF::visitor();

		return $this->hasPermission('openTicketAnyone');
	}

	public function canViewAnyTicket(&$error = null)
	{
		$visitor = \XF::visitor();
		return $this->hasPermission('viewAnyTicket');
	}

	public function canAssignTickets()
	{
		return $this->hasPermission('assignSupportTicket');
	}

	public function canViewAssignedStaff()
	{
		return $this->hasPermission('viewAssigned');
	}

	public function canViewDeletedTickets()
	{
		return $this->hasPermission('viewDeleted');
	}

	public function canViewModeratedTickets()
	{
		return $this->hasPermission('viewModerated');
	}

	public function canUseInlineModeration(&$error = null)
	{
		return $this->hasPermission('inlineMod');
	}

	public function canUploadAndManageAttachments()
	{
		$visitor = \XF::visitor();

		return ($visitor->user_id && $this->hasPermission('uploadAttachment'));
	}

	public function canWatch(&$error = null)
	{
		return $this->canViewAnyTicket($error);
	}

	public function hasPermission($permission)
	{
		/** @var \MJ\SupportTicket\XF\Entity\User $visitor */
		$visitor = \XF::visitor();
		return $visitor->hasTicketDepartmentPermission($this->department_id, $permission);
	}

	public function getUsablePrefixes($forcePrefix = null)
	{
		$prefixes = $this->prefixes;

		if ($forcePrefix instanceof TicketPrefix)
		{
			$forcePrefix = $forcePrefix->prefix_id;
		}

		$prefixes = $prefixes->filter(function($prefix) use ($forcePrefix)
		{
			if ($forcePrefix && $forcePrefix == $prefix->prefix_id)
			{
				return true;
			}
			return $this->isPrefixUsable($prefix);
		});

		return $prefixes->groupBy('prefix_group_id');
	}

	public function getPrefixesGrouped()
	{
		return $this->prefixes->groupBy('prefix_group_id');
	}

	public function getBreadcrumbs($includeSelf = true, $linkType = 'public')
	{
		/** @var \XF\Mvc\Router $router */
		$router = $this->app()->container('router.' . $linkType);
		$breadcrumbs = [];
		if ($linkType == 'public')
		{
			$link = 'support-tickets/departments';
		}
		else
		{
			$link = 'mjst-support/departments';
		}
		$breadcrumbs[] = [
			'value'         => $this->title,
			'href'          => $router->buildLink($link, $this),
			'department_id' => $this->department_id
		];
		return $breadcrumbs;
	}

	/**
	 * @return \XF\Mvc\Entity\ArrayCollection
	 */
	public function getPrefixes()
	{
		if (!$this->prefix_cache)
		{
			return $this->_em->getEmptyCollection();
		}

		$prefixes = $this->finder('MJ\SupportTicket:TicketPrefix')
			->where('prefix_id', $this->prefix_cache)
			->order('materialized_order')
			->fetch();

		return $prefixes;
	}

	public function isPrefixUsable($prefix, \XF\Entity\User $user = null)
	{
		if (!$this->isPrefixValid($prefix))
		{
			return false;
		}

		if (!($prefix instanceof TicketPrefix))
		{
			$prefix = $this->em()->find('MJ\SupportTicket:TicketPrefix', $prefix);
			if (!$prefix)
			{
				return false;
			}
		}

		return $prefix->isUsableByUser($user);
	}

	public function isPrefixValid($prefix)
	{
		if ($prefix instanceof TicketPrefix)
		{
			$prefix = $prefix->prefix_id;
		}

		return (!$prefix || isset($this->prefix_cache[$prefix]));
	}

	public function getNewContentState(Ticket $ticket = null)
	{
		$visitor = \XF::visitor();

		if ($visitor->user_id && $visitor->hasTicketDepartmentPermission($this->department_id, 'approveUnapprove'))
		{
			return 'visible';
		}

		if (!$visitor->hasPermission('general', 'submitWithoutApproval'))
		{
			return 'moderated';
		}

		return 'visible';
	}

	public function getNewTicket()
	{
		$ticket = $this->_em->create('MJ\SupportTicket:Ticket');
		$ticket->department_id = $this->department_id;

		return $ticket;
	}

	public function ticketAdded(Ticket $ticket)
	{
		$this->ticket_count++;
	}

	public function activeAdded(Ticket $ticket)
	{
		$this->active_count++;
	}

	public function awaitReplyAdded(Ticket $ticket)
	{
		$this->wait_reply_count++;
	}

	public function ticketRemoved(Ticket $ticket)
	{
		$this->ticket_count--;
		if($this->ticket_count <= 0){
			$this->ticket_count = 0;
		}
	}

	public function activeRemoved(Ticket $ticket)
	{
		$this->active_count--;
		if($this->active_count <= 0){
			$this->active_count = 0;
		}
	}

	public function awaitReplyRemoved(Ticket $ticket)
	{
		$this->wait_reply_count--;
		if($this->wait_reply_count <= 0){
			$this->wait_reply_count = 0;
		}
	}

	protected function _postSave()
	{
		if ($this->isInsert())
		{
			$this->app()->jobManager()->enqueueUnique('permissionRebuild', 'XF:PermissionRebuild');
		}
	}

	protected function _postDelete()
	{
		$db = $this->db();

		$db->delete('xf_mjst_department_field', 'department_id = ?', $this->department_id);
		$db->delete('xf_mjst_department_prefix', 'department_id = ?', $this->department_id);
		$db->delete('xf_mjst_department_watch', 'department_id = ?', $this->department_id);

		if ($this->getOption('delete_tickets'))
		{
			$this->app()->jobManager()->enqueueUnique('mjstDepartmentDelete' . $this->department_id, 'MJ\SupportTicket:DepartmentDelete', [
				'department_id' => $this->department_id
			]);
		}
	}

	public function rebuildCounters()
	{
		$db = $this->db();
		$counter = $db->fetchOne("
			SELECT COUNT(*)
			FROM xf_mjst_ticket
			WHERE department_id = ?
		", $this->department_id);

		list($activeIds, $waitReplyIds) = $this->repository('MJ\SupportTicket:TicketStatus')->getStatusTypesCache();

		$activeCounter = 0;

		if($activeIds){
			$activeCounter = $db->fetchOne("
				SELECT COUNT(*)
				FROM xf_mjst_ticket
				WHERE department_id = ? AND ticket_status_id IN (". $db->quote($activeIds) .")
			", $this->department_id);
		}

		$waitReplyCounter = 0;

		if($waitReplyIds){
			$waitReplyCounter = $db->fetchOne("
				SELECT COUNT(*)
				FROM xf_mjst_ticket
				WHERE department_id = ? AND ticket_status_id IN (". $db->quote($waitReplyIds) .")
			", $this->department_id);
		}

		$this->ticket_count     = $counter;
		$this->active_count     = $activeCounter;
		$this->wait_reply_count = $waitReplyCounter;
	}

	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_mjst_department';
		$structure->shortName = 'MJ\SupportTicket:Department';
		$structure->primaryKey = 'department_id';
		$structure->contentType = 'support_department';
		$structure->columns = [
			'department_id'     => ['type' => self::UINT, 'nullable' => true, 'autoIncrement' => true],
			'title'             => ['type' => self::STR, 'required' => true, 'maxLength' => 50],
			'short_description' => ['type' => self::STR, 'default' => ''],
			'hidden_department' => ['type' => self::BOOL, 'default' => 0],
			'field_cache'       => ['type' => self::SERIALIZED_ARRAY, 'default' => []],
			'prefix_cache'      => ['type' => self::SERIALIZED_ARRAY, 'default' => []],
			'require_prefix'    => ['type' => self::BOOL, 'default' => false],
			'ticket_count'      => ['type' => self::UINT, 'forced' => true, 'default' => 0],
			'message_count'     => ['type' => self::UINT, 'forced' => true, 'default' => 0],
			'active_count'      => ['type' => self::UINT, 'forced' => true, 'default' => 0],
			'wait_reply_count'  => ['type' => self::UINT, 'forced' => true, 'default' => 0],
			'department_date'   => ['type' => self::UINT, 'default' => \XF::$time],
			'display_order'     => ['type' => self::UINT, 'default' => 0]
		];

		$structure->relations = [
			'Permissions' => [
				'entity' => 'XF:PermissionCacheContent',
				'type' => self::TO_MANY,
				'conditions' => [
					['content_type', '=', $structure->contentType],
					['content_id', '=', '$' . $structure->primaryKey]
				],
				'key' => 'permission_combination_id',
				'proxy' => true
			],
			'Watch' => [
				'entity'     => 'MJ\SupportTicket:DepartmentWatch',
				'type'       => self::TO_MANY,
				'conditions' => 'department_id',
				'key'        => 'user_id'
			],
		];
		$structure->getters = [
			'prefixes'      => true,
		];

		$structure->options = [
			'delete_tickets' => true
		];

		return $structure;
	}
}
