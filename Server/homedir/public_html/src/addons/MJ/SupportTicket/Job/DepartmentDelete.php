<?php

namespace MJ\SupportTicket\Job;

use XF\Job\AbstractJob;

class DepartmentDelete extends AbstractJob
{
	protected $defaultData = [
		'department_id' => null,
		'count' => 0,
		'total' => null
	];

	public function run($maxRunTime)
	{
		$s = microtime(true);

		if (!$this->data['department_id'])
		{
			throw new \InvalidArgumentException('Cannot delete tickets without a department_id.');
		}

		$ticketFinder = $this->app->finder('MJ\SupportTicket:Ticket')
			->where('department_id', $this->data['department_id']);

		if ($this->data['total'] === null)
		{
			$this->data['total'] = $ticketFinder->total();
			if (!$this->data['total'])
			{
				return $this->complete();
			}
		}

		$ticketIds = $ticketFinder->pluckFrom('ticket_id')->fetch(1000);
		if (!$ticketIds)
		{
			return $this->complete();
		}

		$continue = count($ticketIds) < 1000 ? false : true;

		foreach ($ticketIds as $ticketId)
		{
			$this->data['count']++;

			$ticket = $this->app->find('MJ\SupportTicket:Ticket', $ticketId);
			if (!$ticket)
			{
				continue;
			}
			$ticket->delete(false);

			if ($maxRunTime && microtime(true) - $s > $maxRunTime)
			{
				$continue = true;
				break;
			}
		}

		if ($continue)
		{
			return $this->resume();
		}
		else
		{
			return $this->complete();
		}
	}

	public function getStatusMessage()
	{
		$actionPhrase = \XF::phrase('deleting');
		$typePhrase = \XF::phrase('mjst_support_tickets');
		return sprintf('%s... %s (%s/%s)', $actionPhrase, $typePhrase,
			\XF::language()->numberFormat($this->data['count']), \XF::language()->numberFormat($this->data['total'])
		);
	}

	public function canCancel()
	{
		return true;
	}

	public function canTriggerByChoice()
	{
		return false;
	}
}