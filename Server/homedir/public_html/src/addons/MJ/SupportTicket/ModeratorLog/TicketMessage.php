<?php

namespace MJ\SupportTicket\ModeratorLog;

use XF\Entity\ModeratorLog;
use XF\Mvc\Entity\Entity;

class TicketMessage extends \XF\ModeratorLog\AbstractHandler
{
	public function isLoggable(Entity $content, $action, \XF\Entity\User $actor)
	{
		switch ($action)
		{
			case 'edit':
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
			case 'message':
				return 'edit';

			case 'message_state':
				if ($newValue == 'visible' && $oldValue == 'moderated')
				{
					return 'approve';
				}
				else if ($newValue == 'visible' && $oldValue == 'deleted')
				{
					return 'undelete';
				}
				else if ($newValue == 'deleted')
				{
					$reason = $content->DeletionLog ? $content->DeletionLog->delete_reason : '';
					return ['delete_soft', ['reason' => $reason]];
				}
				else if ($newValue == 'moderated')
				{
					return 'unapprove';
				}
				break;
		}

		return false;
	}

	protected function setupLogEntityContent(ModeratorLog $log, Entity $content)
	{
		/** @var \MJ\SupportTicket\Entity\TicketMessage $content */
		$log->content_user_id = $content->user_id;
		$log->content_username = $content->username;
		$log->content_title = $content->Ticket->title;
		$log->content_url = \XF::app()->router('public')->buildLink('nopath:support-tickets/messages', $content);
		$log->discussion_content_type = 'support_ticket';
		$log->discussion_content_id = $content->support_ticket_id;
	}

	public function getContentTitle(ModeratorLog $log)
	{
		return \XF::phrase('mjst_message_in_ticket_x', [
			'title' => \XF::app()->stringFormatter()->censorText($log->content_title_)
		]);
	}
}
