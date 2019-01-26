<?php

namespace MJ\SupportTicket\Admin\Controller;

use XF\Admin\Controller\AbstractField;
use XF\Mvc\FormAction;
use XF\Mvc\ParameterBag;

class TicketField extends AbstractField
{
	protected function preDispatchController($action, ParameterBag $params)
	{
		$this->assertAdminPermission('mjstTickets');
	}

	protected function getClassIdentifier()
	{
		return 'MJ\SupportTicket:TicketField';
	}

	protected function getLinkPrefix()
	{
		return 'mjst-support/fields';
	}

	protected function getTemplatePrefix()
	{
		return 'mjst_ticket_field';
	}

	protected function fieldAddEditResponse(\XF\Entity\AbstractField $field)
	{
		$reply = parent::fieldAddEditResponse($field);

		if ($reply instanceof \XF\Mvc\Reply\View)
		{
			/** @var \MJ\SupportTicket\Repository\Department $departmentRepo */
			$departmentRepo = $this->repository('MJ\SupportTicket:Department');

			/** @var \XF\Mvc\Entity\ArrayCollection $fieldAssociations */
			$fieldAssociations = $field->getRelationOrDefault('DepartmentFields', false);

			$reply->setParams([
				'departments' => $departmentRepo->findDepartmentList()->fetch(),
				'departmentIds' => $fieldAssociations->pluckNamed('department_id')
			]);
		}

		return $reply;
	}

	protected function saveAdditionalData(FormAction $form, \XF\Entity\AbstractField $field)
	{
		$departmentIds = $this->filter('department_ids', 'array-uint');

		/** @var \MJ\SupportTicket\Entity\TicketField $field */
		$form->complete(function() use ($field, $departmentIds)
		{
			/** @var \MJ\SupportTicket\Repository\DepartmentField $repo */
			$repo = $this->repository('MJ\SupportTicket:DepartmentField');
			$repo->updateFieldAssociations($field, $departmentIds);
		});

		return $form;
	}
}
