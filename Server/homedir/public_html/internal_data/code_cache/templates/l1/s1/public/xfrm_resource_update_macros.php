<?php
// FROM HASH: fb7d8805411fd02763051e4af67e3a0d
return array('macros' => array('resource_update' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'update' => '!',
		'resource' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__templater->includeCss('message.less');
	$__finalCompiled .= '
	<div class="message message--simple js-resourceUpdate" id="js-resourceUpdate-' . $__templater->escape($__vars['update']['resource_update_id']) . '">
		<span class="u-anchorTarget" id="resource-update-' . $__templater->escape($__vars['update']['resource_update_id']) . '"></span>
		<div class="message-inner">
			<div class="message-cell message-cell--main">
				<div class="js-quickEditTarget">
					<div class="message-content js-messageContent">
						<div class="message-attribution">
							<h2 class="message-attribution-main block-textHeader">
								<a href="' . $__templater->fn('link', array('resources/update', $__vars['update'], ), true) . '" class="u-concealed" rel="nofollow">' . $__templater->escape($__vars['update']['title']) . '</a>
							</h2>
							<span class="message-attribution-opposite">
								<a href="' . $__templater->fn('link', array('resources/update', $__vars['update'], ), true) . '" class="u-concealed" rel="nofollow">' . $__templater->fn('date_dynamic', array($__vars['update']['post_date'], array(
	))) . '</a>
							</span>
						</div>

						';
	if ($__vars['update']['message_state'] == 'deleted') {
		$__finalCompiled .= '
							<div class="messageNotice messageNotice--deleted">
								' . $__templater->callMacro('deletion_macros', 'notice', array(
			'log' => $__vars['update']['DeletionLog'],
		), $__vars) . '
							</div>
						';
	} else if ($__vars['update']['message_state'] == 'moderated') {
		$__finalCompiled .= '
							<div class="messageNotice messageNotice--moderated">
								' . 'This message is awaiting moderator approval, and is invisible to normal visitors.' . '
							</div>
						';
	}
	$__finalCompiled .= '
						';
	if ($__vars['update']['warning_message']) {
		$__finalCompiled .= '
							<div class="messageNotice messageNotice--warning">
								' . $__templater->escape($__vars['update']['warning_message']) . '
							</div>
						';
	}
	$__finalCompiled .= '

						<div class="message-userContent lbContainer js-lbContainer"
							data-lb-id="resource_update-' . $__templater->escape($__vars['update']['resource_update_id']) . '"
							data-lb-caption-desc="' . ($__vars['resource']['User'] ? $__templater->escape($__vars['resource']['User']['username']) : $__templater->escape($__vars['resource']['username'])) . ' &middot; ' . $__templater->fn('date_time', array($__vars['update']['post_date'], ), true) . '">

							<blockquote class="message-body">
								' . $__templater->fn('bb_code', array($__vars['update']['message'], 'resource_update', $__vars['update'], ), true) . '
							</blockquote>

							';
	if ($__vars['update']['attach_count']) {
		$__finalCompiled .= '
								' . $__templater->callMacro('message_macros', 'attachments', array(
			'attachments' => $__vars['update']['Attachments'],
			'message' => $__vars['update'],
			'canView' => $__templater->method($__vars['resource'], 'canViewUpdateImages', array()),
		), $__vars) . '
							';
	}
	$__finalCompiled .= '
						</div>

						';
	$__compilerTemp1 = '';
	$__compilerTemp1 .= '
									';
	$__compilerTemp2 = '';
	$__compilerTemp2 .= '
											';
	if ($__templater->method($__vars['update'], 'canLike', array())) {
		$__compilerTemp2 .= '
												<a href="' . $__templater->fn('link', array('resources/update/like', $__vars['update'], ), true) . '"
													class="actionBar-action actionBar-action--like"
													data-xf-click="like"
													data-like-list="< .js-resourceUpdate | .js-likeList">';
		if ($__templater->method($__vars['update'], 'isLiked', array())) {
			$__compilerTemp2 .= 'Unlike';
		} else {
			$__compilerTemp2 .= 'Like';
		}
		$__compilerTemp2 .= '</a>
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
	if ($__templater->method($__vars['update'], 'canReport', array())) {
		$__compilerTemp3 .= '
												<a href="' . $__templater->fn('link', array('resources/update/report', $__vars['update'], ), true) . '"
													class="actionBar-action actionBar-action--report"
													data-xf-click="overlay">' . 'Report' . '</a>
											';
	}
	$__compilerTemp3 .= '

											';
	$__vars['hasActionBarMenu'] = false;
	$__compilerTemp3 .= '
											';
	if ($__templater->method($__vars['update'], 'canEdit', array())) {
		$__compilerTemp3 .= '
												';
		$__templater->includeJs(array(
			'src' => 'xf/message.js',
			'min' => '1',
		));
		$__compilerTemp3 .= '
												<a href="' . $__templater->fn('link', array('resources/update/edit', $__vars['update'], ), true) . '"
													class="actionBar-action actionBar-action--edit actionBar-action--menuItem"
													data-xf-click="quick-edit"
													data-editor-target="#js-resourceUpdate-' . $__templater->escape($__vars['update']['resource_update_id']) . ' .js-quickEditTarget"
													data-menu-closer="true">' . 'Edit' . '</a>
												';
		$__vars['hasActionBarMenu'] = true;
		$__compilerTemp3 .= '
											';
	}
	$__compilerTemp3 .= '
											';
	if ($__templater->method($__vars['update'], 'canDelete', array('soft', ))) {
		$__compilerTemp3 .= '
												<a href="' . $__templater->fn('link', array('resources/update/delete', $__vars['update'], ), true) . '"
													class="actionBar-action actionBar-action--delete actionBar-action--menuItem"
													data-xf-click="overlay">' . 'Delete' . '</a>
												';
		$__vars['hasActionBarMenu'] = true;
		$__compilerTemp3 .= '
											';
	}
	$__compilerTemp3 .= '
											';
	if (($__vars['update']['message_state'] == 'deleted') AND $__templater->method($__vars['update'], 'canUndelete', array())) {
		$__compilerTemp3 .= '
												<a href="' . $__templater->fn('link', array('resources/update/undelete', $__vars['update'], array('t' => $__templater->fn('csrf_token', array(), false), ), ), true) . '"
													class="actionBar-action actionBar-action--undelete actionBar-action--menuItem">' . 'Undelete' . '</a>
												';
		$__vars['hasActionBarMenu'] = true;
		$__compilerTemp3 .= '
											';
	}
	$__compilerTemp3 .= '
											';
	if ($__templater->method($__vars['xf']['visitor'], 'canViewIps', array()) AND $__vars['update']['ip_id']) {
		$__compilerTemp3 .= '
												<a href="' . $__templater->fn('link', array('resources/update/ip', $__vars['update'], ), true) . '"
													class="actionBar-action actionBar-action--ip actionBar-action--menuItem"
													data-xf-click="overlay">' . 'IP' . '</a>
												';
		$__vars['hasActionBarMenu'] = true;
		$__compilerTemp3 .= '
											';
	}
	$__compilerTemp3 .= '
											';
	if ($__templater->method($__vars['update'], 'canWarn', array())) {
		$__compilerTemp3 .= '
												<a href="' . $__templater->fn('link', array('resources/update/warn', $__vars['update'], ), true) . '"
													class="actionBar-action actionBar-action--warn actionBar-action--menuItem">' . 'Warn' . '</a>
												';
		$__vars['hasActionBarMenu'] = true;
		$__compilerTemp3 .= '
											';
	} else if ($__vars['update']['warning_id'] AND $__templater->method($__vars['xf']['visitor'], 'canViewWarnings', array())) {
		$__compilerTemp3 .= '
												<a href="' . $__templater->fn('link', array('warnings', array('warning_id' => $__vars['update']['warning_id'], ), ), true) . '"
													class="actionBar-action actionBar-action--warn actionBar-action--menuItem"
													data-xf-click="overlay">' . 'View warning' . '</a>
												';
		$__vars['hasActionBarMenu'] = true;
		$__compilerTemp3 .= '
											';
	}
	$__compilerTemp3 .= '
											';
	if ($__templater->method($__vars['update'], 'canApproveUnapprove', array())) {
		$__compilerTemp3 .= '
												';
		if ($__vars['update']['message_state'] == 'moderated') {
			$__compilerTemp3 .= '
													<a href="' . $__templater->fn('link', array('resources/update/approve', $__vars['update'], array('t' => $__templater->fn('csrf_token', array(), false), ), ), true) . '"
														class="actionBar-action actionBar-action--approve actionBar-action--menuItem">' . 'Approve' . '</a>
													';
			$__vars['hasActionBarMenu'] = true;
			$__compilerTemp3 .= '
												';
		} else if ($__vars['update']['message_state'] == 'visible') {
			$__compilerTemp3 .= '
													<a href="' . $__templater->fn('link', array('resources/update/unapprove', $__vars['update'], array('t' => $__templater->fn('csrf_token', array(), false), ), ), true) . '"
														class="actionBar-action actionBar-action--unapprove actionBar-action--menuItem">' . 'Unapprove' . '</a>
													';
			$__vars['hasActionBarMenu'] = true;
			$__compilerTemp3 .= '
												';
		}
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

						<div class="likesBar js-likeList ' . ($__vars['update']['likes'] ? 'is-active' : '') . '">
							' . $__templater->fn('likes_content', array($__vars['update'], $__templater->fn('link', array('resources/update/likes', $__vars['update'], ), false), array(
		'url' => $__templater->fn('link', array('resources/update/likes', $__vars['update'], ), false),
	))) . '
						</div>

						<div class="js-historyTarget toggleTarget" data-href="trigger-href"></div>
					</div>
				</div>
			</div>
		</div>
	</div>
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';

	return $__finalCompiled;
});