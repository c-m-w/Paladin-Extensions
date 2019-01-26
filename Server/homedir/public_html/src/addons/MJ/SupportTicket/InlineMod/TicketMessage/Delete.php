<?php

namespace MJ\SupportTicket\InlineMod\TicketMessage;

use XF\Http\Request;
use XF\InlineMod\AbstractAction;
use XF\Mvc\Entity\AbstractCollection;
use XF\Mvc\Entity\Entity;

class Delete extends AbstractAction
{
	public function getTitle()
	{
		return \XF::phrase('mjst_delete_messages...');
	}

	protected function canApplyToEntity(Entity $entity, array $options, &$error = null)
	{
		/** @var \MJ\SupportTicket\Entity\TicketMessage $entity */
		return $entity->canDelete($options['type'], $error);
	}

	protected function applyInternal(AbstractCollection $entities, array $options)
	{
		$skipped = [];

		foreach ($entities as $entity)
		{
			if (!empty($skipped[$entity->support_ticket_id]))
			{
				continue;
			}

			$this->applyToEntity($entity, $options);

			$ticket = $entity->Ticket;
			if (/*$options['type'] == 'hard' && */$entity->message_id == $ticket->first_message_id)
			{
				// all messages in this ticket have been removed, so skip them
				$skipped[$ticket->support_ticket_id] = true;
			}
		}
	}

	protected function applyToEntity(Entity $entity, array $options)
	{
		/** @var \MJ\SupportTicket\Service\TicketMessage\Deleter $deleter */
		$deleter = $this->app()->service('MJ\SupportTicket:TicketMessage\Deleter', $entity);

		if ($options['alert'])
		{
			$deleter->setSendAlert(true, $options['alert_reason']);
		}

		$deleter->delete($options['type'], $options['reason']);

		if ($deleter->wasTicketDeleted())
		{
			$this->returnUrl = $this->app()->router('public')->buildLink('support-tickets');
		}
	}

	public function getBaseOptions()
	{
		return [
			'type' => 'soft',
			'reason' => '',
			'alert' => false,
			'alert_reason' => ''
		];
	}

	public function renderForm(AbstractCollection $entities, \XF\Mvc\Controller $controller)
	{
		$firstMessageCount = 0;
		foreach ($entities as $message)
		{
			if ($message->message_id == $message->Ticket->first_message_id)
			{
				$firstMessageCount++;
			}
		}

		$viewParams = [
			'messages' => $entities,
			'firstMessageCount' => $firstMessageCount,
			'total' => count($entities),
			'canHardDelete' => $this->canApply($entities, ['type' => 'hard'])
		];
		return $controller->view('MJ\SupportTicket:Public:InlineMod\TicketMessage\Delete', 'mjst_inline_mod_message_delete', $viewParams);
	}

	public function getFormOptions(AbstractCollection $entities, Request $request)
	{
		return [
			'type' => $request->filter('hard_delete', 'bool') ? 'hard' : 'soft',
			'reason' => $request->filter('reason', 'str'),
			'alert' => $request->filter('author_alert', 'bool'),
			'alert_reason' => $request->filter('author_alert_reason', 'str')
		];
	}
}
