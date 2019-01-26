<?php

namespace MJ\SupportTicket\Admin\Controller;

use XF\Mvc\FormAction;
use XF\Mvc\ParameterBag;
use XF\Admin\Controller\AbstractController;

class TicketStatus extends AbstractController
{
	protected function preDispatchController($action, ParameterBag $params)
	{
		$this->assertAdminPermission('mjstTickets');
	}

	public function actionIndex()
	{
		$viewParams = [
			'ticketStatuses' => $this->getTicketStatusRepo()->findTicketStatusForList()->fetch()
		];
		return $this->view('MJ\SupportTicket:TicketStatus\Listing', 'mjst_ticket_status_list', $viewParams);
	}

	protected function ticketStatusAddEdit(\MJ\SupportTicket\Entity\TicketStatus $ticketStatus)
	{
		$viewParams = [
			'ticketStatus' => $ticketStatus,
		];
		return $this->view('MJ\SupportTicket:TicketStatus\Edit', 'mjst_ticket_status_edit', $viewParams);
	}

	public function actionAdd()
	{
		/** @var \MJ\SupportTicket\Entity\TicketStatus $ticketStatus */
		$ticketStatus = $this->em()->create('MJ\SupportTicket:TicketStatus');
		return $this->ticketStatusAddEdit($ticketStatus);
	}

	public function actionEdit(ParameterBag $params)
	{
		$ticketStatus = $this->assertTicketStatusExists($params->ticket_status_id);

		return $this->ticketStatusAddEdit($ticketStatus);
	}

	protected function ticketStatusSaveProcess(\MJ\SupportTicket\Entity\TicketStatus $ticketStatus)
	{
		$form = $this->formAction();

		$input = $this->filter([
			'status_color'        => 'str',
			'group_active'        => 'bool',
			'group_waiting_reply' => 'bool',
		]);

		$form->basicEntitySave($ticketStatus, $input);

		$phraseInput = $this->filter([
			'title' => 'str'
		]);
		$form->validate(function(FormAction $form) use ($phraseInput)
		{
			if ($phraseInput['title'] === '')
			{
				$form->logError(\XF::phrase('please_enter_valid_title'), 'title');
			}
		});
		$form->apply(function() use ($phraseInput, $ticketStatus)
		{
			$title = $ticketStatus->getMasterPhrase();
			$title->phrase_text = $phraseInput['title'];
			$title->save();
		});

		return $form;
	}

	public function actionSave(ParameterBag $params)
	{
		if ($params->ticket_status_id)
		{
			$ticketStatus = $this->assertTicketStatusExists($params->ticket_status_id);
		}
		else
		{
			/** @var \MJ\SupportTicket\Entity\TicketStatus $ticketStatus */
			$ticketStatus = $this->em()->create('MJ\SupportTicket:TicketStatus');
		}

		$this->ticketStatusSaveProcess($ticketStatus)->run();

		return $this->redirect($this->buildLink('mjst-support/statuses') . $this->buildLinkHash($ticketStatus->ticket_status_id));
	}

	public function actionDelete(ParameterBag $params)
	{
		$ticketStatus = $this->assertTicketStatusExists($params->ticket_status_id);
		if (!$ticketStatus->preDelete())
		{
			return $this->error($ticketStatus->getErrors());
		}

		if ($this->isPost())
		{
			$ticketStatus->delete();

			return $this->redirect($this->buildLink('mjst-support/statuses'));
		}
		else
		{
			$viewParams = [
				'ticketStatus' => $ticketStatus
			];
			return $this->view('MJ\SupportTicket:TicketStatus\Delete', 'mjst_ticket_status_delete', $viewParams);
		}
	}

	/**
	 * @param string $id
	 * @param array|string|null $with
	 * @param null|string $phraseKey
	 *
	 * @return \MJ\SupportTicket\Entity\TicketStatus
	 */
	protected function assertTicketStatusExists($id, $with = null, $phraseKey = null)
	{
		return $this->assertRecordExists('MJ\SupportTicket:TicketStatus', $id, $with, $phraseKey ?: 'mjst_requested_ticket_status_not_found');
	}

	/**
	 * @return \MJ\SupportTicket\Repository\TicketStatus
	 */
	protected function getTicketStatusRepo()
	{
		return $this->repository('MJ\SupportTicket:TicketStatus');
	}
}
