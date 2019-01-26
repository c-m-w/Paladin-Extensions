<?php

namespace MJ\SupportTicket\ControllerPlugin;

use XF\ControllerPlugin\AbstractPlugin;

class Overview extends AbstractPlugin
{
	public function getDepartmentListData(\MJ\SupportTicket\Entity\Department $department = null)
	{
		$departmentRepo = $this->getDepartmentRepo();
		$departments = $departmentRepo->getViewableDepartments();

		return [
			'departments' => $departments,
		];
	}

	public function getCoreListData(array $sourceDepartmentIds, $page = 0, \MJ\SupportTicket\Entity\Department $department = null)
	{
		$ticketRepo = $this->getTicketRepo();

		$allowOwnPending = is_callable([$this->controller, 'hasContentPendingApproval'])
			? $this->controller->hasContentPendingApproval()
			: true;

		$ticketFinder = $ticketRepo->findTicketsForOverviewList();

		$visitorId = \XF::visitor()->user_id;

		if($department){
			$ticketFinder->where('department_id', $department->department_id);
			if(!$sourceDepartmentIds){
				$ticketFinder->where('user_id', $visitorId);
			}
		}else{
			if($sourceDepartmentIds){
				$ticketFinder->whereOr(
					['user_id', '=', $visitorId],
					['department_id', $sourceDepartmentIds]
				);
			}else{
				$ticketFinder->where('user_id', $visitorId);
			}
		}

		$filters = $this->getTicketFilterInput();
		$this->applyTicketFilters($ticketFinder, $filters);

		// TODO: if no filters and can't view deleted/moderated, can total from department info
		$totalTickets = $ticketFinder->total();
		$page = $this->filterPage($page);
		$perPage = $this->options()->mjstTicketsPerPage;

		$ticketFinder->limitByPage($page, $perPage);
		$tickets = $ticketFinder->fetch()->filterViewable();
		if (!empty($filters['owner_id']))
		{
			$ownerFilter = $this->em()->find('XF:User', $filters['owner_id']);
		}
		else
		{
			$ownerFilter = null;
		}
		if (!empty($filters['assigned_id']))
		{
			$assignedFilter = $this->em()->find('XF:User', $filters['assigned_id']);
		}
		else
		{
			$assignedFilter = null;
		}

		$canInlineMod = false;
		foreach ($tickets as $ticket)
		{
			/** @var \MJ\SupportTicket\Entity\Ticket $ticket */
			if ($ticket->canUseInlineModeration())
			{
				$canInlineMod = true;
				break;
			}
		}
		return [
			'tickets'        => $tickets,
			'filters'        => $filters,
			'ownerFilter'    => $ownerFilter,
			'assignedFilter' => $assignedFilter,
			'canInlineMod'   => $canInlineMod,

			'total'          => $totalTickets,
			'page'           => $page,
			'perPage'        => $perPage,
		];
	}

	public function applyTicketFilters(\MJ\SupportTicket\Finder\Ticket $ticketFinder, array $filters)
	{
		if (!empty($filters['prefix_id']))
		{
			$ticketFinder->where('prefix_id', intval($filters['prefix_id']));
		}
		if (!empty($filters['ticket_status_id']))
		{
			$ticketFinder->where('ticket_status_id', intval($filters['ticket_status_id']));
		}

		if (!empty($filters['urgency']))
		{
			$ticketFinder->where('urgency', intval($filters['urgency']));
		}

		if (!empty($filters['owner_id']))
		{
			$ticketFinder->where('user_id', intval($filters['owner_id']));
		}

		if (!empty($filters['assigned_id']))
		{
			$ticketFinder->where('assigned_user_id', intval($filters['assigned_id']));
		}

		if (!empty($filters['ticket_id']))
		{
			$ticketId = $filters['ticket_id'];
			$ticketId = trim($ticketId, '#');
			$ticketFinder->where('ticket_id', $ticketId);
		}

		$sorts = $this->getAvailableTicketSorts();

		if (!empty($filters['order']) && isset($sorts[$filters['order']]))
		{
			$ticketFinder->order($sorts[$filters['order']], $filters['direction']);
		}
		// else the default order has already been applied
	}

	public function getTicketFilterInput()
	{
		$filters = [];

		$input = $this->filter([
			'prefix_id'        => 'uint',
			'ticket_status_id' => 'uint',
			'type'             => 'str',
			'owner'            => 'str',
			'owner_id'         => 'uint',
			'assigned'         => 'str',
			'assigned_id'      => 'uint',
			'order'            => 'str',
			'direction'        => 'str',
			'ticket_id'        => 'str',
			'urgency'          => 'uint'
		]);

		if ($input['prefix_id'])
		{
			$filters['prefix_id'] = $input['prefix_id'];
		}

		if ($input['ticket_id'])
		{
			$filters['ticket_id'] = $input['ticket_id'];
		}

		if ($input['ticket_status_id'])
		{
			$filters['ticket_status_id'] = $input['ticket_status_id'];
		}

		if ($input['owner_id'])
		{
			$filters['owner_id'] = $input['owner_id'];
		}
		else if ($input['owner'])
		{
			$user = $this->em()->findOne('XF:User', ['username' => $input['owner']]);
			if ($user)
			{
				$filters['owner_id'] = $user->user_id;
			}
		}

		if ($input['assigned_id'])
		{
			$filters['assigned_id'] = $input['assigned_id'];
		}
		else if ($input['assigned'])
		{
			$user = $this->em()->findOne('XF:User', ['username' => $input['assigned']]);
			if ($user)
			{
				$filters['assigned_id'] = $user->user_id;
			}
		}
		if ($input['urgency'])
		{
			$filters['urgency'] = $input['urgency'];
		}

		$sorts = $this->getAvailableTicketSorts();

		if ($input['order'] && isset($sorts[$input['order']]))
		{
			if (!in_array($input['direction'], ['asc', 'desc']))
			{
				$input['direction'] = 'desc';
			}
			$defaultSort = $this->options()->mjstDefaultSortOrder;
			$defaultOrder = !empty($defaultSort['order']) ? $defaultSort['order'] : 'last_update';
			$defaultDir = !empty($defaultSort['direction']) ? $defaultSort['direction'] : 'desc';

			if ($input['order'] != $defaultOrder || $input['direction'] != $defaultDir)
			{
				$filters['order'] = $input['order'];
				$filters['direction'] = $input['direction'];
			}
		}

		return $filters;
	}

	public function getAvailableTicketSorts()
	{
		// maps [name of sort] => field in/relative to Ticket entity
		return [
			'last_update'       => 'last_update',
			'open_date'         => 'open_date',
			'last_message_date' => 'last_message_date',
			'title'             => 'title',
			'reply_count'       => 'reply_count',
		];
	}

	public function actionFilters(\MJ\SupportTicket\Entity\Department $department = null)
	{
		$filters = $this->getTicketFilterInput();

		if ($this->filter('apply', 'bool'))
		{
			return $this->redirect($this->buildLink(
				$department ? 'mjst-support/departments' : 'mjst-support',
				$department,
				$filters
			));
		}

		if (!empty($filters['owner_id']))
		{
			$ownerFilter = $this->em()->find('XF:User', $filters['owner_id']);
		}
		else
		{
			$ownerFilter = null;
		}

		if (!empty($filters['assigned_id']))
		{
			$assignedFilter = $this->em()->find('XF:User', $filters['assigned_id']);
		}
		else
		{
			$assignedFilter = null;
		}

		$applicableDepartments = $this->getDepartmentRepo()->getViewableDepartments($department);
		$applicableDepartmentIds = $applicableDepartments->keys();
		if ($department)
		{
			$applicableDepartmentIds[] = $department->ticket_department_id;
		}

		$availablePrefixIds = $this->repository('MJ\SupportTicket:DepartmentPrefix')->getPrefixIdsInContent($applicableDepartmentIds);
		$prefixes = $this->repository('MJ\SupportTicket:TicketPrefix')->findPrefixesForList()
			->where('prefix_id', $availablePrefixIds)
			->fetch();

		$defaultSort = $this->options()->mjstDefaultSortOrder;
		$defaultOrder = !empty($defaultSort['order']) ? $defaultSort['order'] : 'last_update';
		$defaultDir = !empty($defaultSort['direction']) ? $defaultSort['direction'] : 'desc';

		if (empty($filters['order']))
		{
			$filters['order'] = $defaultOrder;
		}
		if (empty($filters['direction']))
		{
			$filters['direction'] = $defaultDir;
		}

		$viewParams = [
			'department'      => $department,
			'prefixesGrouped' => $prefixes->groupBy('prefix_group_id'),
			'filters'         => $filters,
			'ownerFilter'     => $ownerFilter,
			'assignedFilter'  => $assignedFilter
		];
		return $this->view('MJ\SupportTicket:Filters', 'mjst_filters', $viewParams);
	}

	public function actionFeatured(\MJ\SupportTicket\Entity\Department $department = null)
	{
		$viewableDepartmentIds = $this->getDepartmentRepo()->getViewableDepartmentIds($department);

		$finder = $this->getTicketRepo()->findFeaturedTickets($viewableDepartmentIds);
		$finder->order('Featured.feature_date', 'desc');

		$tickets = $finder->fetch()->filterViewable();

		$canInlineMod = false;
		foreach ($tickets as $ticket)
		{
			/** @var \MJ\SupportTicket\Entity\Ticket $ticket */
			if ($ticket->canUseInlineModeration())
			{
				$canInlineMod = true;
				break;
			}
		}

		$viewParams = [
			'department' => $department,
			'tickets' => $tickets,
			'canInlineMod' => $canInlineMod
		];
		return $this->view('MJ\SupportTicket:Featured', 'mjst_featured', $viewParams);
	}

	/**
	 * @return \MJ\SupportTicket\Repository\Ticket
	 */
	protected function getTicketRepo()
	{
		return $this->repository('MJ\SupportTicket:Ticket');
	}

	/**
	 * @return \MJ\SupportTicket\Repository\Department
	 */
	protected function getDepartmentRepo()
	{
		return $this->repository('MJ\SupportTicket:Department');
	}
}
