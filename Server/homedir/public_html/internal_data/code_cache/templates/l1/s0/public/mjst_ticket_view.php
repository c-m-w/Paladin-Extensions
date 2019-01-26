<?php
// FROM HASH: 8d4feda1495f1dc3917079b89fa1e845
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->fn('prefix', array('support_ticket', $__vars['ticket'], 'escaped', ), true) . $__templater->escape($__vars['ticket']['full_title']));
	$__templater->pageParams['pageNumber'] = $__vars['page'];
	$__finalCompiled .= '
';
	$__templater->pageParams['pageH1'] = $__templater->preEscaped('<span class="urgency urgency-' . $__templater->escape($__vars['ticket']['urgency']) . '"><i class="fa fa-flag" aria-hidden="true"></i></span> ' . $__templater->fn('prefix', array('support_ticket', $__vars['ticket'], ), true) . $__templater->filter($__templater->method($__vars['ticket'], 'getFullTitle', array(true, )), array(array('raw', array()),), true));
	$__finalCompiled .= '

';
	$__templater->includeCss('mjst.less');
	$__finalCompiled .= '
';
	$__templater->pageParams['pageDescription'] = $__templater->preEscaped('
	<ul class="listInline listInline--bullet">
		<li>
			<i class="fa fa-user" aria-hidden="true" title="' . $__templater->filter('Ticket sumitter', array(array('for_attr', array()),), true) . '"></i>
			<span class="u-srOnly">' . 'Ticket sumitter' . '</span>

			' . $__templater->fn('username_link', array($__vars['ticket']['User'], false, array(
		'defaultname' => $__vars['ticket']['username'],
		'class' => 'u-concealed',
	))) . '
		</li>
		<li>
			<i class="fa fa-clock-o" aria-hidden="true" title="' . $__templater->filter('Start date', array(array('for_attr', array()),), true) . '"></i>
			<span class="u-srOnly">' . 'Start date' . '</span>

			<a href="' . $__templater->fn('link', array('support-tickets', $__vars['ticket'], ), true) . '" class="u-concealed">' . $__templater->fn('date_dynamic', array($__vars['ticket']['open_date'], array(
	))) . '</a>
		</li>
	</ul>
');
	$__templater->pageParams['pageDescriptionMeta'] = false;
	$__finalCompiled .= '

';
	$__vars['fpSnippet'] = $__templater->fn('snippet', array($__vars['firstMessage']['message'], 0, array('stripBbCode' => true, ), ), false);
	$__finalCompiled .= '

' . $__templater->callMacro('metadata_macros', 'metadata', array(
		'description' => $__vars['fpSnippet'],
		'shareUrl' => $__templater->fn('link', array('canonical:support-tickets', $__vars['ticket'], ), false),
		'canonicalUrl' => $__templater->fn('link', array('canonical:support-tickets', $__vars['ticket'], array('page' => $__vars['page'], ), ), false),
	), $__vars) . '

' . '

';
	if ($__vars['pendingApproval']) {
		$__finalCompiled .= '
	<div class="blockMessage blockMessage--important">' . 'Your content has been submitted and will be displayed pending approval by a moderator.' . '</div>
';
	}
	$__finalCompiled .= '

' . $__templater->callMacro('mjst_department_macros', 'department_page_options', array(
		'department' => $__vars['department'],
		'ticket' => $__vars['ticket'],
	), $__vars) . '

';
	$__templater->breadcrumbs($__templater->method($__vars['department'], 'getBreadcrumbs', array()));
	$__finalCompiled .= '

';
	if ($__vars['canInlineMod'] OR $__templater->method($__vars['ticket'], 'canUseInlineModeration', array())) {
		$__finalCompiled .= '
	';
		$__templater->includeJs(array(
			'src' => 'xf/inline_mod.js',
			'min' => '1',
		));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

' . $__templater->callMacro('lightbox_macros', 'setup', array(
		'canViewAttachments' => $__templater->method($__vars['ticket'], 'canViewAttachments', array()),
	), $__vars) . '

' . $__templater->callAdsMacro('ticket_view_above_messages', array(
		'ticket' => $__vars['ticket'],
	), $__vars) . '

<div class="block block--messages" data-xf-init="' . ($__vars['canInlineMod'] ? 'inline-mod' : '') . '" data-type="support_ticket_message" data-href="' . $__templater->fn('link', array('inline-mod', ), true) . '">

	<div class="block-outer">';
	$__compilerTemp1 = '';
	$__compilerTemp2 = '';
	$__compilerTemp2 .= '
					';
	if ($__vars['canInlineMod']) {
		$__compilerTemp2 .= '
						' . $__templater->callMacro('inline_mod_macros', 'button', array(), $__vars) . '
					';
	}
	$__compilerTemp2 .= '
					';
	if ($__templater->method($__vars['ticket'], 'canClose', array()) AND (!$__templater->method($__vars['ticket'], 'isClosed', array()))) {
		$__compilerTemp2 .= '
						' . $__templater->button('
							' . 'Close' . '
						', array(
			'href' => $__templater->fn('link', array('support-tickets/close', $__vars['ticket'], ), false),
			'class' => 'button--link',
			'overlay' => 'true',
		), '', array(
		)) . '
					';
	}
	$__compilerTemp2 .= '
					';
	if ($__vars['xf']['visitor']['user_id'] AND $__templater->method($__vars['ticket'], 'isUnread', array())) {
		$__compilerTemp2 .= '
						' . $__templater->button('
								' . 'Jump to new' . '
						', array(
			'href' => ($__vars['firstUnread'] ? ('#message-' . $__vars['firstUnread']['message_id']) : $__templater->fn('link', array('support-tickets/unread', $__vars['ticket'], array('new' => 1, ), ), false)),
			'class' => 'button--link',
			'data-xf-click' => 'scroll-to',
			'data-silent' => 'true',
		), '', array(
		)) . '
					';
	}
	$__compilerTemp2 .= '
					';
	if ($__templater->method($__vars['ticket'], 'canWatch', array())) {
		$__compilerTemp2 .= '
						';
		$__compilerTemp3 = '';
		if ($__vars['ticket']['Watch'][$__vars['xf']['visitor']['user_id']]) {
			$__compilerTemp3 .= '
								' . 'Unwatch' . '
							';
		} else {
			$__compilerTemp3 .= '
								' . 'Watch' . '
							';
		}
		$__compilerTemp2 .= $__templater->button('
							' . $__compilerTemp3 . '
						', array(
			'href' => $__templater->fn('link', array('support-tickets/watch', $__vars['ticket'], ), false),
			'class' => 'button--link',
			'data-xf-click' => 'switch-overlay',
			'data-sk-watch' => 'Watch',
			'data-sk-unwatch' => 'Unwatch',
		), '', array(
		)) . '
					';
	}
	$__compilerTemp2 .= '

					';
	$__compilerTemp4 = '';
	$__compilerTemp4 .= '
										' . '
										';
	if ($__templater->method($__vars['ticket'], 'canAssignSupportTicket', array())) {
		$__compilerTemp4 .= '
											<a href="' . $__templater->fn('link', array('support-tickets/assign', $__vars['ticket'], ), true) . '" data-xf-click="overlay" class="menu-linkRow">' . 'Assign ticket' . '</a>
										';
	}
	$__compilerTemp4 .= '
										';
	if ($__templater->method($__vars['ticket'], 'canEdit', array())) {
		$__compilerTemp4 .= '
											<a href="' . $__templater->fn('link', array('support-tickets/edit', $__vars['ticket'], ), true) . '" data-xf-click="overlay" class="menu-linkRow">' . 'Edit ticket' . '</a>
										';
	}
	$__compilerTemp4 .= '
										';
	if ($__templater->method($__vars['ticket'], 'canDelete', array())) {
		$__compilerTemp4 .= '
											<a href="' . $__templater->fn('link', array('support-tickets/delete', $__vars['ticket'], ), true) . '" data-xf-click="overlay" class="menu-linkRow">' . 'Delete ticket' . '</a>
										';
	}
	$__compilerTemp4 .= '
										';
	if ($__templater->method($__vars['ticket'], 'canMove', array())) {
		$__compilerTemp4 .= '
											<a href="' . $__templater->fn('link', array('support-tickets/move', $__vars['ticket'], ), true) . '" data-xf-click="overlay" class="menu-linkRow">' . 'Move ticket' . '</a>
										';
	}
	$__compilerTemp4 .= '
										';
	if ($__templater->method($__vars['ticket'], 'canViewModeratorLogs', array())) {
		$__compilerTemp4 .= '
											<a href="' . $__templater->fn('link', array('support-tickets/moderator-actions', $__vars['ticket'], ), true) . '" data-xf-click="overlay" class="menu-linkRow">' . 'Moderator actions' . '</a>
										';
	}
	$__compilerTemp4 .= '
										';
	if ($__templater->method($__vars['ticket'], 'canViewGuestTicket', array()) AND (!$__vars['ticket']['user_id'])) {
		$__compilerTemp4 .= '
											<a href="' . $__templater->fn('link', array('support-tickets/password', $__vars['ticket'], ), true) . '" data-xf-click="overlay" class="menu-linkRow">' . 'Guest password' . '</a>
										';
	}
	$__compilerTemp4 .= '
										' . '
										';
	if ($__templater->method($__vars['ticket'], 'canUseInlineModeration', array())) {
		$__compilerTemp4 .= '
											<div class="menu-footer"
												data-xf-init="inline-mod"
												data-type="support_ticket"
												data-href="' . $__templater->fn('link', array('inline-mod', ), true) . '"
												data-toggle=".js-ticketInlineModToggle">
												' . $__templater->formCheckBox(array(
		), array(array(
			'class' => 'js-ticketInlineModToggle',
			'value' => $__vars['ticket']['support_ticket_id'],
			'label' => 'Select for moderation',
			'_type' => 'option',
		))) . '
											</div>
										';
	}
	$__compilerTemp4 .= '
										' . '
									';
	if (strlen(trim($__compilerTemp4)) > 0) {
		$__compilerTemp2 .= '
						<div class="buttonGroup-buttonWrapper">
							' . $__templater->button('&#8226;&#8226;&#8226;', array(
			'class' => 'button--link menuTrigger',
			'data-xf-click' => 'menu',
			'aria-expanded' => 'false',
			'aria-haspopup' => 'true',
			'title' => $__templater->filter('More options', array(array('for_attr', array()),), false),
		), '', array(
		)) . '
							<div class="menu" data-menu="menu" aria-hidden="true">
								<div class="menu-content">
									<h4 class="menu-header">' . 'More options' . '</h4>
									' . $__compilerTemp4 . '
								</div>
							</div>
						</div>
					';
	}
	$__compilerTemp2 .= '
				';
	if (strlen(trim($__compilerTemp2)) > 0) {
		$__compilerTemp1 .= '
			<div class="block-outer-opposite">
				<div class="buttonGroup">
				' . $__compilerTemp2 . '
				</div>
			</div>
		';
	}
	$__finalCompiled .= trim('
		' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => ($__vars['ticket']['reply_count'] + 1),
		'link' => 'support-tickets',
		'data' => $__vars['ticket'],
		'wrapperclass' => 'block-outer-main',
		'perPage' => $__vars['perPage'],
	))) . '
		' . $__compilerTemp1 . '
	') . '</div>

	<div class="block-outer js-ticketStatusField">';
	$__compilerTemp5 = '';
	$__compilerTemp6 = '';
	$__compilerTemp6 .= '
					' . $__templater->callMacro('custom_fields_macros', 'custom_fields_view', array(
		'type' => 'tickets',
		'group' => 'ticket_status',
		'onlyInclude' => $__vars['department']['field_cache'],
		'set' => $__vars['ticket']['custom_fields'],
		'wrapperClass' => 'blockStatus-message',
	), $__vars) . '
				';
	if (strlen(trim($__compilerTemp6)) > 0) {
		$__compilerTemp5 .= '
			<div class="blockStatus blockStatus--info">
				' . $__compilerTemp6 . '
			</div>
		';
	}
	$__finalCompiled .= trim('
		' . $__compilerTemp5 . '
	') . '</div>

	<div class="block-container lbContainer"
		data-xf-init="lightbox' . ($__vars['xf']['options']['selectQuotable'] ? ' select-to-quote' : '') . '"
		data-message-selector=".js-message"
		data-lb-id="ticket-' . $__templater->escape($__vars['ticket']['support_ticket_id']) . '"
		data-lb-universal="' . $__templater->escape($__vars['xf']['options']['lightBoxUniversal']) . '">

		<div class="block-body js-replyNewMessageContainer">
			';
	if ($__templater->isTraversable($__vars['messages'])) {
		foreach ($__vars['messages'] AS $__vars['message']) {
			$__finalCompiled .= '
				';
			if ($__vars['message']['message_state'] == 'deleted') {
				$__finalCompiled .= '
					' . $__templater->callMacro('mjst_message_macros', 'message_deleted', array(
					'message' => $__vars['message'],
					'ticket' => $__vars['ticket'],
				), $__vars) . '
				';
			} else {
				$__finalCompiled .= '
					' . $__templater->callMacro('mjst_message_macros', 'message', array(
					'message' => $__vars['message'],
					'ticket' => $__vars['ticket'],
				), $__vars) . '
				';
			}
			$__finalCompiled .= '
			';
		}
	}
	$__finalCompiled .= '
		</div>
	</div>

	';
	$__compilerTemp7 = '';
	$__compilerTemp7 .= '
				' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => ($__vars['ticket']['reply_count'] + 1),
		'link' => 'support-tickets',
		'data' => $__vars['ticket'],
		'wrapperclass' => 'block-outer-main',
		'perPage' => $__vars['perPage'],
	))) . '
				' . $__templater->fn('show_ignored', array(array(
		'wrapperclass' => 'block-outer-opposite',
	))) . '
				';
	if (!$__templater->method($__vars['ticket'], 'canReply', array())) {
		$__compilerTemp7 .= '
					<div class="block-outer-opposite">
						';
		if ($__vars['xf']['visitor']['user_id']) {
			$__compilerTemp7 .= '
							<span class="button is-disabled">
								' . 'You have insufficient privileges to reply here.' . '
								<!-- this is not interactive so shouldn\'t be a button element -->
							</span>
						';
		} else {
			$__compilerTemp7 .= '
							' . $__templater->button('
								' . 'You must log in or register to reply here.' . '
							', array(
				'href' => $__templater->fn('link', array('login', ), false),
				'class' => 'button--link',
				'overlay' => 'true',
			), '', array(
			)) . '
						';
		}
		$__compilerTemp7 .= '
					</div>
				';
	}
	$__compilerTemp7 .= '
			';
	if (strlen(trim($__compilerTemp7)) > 0) {
		$__finalCompiled .= '
		<div class="block-outer block-outer--after">
			' . $__compilerTemp7 . '
		</div>
	';
	}
	$__finalCompiled .= '
</div>

' . $__templater->callAdsMacro('ticket_view_below_messages', array(
		'ticket' => $__vars['ticket'],
	), $__vars) . '

';
	if ($__templater->method($__vars['ticket'], 'canReply', array())) {
		$__finalCompiled .= '
	';
		$__templater->includeJs(array(
			'src' => 'xf/message.js',
			'min' => '1',
		));
		$__vars['lastMessage'] = $__templater->filter($__vars['messages'], array(array('last', array()),), false);
		$__finalCompiled .= $__templater->form('

		' . '' . '
		' . '' . '

		<div class="block-container">
			<div class="block-body">
				' . $__templater->callMacro('quick_reply_macros', 'body', array(
			'message' => $__vars['ticket']['draft_reply']['message'],
			'attachmentData' => $__vars['attachmentData'],
			'forceHash' => $__vars['ticket']['draft_reply']['attachment_hash'],
			'messageSelector' => '.js-message',
			'multiQuoteHref' => $__templater->fn('link', array('support-tickets/multi-quote', $__vars['ticket'], ), false),
			'multiQuoteStorageKey' => 'multiQuoteticket',
			'lastDate' => $__vars['lastMessage']['message_date'],
			'lastKnownDate' => $__vars['ticket']['last_message_date'],
		), $__vars) . '
			</div>
		</div>
	', array(
			'action' => $__templater->fn('link', array('support-tickets/add-reply', $__vars['ticket'], ), false),
			'ajax' => 'true',
			'draft' => $__templater->fn('link', array('support-tickets/draft', $__vars['ticket'], ), false),
			'class' => 'block js-quickReply',
			'data-xf-init' => 'attachment-manager quick-reply' . ($__templater->method($__vars['xf']['visitor'], 'isShownCaptcha', array()) ? ' guest-captcha' : ''),
			'data-message-container' => '.js-replyNewMessageContainer',
			'data-preview-url' => $__templater->fn('link', array('support-tickets/reply-preview', $__vars['ticket'], array('quick_reply' => 1, ), ), false),
		)) . '
';
	}
	$__finalCompiled .= '

';
	$__compilerTemp8 = '';
	if (($__vars['xf']['options']['mjstQuickUpdate'] AND $__templater->method($__vars['ticket'], 'canEdit', array()))) {
		$__compilerTemp8 .= '
			';
		$__compilerTemp9 = '';
		if ($__templater->method($__vars['ticket'], 'canEditTicketDepartment', array()) AND $__vars['departments']) {
			$__compilerTemp9 .= '
						' . $__templater->callMacro('mjst_ticket_edit_macros', 'department', array(
				'departments' => $__vars['departments'],
				'ticket' => $__vars['ticket'],
				'rowtype' => 'fullWidth',
			), $__vars) . '
					';
		} else {
			$__compilerTemp9 .= '
						' . $__templater->formRow('
							' . $__templater->escape($__vars['ticket']['Department']['title']) . '
						', array(
				'rowtype' => 'fullWidth',
				'label' => 'Department',
			)) . '
					';
		}
		$__compilerTemp10 = '';
		if ($__vars['ticket']['assigned_user_id'] AND ($__templater->method($__vars['department'], 'canAssignTickets', array()) OR $__templater->method($__vars['department'], 'canViewAssignedStaff', array()))) {
			$__compilerTemp10 .= '
						' . $__templater->formRow('
							' . $__templater->escape($__vars['ticket']['AssignedUser']['username']) . '
						', array(
				'rowtype' => 'fullWidth',
				'label' => 'Assigned to',
			)) . '
						';
			if ($__templater->method($__vars['department'], 'canAssignTickets', array())) {
				$__compilerTemp10 .= '
							' . $__templater->formCheckBoxRow(array(
				), array(array(
					'name' => 'unassign',
					'value' => '1',
					'label' => 'Unassign',
					'_type' => 'option',
				)), array(
					'label' => '',
					'rowtype' => 'fullWidth',
				)) . '
						';
			}
			$__compilerTemp10 .= '
					';
		}
		$__compilerTemp11 = '';
		if ($__templater->method($__vars['ticket'], 'canEditTicketStatus', array()) AND $__vars['ticketStatuses']) {
			$__compilerTemp11 .= '
						' . $__templater->callMacro('mjst_ticket_edit_macros', 'status', array(
				'ticketStatuses' => $__vars['ticketStatuses'],
				'ticket' => $__vars['ticket'],
				'rowtype' => 'fullWidth',
			), $__vars) . '
					';
		} else {
			$__compilerTemp11 .= '
						' . $__templater->formRow('
							<span class="mjstStatus mjstStatus--style' . $__templater->escape($__vars['ticket']['ticket_status_id']) . '">' . $__templater->escape($__vars['ticket']['Status']['title']) . '</span>
						', array(
				'rowtype' => 'fullWidth',
				'label' => 'Status',
			)) . '
					';
		}
		$__compilerTemp8 .= $__templater->form('
				<div class="block-body js-prefixListenContainer">
					' . $__templater->formRow('
						' . $__templater->fn('date_dynamic', array($__vars['ticket']['open_date'], array(
		))) . '
					', array(
			'rowtype' => 'fullWidth',
			'label' => 'Open date',
		)) . '
					' . $__compilerTemp9 . '
					' . $__compilerTemp10 . '
					' . $__compilerTemp11 . '

					' . $__templater->callMacro('mjst_ticket_edit_macros', 'urgency', array(
			'ticket' => $__vars['ticket'],
			'rowtype' => 'fullWidth',
		), $__vars) . '

					' . $__templater->callMacro('mjst_ticket_edit_macros', 'custom_fields', array(
			'ticket' => $__vars['ticket'],
			'department' => $__vars['department'],
			'rowtype' => 'fullWidth',
		), $__vars) . '
				</div>
				<div class="block-footer">
					<span class="block-footer-controls">
						' . $__templater->formHiddenVal('quick_update', '1', array(
		)) . '
						<input type="submit" value="' . 'Update' . '" accesskey="s" class="button primary" />
						' . $__templater->formHiddenVal('quick_update', '1', array(
		)) . '
					</span>
				</div>
			', array(
			'action' => $__templater->fn('link', array('support-tickets/edit', $__vars['ticket'], ), false),
			'ajax' => 'true',
		)) . '
			';
	} else {
		$__compilerTemp8 .= '
				<div class="block-body block-row">
					<dl class="pairs pairs--justified pairs--plainLabel">
						<dt>' . 'Open date' . '</dt>
						<dd>' . $__templater->fn('date_dynamic', array($__vars['ticket']['open_date'], array(
		))) . '</dd>
					</dl>
					<dl class="pairs pairs--justified pairs--plainLabel">
						<dt>' . 'Department' . '</dt>
						<dd>' . $__templater->escape($__vars['ticket']['Department']['title']) . '</dd>
					</dl>
					';
		if ($__vars['ticket']['assigned_user_id'] AND ($__templater->method($__vars['department'], 'canAssignTickets', array()) OR $__templater->method($__vars['department'], 'canViewAssignedStaff', array()))) {
			$__compilerTemp8 .= '
						<dl class="pairs pairs--justified pairs--plainLabel">
							<dt>' . 'Assigned to' . '</dt>
							<dd>' . $__templater->escape($__vars['ticket']['AssignedUser']['username']) . '</dd>
						</dl>
					';
		}
		$__compilerTemp8 .= '
					<dl class="pairs pairs--justified pairs--plainLabel">
						<dt>' . 'Status' . '</dt>
						<dd><span class="mjstStatus mjstStatus--style' . $__templater->escape($__vars['ticket']['ticket_status_id']) . '">' . $__templater->escape($__vars['ticket']['Status']['title']) . '</span></dd>
					</dl>
					<dl class="pairs pairs--justified pairs--plainLabel">
						<dt>' . 'Priority' . '</dt>
						<dd><span class="mjstPrioriy mjstPrioriy--' . $__templater->escape($__vars['ticket']['urgency']) . '">' . $__templater->escape($__vars['ticket']['urgency_title']) . '</span></dd>
					</dl>
					' . $__templater->callMacro('custom_fields_macros', 'custom_fields_view', array(
			'type' => 'tickets',
			'group' => 'ticket_info',
			'onlyInclude' => $__vars['ticket']['Department']['field_cache'],
			'set' => $__vars['ticket']['custom_fields'],
			'wrapperClass' => 'ticket-fields ticket-fields--ticket_info',
		), $__vars) . '
				</div>
			';
	}
	$__compilerTemp12 = '';
	if (!$__vars['ticket']['user_id']) {
		$__compilerTemp12 .= '
					<dl class="pairs pairs--justified pairs--plainLabel">
						<dt>' . 'Name' . '</dt>
						<dd>' . $__templater->escape($__vars['ticket']['username']) . '</dd>
					</dl>
					<dl class="pairs pairs--justified pairs--plainLabel">
						<dt>' . 'Email' . '</dt>
						<dd>' . $__templater->escape($__vars['ticket']['user_email']) . '</dd>
					</dl>
				';
	} else {
		$__compilerTemp12 .= '
					<dl class="pairs pairs--justified pairs--plainLabel">
						<dt>' . 'Name' . '</dt>
						<dd>' . $__templater->escape($__vars['ticket']['User']['username']) . '</dd>
					</dl>
					<dl class="pairs pairs--justified pairs--plainLabel">
						<dt>' . 'Email' . '</dt>
						<dd>' . $__templater->escape($__vars['ticket']['User']['email']) . '</dd>
					</dl>
					<dl class="pairs pairs--justified pairs--plainLabel">
						<dt>' . 'Tickets' . '</dt>
						<dd>' . $__templater->filter($__vars['ticket']['User']['mjst_ticket_count'], array(array('number', array()),), true) . '</dd>
					</dl>
				';
	}
	$__compilerTemp13 = '';
	if (($__templater->method($__vars['ticket'], 'canViewSubmitterIp', array()) AND ($__vars['xf']['options']['mjstDisplaySubmitterIp'] AND $__vars['ticket']['FirstMessage']['Ip']))) {
		$__compilerTemp13 .= '
					<dl class="pairs pairs--justified pairs--plainLabel">
						<dt>' . 'Submitter IP' . '</dt>
						<dd>' . $__templater->filter($__vars['ticket']['FirstMessage']['Ip']['ip'], array(array('ip', array()),), true) . '</dd>
					</dl>
				';
	}
	$__compilerTemp14 = '';
	if ($__templater->method($__vars['ticket'], 'canViewCurrentViewer', array()) AND !$__templater->test($__vars['viewers'], 'empty', array())) {
		$__compilerTemp14 .= '
		';
		$__compilerTemp15 = '';
		$__compilerTemp15 .= '
					';
		if ($__templater->isTraversable($__vars['viewers'])) {
			foreach ($__vars['viewers'] AS $__vars['viewer']) {
				if ($__vars['viewer']['User']['user_id'] !== $__vars['xf']['visitor']['user_id']) {
					$__compilerTemp15 .= '
						<li class="block-row">
							<div class="contentRow contentRow--alignMiddle">
								<div class="contentRow-figure">
									' . $__templater->fn('avatar', array($__vars['viewer']['User'], 'xs', false, array(
					))) . '
								</div>
								<div class="contentRow-main">
									<h3 class="contentRow-title">
										';
					if ($__vars['viewer']['User'] AND $__vars['viewer']['User']['username']) {
						$__compilerTemp15 .= '
											' . $__templater->fn('username_link', array($__vars['viewer']['User'], true, array(
						))) . '
										';
					} else {
						$__compilerTemp15 .= '
											' . 'Guest' . '
										';
					}
					$__compilerTemp15 .= '
									</h3>
								</div>
							</div>
						</li>
					';
				}
			}
		}
		$__compilerTemp15 .= '
					';
		if (strlen(trim($__compilerTemp15)) > 0) {
			$__compilerTemp14 .= '
		<div class="block">
			<div class="block-container">
				<h3 class="block-minorHeader">' . 'Online viewers' . '</h3>
				<ul class="block-body block-row">
					' . $__compilerTemp15 . '
				</ul>
			</div>
		</div>
		';
		}
		$__compilerTemp14 .= '
	';
	}
	$__templater->modifySidebarHtml(null, '
	' . '
	<div class="block">
		<div class="block-container">
			<h3 class="block-minorHeader">' . 'Ticket info' . '</h3>
			' . $__compilerTemp8 . '
		</div>
	</div>

	<div class="block">
		<div class="block-container">
			<h3 class="block-minorHeader">' . 'Submitter info' . '</h3>
			<div class="block-body block-row">
				' . $__compilerTemp12 . '
				' . $__compilerTemp13 . '
				' . $__templater->callMacro('custom_fields_macros', 'custom_fields_view', array(
		'type' => 'tickets',
		'group' => 'submitter_info',
		'onlyInclude' => $__vars['ticket']['Department']['field_cache'],
		'set' => $__vars['ticket']['custom_fields'],
		'wrapperClass' => 'ticket-fields ticket-fields--submitter_info',
	), $__vars) . '
			</div>
		</div>
	</div>
	' . $__compilerTemp14 . '
', 'replace');
	$__finalCompiled .= '
';
	$__templater->modifySidebarHtml('_xfWidgetPositionSidebarMjstTicketViewSidebar', $__templater->widgetPosition('mjst_ticket_view_sidebar', array(
		'ticket' => $__vars['ticket'],
	)), 'replace');
	$__finalCompiled .= '

';
	$__compilerTemp16 = '';
	if ($__vars['ticket']['User']['avatar_highdpi']) {
		$__compilerTemp16 .= '
		';
		$__vars['image'] = $__templater->preEscaped($__templater->escape($__templater->method($__vars['ticket']['User'], 'getAvatarUrl', array('h', null, true, ))));
		$__compilerTemp16 .= '
	';
	} else if ($__vars['ticket']['User']['avatar_date']) {
		$__compilerTemp16 .= '
		';
		$__vars['image'] = $__templater->preEscaped($__templater->escape($__templater->method($__vars['ticket']['User'], 'getAvatarUrl', array('l', null, true, ))));
		$__compilerTemp16 .= '
	';
	} else if ($__templater->fn('property', array('publicMetadataLogoUrl', ), false)) {
		$__compilerTemp16 .= '
		';
		$__vars['image'] = $__templater->preEscaped($__templater->fn('base_url', array($__templater->fn('property', array('publicMetadataLogoUrl', ), false), true, ), true));
		$__compilerTemp16 .= '
	';
	}
	$__compilerTemp17 = '';
	if ($__vars['image']) {
		$__compilerTemp17 .= '
		<script type="application/ld+json">
		{
			"@context": "https://schema.org",
			"@type": "DiscussionDepartmentPosting",
			"@id": "' . $__templater->filter($__templater->fn('link', array('canonical:support-tickets', $__vars['ticket'], ), false), array(array('escape', array('json', )),), true) . '",
			"headline": "' . $__templater->filter($__vars['ticket']['title'], array(array('escape', array('json', )),), true) . '",
			"articleBody": "' . $__templater->filter($__vars['fpSnippet'], array(array('escape', array('json', )),), true) . '",
			"articleSection": "' . $__templater->filter($__vars['ticket']['Department']['title'], array(array('escape', array('json', )),), true) . '",
			"author": {
				"@type": "Person",
				"name": "' . $__templater->filter(($__vars['ticket']['User'] ? $__vars['ticket']['User']['username'] : $__vars['ticket']['username']), array(array('escape', array('json', )),), true) . '"
			},
			"datePublished": "' . $__templater->filter($__templater->fn('date', array($__vars['ticket']['open_date'], 'Y-m-d', ), false), array(array('escape', array('json', )),), true) . '",
			"dateModified": "' . $__templater->filter($__templater->fn('date', array($__vars['ticket']['last_message_date'], 'Y-m-d', ), false), array(array('escape', array('json', )),), true) . '",
			"image": "' . $__templater->filter($__vars['image'], array(array('escape', array('json', )),), true) . '",
			"interactionStatistic": {
				"@type": "InteractionCounter",
				"interactionType": "https://schema.org/ReplyAction",
				"userInteractionCount": ' . $__templater->escape($__vars['ticket']['reply_count']) . '
			}
		}
		</script>
	';
	}
	$__templater->setPageParam('ldJsonHtml', '
	' . $__compilerTemp16 . '
	' . $__compilerTemp17 . '
');
	return $__finalCompiled;
});