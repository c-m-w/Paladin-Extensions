<?php
// FROM HASH: 40f28860001e73ee25956927320671a4
return array('macros' => array('review' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'review' => '!',
		'resource' => '!',
		'showResource' => false,
	), $__arguments, $__vars);
	$__finalCompiled .= '

	';
	$__templater->includeCss('message.less');
	$__finalCompiled .= '
	';
	$__templater->includeJs(array(
		'src' => 'xf/comment.js',
		'min' => '1',
	));
	$__finalCompiled .= '

	<div class="message message--simple' . ($__templater->method($__vars['review'], 'isIgnored', array()) ? ' is-ignored' : '') . '">
		<span class="u-anchorTarget" id="resource-review-' . $__templater->escape($__vars['review']['resource_rating_id']) . '"></span>
		<div class="message-inner">
			<span class="message-cell message-cell--user">
				';
	if ($__vars['review']['is_anonymous']) {
		$__finalCompiled .= '
					' . $__templater->callMacro('message_macros', 'user_info_simple', array(
			'user' => null,
			'fallbackName' => '',
		), $__vars) . '
				';
	} else {
		$__finalCompiled .= '
					' . $__templater->callMacro('message_macros', 'user_info_simple', array(
			'user' => $__vars['review']['User'],
			'fallbackName' => 'Deleted member',
		), $__vars) . '
				';
	}
	$__finalCompiled .= '
			</span>
			<div class="message-cell message-cell--main">
				<div class="message-content js-messageContent">
					<div class="message-attribution message-attribution--plain">
						';
	if ($__vars['showResource']) {
		$__finalCompiled .= '
							<div class="message-attribution-source">
								' . 'For ' . ((((('<a href="' . $__templater->fn('link', array('resources', $__vars['resource'], ), true)) . '">') . $__templater->fn('prefix', array('resource', $__vars['resource'], ), true)) . $__templater->escape($__vars['resource']['title'])) . '</a>') . ' in ' . (((('<a href="' . $__templater->fn('link', array('resources/categories', $__vars['resource']['Category'], ), true)) . '">') . $__templater->escape($__vars['resource']['Category']['title'])) . '</a>') . '' . '
							</div>
						';
	}
	$__finalCompiled .= '

						<ul class="listInline listInline--bullet">
							<li class="message-attribution-user">
								';
	if ($__vars['review']['is_anonymous']) {
		$__finalCompiled .= '
									' . $__templater->fn('username_link', array(null, false, array(
			'defaultname' => 'Anonymous',
		))) . '
									';
		if ($__templater->method($__vars['review'], 'canViewAnonymousAuthor', array())) {
			$__finalCompiled .= '
										(' . $__templater->fn('username_link', array($__vars['review']['User'], false, array(
				'defaultname' => 'Deleted member',
			))) . ')
									';
		}
		$__finalCompiled .= '
								';
	} else {
		$__finalCompiled .= '
									' . $__templater->fn('username_link', array($__vars['review']['User'], false, array(
			'defaultname' => 'Deleted member',
		))) . '
								';
	}
	$__finalCompiled .= '
							</li>
							<li>
								' . $__templater->callMacro('rating_macros', 'stars', array(
		'rating' => $__vars['review']['rating'],
		'class' => 'ratingStars--smaller',
	), $__vars) . '
							</li>
							<li><a href="' . $__templater->fn('link', array('resources/review', $__vars['review'], ), true) . '" class="u-concealed">' . $__templater->fn('date_dynamic', array($__vars['review']['rating_date'], array(
	))) . '</a></li>
							';
	if ($__templater->method($__vars['resource'], 'isVersioned', array())) {
		$__finalCompiled .= '
								<li>' . 'Version' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['review']['version_string']) . '</li>
							';
	}
	$__finalCompiled .= '
						</ul>
					</div>

					';
	if ($__vars['review']['rating_state'] == 'deleted') {
		$__finalCompiled .= '
						<div class="messageNotice messageNotice--deleted">
							' . $__templater->callMacro('deletion_macros', 'notice', array(
			'log' => $__vars['review']['DeletionLog'],
		), $__vars) . '
						</div>
					';
	}
	$__finalCompiled .= '

					<div class="message-body">
						' . $__templater->fn('structured_text', array($__vars['review']['message'], ), true) . '
					</div>
				</div>

				';
	$__compilerTemp1 = '';
	$__compilerTemp1 .= '
							';
	$__compilerTemp2 = '';
	$__compilerTemp2 .= '
									';
	if ($__templater->method($__vars['review'], 'canReply', array())) {
		$__compilerTemp2 .= '
										<a class="actionBar-action actionBar-action--reply js-replyTrigger-' . $__templater->escape($__vars['review']['resource_rating_id']) . '"
											data-xf-click="toggle"
											data-target=".js-commentsTarget-' . $__templater->escape($__vars['review']['resource_rating_id']) . '"
											role="button"
											tabindex="0">
											' . 'Reply' . '
										</a>
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
	if ($__templater->method($__vars['review'], 'canReport', array())) {
		$__compilerTemp3 .= '
										<a href="' . $__templater->fn('link', array('resources/review/report', $__vars['review'], ), true) . '" class="actionBar-action actionBar-action--report" data-xf-click="overlay">
											' . 'Report' . '
										</a>
									';
	}
	$__compilerTemp3 .= '

									';
	$__vars['hasActionBarMenu'] = false;
	$__compilerTemp3 .= '
									';
	if ($__templater->method($__vars['review'], 'canDelete', array('soft', ))) {
		$__compilerTemp3 .= '
										<a href="' . $__templater->fn('link', array('resources/review/delete', $__vars['review'], ), true) . '"
											class="actionBar-action actionBar-action--delete actionBar-action--menuItem"
											data-xf-click="overlay">
											' . 'Delete' . '
										</a>
										';
		$__vars['hasActionBarMenu'] = true;
		$__compilerTemp3 .= '
									';
	}
	$__compilerTemp3 .= '
									';
	if (($__vars['review']['rating_state'] == 'deleted') AND $__templater->method($__vars['review'], 'canUndelete', array())) {
		$__compilerTemp3 .= '
										<a href="' . $__templater->fn('link', array('resources/review/undelete', $__vars['review'], array('t' => $__templater->fn('csrf_token', array(), false), ), ), true) . '"
											class="actionBar-action actionBar-action--undelete actionBar-action--menuItem">
											' . 'Undelete' . '
										</a>
										';
		$__vars['hasActionBarMenu'] = true;
		$__compilerTemp3 .= '
									';
	}
	$__compilerTemp3 .= '
									';
	if ($__templater->method($__vars['review'], 'canWarn', array())) {
		$__compilerTemp3 .= '
										<a href="' . $__templater->fn('link', array('resources/review/warn', $__vars['review'], ), true) . '"
											class="actionBar-action actionBar-action--warn actionBar-action--menuItem">
											' . 'Warn' . '
										</a>
										';
		$__vars['hasActionBarMenu'] = true;
		$__compilerTemp3 .= '
									';
	} else if ($__vars['review']['warning_id'] AND $__templater->method($__vars['xf']['visitor'], 'canViewWarnings', array())) {
		$__compilerTemp3 .= '
										<a href="' . $__templater->fn('link', array('warnings', array('warning_id' => $__vars['review']['warning_id'], ), ), true) . '"
											class="actionBar-action actionBar-action--warn actionBar-action--menuItem"
											data-xf-click="overlay">
											' . 'View warning' . '
										</a>
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

				';
	$__compilerTemp4 = '';
	$__compilerTemp4 .= '

						';
	if ($__vars['review']['author_response']) {
		$__compilerTemp4 .= '
							' . $__templater->callMacro(null, 'author_reply_row', array(
			'review' => $__vars['review'],
			'resource' => $__vars['resource'],
		), $__vars) . '
						';
	} else if ($__templater->method($__vars['review'], 'canReply', array())) {
		$__compilerTemp4 .= '
							<div class="js-replyNewMessageContainer"></div>
						';
	}
	$__compilerTemp4 .= '

						';
	if ($__templater->method($__vars['review'], 'canReply', array())) {
		$__compilerTemp4 .= '
							';
		$__templater->includeJs(array(
			'src' => 'xf/message.js',
			'min' => '1',
		));
		$__compilerTemp4 .= '
							<div class="message-responseRow js-commentsTarget-' . $__templater->escape($__vars['review']['resource_rating_id']) . ' toggleTarget">
								' . $__templater->form('

									<div class="comment-inner">
										<span class="comment-avatar">
											' . $__templater->fn('avatar', array($__vars['xf']['visitor'], 'xxs', false, array(
		))) . '
										</span>
										<div class="comment-main">
											' . $__templater->formTextArea(array(
			'name' => 'message',
			'rows' => '1',
			'autosize' => 'true',
			'maxlength' => $__vars['xf']['options']['messageMaxLength'],
			'data-toggle-autofocus' => '1',
			'class' => 'comment-input js-editor',
		)) . '
											<div>
												' . $__templater->button('Post reply', array(
			'type' => 'submit',
			'class' => 'button--primary button--small',
			'icon' => 'reply',
		), '', array(
		)) . '
											</div>
										</div>
									</div>
								', array(
			'action' => $__templater->fn('link', array('resources/review/reply', $__vars['review'], ), false),
			'ajax' => 'true',
			'class' => 'comment',
			'data-xf-init' => 'quick-reply',
			'data-message-container' => '< .js-messageResponses | .js-replyNewMessageContainer',
			'data-submit-hide' => '.js-commentsTarget-' . $__vars['review']['resource_rating_id'] . ', .js-replyTrigger-' . $__vars['review']['resource_rating_id'],
		)) . '
							</div>
						';
	}
	$__compilerTemp4 .= '

					';
	if (strlen(trim($__compilerTemp4)) > 0) {
		$__finalCompiled .= '
					<div class="message-responses js-messageResponses">
					' . $__compilerTemp4 . '
					</div>
				';
	}
	$__finalCompiled .= '
			</div>
		</div>
	</div>
';
	return $__finalCompiled;
},
'author_reply_row' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'review' => '!',
		'resource' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="message-responseRow">
		<div class="comment">
			<div class="comment-inner">
				<span class="comment-avatar">
					' . $__templater->fn('avatar', array($__vars['resource']['User'], 'xxs', false, array(
		'defaultname' => $__vars['resource']['username'],
	))) . '
				</span>
				<div class="comment-main">
					<div class="comment-content">
						<div class="comment-contentWrapper">
							' . $__templater->fn('username_link', array($__vars['resource']['User'], true, array(
		'defaultname' => $__vars['resource']['username'],
		'class' => 'comment-user',
	))) . '
							<div class="comment-body">' . $__templater->fn('structured_text', array($__vars['review']['author_response'], ), true) . '</div>
						</div>
					</div>

					<div class="comment-actionBar actionBar">
						<div class="actionBar-set actionBar-set--internal">
							';
	if ($__templater->method($__vars['review'], 'canDeleteAuthorResponse', array())) {
		$__finalCompiled .= '
								<a href="' . $__templater->fn('link', array('resources/review/reply-delete', $__vars['review'], ), true) . '"
									class="actionBar-action actionBar-action--delete actionBar-action--menuItem"
									data-xf-click="overlay">
									' . 'Delete' . '
								</a>
							';
	}
	$__finalCompiled .= '
						</div>
					</div>
				</div>
			</div>
		</div>
	</div>
';
	return $__finalCompiled;
},
'review_simple' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'review' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="contentRow">
		<div class="contentRow-figure">
			' . $__templater->fn('avatar', array(($__vars['review']['is_anonymous'] ? null : $__vars['review']['User']), 'xxs', false, array(
	))) . '
		</div>
		<div class="contentRow-main contentRow-main--close">
			<a href="' . $__templater->fn('link', array('resources/review', $__vars['review'], ), true) . '">' . $__templater->fn('prefix', array('resource', $__vars['review']['Resource'], ), true) . $__templater->escape($__vars['review']['Resource']['title']) . '</a>
			<div class="contentRow-lesser">
				' . $__templater->callMacro('rating_macros', 'stars', array(
		'rating' => $__vars['review']['rating'],
	), $__vars) . '
			</div>
			<div class="contentRow-lesser">' . $__templater->fn('snippet', array($__vars['review']['message'], 100, ), true) . '</div>
			<div class="contentRow-minor contentRow-minor--smaller">
				<ul class="listInline listInline--bullet">
					<li>
						';
	if ($__vars['review']['is_anonymous']) {
		$__finalCompiled .= '
							' . 'Anonymous' . '
						';
	} else {
		$__finalCompiled .= '
							' . ($__templater->escape($__vars['review']['User']['username']) ?: $__templater->escape($__vars['review']['username'])) . '
						';
	}
	$__finalCompiled .= '
					</li>
					<li>' . $__templater->fn('date_dynamic', array($__vars['review']['rating_date'], array(
	))) . '</li>
				</ul>
			</div>
		</div>
	</div>
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '

' . '

';
	return $__finalCompiled;
});