<?php

namespace MJ\SupportTicket\InlineMod\Ticket;

use XF\Http\Request;
use XF\InlineMod\AbstractAction;
use XF\Mvc\Entity\AbstractCollection;
use XF\Mvc\Entity\Entity;

class Move extends AbstractAction
{
	protected $targetDepartment;
	protected $targetDepartmentId;

	public function getTitle()
	{
		return \XF::phrase('mjst_move_tickets...');
	}

	protected function canApplyInternal(AbstractCollection $entities, array $options, &$error)
	{
		$result = parent::canApplyInternal($entities, $options, $error);

		if ($result)
		{
			if ($options['target_department_id'])
			{
				$department = $this->getTargetDepartment($options['target_department_id']);
				if (!$department)
				{
					return false;
				}

				if ($options['check_department_viewable'] && !$department->canView($error))
				{
					return false;
				}

				if ($options['check_all_same_department'])
				{
					$allSame = true;
					foreach ($entities as $entity)
					{
						/** @var \MJ\SupportTicket\Entity\Ticket $entity */
						if ($entity->department_id != $options['target_department_id'])
						{
							$allSame = false;
							break;
						}
					}

					if ($allSame)
					{
						$error = \XF::phraseDeferred('mjst_all_tickets_in_destination_department');
						return false;
					}
				}
			}
		}

		return $result;
	}

	protected function canApplyToEntity(Entity $entity, array $options, &$error = null)
	{
		/** @var \MJ\SupportTicket\Entity\Ticket $entity */
		return $entity->canMove($error);
	}

	protected function applyToEntity(Entity $entity, array $options)
	{
		$department = $this->getTargetDepartment($options['target_department_id']);
		if (!$department)
		{
			throw new \InvalidArgumentException("No target specified");
		}

		/** @var \MJ\SupportTicket\Service\Ticket\Mover $mover */
		$mover = $this->app()->service('MJ\SupportTicket:Ticket\Mover', $entity);

		if ($options['alert'])
		{
			$mover->setSendAlert(true, $options['alert_reason']);
		}

		if ($options['notify_watchers'])
		{
			$mover->setNotifyWatchers();
		}

		if ($options['redirect'])
		{
			$mover->setRedirect(true, $options['redirect_length']);
		}

		if ($options['prefix_id'] !== null)
		{
			$mover->setPrefix($options['prefix_id']);
		}
		$mover->move($department);

		$this->returnUrl = $this->app()->router('public')->buildLink('support-tickets/departments', $department);
	}

	public function getBaseOptions()
	{
		return [
			'target_department_id'      => 0,
			'check_department_viewable' => true,
			'check_all_same_department' => true,
			'prefix_id'                 => null,
			'redirect'                  => false,
			'redirect_length'           => 0,
			'notify_watchers'           => false,
			'alert'                     => false,
			'alert_reason'              => ''
		];
	}

	public function renderForm(AbstractCollection $entities, \XF\Mvc\Controller $controller)
	{
		/** @var \MJ\SupportTicket\Repository\Department $departmentRepo */
		$departmentRepo = $this->app()->repository('MJ\SupportTicket:Department');
		$departments = $departmentRepo->getFullDepartmentList()->filterViewable();

		$prefixes = $this->app()->finder('MJ\SupportTicket:TicketPrefix')
			->order('materialized_order')
			->fetch();

		$viewParams = [
			'tickets'     => $entities,
			'prefixes'    => $prefixes->groupBy('prefix_group_id'),
			'total'       => count($entities),
			'departments' => $departments,
			'first'       => $entities->first()
		];
		return $controller->view('MJ\SupportTicket:Public:InlineMod\Ticket\Move', 'mjst_inline_mod_ticket_move', $viewParams);
	}

	public function getFormOptions(AbstractCollection $entities, Request $request)
	{
		$options = [
			'target_department_id' => $request->filter('target_department_id', 'uint'),
			'apply_ticket_prefix'  => $request->filter('apply_ticket_prefix', 'bool'),
			'prefix_id'            => $request->filter('prefix_id', 'uint'),
			'notify_watchers'      => $request->filter('notify_watchers', 'bool'),
			'alert'                => $request->filter('starter_alert', 'bool'),
			'alert_reason'         => $request->filter('starter_alert_reason', 'str')
		];
		if (!$options['apply_ticket_prefix'])
		{
			$options['prefix_id'] = null;
		}

		$redirectType = $request->filter('redirect_type', 'str');
		if ($redirectType == 'permanent')
		{
			$options['redirect'] = true;
			$options['redirect_length'] = 0;
		}
		else if ($redirectType == 'temporary')
		{
			$options['redirect'] = true;
			$options['redirect_length'] = $request->filter('redirect_length', 'timeoffset');
		}
		else
		{
			$options['redirect'] = false;
			$options['redirect_length'] = 0;
		}

		return $options;
	}

	/**
	 * @param integer $departmentId
	 *
	 * @return null|\MJ\SupportTicket\Entity\Department
	 */
	protected function getTargetDepartment($departmentId)
	{
		$departmentId = intval($departmentId);

		if ($this->targetDepartmentId && $this->targetDepartmentId == $departmentId)
		{
			return $this->targetDepartment;
		}
		if (!$departmentId)
		{
			return null;
		}

		$department = $this->app()->em()->find('MJ\SupportTicket:Department', $departmentId);
		if (!$department)
		{
			throw new \InvalidArgumentException("Invalid target department ($departmentId)");
		}

		$this->targetDepartmentId = $departmentId;
		$this->targetDepartment = $department;

		return $this->targetDepartment;
	}
}
