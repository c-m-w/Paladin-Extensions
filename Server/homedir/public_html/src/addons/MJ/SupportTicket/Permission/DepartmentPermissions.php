<?php

namespace MJ\SupportTicket\Permission;

use XF\Mvc\Entity\Entity;
use XF\Permission\FlatContentPermissions;

class DepartmentPermissions extends FlatContentPermissions
{
	public function getContentType()
	{
		return 'support_department';
	}

	public function getAnalysisTypeTitle()
	{
		return \XF::phrase('mjst_department_permissions');
	}

	public function isValidPermission(\XF\Entity\Permission $permission)
	{
		return ($permission->permission_group_id == 'mjstSupport');
	}

	public function getContentList()
	{
		/** @var \MJ\SupportTicket\Repository\Department $departmentRepo */
		$departmentRepo = $this->builder->em()->getRepository('MJ\SupportTicket:Department');
		return $departmentRepo->findDepartmentList()->fetch();
	}

	protected function getFinalPerms($contentId, array $calculated, array &$childPerms)
	{
		if (!isset($calculated['mjstSupport']))
		{
			$calculated['mjstSupport'] = [];
		}

		$final = $this->builder->finalizePermissionValues($calculated['mjstSupport']);

		if (empty($final['useTicket']))
		{
			$childPerms['mjstSupport']['useTicket'] = 'deny';
		}

		return $final;
	}

	protected function getFinalAnalysisPerms($contentId, array $calculated, array &$childPerms)
	{
		$final = $this->builder->finalizePermissionValues($calculated);

		if (empty($final['mjstSupport']['useTicket']))
		{
			$childPerms['mjstSupport']['useTicket'] = 'deny';
		}

		return $final;
	}
}
