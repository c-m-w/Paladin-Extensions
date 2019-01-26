<?php

namespace MJ\SupportTicket\XF\Entity;

use XF\Mvc\Entity\Structure;

class User extends XFCP_User
{
	public function getTicketCounts()
	{
		if($this->mjst_department_ids){
			$departments = \XF::app()->finder('MJ\SupportTicket:Department')->where('department_id', $this->mjst_department_ids);
			$activeCount = 0;
			$waitReplyCount = 0;
			if($departments){
				foreach($departments as $department){
					$activeCount += $department->active_count;
					$waitReplyCount += $department->wait_reply_count;
				}
			}
			return [
				'active'    => $activeCount,
				'waitReply' => $waitReplyCount
			];
		}
		return false;
	}

	public function hasTicketDepartmentPermission($contentId, $permission)
	{
		return $this->PermissionSet->hasContentPermission('support_department', $contentId, $permission);
	}

	public function canViewSupportTickets(&$error = null)
	{
		return $this->hasPermission('mjstSupport', 'useTicket');
	}

	public function canViewKb(&$error = null)
	{
		return $this->hasPermission('mjstKb', 'view');
	}

	public function canOpenTicket(&$error = null)
	{
		return $this->hasPermission('mjstSupport', 'openSupportTicket');
	}

	public function canOpenTicketForMember(&$error = null)
	{
		return ($this->user_id && $this->hasPermission('mjstSupport', 'openTicketAnyone'));
	}

	public function cacheSupportDepartmentPermissions(array $departmentIds = null)
	{
		if (is_array($departmentIds))
		{
			\XF::permissionCache()->cacheContentPermsByIds($this->permission_combination_id, 'support_department', $departmentIds);
		}
		else
		{
			\XF::permissionCache()->cacheAllContentPerms($this->permission_combination_id, 'support_department');
		}
	}

	public static function getStructure(Structure $structure)
	{
		$structure = parent::getStructure($structure);

		$structure->columns['mjst_ticket_count'] = ['type' => self::UINT, 'default' => 0, 'forced' => true, 'changeLog' => false];
		$structure->columns['mjst_department_ids'] = ['type' => self::LIST_COMMA, 'default' => [],
			'list' => ['type' => 'posint', 'unique' => true, 'sort' => SORT_NUMERIC]
		];

		return $structure;
	}
}
