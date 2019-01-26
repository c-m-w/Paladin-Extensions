<?php

namespace MJ\SupportTicket\Pub\Controller;

use XF\Mvc\ParameterBag;
use XF\Pub\Controller\AbstractController;
use XF\Mvc\Reply\AbstractReply;

class Ticket extends AbstractController
{
	protected function preDispatchController($action, ParameterBag $params)
	{
		/** @var \MJ\Shop\XF\Entity\User $visitor */
		$visitor = \XF::visitor();

		if (!$visitor->canViewSupportTickets($error))
		{
			throw $this->exception($this->noPermission($error));
		}
		if ($visitor->hasPermission('mjstSupport', 'usePredefinedReply'))
		{
			$this->app()->container()->set('mjstPreReplyEditor', true);
		}
	}

	public function actionIndex(ParameterBag $params)
	{
		if ($params->support_ticket_id)
		{
			return $this->rerouteController(__CLASS__, 'view', $params);
		}
		$visitor = \XF::visitor();
		if(!$visitor->user_id && $visitor->canOpenTicket()){
			return $this->rerouteController(__CLASS__, 'open', $params);
		}

		$this->assertRegistrationRequired();

		/** @var \MJ\SupportTicket\ControllerPlugin\Overview $overviewPlugin */
		$overviewPlugin = $this->plugin('MJ\SupportTicket:Overview');

		$departmentParams = $overviewPlugin->getDepartmentListData();
		$departmentRepo = $this->getDepartmentRepo();

		$viewableAnyDepartments = $departmentRepo->filterViewableAny($departmentParams['departments']);

		$viewableAnyDepartmentIds = $viewableAnyDepartments->keys();

		$listParams = $overviewPlugin->getCoreListData($viewableAnyDepartmentIds, $params->page);

		$this->assertValidPage($listParams['page'], $listParams['perPage'], $listParams['total'], 'support-tickets');

		$this->assertCanonicalUrl($this->buildLink('support-tickets', null, $listParams['filters'] + ['page' => $listParams['page']]));

		$viewParams = $departmentParams + $listParams;

		return $this->view('MJ\SupportTicket:Overview', 'mjst_overview', $viewParams);
	}

	public function actionYours(ParameterBag $params)
	{
		$this->assertRegistrationRequired();

		$visitor = \XF::visitor();

		return $this->redirect($this->buildLink('support-tickets', null, ['owner_id' => $visitor->user_id]), '');
	}

	public function actionAssigned(ParameterBag $params)
	{
		$this->assertRegistrationRequired();

		$visitor = \XF::visitor();

		return $this->redirect($this->buildLink('support-tickets', null, ['assigned_id' => $visitor->user_id]), '');
	}

	public function actionTicketPreview(ParameterBag $params)
	{
		$this->assertPostOnly();

		$departmentId = $this->filter('department_id', 'uint');

		$department = $this->assertViewableDepartment($departmentId);
		if (!$department->canOpenTicket($error))
		{
			return $this->noPermission($error);
		}

		$creator = $this->setupTicketCreate($department);
		if (!$creator->validate($errors))
		{
			return $this->error($errors);
		}

		$ticket = $creator->getTicket();
		$message = $creator->getMessage();
		$attachments = null;

		$tempHash = $this->filter('attachment_hash', 'str');
		if ($tempHash && $ticket->Department->canUploadAndManageAttachments())
		{
			$attachRepo = $this->repository('XF:Attachment');
			$attachments = $attachRepo->findAttachmentsByTempHash($tempHash)->fetch();
		}

		return $this->plugin('XF:BbCodePreview')->actionPreview(
			$message->message, 'support_ticket_message', $message->User, $attachments, $ticket->canViewAttachments()
		);
	}

	/**
	 * @param \MJ\SupportTicket\Entity\Department $department
	 *
	 * @return \XF\Service\Ticket\Creator
	 */
	protected function setupTicketCreate(\MJ\SupportTicket\Entity\Department $department)
	{
		$title = $this->filter('title', 'str');
		$message = $this->plugin('XF:Editor')->fromInput('message');

		/** @var \MJ\SupportTicket\Service\Ticket\Creator $creator */
		$creator = $this->service('MJ\SupportTicket:Ticket\Creator', $department);

		$creator->setContent($title, $message);

		$prefixId = $this->filter('prefix_id', 'uint');
		if ($prefixId && $department->isPrefixUsable($prefixId))
		{
			$creator->setPrefix($prefixId);
		}

		$urgency = $this->filter('urgency', 'uint');
		$creator->setUrgency($urgency);

		$isOpen = $this->filter('is_open', 'bool');
		if($isOpen){
			$targetType = $this->filter('target_type', 'str');
			$userId = 0;
			$username = '';
			$email = '';
			if($targetType == 'member'){
				$username = $this->filter('target_member', 'str');
				$user = $this->finder('XF:User')
					->where('username', $username)
					->fetchOne();
				if(!$user){
					throw $this->errorException(\XF::phrase('requested_user_not_found'));
				}
				$userId = $user->user_id;
				$username = $user->username;
				$email = $user->email;
			}else{
				$username = $this->filter('guest_username', 'str');
				$email = $this->filter('guest_email', 'str');
				if(!$username || !$email){
					throw $this->errorException(\XF::phrase('mjst_you_must_enter_name_and_email_for_guest'));
				}
			}

			if (!$creator->setEmail($email, $error))
			{
				throw $this->exception($this->error($error));
			}

			$creator->setOwner($userId, $username);
		}
		$visitor = \XF::visitor();
		if(!$visitor->user_id){
			$email = $this->filter('guest_email', 'str');
			if (!$creator->setEmail($email, $error))
			{
				throw $this->exception($this->error($error));
			}
		}

		$creator->setUrgency($urgency);

		$ticketStatusId = $this->filter('ticket_status_id', 'uint');
		if ($prefixId && $department->isPrefixUsable($prefixId))
		{
			$creator->setPrefix($prefixId);
		}

		if ($department->canUploadAndManageAttachments())
		{
			$creator->setAttachmentHash($this->filter('attachment_hash', 'str'));
		}

		$customFields = $this->filter('custom_fields', 'array');
		$creator->setCustomFields($customFields);

		return $creator;
	}

	protected function finalizeTicketCreate(\MJ\SupportTicket\Service\Ticket\Creator $creator)
	{
		$creator->sendNotifications();

		$department = $creator->getDepartment();
		$ticket = $creator->getTicket();
		$visitor = \XF::visitor();

		$setOptions = $this->filter('_xfSet', 'array-bool');
		if ($ticket->canWatch())
		{
			if (isset($setOptions['watch_ticket']))
			{
				$watch = $this->filter('watch_ticket', 'bool');
				if ($watch)
				{
					/** @var \MJ\SupportTicket\Repository\TicketWatch $ticketWatchRepo */
					$ticketWatchRepo = $this->repository('MJ\SupportTicket:TicketWatch');

					$state = $this->filter('watch_ticket_email', 'bool') ? 'watch_email' : 'watch_no_email';
					$ticketWatchRepo->setWatchState($ticket, $visitor, $state);
					if($ticket->creator_user_id != $ticket->user_id && $ticket->user_id){
						$ticketWatchRepo->setWatchState($ticket, $ticket->User, $state);
					}
				}
			}
			else
			{
				// use user preferences
				$this->repository('MJ\SupportTicket:TicketWatch')->autoWatchTicket($ticket, $visitor, true);
				if($ticket->creator_user_id != $ticket->user_id && $ticket->user_id){
					$this->repository('MJ\SupportTicket:TicketWatch')->autoWatchTicket($ticket, $ticket->User, true);
				}
			}
		}

		if ($visitor->user_id)
		{
			$this->getTicketRepo()->markTicketReadByVisitor($ticket, $ticket->open_date);

			//$department->draft_ticket->delete();
		}
	}

	public function actionOpen(ParameterBag $params)
	{
		$visitor = \XF::visitor();
		if (!$visitor->canOpenTicket($error))
		{
			return $this->noPermission($error);
		}

		$departmentRepo = $this->getDepartmentRepo();
		$departments = $departmentRepo->getOpenableDepartments();

		if ($this->isPost())
		{
			if ($this->options()->mjstRequireCaptcha && !$this->captchaIsValid())
			{
				return $this->error(\XF::phrase('did_not_complete_the_captcha_verification_properly'));
			}

			$departmentId = $this->filter('department_id', 'uint');
			if(!isset($departments[$departmentId])){
				return $this->noPermission();
			}
			$department = $departments[$departmentId];

			$creator = $this->setupTicketCreate($department);

			$creator->checkForSpam();

			if (!$creator->validate($errors))
			{
				return $this->error($errors);
			}
			$this->assertNotFlooding('support_ticket_message');

			/** @var \MJ\SupportTicket\Entity\Ticket $ticket */
			$ticket = $creator->save();
			$this->finalizeTicketCreate($creator);

			if(!$ticket->user_id){
				return $this->redirect($this->buildLink('support-tickets/created', $ticket));
			}

			if (!$ticket->canView())
			{
				return $this->redirect($this->buildLink('support-tickets/departments', $department, ['pending_approval' => 1]));
			}
			else
			{
				return $this->redirect($this->buildLink('support-tickets', $ticket));
			}
		}else{
			if (!$departments)
			{
				return $this->noPermission();
			}

			$options = $this->options();
			$draft = \XF\Draft::createFromKey('support_ticket');

			/** @var \MJ\SupportTicket\Entity\Ticket $support_ticket */
			$ticket = $this->em()->create('MJ\SupportTicket:Ticket');

			$defaultDepartmentId = $options->mjstDefautDepartment;

			$departmentId = $this->filter('department_id', 'uint');

			if(isset($departments[$departmentId])){
				$department = $departments[$departmentId];
			}elseif(isset($departments[$defaultDepartmentId])){
				$department = $departments[$defaultDepartmentId];
			}else{
				$department = $departments->first();
			}
			$ticket->department_id = $department->department_id;

			$ticket->urgency = $options->mjstDefautPriority;

			if ($ticket->canUploadAndManageAttachments())
			{
				/** @var \XF\Repository\Attachment $attachmentRepo */
				$attachmentRepo = $this->repository('XF:Attachment');
				$attachmentData = $attachmentRepo->getEditorData('support_ticket_message', $department, $draft->attachment_hash);
			}
			else
			{
				$attachmentData = null;
			}

			if ($draft && $draft->custom_fields)
			{
				/** @var \XF\CustomField\Set $customFields */
				$customFields = $ticket->custom_fields;
				$customFields->bulkSet($draft->custom_fields, null, 'user', true);
			}

			$ticket->setDataFromDraft($draft);

			$viewParams = [
				'departments'    => $departments,
				'department'     => $department,
				'ticket'         => $ticket,
				'draft'          => $draft,
				'prefixes'       => $department->getUsablePrefixes(),

				'attachmentData' => $attachmentData,
			];

			return $this->view('MJ\SupportTicket:Ticket\Open', 'mjst_ticket_open', $viewParams);
		}
	}

	public function actionCreated(ParameterBag $params)
	{
		$ticket = $this->assertViewableTicket($params->support_ticket_id, $this->getTicketViewExtraWith(), false);

		if(!$ticket->user_id && !$ticket->canViewGuestTicket()){
			return $this->actionPassword($params);
		}
		$viewParams = [
			'ticket' => $ticket
		];
		return $this->view('MJ\SupportTicket:Ticket\View', 'mjst_ticket_created', $viewParams);
	}

	public function actionDraft(ParameterBag $params)
	{
		$extraData = $this->filter([
			'attachment_hash' => 'str'
		]);

		if ($params->support_ticket_id)
		{
			$ticket = $this->assertViewableTicket($params->support_ticket_id);

			$draft = $ticket->draft_reply;
		}
		else
		{
			$departmentId = $this->filter('department_id', 'str');

			$department = $this->assertViewableDepartment($departmentId);
			/** @var \XF\Service\Ticket\Creator $creator */
			$creator = $this->setupTicketCreate($department);
			$ticket = $creator->getTicket();

			$visitor = \XF::visitor();

			if (!$visitor->canOpenTicket())
			{
				return $this->noPermission();
			}

			$extraData = $extraData + $this->filter([
				'title'            => 'str',
				'prefix_id'        => 'uint',
				'urgency'          => 'uint',
				'is_open'          => 'bool',
				'target_type'      => 'str',
				'target_member'    => 'str',
				'guest_username'   => 'str',
				'guest_email'      => 'str',
				'ticket_status_id' => 'uint',
			]);

			$draft = \XF\Draft::createFromKey('support_ticket');
		}

		/** @var \XF\ControllerPlugin\Draft $draftPlugin */
		$draftPlugin = $this->plugin('XF:Draft');
		return $draftPlugin->actionDraftMessage($draft, $extraData);
	}

	public function actionRate(ParameterBag $params)
	{
		$ticket = $this->assertViewableTicket($params->support_ticket_id, $this->getTicketViewExtraWith(), false);
		if (!$ticket->canRate($error))
		{
			return $this->noPermission($error);
		}

		if($this->isPost()){
			$ratePoint = $this->filter('rating', 'uint');
			$ticket->submitter_rating = $ratePoint;
			$ticket->save();
			return $this->redirect($this->buildLink('support-tickets', $ticket));
		}else{
			$viewParams = [
				'ticket'          => $ticket,
			];
			return $this->view('MJ\SupportTicket:Ticket\Rate', 'mjst_ticket_rate', $viewParams);
		}
	}

	public function actionClose(ParameterBag $params)
	{
		$ticket = $this->assertViewableTicket($params->support_ticket_id, $this->getTicketViewExtraWith(), false);
		if (!$ticket->canClose($error))
		{
			return $this->noPermission($error);
		}

		if($this->isPost()){
			/** @var \XF\Service\Ticket\Closer $closer */
			$closer = $this->service('MJ\SupportTicket:Ticket\Closer', $ticket);

			if ($this->filter('starter_alert', 'bool'))
			{
				$closer->setSendAlert(true, $this->filter('starter_alert_reason', 'str'));
			}

			$closer->close();

			$this->plugin('XF:InlineMod')->clearIdFromCookie('support_ticket', $ticket->support_ticket_id);

			return $this->redirect($this->buildLink('support-tickets', $ticket));
		}else{
			$viewParams = [
				'ticket'          => $ticket,
				'department'      => $ticket->Department,
			];
			return $this->view('MJ\SupportTicket:Ticket\Close', 'mjst_ticket_close', $viewParams);
		}
	}

	public function actionPassword(ParameterBag $params)
	{
		$ticket = $this->assertViewableTicket($params->support_ticket_id, $this->getTicketViewExtraWith(), false);

		if($this->isPost()){
			$password = $this->filter('password', 'str');
			if($password == $ticket->guest_password){
				$this->app->response()->setCookie('msjtp_' . $ticket->support_ticket_id, $password);
			}else{
				return $this->error(\XF::phrase('mjst_invalid_ticket_password'));
			}
			return $this->redirect($this->buildLink('support-tickets', $ticket));
		}else{
			$viewParams = [
				'ticket'          => $ticket,
				'department'      => $ticket->Department,
			];

			return $this->view('MJ\SupportTicket:Ticket\Password', 'mjst_ticket_password', $viewParams);
		}
	}

	public function actionView(ParameterBag $params)
	{
		$ticket = $this->assertViewableTicket($params->support_ticket_id, $this->getTicketViewExtraWith(), false);

		if(!$ticket->user_id && !$ticket->canViewGuestTicket()){
			return $this->rerouteController(__CLASS__, 'password', $params);
		}
		$ticketRepo = $this->getTicketRepo();

		$page = $params->page;
		$perPage = $this->options()->messagesPerPage;

		$this->assertValidPage($page, $perPage, $ticket->reply_count + 1, 'support-tickets', $ticket);
		$this->assertCanonicalUrl($this->buildLink('support-tickets', $ticket, ['page' => $page]));

		$messageRepo = $this->getMessageRepo();

		$messageList = $messageRepo->findMessagesForTicketView($ticket)->onPage($page, $perPage);
		$messages = $messageList->fetch();

		/** @var \XF\Repository\Attachment $attachmentRepo */
		$attachmentRepo = $this->repository('XF:Attachment');
		$attachmentRepo->addAttachmentsToContent($messages, 'support_ticket_message');

		$lastMessage = $messages->last();
		if (!$lastMessage)
		{
			if ($page > 1)
			{
				return $this->redirect($this->buildLink('support-tickets', $ticket));
			}
			else
			{
				// should never really happen
				return $this->error(\XF::phrase('something_went_wrong_please_try_again'));
			}
		}

		$firstMessage = $messages->first();

		/** @var \MJ\SupportTicket\Entity\TicketMessage $message */

		$canInlineMod = false;
		foreach ($messages as $message)
		{
			if ($message->canUseInlineModeration())
			{
				$canInlineMod = true;
				break;
			}
		}

		$firstUnread = null;
		foreach ($messages as $message)
		{
			if ($message->isUnread())
			{
				$firstUnread = $message;
				break;
			}
		}

		$ticketRepo->markTicketReadByVisitor($ticket, $lastMessage->message_date);
		//$ticketRepo->logTicketView($ticket);

		$departmentRepo = $this->getDepartmentRepo();
		$departments = $departmentRepo->getOpenableDepartments();

		$ticketStatuses = $this->repository('MJ\SupportTicket:TicketStatus')->findTicketStatusForList()->fetch();

		if($ticket->canViewCurrentViewer()){
			$sessionFinder = $this->repository('XF:SessionActivity')->findForOnlineList('');
			$sessionFinder->where('controller_action', 'View');
			$sessionFinder->where('view_state', 'valid');
			$sessionFinder->where('params', 'LIKE', $sessionFinder->escapeLike('support_ticket_id=' . $ticket->support_ticket_id, '%?%'));
			$viewers = $sessionFinder->fetch();
		}else{
			$viewers = [];
		}
		$this->app()->container()->set('mjstTicket', $ticket);
		$viewParams = [
			'ticket'             => $ticket,
			'viewers'            => $viewers,
			'department'         => $ticket->Department,
			'messages'           => $messages,
			'firstMessage'       => $firstMessage,
			'lastMessage'        => $lastMessage,
			'firstUnread'        => $firstUnread,
			'canInlineMod'       => $canInlineMod,
			'departments'        => $departments,
			'ticketStatuses'     => $ticketStatuses,
			'page'               => $page,
			'perPage'            => $perPage,
			'attachmentData'     => $this->getReplyAttachmentData($ticket),
			'pendingApproval'    => $this->filter('pending_approval', 'bool')
		];
		return $this->view('MJ\SupportTicket:Ticket\View', 'mjst_ticket_view', $viewParams);
	}

	protected function getTicketViewExtraWith()
	{
		$extraWith = ['User'];
		$userId = \XF::visitor()->user_id;
		if ($userId)
		{
			$extraWith[] = 'Watch|' . $userId;
			$extraWith[] = 'DraftReplies|' . $userId;
		}

		return $extraWith;
	}

	public function actionUnread(ParameterBag $params)
	{
		$ticket = $this->assertViewableTicket($params->support_ticket_id, ['LastMessage']);

		if (!\XF::visitor()->user_id)
		{
			return $this->redirect($this->buildLink('support-tickets', $ticket));
		}

		$messageRepo = $this->getMessageRepo();
		$firstUnreadDate = $ticket->getVisitorReadDate();

		// this would force us to go to a new message, even if we have no read marking data for this ticket
		$forceNew = $this->filter('new', 'bool');

		if (!$forceNew && $firstUnreadDate <= $this->getTicketRepo()->getReadMarkingCutOff())
		{
			// We have no read marking data for this person, so we don't know whether they've read this ticket before.
			// More than likely, they haven't so we have to take them to the beginning.
			return $this->redirect($this->buildLink('support-tickets', $ticket));
		}

		$findFirstUnread = $messageRepo->findNextMessagesInTicket($ticket, $firstUnreadDate);
		$firstUnread = $findFirstUnread->skipIgnored()->fetchOne();

		if (!$firstUnread)
		{
			$firstUnread = $ticket->LastMessage;
		}

		if (!$firstUnread)
		{
			// sanity check, probably shouldn't happen
			return $this->redirect($this->buildLink('support-tickets', $ticket));
		}

		if ($firstUnread->message_id == $ticket->first_message_id)
		{
			return $this->redirect($this->buildLink('support-tickets', $ticket));
		}

		return $this->redirect($this->plugin('MJ\SupportTicket:Ticket')->getMessageLink($firstUnread));
	}

	public function actionLatest(ParameterBag $params)
	{
		$ticket = $this->assertViewableTicket($params->support_ticket_id, ['LastMessage']);
		$message = $ticket->LastMessage;

		if ($message)
		{
			return $this->redirect($this->plugin('MJ\SupportTicket:Ticket')->getMessageLink($message));
		}
		else
		{
			return $this->redirect($this->buildLink('support-tickets', $ticket));
		}
	}

	public function actionMessage(ParameterBag $params)
	{
		$messageId = max(0, intval($params->message_id));
		if (!$messageId)
		{
			return $this->notFound();
		}

		$visitor = \XF::visitor();
		$with = [
			'Ticket',
			'Ticket.Department',
			'Ticket.Department',
			'Ticket.Department.Permissions|' . $visitor->permission_combination_id
		];

		$message = $this->em()->find('MJ\SupportTicket:TicketMessage', $messageId, $with);
		if (!$message)
		{
			return $this->notFound();
		}
		if (!$message->canView($error))
		{
			return $this->noPermission($error);
		}

		return $this->redirectPermanently($this->plugin('MJ\SupportTicket:Ticket')->getMessageLink($message));
	}

	public function actionNewMessages(ParameterBag $params)
	{
		$ticket = $this->assertViewableTicket($params->support_ticket_id, ['FirstMessage']);

		if (!$this->request->isXhr())
		{
			return $this->redirect($this->buildLink('support-tickets', $ticket));
		}

		$after = $this->filter('after', 'uint');
		return $this->getNewMessagesReply($ticket, $after);
	}

	public function actionPreview(ParameterBag $params)
	{
		$ticket = $this->assertViewableTicket($params->support_ticket_id, ['FirstMessage']);
		$firstMessage = $ticket->FirstMessage;

		$viewParams = [
			'ticket' => $ticket,
			'firstMessage' => $firstMessage
		];
		return $this->view('MJ\SupportTicket:Ticket\Preview', 'mjst_ticket_preview', $viewParams);
	}

	/**
	 * @param \MJ\SupportTicket\Entity\Ticket $ticket
	 *
	 * @return \XF\Service\Ticket\Replier
	 */
	protected function setupTicketReply(\MJ\SupportTicket\Entity\Ticket $ticket)
	{
		$message = $this->plugin('XF:Editor')->fromInput('message');

		/** @var \XF\Service\Ticket\Replier $replier */
		$replier = $this->service('MJ\SupportTicket:Ticket\Replier', $ticket);

		$replier->setMessage($message);

		if ($ticket->Department->canUploadAndManageAttachments())
		{
			$replier->setAttachmentHash($this->filter('attachment_hash', 'str'));
		}

		return $replier;
	}

	protected function finalizeTicketReply(\MJ\SupportTicket\Service\Ticket\Replier $replier)
	{
		$replier->sendNotifications();

		$ticket = $replier->getTicket();
		$message = $replier->getMessage();
		$visitor = \XF::visitor();

		$setOptions = $this->filter('_xfSet', 'array-bool');
		if ($ticket->canWatch())
		{
			if (isset($setOptions['watch_ticket']))
			{
				$watch = $this->filter('watch_ticket', 'bool');
				if ($watch)
				{
					/** @var \XF\Repository\TicketWatch $ticketWatchRepo */
					$ticketWatchRepo = $this->repository('MJ\SupportTicket:TicketWatch');

					$state = $this->filter('watch_ticket_email', 'bool') ? 'watch_email' : 'watch_no_email';
					$ticketWatchRepo->setWatchState($ticket, $visitor, $state);
				}
			}
			else
			{
				// use user preferences
				$this->repository('MJ\SupportTicket:TicketWatch')->autoWatchTicket($ticket, $visitor, false);
			}
		}

		$ticket->saveIfChanged($null, false);

		if ($visitor->user_id)
		{
			$readDate = $ticket->getVisitorReadDate();
			if ($readDate && $readDate >= $ticket->getPreviousValue('last_message_date'))
			{
				$message = $replier->getMessage();
				$this->getTicketRepo()->markTicketReadByVisitor($ticket, $message->message_date);
			}

			$ticket->draft_reply->delete();

			if ($message->message_state == 'moderated')
			{
				$this->session()->setHasContentPendingApproval();
			}
		}
	}

	public function actionReply(ParameterBag $params)
	{
		$visitor = \XF::visitor();

		$ticket = $this->assertViewableTicket($params->support_ticket_id, ['Watch|' . $visitor->user_id]);
		if (!$ticket->canReply($error))
		{
			return $this->noPermission($error);
		}

		$defaultMessage = '';
		$forceAttachmentHash = null;

		$quote = $this->filter('quote', 'uint');
		if ($quote)
		{
			/** @var \MJ\SupportTicket\Entity\TicketMessage $message */
			$message = $this->em()->find('MJ\SupportTicket:TicketMessage', $quote, 'User');
			if ($message && $message->support_ticket_id == $ticket->support_ticket_id && $message->canView())
			{
				$defaultMessage = $message->getQuoteWrapper(
					$this->app->stringFormatter()->getBbCodeForQuote($message->message, 'message')
				);
				$forceAttachmentHash = '';
			}
		}
		else if ($this->request->exists('requires_captcha'))
		{
			$defaultMessage = $this->plugin('XF:Editor')->fromInput('message');
			$forceAttachmentHash = $this->filter('attachment_hash', 'str');
		}
		else
		{
			$defaultMessage = $ticket->draft_reply->message;
		}

		$viewParams = [
			'ticket' => $ticket,
			'department' => $ticket->Department,
			'attachmentData' => $this->getReplyAttachmentData($ticket, $forceAttachmentHash),
			'defaultMessage' => $defaultMessage
		];
		return $this->view('MJ\SupportTicket:Ticket\Reply', 'mjst_ticket_reply', $viewParams);
	}

	public function actionAddReply(ParameterBag $params)
	{
		$this->assertPostOnly();

		$visitor = \XF::visitor();
		$ticket = $this->assertViewableTicket($params->support_ticket_id, ['Watch|' . $visitor->user_id]);
		if (!$ticket->canReply($error))
		{
			return $this->noPermission($error);
		}

		if ($this->filter('no_captcha', 'bool')) // JS is disabled so user hasn't seen Captcha.
		{
			$this->request->set('requires_captcha', true);
			return $this->rerouteController(__CLASS__, 'reply', $params);
		}
		else if ($this->options()->mjstRequireCaptcha && !$this->captchaIsValid())
		{
			return $this->error(\XF::phrase('did_not_complete_the_captcha_verification_properly'));
		}

		$replier = $this->setupTicketReply($ticket);
		$replier->checkForSpam();

		if (!$replier->validate($errors))
		{
			return $this->error($errors);
		}
		$this->assertNotFlooding('message');
		$message = $replier->save();

		$this->finalizeTicketReply($replier);

		if ($this->filter('_xfWithData', 'bool') && $this->request->exists('last_date') && $message->canView())
		{
			// request was from quick reply
			$lastDate = $this->filter('last_date', 'uint');
			return $this->getNewMessagesReply($ticket, $lastDate);
		}
		else
		{
			$this->getTicketRepo()->markTicketReadByVisitor($ticket);
			$confirmation = \XF::phrase('your_message_has_been_posted');

			return $this->redirect($this->buildLink('support-tickets/messages', $message), $confirmation);

			if ($message->canView())
			{
				return $this->redirect($this->buildLink('support-tickets/messages', $message), $confirmation);
			}
			else
			{
				return $this->redirect($this->buildLink('support-tickets', $ticket, ['pending_approval' => 1]), $confirmation);
			}

		}
	}

	protected function getNewMessagesReply(\MJ\SupportTicket\Entity\Ticket $ticket, $lastDate)
	{
		$messageRepo = $this->getMessageRepo();

		$limit = 3;

		/** @var \XF\Mvc\Entity\Finder $messageList */
		$messageList = $messageRepo->findNewestMessagesInTicket($ticket, $lastDate)->skipIgnored()->forFullView();
		$messages = $messageList->fetch($limit + 1);

		// We fetched one more message than needed, if more than $limit messages were returned,
		// we can show the 'there are more messages' notice
		if ($messages->count() > $limit)
		{
			$firstUnshownMessage = $messages->first();

			// Remove the extra message
			$messages = $messages->pop();
		}
		else
		{
			$firstUnshownMessage = null;
		}

		// put the messages into oldest-first order
		$messages = $messages->reverse(true);

		/** @var \XF\Repository\Attachment $attachmentRepo */
		$attachmentRepo = $this->repository('XF:Attachment');
		$attachmentRepo->addAttachmentsToContent($messages, 'support_ticket_message');

		$visitor = \XF::visitor();
		$ticketRead = $ticket->Read[$visitor->user_id];

		if ($visitor->user_id)
		{
			if (!$firstUnshownMessage || ($ticketRead && $firstUnshownMessage->message_date <= $ticketRead->support_ticket_read_date))
			{
				$this->getTicketRepo()->markTicketReadByVisitor($ticket);
			}
		}

		$last = $messages->last();
		if ($last)
		{
			$lastDate = $last->message_date;
		}

		$viewParams = [
			'ticket'              => $ticket,
			'messages'            => $messages,
			'firstUnshownMessage' => $firstUnshownMessage
		];
		$view = $this->view('MJ\SupportTicket:Ticket\NewMessages', 'mjst_ticket_new_messages', $viewParams);
		$view->setJsonParam('lastDate', $lastDate);
		return $view;
	}

	public function actionReplyPreview(ParameterBag $params)
	{
		$this->assertPostOnly();

		$ticket = $this->assertViewableTicket($params->support_ticket_id);
		if (!$ticket->canReply($error))
		{
			return $this->noPermission($error);
		}

		$replier = $this->setupTicketReply($ticket);
		if (!$replier->validate($errors))
		{
			return $this->error($errors);
		}

		$message = $replier->getMessage();
		$attachments = [];

		$tempHash = $this->filter('attachment_hash', 'str');
		if ($tempHash && $ticket->Department->canUploadAndManageAttachments())
		{
			$attachRepo = $this->repository('XF:Attachment');
			$attachments = $attachRepo->findAttachmentsByTempHash($tempHash)->fetch();
		}

		return $this->plugin('XF:BbCodePreview')->actionPreview(
			$message->message, 'support_ticket_message', $message->User, $attachments, $ticket->canViewAttachments()
		);
	}

	public function actionMultiQuote()
	{
		$this->assertPostOnly();

		/** @var \XF\ControllerPlugin\Quote $quotePlugin */
		$quotePlugin = $this->plugin('XF:Quote');

		$quotes = $this->filter('quotes', 'json-array');
		if (!$quotes)
		{
			return $this->error(\XF::phrase('no_messages_selected'));
		}
		$quotes = $quotePlugin->prepareQuotes($quotes);

		$messageFinder = $this->finder('MJ\SupportTicket:TicketMessage');

		$messages = $messageFinder
			->with(['User', 'Ticket', 'Ticket.Department'])
			->where('message_id', array_keys($quotes))
			->order('message_date', 'DESC')
			->fetch()
			->filterViewable();

		if ($this->request->exists('insert'))
		{
			$insertOrder = $this->filter('insert', 'array');
			return $quotePlugin->actionMultiQuote($messages, $insertOrder, $quotes, 'message');
		}
		else
		{
			$viewParams = [
				'quotes' => $quotes,
				'messages' => $messages
			];
			return $this->view('MJ\SupportTicket:Ticket\MultiQuote', 'mjst_ticket_multi_quote', $viewParams);
		}
	}

	public function actionPreReplies()
	{
		$preRepliesInfo = $this->repository('MJ\SupportTicket:PreReply')->getPreReplyListData();

		$submitterName = $this->filter('submitter', 'str');
		$visitorName = \XF::visitor()->username;
		$boardTitle = $this->options()->boardTitle;

		foreach($preRepliesInfo['repliesGrouped'] as $groupId => $replies){
			foreach($replies as $reply){
				$message = $reply->message;
				$message = str_replace('[TICKET_USER]', $submitterName, $message);
				$message = str_replace('[SUPPORT_USER]', $visitorName, $message);
				$message = str_replace('[BOARD_TITLE]', $boardTitle, $message);
				$reply->message = $message;
			}
		}

		$viewParams = [
			'preRepliesInfo' => $preRepliesInfo
		];
		return $this->view('MJ\SupportTicket:Editor\PreReplies', 'mjst_editor_pre_replies', $viewParams);
	}

	/**
	 * @param \MJ\SupportTicket\Entity\Ticket $ticket
	 *
	 * @return \XF\Service\Ticket\Editor
	 */
	protected function setupTicketEdit(\MJ\SupportTicket\Entity\Ticket $ticket)
	{
		/** @var \MJ\SupportTicket\Service\Ticket\Editor $editor */
		$editor = $this->service('MJ\SupportTicket:Ticket\Editor', $ticket);

		$quickUpdate = $this->filter('quick_update', 'bool');
		if(!$quickUpdate){
			$prefixId = $this->filter('prefix_id', 'uint');
			if ($prefixId != $ticket->prefix_id && !$ticket->Department->isPrefixUsable($prefixId))
			{
				$prefixId = 0; // not usable, just blank it out
			}
			$editor->setPrefix($prefixId);
			if($title = $this->filter('title', 'str')){
				$editor->setTitle($title);
			}
		}

		$urgency = $this->filter('urgency', 'uint');
		$editor->setUrgency($urgency);

		if($ticket->canEditTicketDepartment()){
			$departmentRepo = $this->getDepartmentRepo();
			$departments = $departmentRepo->getOpenableDepartments();
			$departmentId = $this->filter('department_id', 'uint');
			if($departments && !empty($departments[$departmentId])){
				$editor->setDepartment($departments[$departmentId]);
			}
		}

		if($ticket->canEditTicketStatus()){
			$editor->setStatus($this->filter('ticket_status_id', 'uint'));
		}

		$unassign = $this->filter('unassign', 'bool');
		if ($unassign && $ticket->canAssignSupportTicket())
		{
			$ticket->assigned_user_id = 0;
		}

		if($ticket->canChangeOwner()){
			$changeOwner = $this->filter('change_owner', 'bool');
			if($changeOwner){
				$targetType = $this->filter('target_type', 'str');
				$userId = 0;
				$username = '';
				$email = '';
				if($targetType == 'member'){
					$username = $this->filter('target_member', 'str');
					$user = $this->finder('XF:User')
						->where('username', $username)
						->fetchOne();
					if(!$user){
						throw $this->errorException(\XF::phrase('requested_user_not_found'));
					}
					$userId = $user->user_id;
					$username = $user->username;
					$email = $user->email;
				}else{
					$username = $this->filter('guest_username', 'str');
					$email = $this->filter('guest_email', 'str');
					if(!$username || !$email){
						throw $this->errorException(\XF::phrase('mjst_you_must_enter_name_and_email_for_guest'));
					}
				}

				if (!$editor->setEmail($email, $error))
				{
					throw $this->exception($this->error($error));
				}

				$editor->setOwner($userId, $username);
			}
		}

		$customFields = $this->filter('custom_fields', 'array');
		$editor->setCustomFields($customFields);

		return $editor;
	}

	public function actionEdit(ParameterBag $params)
	{
		$ticket = $this->assertViewableTicket($params->support_ticket_id);
		if (!$ticket->canEdit($error))
		{
			return $this->noPermission($error);
		}
		$department = $ticket->Department;

		$noInlineMod = $this->filter('_xfNoInlineMod', 'bool');
		$departmentName = $this->filter('_xfDepartmentName', 'bool');

		if ($this->isPost())
		{
			$editor = $this->setupTicketEdit($ticket);

			if (!$editor->validate($errors))
			{
				return $this->error($errors);
			}

			$editor->save();

			if ($this->filter('_xfWithData', 'bool') && $this->filter('_xfInlineEdit', 'bool'))
			{
				$viewParams = [
					'ticket' => $ticket,
					'department' => $department,

					'noInlineMod' => $noInlineMod,
					'departmentName' => $departmentName
				];
				$reply = $this->view('MJ\SupportTicket:Ticket\EditInline', 'mjst_ticket_edit_new_ticket', $viewParams);
				$reply->setJsonParam('message', \XF::phrase('your_changes_have_been_saved'));
				return $reply;
			}
			return $this->redirect($this->buildLink('support-tickets', $ticket));
		}
		else
		{
			$prefix = $ticket->Prefix;
			$prefixes = $department->getUsablePrefixes($prefix);

			$departmentRepo = $this->getDepartmentRepo();
			$departments = $departmentRepo->getOpenableDepartments();

			$ticketStatuses = $this->repository('MJ\SupportTicket:TicketStatus')->findTicketStatusForList()->fetch();

			$viewParams = [
				'ticket'         => $ticket,
				'department'     => $department,
				'prefixes'       => $prefixes,

				'departments'    => $departments,
				'ticketStatuses' => $ticketStatuses,

				'noInlineMod'    => $noInlineMod,
				'departmentName' => $departmentName
			];
			return $this->view('MJ\SupportTicket:Ticket\Edit', 'mjst_ticket_edit', $viewParams);
		}
	}

	public function actionQuickClose(ParameterBag $params)
	{
		$this->assertPostOnly();

		$ticket = $this->assertViewableTicket($params->support_ticket_id);

		/** @var \XF\Service\Ticket\Editor $editor */
		$editor = $this->service('MJ\SupportTicket:Ticket\Editor', $ticket);

		if ($ticket->discussion_open)
		{
			$editor->setDiscussionOpen(false);
			$text = \XF::phrase('mjst_open_ticket');
		}
		else
		{
			$editor->setDiscussionOpen(true);
			$text = \XF::phrase('mjst_close_ticket');
		}

		if (!$editor->validate($errors))
		{
			return $this->error($errors);
		}

		$editor->save();

		$reply = $this->redirect($this->getDynamicRedirect());
		$reply->setJsonParams([
			'text' => $text,
			'discussion_open' => $ticket->discussion_open
		]);
		return $reply;
	}

	public function actionUnassign(ParameterBag $params)
	{
		$ticket = $this->assertViewableTicket($params->support_ticket_id);
		if (!$ticket->canAssignSupportTicket($error))
		{
			return $this->noPermission($error);
		}

		$ticket->assigned_user_id = 0;
		$ticket->save();

		return $this->redirect($this->buildLink('support-tickets', $ticket));
	}

	public function actionAssign(ParameterBag $params)
	{
		$ticket = $this->assertViewableTicket($params->support_ticket_id);
		if (!$ticket->canAssignSupportTicket($error))
		{
			return $this->noPermission($error);
		}

		if ($this->isPost())
		{
			/** @var \XF\Service\Ticket\Assigner $assigner */
			$assigner = $this->service('MJ\SupportTicket:Ticket\Assigner', $ticket);

			$username = $this->filter('username', 'str');
			$user = $this->finder('XF:User')
				->where('username', $username)
				->fetchOne();
			if(!$user){
				throw $this->errorException(\XF::phrase('requested_user_not_found'));
			}

			$assigner->setUser($user);

			$assigner->assign();
			return $this->redirect($this->buildLink('support-tickets', $ticket));
		}
		else
		{
			$viewParams = [
				'ticket' => $ticket,
				'department' => $ticket->Department
			];
			return $this->view('MJ\SupportTicket:Ticket\Delete', 'mjst_ticket_assign', $viewParams);
		}
	}

	public function actionDelete(ParameterBag $params)
	{
		$ticket = $this->assertViewableTicket($params->support_ticket_id);
		if (!$ticket->canDelete($error))
		{
			return $this->noPermission($error);
		}

		if ($this->isPost())
		{
			$reason = $this->filter('reason', 'str');

			/** @var \XF\Service\Ticket\Deleter $deleter */
			$deleter = $this->service('MJ\SupportTicket:Ticket\Deleter', $ticket);

			if ($this->filter('starter_alert', 'bool'))
			{
				$deleter->setSendAlert(true, $this->filter('starter_alert_reason', 'str'));
			}

			$deleter->delete($reason);

			$this->plugin('XF:InlineMod')->clearIdFromCookie('support_ticket', $ticket->support_ticket_id);

			return $this->redirect($this->buildLink('support-tickets/departments', $ticket->Department));
		}
		else
		{
			$viewParams = [
				'ticket' => $ticket,
				'department' => $ticket->Department
			];
			return $this->view('MJ\SupportTicket:Ticket\Delete', 'mjst_ticket_delete', $viewParams);
		}
	}

	/**
	 * @param \MJ\SupportTicket\Entity\Ticket $ticket
	 * @param \MJ\SupportTicket\Entity\Department $department
	 *
	 * @return \XF\Service\Ticket\Mover
	 */
	protected function setupTicketMove(\MJ\SupportTicket\Entity\Ticket $ticket, \MJ\SupportTicket\Entity\Department $department)
	{
		$options = $this->filter([
			'notify_watchers'      => 'bool',
			'starter_alert'        => 'bool',
			'starter_alert_reason' => 'str',
			'prefix_id'            => 'uint'
		]);

		/** @var \XF\Service\Ticket\Mover $mover */
		$mover = $this->service('MJ\SupportTicket:Ticket\Mover', $ticket);

		if ($options['starter_alert'])
		{
			$mover->setSendAlert(true, $options['starter_alert_reason']);
		}

		if ($options['notify_watchers'])
		{
			$mover->setNotifyWatchers();
		}

		if ($options['prefix_id'] !== null)
		{
			$mover->setPrefix($options['prefix_id']);
		}

		$mover->addExtraSetup(function($ticket, $department)
		{
			$ticket->title = $this->filter('title', 'str');
		});

		return $mover;
	}

	public function actionMove(ParameterBag $params)
	{
		$ticket = $this->assertViewableTicket($params->support_ticket_id);
		if (!$ticket->canMove($error))
		{
			return $this->noPermission($error);
		}
		$department = $ticket->Department;

		if ($this->isPost())
		{
			$targetDepartmentId = $this->filter('target_department_id', 'uint');

			/** @var \MJ\SupportTicket\Entity\Department $department */
			$targetDepartment = $this->app()->em()->find('MJ\SupportTicket:Department', $targetDepartmentId);
			if (!$targetDepartment || !$targetDepartment->canView())
			{
				return $this->error(\XF::phrase('mjst_requested_department_not_found'));
			}

			$this->setupTicketMove($ticket, $targetDepartment)->move($targetDepartment);

			return $this->redirect($this->buildLink('support-tickets', $ticket));
		}
		else
		{
			/** @var \MJ\SupportTicket\Repository\Department $departmentRepo */
			$departmentRepo = $this->app()->repository('MJ\SupportTicket:Department');
			$departments = $departmentRepo->getFullDepartmentList()->filterViewable();

			$viewParams = [
				'ticket'      => $ticket,
				'department'  => $department,
				'prefixes'    => $department->getUsablePrefixes(),
				'departments' => $departments
			];
			return $this->view('MJ\SupportTicket:Ticket\Move', 'mjst_ticket_move', $viewParams);
		}
	}

	public function actionWatch(ParameterBag $params)
	{
		$visitor = \XF::visitor();
		if (!$visitor->user_id)
		{
			return $this->noPermission();
		}

		$ticket = $this->assertViewableTicket($params->support_ticket_id);
		if (!$ticket->canWatch($error))
		{
			return $this->noPermission($error);
		}

		if ($this->isPost())
		{
			if ($this->filter('stop', 'bool'))
			{
				$newState = 'delete';
			}
			else if ($this->filter('email_subscribe', 'bool'))
			{
				$newState = 'watch_email';
			}
			else
			{
				$newState = 'watch_no_email';
			}

			/** @var \XF\Repository\TicketWatch $watchRepo */
			$watchRepo = $this->repository('MJ\SupportTicket:TicketWatch');
			$watchRepo->setWatchState($ticket, $visitor, $newState);

			$redirect = $this->redirect($this->buildLink('support-tickets', $ticket));
			$redirect->setJsonParam('switchKey', $newState == 'delete' ? 'watch' : 'unwatch');
			return $redirect;
		}
		else
		{
			$viewParams = [
				'ticket' => $ticket,
				'isWatched' => !empty($ticket->Watch[$visitor->user_id]),
				'department' => $ticket->Department
			];
			return $this->view('MJ\SupportTicket:Ticket\Watch', 'mjst_ticket_watch', $viewParams);
		}
	}

	public function actionModeratorActions(ParameterBag $params)
	{
		$ticket = $this->assertViewableTicket($params->support_ticket_id);
		if (!$ticket->canViewModeratorLogs($error))
		{
			return $this->noPermission($error);
		}

		$breadcrumbs = $ticket->getBreadcrumbs();
		$prefix = $this->app()->templater()->fn('prefix', ['support_ticket', $ticket, 'escaped']);
		$title = $prefix . $ticket->title;

		$this->request()->set('page', $params->page);

		/** @var \XF\ControllerPlugin\ModeratorLog $modLogPlugin */
		$modLogPlugin = $this->plugin('XF:ModeratorLog');
		return $modLogPlugin->actionModeratorActions(
			$ticket,
			['support-tickets/moderator-actions', $ticket],
			$title, $breadcrumbs
		);
	}

	/**
	 * @param $ticketId
	 * @param array $extraWith
	 *
	 * @return \MJ\SupportTicket\Entity\Ticket
	 *
	 * @throws \XF\Mvc\Reply\Exception
	 */
	protected function assertViewableTicket($ticketId, array $extraWith = [], $throwViewError = true)
	{
		$visitor = \XF::visitor();

		$extraWith[] = 'Department';
		$extraWith[] = 'Department.Permissions|' . $visitor->permission_combination_id;
		if ($visitor->user_id)
		{
			$extraWith[] = 'Read|' . $visitor->user_id;
		}

		/** @var \MJ\SupportTicket\Entity\Ticket $ticket */
		$ticket = $this->em()->find('MJ\SupportTicket:Ticket', $ticketId, $extraWith);
		if (!$ticket)
		{
			throw $this->exception($this->notFound(\XF::phrase('mjst_requested_ticket_not_found')));
		}

		if(!$ticket->user_id){
			if(!$ticket->canViewGuestTicket() && $throwViewError){
				throw $this->exception($this->noPermission($error));
			}
		}else{
			if (!$ticket->canView($error))
			{
				throw $this->exception($this->noPermission($error));
			}
		}

		$this->setContentKey('ticket-' . $ticket->support_ticket_id);

		return $ticket;
	}

	protected function getReplyAttachmentData(\MJ\SupportTicket\Entity\Ticket $ticket, $forceAttachmentHash = null)
	{
		/** @var \MJ\SupportTicket\Entity\Department $department */
		$department = $ticket->Department;

		if ($department && $department->canUploadAndManageAttachments())
		{
			if ($forceAttachmentHash !== null)
			{
				$attachmentHash = $forceAttachmentHash;
			}
			else
			{
				$attachmentHash = $ticket->draft_reply->attachment_hash;
			}

			/** @var \XF\Repository\Attachment $attachmentRepo */
			$attachmentRepo = $this->repository('XF:Attachment');
			return $attachmentRepo->getEditorData('support_ticket_message', $ticket, $attachmentHash);
		}
		else
		{
			return null;
		}
	}

	protected function canUpdateSessionActivity($action, ParameterBag $params, AbstractReply &$reply, &$viewState)
	{
		if (strtolower($action) == 'addreply')
		{
			$viewState = 'valid';
			return true;
		}
		return parent::canUpdateSessionActivity($action, $params, $reply, $viewState);
	}

	public static function getActivityDetails(array $activities)
	{
		return self::getActivityDetailsForContent(
			$activities,
			\XF::phrase('mjst_viewing_ticket'),
			'support_ticket_id',
			function(array $ids)
			{
				$tickets = \XF::em()->findByIds(
					'MJ\SupportTicket:Ticket',
					$ids,
					['Department', 'Department.Permissions|' . \XF::visitor()->permission_combination_id]
				);

				$router = \XF::app()->router('public');
				$data = [];

				foreach ($tickets->filterViewable() as $id => $ticket)
				{
					$data[$id] = [
						'title' => $ticket->title,
						'url' => $router->buildLink('support-tickets', $ticket)
					];
				}

				return $data;
			}
		);
	}

	protected function assertViewableDepartment($departmentId, array $extraWith = [])
	{
		$visitor = \XF::visitor();

		$extraWith[] = 'Permissions|' . $visitor->permission_combination_id;
		if ($visitor->user_id)
		{
			//$extraWith[] = 'Read|' . $visitor->user_id;
		}

		/** @var \MJ\SupportTicket\Entity\Ticket $ticket */
		$department = $this->em()->find('MJ\SupportTicket:Department', $departmentId, $extraWith);
		if (!$department)
		{
			throw $this->exception($this->notFound(\XF::phrase('mjst_requested_ticket_not_found')));
		}

		if (!$department->canView($error))
		{
			throw $this->exception($this->noPermission($error));
		}

		return $department;
	}

	/**
	 * @return \MJ\SupportTicket\Repository\Department
	 */
	protected function getDepartmentRepo()
	{
		return $this->repository('MJ\SupportTicket:Department');
	}

	/**
	 * @return \XF\Repository\Ticket
	 */
	protected function getTicketRepo()
	{
		return $this->repository('MJ\SupportTicket:Ticket');
	}

	/**
	 * @return \XF\Repository\Message
	 */
	protected function getMessageRepo()
	{
		return $this->repository('MJ\SupportTicket:TicketMessage');
	}
}
