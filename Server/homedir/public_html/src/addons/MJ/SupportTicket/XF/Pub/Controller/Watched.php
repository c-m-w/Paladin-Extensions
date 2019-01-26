<?php

namespace MJ\SupportTicket\XF\Pub\Controller;

class Watched extends XFCP_Watched
{
	public function actionTickets()
	{
		$this->setSectionContext('mjstSupportTicket');

		$page = $this->filterPage();
		$perPage = $this->options()->mjstTicketsPerPage;

		/** @var \MJ\SupportTicket\Repository\Ticket $ticketRepo */
		$ticketRepo = $this->repository('MJ\SupportTicket:Ticket');
		$ticketFinder = $ticketRepo->findTicketsForWatchedList();

		$total = $ticketFinder->total();
		$tickets = $ticketFinder->limitByPage($page, $perPage)->fetch();

		$viewParams = [
			'page'    => $page,
			'perPage' => $perPage,
			'total'   => $total,
			'tickets' => $tickets->filterViewable()
		];
		return $this->view('MJ\SupportTicket:Watched\Tickets', 'mjst_watched_tickets_list', $viewParams);
	}

	public function actionTicketsManage()
	{
		$this->setSectionContext('mjstSupportTicket');

		if (!$state = $this->filter('state', 'str'))
		{
			return $this->redirect($this->buildLink('watched/tickets'));
		}

		if ($this->isPost())
		{
			/** @var \MJ\SupportTicket\Repository\TicketWatch $ticketWatchRepo */
			$ticketWatchRepo = $this->repository('MJ\SupportTicket:TicketWatch');

			if ($ticketWatchRepo->isValidWatchState($state))
			{
				$ticketWatchRepo->setWatchStateForAll(\XF::visitor(), $state);
			}

			return $this->redirect($this->buildLink('watched/tickets'));
		}
		else
		{
			$viewParams = [
				'state' => $state
			];
			return $this->view('MJ\SupportTicket:Watched\TicketsManage', 'mjst_watched_tickets_manage', $viewParams);
		}
	}

	public function actionTicketsUpdate()
	{
		$this->assertPostOnly();
		$this->setSectionContext('mjstSupportTicket');

		/** @var \MJ\SupportTicket\Repository\TicketWatch $ticketWatchRepo */
		$ticketWatchRepo = $this->repository('MJ\SupportTicket:TicketWatch');

		$state = $this->filter('state', 'str');

		if ($state && $ticketWatchRepo->isValidWatchState($state))
		{
			$ticketIds = $this->filter('ticket_ids', 'array-uint');
			$tickets = $this->em()->findByIds('MJ\SupportTicket:Ticket', $ticketIds);
			$visitor = \XF::visitor();

			/** @var \MJ\SupportTicket\Entity\Ticket $ticket */
			foreach ($tickets as $ticket)
			{
				$ticketWatchRepo->setWatchState($ticket, $visitor, $state);
			}
		}

		return $this->redirect($this->buildLink('watched/tickets'));
	}

	public function actionTicketDepartments()
	{
		$this->setSectionContext('mjstSupportTicket');

		$watchedFinder = $this->finder('MJ\SupportTicket:DepartmentWatch');
		$watchedDepartments = $watchedFinder->where('user_id', \XF::visitor()->user_id)
			->keyedBy('department_id')
			->fetch();

		/** @var \MJ\SupportTicket\Repository\Department $departmentRepo */
		$departmentRepo = $this->repository('MJ\SupportTicket:Department');
		$departments = $departmentRepo->getViewableDepartments();

		$viewParams = [
			'departments'        => $departments,
			'watchedDepartments' => $watchedDepartments
		];
		return $this->view('XF:Watched\Departments', 'mjst_watched_departments_list', $viewParams);
	}

	public function actionTicketDepartmentsManage()
	{
		$this->setSectionContext('mjstSupportTicket');

		if (!$state = $this->filter('state', 'str'))
		{
			return $this->redirect($this->buildLink('watched/ticket-departments'));
		}

		if ($this->isPost())
		{
			/** @var \XF\Repository\DepartmentWatch $departmentWatchRepo */
			$departmentWatchRepo = $this->repository('XF:DepartmentWatch');

			if ($departmentWatchRepo->isValidWatchState($state))
			{
				$departmentWatchRepo->setWatchStateForAll(\XF::visitor(), $state);
			}

			return $this->redirect($this->buildLink('watched/ticket-departments'));
		}
		else
		{
			$viewParams = [
				'state' => $state
			];
			return $this->view('XF:Watched\DepartmentsManage', 'mjst_watched_departments_manage', $viewParams);
		}
	}

	public function actionTicketDepartmentsUpdate()
	{
		$this->assertPostOnly();
		$this->setSectionContext('mjstSupportTicket');

		if ($action = $this->filter('action', 'str'))
		{
			$departmentIds = $this->filter('department_ids', 'array-uint');
			$visitor = \XF::visitor();

			foreach ($departmentIds as $departmentId)
			{
				$watch = $this->em()->find('MJ\SupportTicket:DepartmentWatch', [
					'department_id' => $departmentId,
					'user_id' => $visitor->user_id
				]);
				if (!$watch)
				{
					continue;
				}

				switch ($action)
				{
					case 'email':
					case 'no_email':
						$watch->send_email = ($action == 'email');
						$watch->save();
						break;

					case 'alert':
					case 'no_alert':
						$watch->send_alert = ($action == 'alert');
						$watch->save();
						break;

					case 'delete':
						$watch->delete();
						break;
				}
			}
		}

		return $this->redirect($this->buildLink('watched/ticket-departments'));
	}
}
