<?php

namespace MJ\SupportTicket\InlineMod\TicketMessage;

use XF\Http\Request;
use XF\InlineMod\AbstractAction;
use XF\Mvc\Entity\AbstractCollection;
use XF\Mvc\Entity\Entity;

class Merge extends AbstractAction
{
	public function getTitle()
	{
		return \XF::phrase('mjst_merge_messages...');
	}

	protected function canApplyInternal(AbstractCollection $entities, array $options, &$error)
	{
		$result = parent::canApplyInternal($entities, $options, $error);

		if ($result)
		{
			if ($options['target_message_id'])
			{
				if (!isset($entities[$options['target_message_id']]))
				{
					return false;
				}
			}

			if ($entities->count() < 2)
			{
				return false;
			}
		}

		return $result;
	}

	protected function canApplyToEntity(Entity $entity, array $options, &$error = null)
	{
		/** @var \MJ\SupportTicket\Entity\TicketMessage $entity */
		return $entity->canMerge($error);
	}

	public function applyInternal(AbstractCollection $entities, array $options)
	{
		if (!$options['target_message_id'])
		{
			throw new \InvalidArgumentException("No target message selected");
		}

		$source = $entities->toArray();
		$target = $source[$options['target_message_id']];
		unset($source[$options['target_message_id']]);

		/** @var \MJ\SupportTicket\Service\TicketMessage\Merger $merger */
		$merger = $this->app()->service('MJ\SupportTicket:TicketMessage\Merger', $target);

		$merger->setMessage($options['message']);

		if ($options['alert'])
		{
			$merger->setSendAlert(true, $options['alert_reason']);
		}

		$merger->merge($source);
	}

	protected function applyToEntity(Entity $entity, array $options)
	{
		throw new \LogicException("applyToEntity should not be called on message merging");
	}

	public function getBaseOptions()
	{
		return [
			'target_message_id' => 0,
			'message' => '',
			'alert' => false,
			'alert_reason' => ''
		];
	}

	public function renderForm(AbstractCollection $entities, \XF\Mvc\Controller $controller)
	{
		$viewParams = [
			'messages' => $entities,
			'messageText' => trim(implode("\n\n", $entities->pluckNamed('message'))),

			'total' => count($entities),
			'first' => $entities->first()
		];
		return $controller->view('MJ\SupportTicket:Public:InlineMod\TicketMessage\Merge', 'mjst_inline_mod_message_merge', $viewParams);
	}

	public function getFormOptions(AbstractCollection $entities, Request $request)
	{
		$options = [
			'target_message_id' => $request->filter('target_message_id', 'uint'),
			'message' => $request->filter('message', 'str'),
			'alert' => $request->filter('author_alert', 'bool'),
			'alert_reason' => $request->filter('author_alert_reason', 'str')
		];

		return $options;
	}
}
