<?php

namespace MJ\SupportTicket\ModeratorLog;

use XF\Entity\ModeratorLog;
use XF\Mvc\Entity\Entity;

class Ticket extends \XF\ModeratorLog\AbstractHandler
{
	public function isLoggable(Entity $content, $action, \XF\Entity\User $actor)
	{
		switch ($action)
		{
			case 'title':
			case 'prefix_id':
			case 'custom_fields':
				if ($actor->user_id == $content->user_id)
				{
					return false;
				}
		}

		return parent::isLoggable($content, $action, $actor);
	}

	protected function getLogActionForChange(Entity $content, $field, $newValue, $oldValue)
	{
		switch ($field)
		{
			case 'custom_fields':
				return 'custom_fields_edit';

			case 'title':
				return ['title', ['old' => $oldValue]];

			case 'prefix_id':
				if ($oldValue)
				{
					$old = \XF::phrase('mjst_ticket_prefix.' . $oldValue)->render();
				}
				else
				{
					$old = '-';
				}
				return ['prefix', ['old' => $old]];

			case 'department_id':
				$department = \XF::em()->find('MJ\SupportTicket:Department', $oldValue);
				$oldDepartment = $department ? $department->title : '';
				return ['move', ['from' => $oldDepartment]];
		}

		return false;
	}

	protected function setupLogEntityContent(ModeratorLog $log, Entity $content)
	{
		/** @var \XF\Entity\Ticket $content */
		$log->content_user_id = $content->user_id;
		$log->content_username = $content->username;
		$log->content_title = $content->title;
		$log->content_url = \XF::app()->router('public')->buildLink('nopath:support-tickets', $content);
		$log->discussion_content_type = 'support_ticket';
		$log->discussion_content_id = $content->support_ticket_id;
	}

	protected function getActionPhraseParams(ModeratorLog $log)
	{
		if ($log->action == 'edit')
		{
			return ['elements' => implode(', ', array_keys($log->action_params))];
		}
		else
		{
			return parent::getActionPhraseParams($log);
		}
	}
}
