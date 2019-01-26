<?php

namespace MJ\SupportTicket\ControllerPlugin;

use XF\ControllerPlugin\AbstractPermission;

class DepartmentPermission extends AbstractPermission
{
	protected $viewFormatter = 'MJ\SupportTicket:Permission\Department%s';
	protected $templateFormatter = 'mjst_permission_department_%s';
	protected $routePrefix = 'permissions/mjst-departments';
	protected $contentType = 'support_department';
	protected $entityIdentifier = 'MJ\SupportTicket:Department';
	protected $primaryKey = 'department_id';
	protected $privatePermissionGroupId = 'mjstSupport';
	protected $privatePermissionId = 'useTicket';
}
