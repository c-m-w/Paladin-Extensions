<?php

namespace MJ\SupportTicket\EditHistory;

use XF\Mvc\Entity\Entity;

class TicketMessage extends \XF\EditHistory\AbstractHandler
{
	/**
	 * @param \MJ\SupportTicket\Entity\TicketMessage $content
	 */
	public function canViewHistory(Entity $content)
	{
		return ($content->canView() && $content->canViewHistory());
	}

	/**
	 * @param \MJ\SupportTicket\Entity\TicketMessage $content
	 */
	public function canRevertContent(Entity $content)
	{
		return $content->canEdit();
	}

	/**
	 * @param \MJ\SupportTicket\Entity\TicketMessage $content
	 */
	public function getContentTitle(Entity $content)
	{
		return \XF::phrase('mjst_message_in_ticket_x', ['title' => $content->Ticket->title]);
	}

	/**
	 * @param \MJ\SupportTicket\Entity\TicketMessage $content
	 */
	public function getContentText(Entity $content)
	{
		return $content->message;
	}

	public function getContentLink(Entity $content)
	{
		return \XF::app()->router('public')->buildLink('support-tickets/messages', $content);
	}

	/**
	 * @param \MJ\SupportTicket\Entity\TicketMessage $content
	 */
	public function getBreadcrumbs(Entity $content)
	{
		/** @var \XF\Mvc\Router $router */
		$router = \XF::app()->container('router');

		$breadcrumbs = $content->Ticket->Department->getBreadcrumbs();
		$breadcrumbs[] = [
			'value' => $content->Ticket->title,
			'href' => $router->buildLink('support-tickets', $content->Ticket)
		];
		return $breadcrumbs;
	}

	/**
	 * @param \MJ\SupportTicket\Entity\TicketMessage $content
	 */
	public function revertToVersion(Entity $content, \XF\Entity\EditHistory $history, \XF\Entity\EditHistory $previous = null)
	{
		/** @var \MJ\SupportTicket\Service\TicketMessage\Editor $editor */
		$editor = \XF::app()->service('MJ\SupportTicket:TicketMessage\Editor', $content);

		$editor->logEdit(false);
		$editor->setMessage($history->old_text);

		if (!$previous || $previous->edit_user_id != $content->user_id)
		{
			$content->last_edit_date = 0;
		}
		else if ($previous && $previous->edit_user_id == $content->user_id)
		{
			$content->last_edit_date = $previous->edit_date;
			$content->last_edit_user_id = $previous->edit_user_id;
		}

		return $editor->save();
	}

	public function getHtmlFormattedContent($text, Entity $content = null)
	{
		return \XF::app()->templater()->fn('bb_code', [$text, 'support_ticket_message', $content]);
	}

	public function getSectionContext()
	{
		return 'departments';
	}

	public function getEntityWith()
	{
		$visitor = \XF::visitor();
		return ['Ticket', 'Ticket.Department', 'Ticket.Department.Permissions|' . $visitor->permission_combination_id];
	}
}
