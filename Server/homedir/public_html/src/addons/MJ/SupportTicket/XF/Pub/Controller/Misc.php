<?php

namespace MJ\SupportTicket\XF\Pub\Controller;

class Misc extends XFCP_Misc
{
	protected function setupCreateTicket()
	{
		$options = $this->options();
		$contactOptions = $options->mjstContactAsTicket;
		if(!empty($contactOptions['enabled'])){
			$departmentId = !empty($contactOptions['department_id']) ? $contactOptions['department_id'] : 0;
			if(!$departmentId){
				$departmentId = $options->mjstDefautDepartment;
			}

			$visitor = \XF::visitor();
			$extraWith[] = 'Permissions|' . $visitor->permission_combination_id;
			/** @var \MJ\SupportTicket\Entity\Department $department */
			$department = $this->em()->find('MJ\SupportTicket:Department', $departmentId, $extraWith);
			if(!$department->canOpenTicket()){
				return false;
			}
			/** @var \MJ\SupportTicket\Service\Ticket\Creator $creator */
			$creator = $this->service('MJ\SupportTicket:Ticket\Creator', $department);

			$input = $this->filter([
				'username' => 'str',
				'email'    => 'str',
				'subject'  => 'str',
				'message'  => 'str'
			]);

			$creator->setContent($input['subject'], $input['message']);
			$ticket = $creator->getTicket();

			if ($visitor->user_id)
			{
				$creator->setOwner($visitor->user_id, $visitor->username);
				if (!$visitor->email)
				{
					if (!$creator->setEmail($input['email'], $error))
					{
						throw $this->exception($this->error($error));
					}
				}else{
					$creator->setEmail($visitor->email);
				}
			}
			else
			{
				if (!$creator->setEmail($input['email'], $error))
				{
					throw $this->exception($this->error($error));
				}
				$creator->setOwner(0, $input['username']);
			}
			$creator->setUrgency($options->mjstDefautPriority);

			if (!$creator->validate($errors))
			{
				throw $this->exception($this->error($errors));
			}

			/** @var \MJ\SupportTicket\Entity\Ticket $ticket */
			$ticket = $creator->save();
			if ($ticket->canWatch())
			{
				// use user preferences
				$this->repository('MJ\SupportTicket:TicketWatch')->autoWatchTicket($ticket, $visitor, true);
				if($ticket->creator_user_id != $ticket->user_id && $ticket->user_id){
					$this->repository('MJ\SupportTicket:TicketWatch')->autoWatchTicket($ticket, $ticket->User, true);
				}
			}
			if ($visitor->user_id)
			{
				$this->repository('MJ\SupportTicket:Ticket')->markTicketReadByVisitor($ticket, $ticket->open_date);
			}
			$creator->sendNotifications();
			return $ticket;
		}
		return false;
	}

	public function actionContact()
	{
		$options = $this->options();

		if ($options->contactUrl['type'] == 'custom')
		{
			return $this->redirect($options->contactUrl['custom']);
		}
		else if (!$options->contactUrl['type'])
		{
			return $this->redirect($this->buildLink('index'));
		}

		if (!\XF::visitor()->canUseContactForm())
		{
			return $this->noPermission();
		}
		if ($this->isPost())
		{
			$contactOptions = $options->mjstContactAsTicket;
			if(!empty($contactOptions['enabled'])){
				$ticket = $this->setupCreateTicket();
				if($ticket && !empty($contactOptions['disable_email'])){
					return $this->redirect($this->buildLink('support-tickets/created', $ticket));
				}
			}
		}

		$contact = parent::actionContact();
		if(!empty($ticket)){
			return $this->redirect($this->buildLink('support-tickets', $ticket));
		}else{
			return $contact;
		}
	}
}
