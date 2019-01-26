<?php

namespace XR\PM\XF\Entity;

class User extends XFCP_User
{
	public function canViewProducts(&$error = null)
	{
		return $this->hasPermission('xr_pm', 'view');
	}

	public function hasXrPmCategoryPermission($contentId, $permission)
	{
		return $this->PermissionSet->hasContentPermission('xr_pm_category', $contentId, $permission);
	}
}