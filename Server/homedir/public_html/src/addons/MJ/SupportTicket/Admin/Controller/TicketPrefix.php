<?php

namespace MJ\SupportTicket\Admin\Controller;

use XF\Admin\Controller\AbstractPrefix;
use XF\Mvc\Entity\ArrayCollection;
use XF\Mvc\ParameterBag;
use XF\Mvc\FormAction;

class TicketPrefix extends AbstractPrefix
{
	protected function preDispatchController($action, ParameterBag $params)
	{
		$this->assertAdminPermission('mjstTickets');
	}

	protected function getClassIdentifier()
	{
		return 'MJ\SupportTicket:TicketPrefix';
	}

	protected function getLinkPrefix()
	{
		return 'mjst-support/prefixes';
	}

	protected function getTemplatePrefix()
	{
		return 'mjst_ticket_prefix';
	}

	protected function getDepartmentParams(\MJ\SupportTicket\Entity\TicketPrefix $prefix)
	{
		/** @var \MJ\SupportTicket\Repository\Department $departmentRepo */
		$departmentRepo = \XF::repository('MJ\SupportTicket:Department');

		return [
			'departments' => $departmentRepo->findDepartmentList()->fetch(),
		];
	}

	protected function prefixAddEditResponse(\XF\Entity\AbstractPrefix $prefix)
	{
		$reply = parent::prefixAddEditResponse($prefix);

		if ($reply instanceof \XF\Mvc\Reply\View)
		{
			$reply->setParams($this->getDepartmentParams($prefix));
		}

		return $reply;
	}

	protected function quickSetAdditionalData(FormAction $form, ArrayCollection $prefixes)
	{
		$input = $this->filter([
			'apply_department_ids' => 'bool',
			'department_ids' => 'array-uint'
		]);

		if ($input['apply_department_ids'])
		{
			$form->complete(function() use($prefixes, $input)
			{
				$mapRepo = $this->getDepartmentPrefixRepo();

				foreach ($prefixes as $prefix)
				{
					$mapRepo->updatePrefixAssociations($prefix, $input['department_ids']);
				}
			});
		}

		return $form;
	}

	public function actionQuickSet()
	{
		$reply = parent::actionQuickSet();

		if ($reply instanceof \XF\Mvc\Reply\View)
		{
			if ($reply->getTemplateName() == $this->getTemplatePrefix() . '_quickset_editor')
			{
				$reply->setParams($this->getDepartmentParams($reply->getParam('prefix')));
			}
		}

		return $reply;
	}

	protected function saveAdditionalData(FormAction $form, \XF\Entity\AbstractPrefix $prefix)
	{
		$departmentIds = $this->filter('department_ids', 'array-uint');

		$form->complete(function() use($prefix, $departmentIds)
		{
			$this->getDepartmentPrefixRepo()->updatePrefixAssociations($prefix, $departmentIds);
		});

		return $form;
	}

	/**
	 * @return \MJ\SupportTicket\Repository\DepartmentPrefix
	 */
	protected function getDepartmentPrefixRepo()
	{
		return $this->repository('MJ\SupportTicket:DepartmentPrefix');
	}
}
