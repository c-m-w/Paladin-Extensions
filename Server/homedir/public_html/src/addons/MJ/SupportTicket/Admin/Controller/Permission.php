<?php

namespace MJ\SupportTicket\Admin\Controller;

use XF\Admin\Controller\AbstractController;
use XF\Mvc\FormAction;
use XF\Mvc\ParameterBag;

class Permission extends AbstractController
{
	protected function preDispatchController($action, ParameterBag $params)
	{
		$this->assertAdminPermission('mjstSupport');
	}

	/**
	 * @return \MJ\SupportTicket\ControllerPlugin\DepartmentPermission
	 */
	protected function getDepartmentPermissionPlugin()
	{
		/** @var \MJ\SupportTicket\ControllerPlugin\DepartmentPermission $plugin */
		$plugin = $this->plugin('MJ\SupportTicket:DepartmentPermission');
		$plugin->setFormatters('MJ\SupportTicket\Permission\Department%s', 'mjst_permission_department_%s');
		$plugin->setRoutePrefix('permissions/mjst-departments');

		return $plugin;
	}

	public function actionDepartment(ParameterBag $params)
	{
		if ($params->department_id)
		{
			return $this->getDepartmentPermissionPlugin()->actionList($params);
		}
		else
		{
			$departmentRepo = $this->repository('MJ\SupportTicket:Department');
			$departments = $departmentRepo->getFullDepartmentList();

			$customPermissions = $this->repository('XF:PermissionEntry')->getContentWithCustomPermissions('support_department');

			$viewParams = [
				'departments' => $departments,
				'customPermissions' => $customPermissions
			];
			return $this->view('MJ\SupportTicket:Permission\DepartmentOverview', 'mjst_permission_department_overview', $viewParams);
		}
	}

	public function actionDepartmentEdit(ParameterBag $params)
	{
		return $this->getDepartmentPermissionPlugin()->actionEdit($params);
	}

	public function actionDepartmentSave(ParameterBag $params)
	{
		return $this->getDepartmentPermissionPlugin()->actionSave($params);
	}
}
