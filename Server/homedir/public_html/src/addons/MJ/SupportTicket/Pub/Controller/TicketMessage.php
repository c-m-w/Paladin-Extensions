<?php

namespace MJ\SupportTicket\Pub\Controller;

use XF\Mvc\ParameterBag;
use XF\Pub\Controller\AbstractController;
use XF\Mvc\Reply\AbstractReply;

class TicketMessage extends AbstractController
{
	protected function preDispatchController($action, ParameterBag $params)
	{
		/** @var \MJ\Shop\XF\Entity\User $visitor */
		$visitor = \XF::visitor();

		if (!$visitor->canViewSupportTickets($error))
		{
			throw $this->exception($this->noPermission($error));
		}
		if (!$visitor->hasPermission('mjstSupport', 'usePredefinedReply'))
		{
			$this->app()->container()->set('mjstPreReplyEditor', true);
		}
	}

	public function actionIndex(ParameterBag $params)
	{
		$message = $this->assertViewableMessage($params->message_id);

		return $this->redirectPermanently($this->plugin('MJ\SupportTicket:Ticket')->getMessageLink($message));
	}

	public function actionShow(ParameterBag $params)
	{
		$message = $this->assertViewableMessage($params->message_id);

		$viewParams = [
			'message'      => $message,
			'ticket'       => $message->Ticket,
			'department'   => $message->Ticket->Department,
			'canInlineMod' => $message->canUseInlineModeration()
		];
		return $this->view('MJ\SupportTicket:TicketMessage\Show', 'mjst_message', $viewParams);
	}

	/**
	 * @param \MJ\SupportTicket\Entity\TicketMessage $message
	 *
	 * @return \XF\Service\Message\Editor
	 */
	protected function setupMessageEdit(\MJ\SupportTicket\Entity\TicketMessage $message)
	{
		$messageText = $this->plugin('XF:Editor')->fromInput('message');

		/** @var \XF\Service\Message\Editor $editor */
		$editor = $this->service('MJ\SupportTicket:TicketMessage\Editor', $message);
		if ($message->canEditSilently())
		{
			$silentEdit = $this->filter('silent', 'bool');
			if ($silentEdit)
			{
				$editor->logEdit(false);
				if ($this->filter('clear_edit', 'bool'))
				{
					$message->last_edit_date = 0;
				}
			}
		}
		$editor->setMessage($messageText);

		$department = $message->Ticket->Department;
		if ($department->canUploadAndManageAttachments())
		{
			$editor->setAttachmentHash($this->filter('attachment_hash', 'str'));
		}

		if ($this->filter('author_alert', 'bool') && $message->canSendModeratorActionAlert())
		{
			$editor->setSendAlert(true, $this->filter('author_alert_reason', 'str'));
		}

		return $editor;
	}

	/**
	 * @param \MJ\SupportTicket\Entity\Ticket $ticket
	 * @param array $ticketChanges Returns a list of whether certain important ticket fields are changed
	 *
	 * @return \XF\Service\Ticket\Editor
	 */
	protected function setupFirstMessageTicketEdit(\MJ\SupportTicket\Entity\Ticket $ticket, &$ticketChanges)
	{
		/** @var \XF\Service\Ticket\Editor $ticketEditor */
		$ticketEditor = $this->service('MJ\SupportTicket:Ticket\Editor', $ticket);

		$prefixId = $this->filter('prefix_id', 'uint');
		if ($prefixId != $ticket->prefix_id && !$ticket->Department->isPrefixUsable($prefixId))
		{
			$prefixId = 0; // not usable, just blank it out
		}
		$ticketEditor->setPrefix($prefixId);

		$ticketEditor->setTitle($this->filter('title', 'str'));

		$customFields = $this->filter('custom_fields', 'array');
		$ticketEditor->setCustomFields($customFields);

		$ticketChanges = [
			'title' => $ticket->isChanged(['title', 'prefix_id']),
			'customFields' => $ticket->isChanged('custom_fields')
		];

		return $ticketEditor;
	}

	protected function finalizeMessageEdit(
		\MJ\SupportTicket\Service\TicketMessage\Editor $editor,
		\MJ\SupportTicket\Service\Ticket\Editor $ticketEditor = null
	)
	{
	}

	public function actionEdit(ParameterBag $params)
	{
		$message = $this->assertViewableMessage($params->message_id, ['Ticket.Prefix']);
		if (!$message->canEdit($error))
		{
			return $this->noPermission($error);
		}

		$ticket = $message->Ticket;

		if ($this->isPost())
		{
			$editor = $this->setupMessageEdit($message);
			$editor->checkForSpam();

			if (!$editor->validate($errors))
			{
				return $this->error($errors);
			}

			if ($message->isFirstMessage() && $ticket->canEdit())
			{
				$ticketEditor = $this->setupFirstMessageTicketEdit($ticket, $ticketChanges);
				if (!$ticketEditor->validate($errors))
				{
					return $this->error($errors);
				}
			}
			else
			{
				$ticketEditor = null;
				$ticketChanges = [];
			}

			$editor->save();

			if ($ticketEditor)
			{
				$ticketEditor->save();
			}

			$this->finalizeMessageEdit($editor, $ticketEditor);

			if ($this->filter('_xfWithData', 'bool') && $this->filter('_xfInlineEdit', 'bool'))
			{
				/** @var \XF\Repository\Attachment $attachmentRepo */
				$attachmentRepo = $this->repository('XF:Attachment');
				$attachmentRepo->addAttachmentsToContent([$message->message_id => $message], 'support_ticket_message');

				$viewParams = [
					'message' => $message,
					'ticket' => $ticket
				];
				$reply = $this->view('MJ\SupportTicket:TicketMessage\EditNewMessage', 'mjst_message_edit_new_message', $viewParams);
				$reply->setJsonParams([
					'message' => \XF::phrase('your_changes_have_been_saved'),
					'ticketChanges' => $ticketChanges
				]);
				return $reply;
			}
			else
			{
				return $this->redirect($this->buildLink('support-tickets/messages', $message));
			}
		}
		else
		{
			/** @var \XF\Entity\Department $department */
			$department = $message->Ticket->Department;
			if ($department->canUploadAndManageAttachments())
			{
				/** @var \XF\Repository\Attachment $attachmentRepo */
				$attachmentRepo = $this->repository('XF:Attachment');
				$attachmentData = $attachmentRepo->getEditorData('support_ticket_message', $message);
			}
			else
			{
				$attachmentData = null;
			}

			$prefix = $ticket->Prefix;
			$prefixes = $department->getUsablePrefixes($prefix);

			$viewParams = [
				'message'        => $message,
				'ticket'         => $ticket,
				'department'     => $department,
				'prefixes'       => $prefixes,
				'attachmentData' => $attachmentData,
				'quickEdit'      => $this->filter('_xfWithData', 'bool')
			];
			return $this->view('MJ\SupportTicket:TicketMessage\Edit', 'mjst_message_edit', $viewParams);
		}
	}

	public function actionPreview(ParameterBag $params)
	{
		$this->assertPostOnly();

		$message = $this->assertViewableMessage($params->message_id);
		if (!$message->canEdit($error))
		{
			return $this->noPermission($error);
		}

		$ticket = $message->Ticket;

		$editor = $this->setupMessageEdit($message);

		if (!$editor->validate($errors))
		{
			return $this->error($errors);
		}

		$attachments = [];
		$tempHash = $this->filter('attachment_hash', 'str');

		if ($ticket->Department->canUploadAndManageAttachments())
		{
			/** @var \XF\Repository\Attachment $attachmentRepo */
			$attachmentRepo = $this->repository('XF:Attachment');
			$attachmentData = $attachmentRepo->getEditorData('support_ticket_message', $message, $tempHash);
			$attachments = $attachmentData['attachments'];
		}

		return $this->plugin('XF:BbCodePreview')->actionPreview(
			$message->message, 'support_ticket_message', $message->User, $attachments, $ticket->canViewAttachments()
		);
	}

	public function actionDelete(ParameterBag $params)
	{
		$message = $this->assertViewableMessage($params->message_id);
		if (!$message->canDelete('soft', $error))
		{
			return $this->noPermission($error);
		}

		if ($this->isPost())
		{
			$type = $this->filter('hard_delete', 'bool') ? 'hard' : 'soft';
			$reason = $this->filter('reason', 'str');

			if (!$message->canDelete($type, $error))
			{
				return $this->noPermission($error);
			}

			/** @var \MJ\SupportTicket\Entity\Ticket $ticket */
			$ticket = $message->Ticket;

			/** @var \XF\Service\Message\Deleter $deleter */
			$deleter = $this->service('MJ\SupportTicket:TicketMessage\Deleter', $message);

			if ($this->filter('author_alert', 'bool') && $message->canSendModeratorActionAlert())
			{
				$deleter->setSendAlert(true, $this->filter('author_alert_reason', 'str'));
			}

			$deleter->delete($type, $reason);

			$this->plugin('XF:InlineMod')->clearIdFromCookie('support_ticket_message', $message->message_id);

			if ($deleter->wasTicketDeleted())
			{
				$this->plugin('XF:InlineMod')->clearIdFromCookie('support_ticket', $message->support_ticket_id);

				return $this->redirect(
					$ticket && $ticket->Department
						? $this->buildLink('support-tickets/departments', $ticket->Department)
						: $this->buildLink('support-tickets')
				);
			}
			else
			{
				return $this->redirect(
					$this->getDynamicRedirect($this->buildLink('support-tickets', $ticket), false)
				);
			}
		}
		else
		{
			$viewParams = [
				'message' => $message,
				'ticket' => $message->Ticket,
				'department' => $message->Ticket->Department
			];
			return $this->view('MJ\SupportTicket:TicketMessage\Delete', 'mjst_message_delete', $viewParams);
		}
	}

	public function actionIp(ParameterBag $params)
	{
		$message = $this->assertViewableMessage($params->message_id);
		$breadcrumbs = $message->Ticket->getBreadcrumbs();

		/** @var \XF\ControllerPlugin\Ip $ipPlugin */
		$ipPlugin = $this->plugin('XF:Ip');
		return $ipPlugin->actionIp($message, $breadcrumbs);
	}

	public function actionReport(ParameterBag $params)
	{
		$message = $this->assertViewableMessage($params->message_id);
		if (!$message->canReport($error))
		{
			return $this->noPermission($error);
		}

		/** @var \XF\ControllerPlugin\Report $reportPlugin */
		$reportPlugin = $this->plugin('XF:Report');
		return $reportPlugin->actionReport(
			'support_ticket_message',
			$message,
			$this->buildLink('support-tickets/messages/report', $message),
			$this->buildLink('support-tickets/messages', $message)
		);
	}

	public function actionQuote(ParameterBag $params)
	{
		$message = $this->assertViewableMessage($params->message_id);
		if (!$message->Ticket->canReply($error))
		{
			return $this->noPermission($error);
		}

		return $this->plugin('XF:Quote')->actionQuote($message, 'support_ticket_message');
	}

	public function actionHistory(ParameterBag $params)
	{
		return $this->rerouteController('XF:EditHistory', 'index', [
			'content_type' => 'support_ticket_message',
			'content_id' => $params->message_id
		]);
	}

	public function actionWarn(ParameterBag $params)
	{
		$message = $this->assertViewableMessage($params->message_id);

		if (!$message->canWarn($error))
		{
			return $this->noPermission($error);
		}

		$breadcrumbs = $message->Ticket->getBreadcrumbs();

		/** @var \XF\ControllerPlugin\Warn $warnPlugin */
		$warnPlugin = $this->plugin('XF:Warn');
		return $warnPlugin->actionWarn(
			'support_ticket_message',
			$message,
			$this->buildLink('support-tickets/messages/warn', $message),
			$breadcrumbs
		);
	}

	/**
	 * @param $messageId
	 * @param array $extraWith
	 *
	 * @return \MJ\SupportTicket\Entity\TicketMessage
	 *
	 * @throws \XF\Mvc\Reply\Exception
	 */
	protected function assertViewableMessage($messageId, array $extraWith = [], $throw = true)
	{
		$visitor = \XF::visitor();
		$extraWith[] = 'Ticket';
		$extraWith[] = 'Ticket.Department';
		$extraWith[] = 'Ticket.Department.Permissions|' . $visitor->permission_combination_id;

		/** @var \MJ\SupportTicket\Entity\TicketMessage $message */
		$message = $this->em()->find('MJ\SupportTicket:TicketMessage', $messageId, $extraWith);
		if (!$message)
		{
			throw $this->exception($this->notFound(\XF::phrase('mjst_requested_message_not_found')));
		}

		if (!$message->canView($error))
		{
			if(!$throw){
				throw $this->exception($this->noPermission($error));
			}
		}

		return $message;
	}

	/**
	 * @return \MJ\SupportTicket\Repository\Ticket
	 */
	protected function getTicketRepo()
	{
		return $this->repository('MJ\SupportTicket:Ticket');
	}

	/**
	 * @return \MJ\SupportTicket\Repository\TicketMessage
	 */
	protected function getMessageRepo()
	{
		return $this->repository('MJ\SupportTicket:TicketMessage');
	}

	public static function getActivityDetails(array $activities)
	{
		return \XF::phrase('mjst_viewing_ticket');  // no need to be more specific - this is a fairly infrequent event
	}
}
