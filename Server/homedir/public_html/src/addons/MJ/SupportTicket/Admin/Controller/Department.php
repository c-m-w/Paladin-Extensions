<?php

namespace MJ\SupportTicket\Admin\Controller;

use XF\Mvc\FormAction;
use XF\Mvc\ParameterBag;
use XF\Admin\Controller\AbstractController;

class Department extends AbstractController
{
	protected function preDispatchController($action, ParameterBag $params)
	{
		$this->assertAdminPermission('mjstDepartment');
	}

	public function actionIndex()
	{
		$customPermissions = $this->repository('XF:PermissionEntry')->getContentWithCustomPermissions('support_department');

		$viewParams = [
			'departments' => $this->getDepartmentRepo()->findDepartmentList()->fetch(),
			'customPermissions' => $customPermissions
		];
		return $this->view('MJ\SupportTicket:Department\Listing', 'mjst_department_list', $viewParams);
	}

	public function actionMember(ParameterBag $params)
	{
		$department = $this->assertDepartmentExists($params->department_id);

		$criteria = $this->filter('criteria', 'array');
		$order = $this->filter('order', 'str');
		$direction = $this->filter('direction', 'str');

		$page = $this->filterPage();
		$perPage = 20;

		$showingAll = $this->filter('all', 'bool');
		if ($showingAll)
		{
			$page = 1;
			$perPage = 5000;
		}

		$searcher = $this->searcher('XF:User', $criteria);

		if ($order && !$direction)
		{
			$direction = $searcher->getRecommendedOrderDirection($order);
		}

		$searcher->setOrder($order, $direction);

		$finder = $searcher->getFinder();
		$finder->limitByPage($page, $perPage);

		$filter = $this->filter('_xfFilter', [
			'text' => 'str',
			'prefix' => 'bool'
		]);
		if (strlen($filter['text']))
		{
			$finder->where('username', 'LIKE', $finder->escapeLike($filter['text'], $filter['prefix'] ? '?%' : '%?%'));
		}
		$finder->whereSql('FIND_IN_SET(' . $finder->quote($department->department_id) . ', mjst_department_ids)');

		$total = $finder->total();
		$users = $finder->fetch();

		$viewParams = [
			'department'  => $department,
			'users'       => $users,

			'total'       => $total,
			'page'        => $page,
			'perPage'     => $perPage,

			'showingAll'  => $showingAll,
			'showAll'     => (!$showingAll && $total <= 5000),

			'criteria'    => $searcher->getFilteredCriteria(),
			'filter'      => $filter['text'],
			'sortOptions' => $searcher->getOrderOptions(),
			'order'       => $order,
			'direction'   => $direction
		];
		return $this->view('XF:User\Listing', 'mjst_department_member', $viewParams);
	}

	public function actionMemberAdd(ParameterBag $params)
	{
		$department = $this->assertDepartmentExists($params->department_id);

		/** @var \XF\Repository\Permission $permissionRepo */
		$permissionRepo = $this->repository('XF:Permission');
		$permissionData = $permissionRepo->getContentPermissionListData('support_department');

		/** @var \XF\Repository\PermissionEntry $entryRepo */
		$entryRepo = $this->repository('XF:PermissionEntry');
		$permissionData['values'] = [];

		$viewParams = [
			'department' => $department,
			'permissionData' => $permissionData
		];
		return $this->view('MJ\SupportTicket:Department\Delete', 'mjst_department_member_edit', $viewParams);
	}

	public function actionMemberEdit(ParameterBag $params)
	{
		$department = $this->assertDepartmentExists($params->department_id);

		$userId = $this->filter('user_id', 'uint');

		$user = $this->em()->find('XF:User', $userId);
		if(!$user){
			return $this->error(\XF::phrase('requested_user_not_found'));
		}
		if(!$user->mjst_department_ids || !in_array($department->department_id, $user->mjst_department_ids)){
			return $this->error(\XF::phrase('mjst_this_user_not_member_of_this_department'));
		}

		/** @var \XF\Repository\Permission $permissionRepo */
		$permissionRepo = $this->repository('XF:Permission');
		$permissionData = $permissionRepo->getContentPermissionListData('support_department');

		/** @var \XF\Repository\PermissionEntry $entryRepo */
		$entryRepo = $this->repository('XF:PermissionEntry');
		$permissionData['values'] = $entryRepo->getContentUserPermissionEntries(
			'support_department',
			$department->department_id,
			$user->user_id
		);

		$viewParams = [
			'department'     => $department,
			'user'           => $user,
			'permissionData' => $permissionData
		];
		return $this->view('MJ\SupportTicket:Department\Delete', 'mjst_department_member_edit', $viewParams);
	}

	public function actionMemberSave(ParameterBag $params)
	{
		$department = $this->assertDepartmentExists($params->department_id);

		$userId = $this->filter('user_id', 'uint');
		if($userId){
			$user = $this->em()->find('XF:User', $userId);
		}else{
			$username = $this->filter('username', 'str');
			$user = $this->finder('XF:User')
				->where('username', $username)
				->fetchOne();
		}
		if (!$user)
		{
			return $this->error(\XF::phrase('requested_user_not_found'));
		}

		$isNew = false;
		$ids = $user->mjst_department_ids;
		if(!$ids){
			$ids = [];
		}
		if(!$ids || !in_array($department->department_id, $ids)){
			$isNew = true;
		}
		$ids[] = $department->department_id;
		$user->mjst_department_ids = array_unique($ids);
		$user->save();
		if($isNew){
			/** @var \MJ\SupportTicket\Repository\DepartmentWatch $watchRepo */
			$watchRepo = $this->repository('MJ\SupportTicket:DepartmentWatch');
			$watchRepo->setWatchState($department, $user, 'message', true, true);
		}

		/** @var \XF\Service\UpdatePermissions $permissionUpdater */
		$permissionUpdater = $this->service('XF:UpdatePermissions');
		$permissions = $this->filter('permissions', 'array');

		$permissionUpdater->setUser($user)->setContent('support_department', $department->department_id);
		$permissionUpdater->updatePermissions($permissions);

		return $this->redirect($this->buildLink('mjst-support/departments/members', $department));
	}

	public function actionMemberRemove(ParameterBag $params)
	{
		$department = $this->assertDepartmentExists($params->department_id);

		$userId = $this->filter('user_id', 'uint');

		$user = $this->em()->find('XF:User', $userId);
		if(!$user){
			return $this->error(\XF::phrase('requested_user_not_found'));
		}
		if(!$user->mjst_department_ids || !in_array($department->department_id, $user->mjst_department_ids)){
			return $this->error(\XF::phrase('mjst_this_user_not_member_of_this_department'));
		}

		if ($this->isPost())
		{
			$ids = $user->mjst_department_ids;
			if (($key = array_search($department->department_id, $ids)) !== false) {
				unset($ids[$key]);
			}
			$user->mjst_department_ids = array_unique($ids);
			$user->save();

			/** @var \XF\Service\UpdatePermissions $permissionUpdater */
			$permissionUpdater = $this->service('XF:UpdatePermissions');
			$permissions = $this->filter('permissions', 'array');

			$permissionUpdater->setUser($user)->setContent('support_department', $department->department_id);
			$permissionUpdater->updatePermissions($permissions);

			return $this->redirect($this->buildLink('mjst-support/departments/members', $department));
		}
		else
		{
			/** @var \XF\Repository\Permission $permissionRepo */
			$permissionRepo = $this->repository('XF:Permission');
			$permissionData = $permissionRepo->getContentPermissionListData('support_department');

			/** @var \XF\Repository\PermissionEntry $entryRepo */
			$entryRepo = $this->repository('XF:PermissionEntry');
			/*$permissionData['values'] = $entryRepo->getContentUserPermissionEntries(
				'support_department',
				$department->department_id,
				$user->user_id
			);*/
			$permissionData['values'] = [];

			$viewParams = [
				'department'     => $department,
				'user'           => $user,
				'permissionData' => $permissionData
			];
			return $this->view('MJ\SupportTicket:Department\Delete', 'mjst_department_member_remove', $viewParams);
		}
	}

	protected function departmentAddEdit(\MJ\SupportTicket\Entity\Department $department)
	{
		/** @var \XMJ\SupportTicketF\Repository\TicketPrefix $prefixRepo */
		$prefixRepo = $this->repository('MJ\SupportTicket:TicketPrefix');
		$availablePrefixes = $prefixRepo->findPrefixesForList()->fetch();
		$availablePrefixes = $availablePrefixes->pluckNamed('title', 'prefix_id');

		/** @var \MJ\SupportTicket\Repository\TicketField $fieldRepo */
		$fieldRepo = $this->repository('MJ\SupportTicket:TicketField');
		$availableFields = $fieldRepo->findFieldsForList()->fetch();
		$availableFields = $availableFields->pluckNamed('title', 'field_id');

		$viewParams = [
			'department' => $department,

			'availableFields' => $availableFields,
			'availablePrefixes' => $availablePrefixes,
		];
		return $this->view('MJ\SupportTicket:Department\Edit', 'mjst_department_edit', $viewParams);
	}

	public function actionAdd()
	{
		/** @var \MJ\SupportTicket\Entity\Department $department */
		$department = $this->em()->create('MJ\SupportTicket:Department');
		return $this->departmentAddEdit($department);
	}

	public function actionEdit(ParameterBag $params)
	{
		$department = $this->assertDepartmentExists($params->department_id);

		return $this->departmentAddEdit($department);
	}

	protected function departmentSaveProcess(\MJ\SupportTicket\Entity\Department $department)
	{
		$form = $this->formAction();

		$input = $this->filter([
			'title'             => 'str',
			'short_description' => 'str',
			'display_order'     => 'uint',
			'require_prefix'    => 'bool',
		]);

		$form->basicEntitySave($department, $input);

		$prefixIds = $this->filter('available_prefixes', 'array-uint');
		$form->complete(function() use ($department, $prefixIds)
		{
			/** @var \MJ\SupportTicket\Repository\DepartmentPrefix $repo */
			$repo = $this->repository('MJ\SupportTicket:DepartmentPrefix');
			$repo->updateContentAssociations($department->department_id, $prefixIds);
		});

		$fieldIds = $this->filter('available_fields', 'array-str');
		$form->complete(function() use ($department, $fieldIds)
		{
			/** @var \MJ\SupportTicket\Repository\DepartmentField $repo */
			$repo = $this->repository('MJ\SupportTicket:DepartmentField');
			$repo->updateContentAssociations($department->department_id, $fieldIds);
		});

		return $form;
	}

	public function actionSave(ParameterBag $params)
	{
		if ($params->department_id)
		{
			$department = $this->assertDepartmentExists($params->department_id);
		}
		else
		{
			/** @var \MJ\SupportTicket\Entity\Department $department */
			$department = $this->em()->create('MJ\SupportTicket:Department');
		}

		$this->departmentSaveProcess($department)->run();

		return $this->redirect($this->buildLink('mjst-support/departments') . $this->buildLinkHash($department->department_id));
	}

	public function actionDelete(ParameterBag $params)
	{
		$department = $this->assertDepartmentExists($params->department_id);
		if (!$department->preDelete())
		{
			return $this->error($department->getErrors());
		}

		if ($this->isPost())
		{
			$department->delete();

			return $this->redirect($this->buildLink('mjst-support/departments'));
		}
		else
		{
			$viewParams = [
				'department' => $department
			];
			return $this->view('MJ\SupportTicket:Department\Delete', 'mjst_department_delete', $viewParams);
		}
	}

	/**
	 * @return \MJ\SupportTicket\ControllerPlugin\DepartmentPermission
	 */
	protected function getDepartmentPermissionPlugin()
	{
		/** @var \MJ\SupportTicket\ControllerPlugin\DepartmentPermission $plugin */
		$plugin = $this->plugin('MJ\SupportTicket:DepartmentPermission');
		$plugin->setFormatters('MJ\SupportTicket:Department\Permission%s', 'mjst_department_permission_%s');
		$plugin->setRoutePrefix('mjst-support/departments/permissions');

		return $plugin;
	}

	public function actionPermissions(ParameterBag $params)
	{
		return $this->getDepartmentPermissionPlugin()->actionList($params);
	}

	public function actionPermissionsEdit(ParameterBag $params)
	{
		return $this->getDepartmentPermissionPlugin()->actionEdit($params);
	}

	public function actionPermissionsSave(ParameterBag $params)
	{
		return $this->getDepartmentPermissionPlugin()->actionSave($params);
	}

	/**
	 * @param string $id
	 * @param array|string|null $with
	 * @param null|string $phraseKey
	 *
	 * @return \MJ\SupportTicket\Entity\Department
	 */
	protected function assertDepartmentExists($id, $with = null, $phraseKey = null)
	{
		return $this->assertRecordExists('MJ\SupportTicket:Department', $id, $with, $phraseKey ?: 'mjst_requested_department_not_found');
	}

	/**
	 * @return \MJ\SupportTicket\Repository\Department
	 */
	protected function getDepartmentRepo()
	{
		return $this->repository('MJ\SupportTicket:Department');
	}
}
