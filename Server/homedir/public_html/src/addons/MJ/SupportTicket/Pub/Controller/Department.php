<?php

namespace MJ\SupportTicket\Pub\Controller;

use XF\Mvc\ParameterBag;
use XF\Pub\Controller\AbstractController;

class Department extends AbstractController
{
	protected function preDispatchController($action, ParameterBag $params)
	{
		/** @var \MJ\Shop\XF\Entity\User $visitor */
		$visitor = \XF::visitor();

		if (!$visitor->canViewSupportTickets($error))
		{
			throw $this->exception($this->noPermission($error));
		}
	}

	public function actionIndex(ParameterBag $params)
	{
		$visitor = \XF::visitor();
		if(!$visitor->user_id){
			if($visitor->canOpenTicket() && !$visitor->hasTicketDepartmentPermission($params->department_id, 'viewAnyTicket')){
				return $this->redirect($this->buildLink('support-tickets/open'));
			}
		}

		$department = $this->assertViewableDepartment($params->department_id, $this->getDepartmentViewExtraWith());

		/** @var \MJ\SupportTicket\ControllerPlugin\Overview $overviewPlugin */
		$overviewPlugin = $this->plugin('MJ\SupportTicket:Overview');

		$departmentParams = $overviewPlugin->getDepartmentListData($department);

		$viewableDepartmentIds = [];
		if($department->canViewAnyTicket()){
			$viewableDepartmentIds[] = $department->department_id;
		}

		$listParams = $overviewPlugin->getCoreListData($viewableDepartmentIds, $params->page, $department);

		$this->assertValidPage(
			$listParams['page'],
			$listParams['perPage'],
			$listParams['total'],
			'support-tickets/departments',
			$department
		);

		$this->assertCanonicalUrl($this->buildLink(
			'support-tickets/departments',
			$department,
			['page' => $listParams['page']]
		));

		$viewParams = [
			'department'      => $department,
			'pendingApproval' => $this->filter('pending_approval', 'bool'),
			'iconError'       => $this->filter('icon_error', 'bool')
		];
		$viewParams += $departmentParams + $listParams;

		return $this->view('MJ\SupportTicket:Department\View', 'mjst_department_view', $viewParams);
	}

	protected function getDepartmentViewExtraWith()
	{
		$extraWith = [];
		$userId = \XF::visitor()->user_id;
		if ($userId)
		{
			$extraWith[] = 'Watch|' . $userId;
		}

		return $extraWith;
	}

	public function actionFilters(ParameterBag $params)
	{
		$department = $this->assertViewableDepartment($params->department_id);

		/** @var \MJ\SupportTicket\ControllerPlugin\Overview $overviewPlugin */
		$overviewPlugin = $this->plugin('MJ\SupportTicket:Overview');

		return $overviewPlugin->actionFilters($department);
	}

	public function actionWatch(ParameterBag $params)
	{
		$visitor = \XF::visitor();
		if (!$visitor->user_id)
		{
			return $this->noPermission();
		}

		$department = $this->assertViewableDepartment($params->department_id);
		if (!$department->canWatch($error))
		{
			return $this->noPermission($error);
		}

		if ($this->isPost())
		{
			if ($this->filter('stop', 'bool'))
			{
				$notifyType = 'delete';
			}
			else
			{
				$notifyType = $this->filter('notify', 'str');
				if ($notifyType != 'ticket' && $notifyType != 'message')
				{
					$notifyType = '';
				}
			}

			$sendAlert = $this->filter('send_alert', 'bool');
			$sendEmail = $this->filter('send_email', 'bool');

			/** @var \MJ\SupportTicket\Repository\DepartmentWatch $watchRepo */
			$watchRepo = $this->repository('MJ\SupportTicket:DepartmentWatch');
			$watchRepo->setWatchState($department, $visitor, $notifyType, $sendAlert, $sendEmail);

			$redirect = $this->redirect($this->buildLink('departments', $department));
			$redirect->setJsonParam('switchKey', $notifyType == 'delete' ? 'watch' : 'unwatch');
			return $redirect;
		}
		else
		{
			$viewParams = [
				'department' => $department,
				'isWatched' => !empty($department->Watch[$visitor->user_id])
			];
			return $this->view('MJ\SupportTicket:Department\Watch', 'mjst_department_watch', $viewParams);
		}
	}

	public function actionPrefixes(ParameterBag $params)
	{
		$this->assertPostOnly();

		$viewParams = [];

		$departmentId = $this->filter('val', 'uint');
		if ($departmentId)
		{
			$department = $this->assertViewableDepartment($departmentId);

			$viewParams['department'] = $department;
			$viewParams['prefixes'] = $department->getUsablePrefixes();
		}

		return $this->view('MJ\SupportTicket:Department\Prefixes', 'mjst_department_prefixes', $viewParams);
	}

	public function actionCustomFields(ParameterBag $params)
	{
		$this->assertPostOnly();

		$viewParams = [];

		$departmentId = $this->filter('val', 'uint');
		if ($departmentId)
		{
			$department = $this->assertViewableDepartment($departmentId);

			$ticketId = $this->filter('tid', 'uint');
			if($ticketId){
				$ticket = $this->em()->find('MJ\SupportTicket:Ticket', $ticketId);
			}else{
				$ticket = $department->getNewTicket();
			}
			$viewParams['ticket'] = $ticket;
			$viewParams['department'] = $department;
		}
		$rowType = $this->filter('row_type', 'str');
		$viewParams['rowType'] = $rowType;
		return $this->view('MJ\SupportTicket:Department\CustomFields', 'mjst_department_custom_fields', $viewParams);
	}

	/**
	 * @param string|int $departmentId
	 * @param array $extraWith
	 *
	 * @return \MJ\SupportTicket\Entity\Department
	 *
	 * @throws \XF\Mvc\Reply\Exception
	 */
	protected function assertViewableDepartment($departmentId, array $extraWith = [])
	{
		if ($departmentId === null)
		{
			throw new \InvalidArgumentException("Department ID not passed in correctly");
		}

		$visitor = \XF::visitor();
		$extraWith[] = 'Permissions|' . $visitor->permission_combination_id;
		if ($visitor->user_id)
		{
			//$extraWith[] = 'Read|' . $visitor->user_id;
		}

		/** @var \MJ\SupportTicket\Entity\Department $department */
		$department = $this->em()->find('MJ\SupportTicket:Department', $departmentId, $extraWith);

		if (!$department)
		{
			throw $this->exception($this->notFound(\XF::phrase('mjst_requested_department_not_found')));
		}
		if (!$department->canView($error))
		{
			throw $this->exception($this->noPermission($error));
		}

		return $department;
	}
}
