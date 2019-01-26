<?php

namespace MJ\SupportTicket\InlineMod\Ticket;

use XF\Http\Request;
use XF\InlineMod\AbstractAction;
use XF\Mvc\Entity\AbstractCollection;
use XF\Mvc\Entity\Entity;

class ApplyPrefix extends AbstractAction
{
	public function getTitle()
	{
		return \XF::phrase('apply_prefix...');
	}

	protected function canApplyToEntity(Entity $entity, array $options, &$error = null)
	{
		/** @var \MJ\SupportTicket\Entity\Ticket $entity */
		return $entity->canEdit($error);
	}

	protected function applyToEntity(Entity $entity, array $options)
	{
		/** @var \MJ\SupportTicket\Entity\Ticket $entity */
		if (!$entity->Department->isPrefixValid($options['prefix_id']))
		{
			return;
		}

		/** @var \XF\Service\Ticket\Editor $editor */
		$editor = $this->app()->service('MJ\SupportTicket:Ticket\Editor', $entity);
		$editor->setPerformValidations(false);
		$editor->setPrefix($options['prefix_id']);
		if ($editor->validate($errors))
		{
			$editor->save();
		}
	}

	public function getBaseOptions()
	{
		return [
			'prefix_id' => null
		];
	}

	public function renderForm(AbstractCollection $entities, \XF\Mvc\Controller $controller)
	{
		$departments = $entities->pluckNamed('Department', 'department_id');
		$prefixIds = [];

		foreach ($departments as $department)
		{
			$prefixIds = array_merge($prefixIds, array_keys($department->prefix_cache));
		}

		$prefixes = $this->app()->finder('MJ\SupportTicket:TicketPrefix')
			->where('prefix_id', array_unique($prefixIds))
			->order('materialized_order')
			->fetch();

		$prefixes = $prefixes->filter(function(\MJ\SupportTicket\Entity\TicketPrefix $prefix)
		{
			return $prefix->isUsableByUser();
		});

		if (!$prefixes->count())
		{
			return $controller->error(\XF::phrase('mjst_no_ticket_prefixes_available_for_selected_departments'));
		}

		$selectedPrefix = 0;
		$prefixCounts = [0 => 0];
		foreach ($entities as $ticket)
		{
			$ticketPrefixId = $ticket->prefix_id;

			if (!isset($prefixCounts[$ticketPrefixId]))
			{
				$prefixCounts[$ticketPrefixId] = 1;
			}
			else
			{
				$prefixCounts[$ticketPrefixId]++;
			}

			if ($prefixCounts[$ticketPrefixId] > $prefixCounts[$selectedPrefix])
			{
				$selectedPrefix = $ticketPrefixId;
			}
		}

		$viewParams = [
			'tickets' => $entities,
			'prefixes' => $prefixes->groupBy('prefix_group_id'),
			'departmentCount' => count($departments->keys()),
			'selectedPrefix' => $selectedPrefix,
			'total' => count($entities)
		];
		return $controller->view('XF:Public:InlineMod\Ticket\ApplyPrefix', 'mjst_inline_mod_ticket_apply_prefix', $viewParams);
	}

	public function getFormOptions(AbstractCollection $entities, Request $request)
	{
		return [
			'prefix_id' => $request->filter('prefix_id', 'uint')
		];
	}
}
