<?php

namespace MJ\SupportTicket\Admin\Controller;

use XF\Mvc\FormAction;
use XF\Mvc\ParameterBag;
use XF\Admin\Controller\AbstractController;

class TicketEscalation extends AbstractController
{
	protected function preDispatchController($action, ParameterBag $params)
	{
		$this->assertAdminPermission('mjstTickets');
	}

	public function actionIndex()
	{
		$viewParams = [
			'ticketEscalations' => $this->getTicketEscalationRepo()->findTicketEscalationForList()->fetch()
		];
		return $this->view('MJ\SupportTicket:TicketEscalation\Listing', 'mjst_ticket_escalation_list', $viewParams);
	}

	protected function ticketEscalationAddEdit(\MJ\SupportTicket\Entity\TicketEscalation $ticketEscalation)
	{
		/** @var \MJ\SupportTicket\Repository\Department $departmentRepo */
		$departmentRepo = \XF::repository('MJ\SupportTicket:Department');
		$statusRepo = \XF::repository('MJ\SupportTicket:TicketStatus');

		$viewParams = [
			'ticketEscalation' => $ticketEscalation,
			'departments'      => $departmentRepo->findDepartmentList()->fetch(),
			'ticketStatuses'   => $statusRepo->findTicketStatusForList()->fetch()
		];
		return $this->view('MJ\SupportTicket:TicketEscalation\Edit', 'mjst_ticket_escalation_edit', $viewParams);
	}

	public function actionAdd()
	{
		/** @var \MJ\SupportTicket\Entity\TicketEscalation $ticketEscalation */
		$ticketEscalation = $this->em()->create('MJ\SupportTicket:TicketEscalation');
		return $this->ticketEscalationAddEdit($ticketEscalation);
	}

	public function actionEdit(ParameterBag $params)
	{
		$ticketEscalation = $this->assertTicketEscalationExists($params->ticket_escalation_id);

		return $this->ticketEscalationAddEdit($ticketEscalation);
	}

	protected function ticketEscalationSaveProcess(\MJ\SupportTicket\Entity\TicketEscalation $ticketEscalation)
	{
		$form = $this->formAction();

		$input = $this->filter([
			'title'                => 'str',
			'time_elapsed'         => 'uint',
			'new_department_id'    => 'uint',
			'new_priority'         => 'uint',
			'new_ticket_status_id' => 'uint',
			'department_ids'       => 'array-uint',
			'ticket_status_ids'    => 'array-uint',
			'priorities'           => 'array-uint',
		]);

		$username = $this->filter('username', 'str');
		$userId = 0;
		if ($username)
		{
			$user = $this->finder('XF:User')->where('username', $username)->fetchOne();
			if ($user)
			{
				$userId = $user->user_id;
			}
		}
		$replyMessage = $this->plugin('XF:Editor')->fromInput('reply_message');

		if($replyMessage && $userId){
			$input['reply_user_id'] = $userId;
			$input['reply_message'] = $replyMessage;
		}else{
			$input['reply_user_id'] = 0;
			$input['reply_message'] = '';
		}

		$form->basicEntitySave($ticketEscalation, $input);

		return $form;
	}

	public function actionSave(ParameterBag $params)
	{
		if ($params->ticket_escalation_id)
		{
			$ticketEscalation = $this->assertTicketEscalationExists($params->ticket_escalation_id);
		}
		else
		{
			/** @var \MJ\SupportTicket\Entity\TicketEscalation $ticketEscalation */
			$ticketEscalation = $this->em()->create('MJ\SupportTicket:TicketEscalation');
		}

		$this->ticketEscalationSaveProcess($ticketEscalation)->run();

		return $this->redirect(
			$this->buildLink('mjst-support/escalations') . $this->buildLinkHash($ticketEscalation->ticket_escalation_id)
		);
	}

	public function actionDelete(ParameterBag $params)
	{
		$ticketEscalation = $this->assertTicketEscalationExists($params->ticket_escalation_id);
		if (!$ticketEscalation->preDelete())
		{
			return $this->error($ticketEscalation->getErrors());
		}

		if ($this->isPost())
		{
			$ticketEscalation->delete();

			return $this->redirect($this->buildLink('mjst-support/escalations'));
		}
		else
		{
			$viewParams = [
				'ticketEscalation' => $ticketEscalation
			];
			return $this->view('MJ\SupportTicket:TicketEscalation\Delete', 'mjst_ticket_escalation_delete', $viewParams);
		}
	}

	/**
	 * @param string $id
	 * @param array|string|null $with
	 * @param null|string $phraseKey
	 *
	 * @return \MJ\SupportTicket\Entity\TicketEscalation
	 */
	protected function assertTicketEscalationExists($id, $with = null, $phraseKey = null)
	{
		return $this->assertRecordExists('MJ\SupportTicket:TicketEscalation', $id, $with, $phraseKey ?: 'mjst_requested_ticket_escalation_not_found');
	}

	/**
	 * @return \MJ\SupportTicket\Repository\TicketEscalation
	 */
	protected function getTicketEscalationRepo()
	{
		return $this->repository('MJ\SupportTicket:TicketEscalation');
	}
}
