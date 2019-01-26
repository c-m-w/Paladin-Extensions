<?php

namespace MJ\SupportTicket\Admin\Controller;

use XF\Mvc\FormAction;
use XF\Mvc\ParameterBag;
use XF\Admin\Controller\AbstractController;

class Ticket extends AbstractController
{
	protected function preDispatchController($action, ParameterBag $params)
	{
		$this->assertAdminPermission('mjstTickets');
	}

	public function actionIndex()
	{
		$ticketFinder = $this->finder('MJ\SupportTicket:Ticket');

		$ticketCount = $ticketFinder->total();

		list($activeIds, $waitReplyIds) = $this->repository('MJ\SupportTicket:TicketStatus')->getStatusTypesCache();
		$ticketFinder->where('ticket_status_id', $activeIds);

		$activeTickets = $ticketFinder->total();

		$ticketFinder->where('ticket_status_id', $waitReplyIds);

		$waitTickets = $ticketFinder->total();

		$departmentCount = $this->finder('MJ\SupportTicket:Department')->total();
		$kbCount = $this->finder('MJ\SupportTicket:KnowledgeBase')->total();
		$preReplyCount = $this->finder('MJ\SupportTicket:PreReply')->total();

		$viewParams = [
			'ticketCount'     => $ticketCount,
			'activeTickets'   => $activeTickets,
			'waitTickets'     => $waitTickets,
			'departmentCount' => $departmentCount,
			'kbCount'         => $kbCount,
			'preReplyCount'   => $preReplyCount,
		];
		return $this->view('MJ\SupportTicket:Ticket\Stats', 'mjst_stats', $viewParams);
	}

	/**
	 * @return \XF\Repository\Ticket
	 */
	protected function getTicketRepo()
	{
		return $this->repository('MJ\SupportTicket:Ticket');
	}
}
