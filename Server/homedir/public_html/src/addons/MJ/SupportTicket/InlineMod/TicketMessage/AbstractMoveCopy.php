<?php

namespace MJ\SupportTicket\InlineMod\TicketMessage;

use XF\Http\Request;
use XF\InlineMod\AbstractAction;
use XF\Mvc\Entity\AbstractCollection;
use XF\Mvc\Entity\Entity;

abstract class AbstractMoveCopy extends AbstractAction
{
	protected $targetDepartment;
	protected $targetNodeId;

	protected $targetTicket;

	public function getTitle()
	{
		throw new \LogicException("The title phrase must be overridden.");
	}

	protected function canApplyInternal(AbstractCollection $entities, array $options, &$error)
	{
		$result = parent::canApplyInternal($entities, $options, $error);

		if ($result && $options['ticket_type'])
		{
			$department = null;

			switch ($options['ticket_type'])
			{
				case 'existing':
					$ticketRepo = $this->app()->repository('MJ\SupportTicket:Ticket');
					$ticket = $ticketRepo->getTicketFromUrl($options['existing_url'], null, $ticketFetchError);
					if ($ticket)
					{
						$department = $ticket->Department;
					}
					else
					{
						$error = $ticketFetchError;
						return false;
					}
					break;

				case 'new':
					$department = $this->getTargetDepartment($options['department_id']);
					break;
			}

			if ($options['check_department_viewable'] && (!$department || !$department->canView($error)))
			{
				return false;
			}
		}

		return $result;
	}

	protected function canApplyToEntity(Entity $entity, array $options, &$error = null)
	{
		throw new \LogicException("canApplyToEntity must be overridden.");
	}

	public function applyInternal(AbstractCollection $entities, array $options)
	{
		throw new \LogicException("applyInternal must be overridden.");
	}

	protected function applyToEntity(Entity $entity, array $options)
	{
		throw new \LogicException("applyToEntity should not be called on post moving or copying");
	}

	public function getBaseOptions()
	{
		return [
			'ticket_type'               => '',
			'department_id'             => 0,
			'check_department_viewable' => true,
			'prefix_id'                 => null,
			'title'                     => '',
			'existing_url'              => null,
			'alert'                     => false,
			'alert_reason'              => ''
		];
	}

	public function renderForm(AbstractCollection $entities, \XF\Mvc\Controller $controller)
	{
		throw new \LogicException("renderForm must be overridden.");
	}

	public function getFormOptions(AbstractCollection $entities, Request $request)
	{
		$options = [
			'ticket_type'   => $request->filter('ticket_type', 'str'), // existing or new
			'department_id' => $request->filter('department_id', 'uint'),
			'prefix_id'     => $request->filter('prefix_id', 'int'), // need to allow -1
			'title'         => $request->filter('title', 'str'),
			'existing_url'  => $request->filter('existing_url', 'str'),
			'alert'         => $request->filter('author_alert', 'bool'),
			'alert_reason'  => $request->filter('author_alert_reason', 'str')
		];
		if ($options['prefix_id'] < 0)
		{
			$options['prefix_id'] = null;
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
		if (!$departmentId)
		{
			return null;
		}

		$departmentId = intval($departmentId);

		if ($this->targetNodeId && $this->targetNodeId == $departmentId)
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

		$this->targetNodeId = $departmentId;
		$this->targetDepartment = $department;

		return $this->targetDepartment;
	}

	protected function getTargetTicketFromOptions(array $options)
	{
		if ($options['ticket_type'] == 'existing')
		{
			$ticket = $this->app()->repository('MJ\SupportTicket:Ticket')->getTicketFromUrl($options['existing_url']);
		}
		else
		{
			$department = $this->getTargetDepartment($options['department_id']);
			if (!$department)
			{
				throw new \InvalidArgumentException("No target department available");
			}

			$ticket = $this->app()->em()->create('MJ\SupportTicket:Ticket');
			$ticket->title = $options['title'];
			$ticket->department_id = $department->department_id;
		}

		if (!$ticket)
		{
			throw new \InvalidArgumentException("No target ticket available");
		}

		return $ticket;
	}
}
