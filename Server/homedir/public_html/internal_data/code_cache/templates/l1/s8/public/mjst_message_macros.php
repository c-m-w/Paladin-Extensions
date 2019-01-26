<?php
// FROM HASH: 70436cfde136557169edabdd6e88d6af
return array('macros' => array('message' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'message' => '!',
		'ticket' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__templater->includeCss('message.less');
	$__finalCompiled .= '
	';
	$__vars['isIgnored'] = $__templater->method($__vars['message'], 'isIgnored', array());
	$__finalCompiled .= '
	<article class="message message--message js-message js-inlineModContainer ' . ($__vars['isIgnored'] ? 'is-ignored' : '') . ' ' . ($__templater->method($__vars['message'], 'isUnread', array()) ? ' is-unread' : '') . '"
		data-author="' . ($__templater->escape($__vars['message']['User']['username']) ?: $__templater->escape($__vars['message']['username'])) . '"
		data-content="message-' . $__templater->escape($__vars['message']['message_id']) . '"
		id="js-message-' . $__templater->escape($__vars['message']['message_id']) . '">

		<span class="u-anchorTarget" id="message-' . $__templater->escape($__vars['message']['message_id']) . '"></span>

		<div class="message-inner">
			<div class="message-cell message-cell--user">
				';
	$__vars['dateHtml'] = $__templater->preEscaped('<a href="' . $__templater->fn('link', array('support-tickets/message', $__vars['ticket'], array('message_id' => $__vars['message']['message_id'], ), ), true) . '" class="u-concealed" rel="nofollow">' . $__templater->fn('date_dynamic', array($__vars['message']['message_date'], array(
	))) . '</a>');
	$__finalCompiled .= '
				';
	$__vars['linkHtml'] = $__templater->preEscaped('<a href="' . $__templater->fn('link', array('support-tickets/message', $__vars['ticket'], array('message_id' => $__vars['message']['message_id'], ), ), true) . '" class="u-concealed" rel="nofollow">#' . $__templater->fn('number', array($__vars['message']['position'] + 1, ), true) . '</a>');
	$__finalCompiled .= '
				' . $__templater->callMacro('message_macros', 'user_info', array(
		'user' => $__vars['message']['User'],
		'fallbackName' => $__vars['message']['username'],
		'dateHtml' => $__vars['dateHtml'],
		'linkHtml' => $__vars['linkHtml'],
	), $__vars) . '
			</div>
			<div class="message-cell message-cell--main">
				<div class="message-main js-quickEditTarget">

					<header class="message-attribution">
						<a href="' . $__templater->fn('link', array('support-tickets/message', $__vars['ticket'], array('message_id' => $__vars['message']['message_id'], ), ), true) . '" class="message-attribution-main u-concealed" rel="nofollow">' . $__templater->fn('date_dynamic', array($__vars['message']['message_date'], array(
	))) . '</a>
						<div class="message-attribution-opposite">
							';
	if ($__templater->method($__vars['message'], 'isUnread', array())) {
		$__finalCompiled .= '
								<span class="message-newIndicator">' . 'New' . '</span>
							';
	}
	$__finalCompiled .= '
							<a href="' . $__templater->fn('link', array('support-tickets/message', $__vars['ticket'], array('message_id' => $__vars['message']['message_id'], ), ), true) . '" class="u-concealed" rel="nofollow">#' . $__templater->fn('number', array($__vars['message']['position'] + 1, ), true) . '</a>
						</div>
					</header>

					<div class="message-content js-messageContent">

						';
	if ($__vars['message']['message_state'] == 'deleted') {
		$__finalCompiled .= '
							<div class="messageNotice messageNotice--deleted">
								' . $__templater->callMacro('deletion_macros', 'notice', array(
			'log' => $__vars['message']['DeletionLog'],
		), $__vars) . '
							</div>
						';
	} else if ($__vars['message']['message_state'] == 'moderated') {
		$__finalCompiled .= '
							<div class="messageNotice messageNotice--moderated">
								' . 'This message is awaiting moderator approval, and is invisible to normal visitors.' . '
							</div>
						';
	}
	$__finalCompiled .= '
						';
	if ($__vars['isIgnored']) {
		$__finalCompiled .= '
							<div class="messageNotice messageNotice--ignored">
								' . 'You are ignoring content by this member.' . '
								' . $__templater->fn('show_ignored', array(array(
		))) . '
							</div>
						';
	}
	$__finalCompiled .= '

						<div class="message-userContent lbContainer js-lbContainer ' . ($__vars['isIgnored'] ? 'is-ignored' : '') . '"
							data-lb-id="message-' . $__templater->escape($__vars['message']['message_id']) . '"
							data-lb-caption-desc="' . ($__vars['message']['User'] ? $__templater->escape($__vars['message']['User']['username']) : $__templater->escape($__vars['message']['username'])) . ' &middot; ' . $__templater->fn('date_time', array($__vars['message']['message_date'], ), true) . '">

							';
	if ($__templater->method($__vars['message'], 'isFirstMessage', array())) {
		$__finalCompiled .= '
								' . $__templater->callMacro('custom_fields_macros', 'custom_fields_view', array(
			'type' => 'tickets',
			'group' => 'before',
			'onlyInclude' => $__vars['ticket']['Department']['field_cache'],
			'set' => $__vars['ticket']['custom_fields'],
			'wrapperClass' => 'message-fields message-fields--before',
		), $__vars) . '
							';
	}
	$__finalCompiled .= '

							<article class="message-body js-selectToQuote">
								' . $__templater->callAdsMacro('message_above_content', array(
		'message' => $__vars['message'],
	), $__vars) . '
								' . $__templater->fn('bb_code', array($__vars['message']['message'], 'support_ticket_message', $__vars['message'], ), true) . '
								<div class="js-selectToQuoteEnd">&nbsp;</div>
								' . $__templater->callAdsMacro('message_below_content', array(
		'message' => $__vars['message'],
	), $__vars) . '
							</article>

							';
	if ($__templater->method($__vars['message'], 'isFirstMessage', array())) {
		$__finalCompiled .= '
								' . $__templater->callMacro('custom_fields_macros', 'custom_fields_view', array(
			'type' => 'tickets',
			'group' => 'after',
			'onlyInclude' => $__vars['ticket']['Department']['field_cache'],
			'set' => $__vars['ticket']['custom_fields'],
			'wrapperClass' => 'message-fields message-fields--after',
		), $__vars) . '
							';
	}
	$__finalCompiled .= '

							';
	if ($__vars['message']['attach_count']) {
		$__finalCompiled .= '
								' . $__templater->callMacro('message_macros', 'attachments', array(
			'attachments' => $__vars['message']['Attachments'],
			'message' => $__vars['message'],
			'canView' => $__templater->method($__vars['ticket'], 'canViewAttachments', array()),
		), $__vars) . '
							';
	}
	$__finalCompiled .= '
						</div>

						';
	if ($__vars['message']['last_edit_date']) {
		$__finalCompiled .= '
							<div class="message-lastEdit">
								';
		if ($__vars['message']['user_id'] == $__vars['message']['last_edit_user_id']) {
			$__finalCompiled .= '
									' . 'Last edited' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->fn('date_dynamic', array($__vars['message']['last_edit_date'], array(
			))) . '
								';
		} else {
			$__finalCompiled .= '
									' . 'Last edited by a moderator' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->fn('date_dynamic', array($__vars['message']['last_edit_date'], array(
			))) . '
								';
		}
		$__finalCompiled .= '
							</div>
						';
	}
	$__finalCompiled .= '

						' . $__templater->callMacro('message_macros', 'signature', array(
		'user' => $__vars['message']['User'],
	), $__vars) . '
					</div>

					<footer class="message-footer">
						';
	$__compilerTemp1 = '';
	$__compilerTemp1 .= '
									';
	$__compilerTemp2 = '';
	$__compilerTemp2 .= '
											';
	if ($__templater->method($__vars['ticket'], 'canReply', array())) {
		$__compilerTemp2 .= '
												';
		$__vars['quoteLink'] = $__templater->preEscaped($__templater->fn('link', array('support-tickets/reply', $__vars['ticket'], array('quote' => $__vars['message']['message_id'], ), ), true));
		$__compilerTemp2 .= '

												';
		if ($__vars['xf']['options']['multiQuote']) {
			$__compilerTemp2 .= '
													<a href="' . $__templater->escape($__vars['quoteLink']) . '"
														class="actionBar-action actionBar-action--mq u-jsOnly js-multiQuote"
														title="' . $__templater->filter('Toggle multi-quote', array(array('for_attr', array()),), true) . '"
														data-message-id="' . $__templater->escape($__vars['message']['message_id']) . '"
														data-mq-action="add">' . 'Quote' . '</a>
												';
		}
		$__compilerTemp2 .= '

												<a href="' . $__templater->escape($__vars['quoteLink']) . '"
													class="actionBar-action actionBar-action--reply"
													title="' . $__templater->filter('Reply, quoting this message', array(array('for_attr', array()),), true) . '"
													data-xf-click="quote"
													data-quote-href="' . $__templater->fn('link', array('support-tickets/messages/quote', $__vars['message'], ), true) . '">' . 'Reply' . '</a>
											';
	}
	$__compilerTemp2 .= '
										';
	if (strlen(trim($__compilerTemp2)) > 0) {
		$__compilerTemp1 .= '
										<div class="actionBar-set actionBar-set--external">
										' . $__compilerTemp2 . '
										</div>
									';
	}
	$__compilerTemp1 .= '

									';
	$__compilerTemp3 = '';
	$__compilerTemp3 .= '
											';
	if ($__templater->method($__vars['message'], 'canUseInlineModeration', array())) {
		$__compilerTemp3 .= '
												<span class="actionBar-action actionBar-action--inlineMod">
													' . $__templater->formCheckBox(array(
			'standalone' => 'true',
		), array(array(
			'value' => $__vars['message']['message_id'],
			'class' => 'js-inlineModToggle',
			'data-xf-init' => 'tooltip',
			'title' => $__templater->filter('Select for moderation', array(array('for_attr', array()),), false),
			'label' => 'Select for moderation',
			'hiddenlabel' => 'true',
			'_type' => 'option',
		))) . '
												</span>
											';
	}
	$__compilerTemp3 .= '

											';
	$__vars['hasActionBarMenu'] = false;
	$__compilerTemp3 .= '
											';
	if ($__templater->method($__vars['message'], 'canEdit', array())) {
		$__compilerTemp3 .= '
												';
		$__templater->includeJs(array(
			'src' => 'xf/message.js',
			'min' => '1',
		));
		$__compilerTemp3 .= '
												<a href="' . $__templater->fn('link', array('support-tickets/messages/edit', $__vars['message'], ), true) . '"
													class="actionBar-action actionBar-action--edit actionBar-action--menuItem"
													data-xf-click="quick-edit"
													data-editor-target="#js-message-' . $__templater->escape($__vars['message']['message_id']) . ' .js-quickEditTarget"
													data-menu-closer="true">' . 'Edit' . '</a>

												';
		$__vars['hasActionBarMenu'] = true;
		$__compilerTemp3 .= '
											';
	}
	$__compilerTemp3 .= '
											';
	if ($__vars['message']['edit_count'] AND $__templater->method($__vars['message'], 'canViewHistory', array())) {
		$__compilerTemp3 .= '
												<a href="' . $__templater->fn('link', array('support-tickets/messages/history', $__vars['message'], ), true) . '"
													class="actionBar-action actionBar-action--history actionBar-action--menuItem"
													data-xf-click="toggle"
													data-target="#js-message-' . $__templater->escape($__vars['message']['message_id']) . ' .js-historyTarget"
													data-menu-closer="true">' . 'History' . '</a>

												';
		$__vars['hasActionBarMenu'] = true;
		$__compilerTemp3 .= '
											';
	}
	$__compilerTemp3 .= '
											';
	if ($__templater->method($__vars['message'], 'canDelete', array('soft', ))) {
		$__compilerTemp3 .= '
												<a href="' . $__templater->fn('link', array('support-tickets/messages/delete', $__vars['message'], ), true) . '"
													class="actionBar-action actionBar-action--delete actionBar-action--menuItem"
													data-xf-click="overlay">' . 'Delete' . '</a>

												';
		$__vars['hasActionBarMenu'] = true;
		$__compilerTemp3 .= '
											';
	}
	$__compilerTemp3 .= '
											';
	if ($__templater->method($__vars['message'], 'canCleanSpam', array())) {
		$__compilerTemp3 .= '
												<a href="' . $__templater->fn('link', array('spam-cleaner', $__vars['message'], ), true) . '"
													class="actionBar-action actionBar-action--spam actionBar-action--menuItem"
													data-xf-click="overlay">' . 'Spam' . '</a>

												';
		$__vars['hasActionBarMenu'] = true;
		$__compilerTemp3 .= '
											';
	}
	$__compilerTemp3 .= '
											';
	if ($__templater->method($__vars['xf']['visitor'], 'canViewIps', array()) AND $__vars['message']['ip_id']) {
		$__compilerTemp3 .= '
												<a href="' . $__templater->fn('link', array('support-tickets/messages/ip', $__vars['message'], ), true) . '"
													class="actionBar-action actionBar-action--ip actionBar-action--menuItem"
													data-xf-click="overlay">' . 'IP' . '</a>

												';
		$__vars['hasActionBarMenu'] = true;
		$__compilerTemp3 .= '
											';
	}
	$__compilerTemp3 .= '

											';
	if ($__vars['hasActionBarMenu']) {
		$__compilerTemp3 .= '
												<a class="actionBar-action actionBar-action--menuTrigger"
													data-xf-click="menu"
													title="' . $__templater->filter('More options', array(array('for_attr', array()),), true) . '"
													role="button"
													tabindex="0"
													aria-expanded="false"
													aria-haspopup="true">&#8226;&#8226;&#8226;</a>

												<div class="menu" data-menu="menu" aria-hidden="true" data-menu-builder="actionBar">
													<div class="menu-content">
														<h4 class="menu-header">' . 'More options' . '</h4>
														<div class="js-menuBuilderTarget"></div>
													</div>
												</div>
											';
	}
	$__compilerTemp3 .= '
										';
	if (strlen(trim($__compilerTemp3)) > 0) {
		$__compilerTemp1 .= '
										<div class="actionBar-set actionBar-set--internal">
										' . $__compilerTemp3 . '
										</div>
									';
	}
	$__compilerTemp1 .= '

								';
	if (strlen(trim($__compilerTemp1)) > 0) {
		$__finalCompiled .= '
							<div class="message-actionBar actionBar">
								' . $__compilerTemp1 . '
							</div>
						';
	}
	$__finalCompiled .= '
						<div class="js-historyTarget message-historyTarget toggleTarget" data-href="trigger-href"></div>
					</footer>
				</div>
			</div>
		</div>
	</article>

	' . $__templater->callAdsMacro('message_below_container', array(
		'message' => $__vars['message'],
	), $__vars) . '
';
	return $__finalCompiled;
},
'message_deleted' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'message' => '!',
		'ticket' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__templater->includeCss('message.less');
	$__finalCompiled .= '
	<div class="message message--deleted message--message' . ($__templater->method($__vars['message'], 'isIgnored', array()) ? ' is-ignored' : '') . ($__templater->method($__vars['message'], 'isUnread', array()) ? ' is-unread' : '') . ' js-message js-inlineModContainer"
		data-author="' . ($__templater->escape($__vars['message']['User']['username']) ?: $__templater->escape($__vars['message']['username'])) . '"
		data-content="message-' . $__templater->escape($__vars['message']['message_id']) . '">

		<span class="u-anchorTarget" id="message-' . $__templater->escape($__vars['message']['message_id']) . '"></span>
		<div class="message-inner">
			<div class="message-cell message-cell--user">
				' . $__templater->callMacro('message_macros', 'user_info', array(
		'user' => $__vars['message']['User'],
		'fallbackName' => $__vars['message']['username'],
	), $__vars) . '
			</div>
			<div class="message-cell message-cell--main">
				<div class="message-attribution">
					<ul class="listInline listInline--bullet message-attribution-main">
						<li><a href="' . $__templater->fn('link', array('support-tickets/message', $__vars['ticket'], array('message_id' => $__vars['message']['message_id'], ), ), true) . '" class="u-concealed" rel="nofollow">' . $__templater->fn('date_dynamic', array($__vars['message']['message_date'], array(
	))) . '</a></li>
						<li>' . $__templater->fn('username_link', array($__vars['message']['User'], false, array(
		'defaultname' => $__vars['message']['username'],
		'class' => 'u-concealed',
	))) . '</li>
					</ul>
				</div>

				<div class="messageNotice messageNotice--deleted">
					' . $__templater->callMacro('deletion_macros', 'notice', array(
		'log' => $__vars['message']['DeletionLog'],
	), $__vars) . '

					<a href="' . $__templater->fn('link', array('support-tickets/messages/show', $__vars['message'], ), true) . '" class="u-jsOnly" data-xf-click="inserter" data-replace="[data-content=message-' . $__templater->escape($__vars['message']['message_id']) . ']">' . 'Show' . $__vars['xf']['language']['ellipsis'] . '</a>
				</div>
			</div>
		</div>
	</div>

	' . $__templater->callAdsMacro('message_below_container', array(
		'message' => $__vars['message'],
	), $__vars) . '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '

';
	return $__finalCompiled;
});