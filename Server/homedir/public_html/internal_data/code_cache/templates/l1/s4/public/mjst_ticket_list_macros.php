<?php
// FROM HASH: 041ce80758b0596941c12b118dda279d
return array('macros' => array('ticket' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'ticket' => '!',
		'department' => null,
		'forceRead' => false,
		'showWatched' => true,
		'allowInlineMod' => true,
		'chooseName' => '',
		'extraInfo' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '

	';
	$__templater->includeCss('structured_list.less');
	$__finalCompiled .= '
	';
	$__templater->includeCss('mjst.less');
	$__finalCompiled .= '

	<div class="structItem structItem--ticket ' . ($__templater->method($__vars['ticket'], 'isIgnored', array()) ? 'is-ignored' : '') . (($__templater->method($__vars['ticket'], 'isUnread', array()) AND (!$__vars['forceRead'])) ? ' is-unread' : '') . ' js-inlineModContainer js-ticketListItem-' . $__templater->escape($__vars['ticket']['support_ticket_id']) . '" data-author="' . ($__templater->escape($__vars['ticket']['User']['username']) ?: $__templater->escape($__vars['ticket']['username'])) . '">
		<div class="structItem-cell structItem-cell--icon">
			<div class="structItem-iconContainer">
				<span class="urgency urgency-' . $__templater->escape($__vars['ticket']['urgency']) . '"><i class="fa fa-flag" aria-hidden="true"></i></span>
			</div>
		</div>
		<div class="structItem-cell structItem-cell--icon structItem-cell--iconExpanded">
			<div class="structItem-iconContainer">
				' . $__templater->fn('avatar', array($__vars['ticket']['User'], 's', false, array(
		'defaultname' => $__vars['ticket']['username'],
	))) . '
				';
	if ($__vars['ticket']['assigned_user_id'] AND $__templater->method($__vars['ticket'], 'canViewAssigned', array())) {
		$__finalCompiled .= '
					' . $__templater->fn('avatar', array($__vars['ticket']['AssignedUser'], 's', false, array(
			'class' => 'avatar--separated structItem-secondaryIcon',
		))) . '
				';
	}
	$__finalCompiled .= '
			</div>
		</div>
		<div class="structItem-cell structItem-cell--main" data-xf-init="touch-proxy">
			';
	$__compilerTemp1 = '';
	$__compilerTemp1 .= '
					';
	if ($__vars['showWatched'] AND $__vars['xf']['visitor']['user_id']) {
		$__compilerTemp1 .= '
						';
		if ($__vars['ticket']['Watch'][$__vars['xf']['visitor']['user_id']]) {
			$__compilerTemp1 .= '
							<li>
								<i class="structItem-status structItem-status--watched" aria-hidden="true" title="' . $__templater->filter('Ticket watched', array(array('for_attr', array()),), true) . '"></i>
								<span class="u-srOnly">' . 'Ticket watched' . '</span>
							</li>
						';
		} else if ((!$__vars['department']) AND $__vars['ticket']['Department']['Watch'][$__vars['xf']['visitor']['user_id']]) {
			$__compilerTemp1 .= '
							<li>
								<i class="structItem-status structItem-status--watched" aria-hidden="true" title="' . $__templater->filter('Department watched', array(array('for_attr', array()),), true) . '"></i>
								<span class="u-srOnly">' . 'Department watched' . '</span>
							</li>
						';
		}
		$__compilerTemp1 .= '
					';
	}
	$__compilerTemp1 .= '
				';
	if (strlen(trim($__compilerTemp1)) > 0) {
		$__finalCompiled .= '
				<ul class="structItem-statuses">
				' . $__compilerTemp1 . '
				</ul>
			';
	}
	$__finalCompiled .= '
			<span class="mjstStatus mjstStatus--style' . $__templater->escape($__vars['ticket']['ticket_status_id']) . '">' . $__templater->escape($__vars['ticket']['Status']['title']) . '</span>
			<div class="structItem-title">
				';
	$__vars['canPreview'] = $__templater->method($__vars['ticket'], 'canPreview', array());
	$__finalCompiled .= '
				';
	if ($__vars['ticket']['prefix_id']) {
		$__finalCompiled .= '
					';
		if ($__vars['department']) {
			$__finalCompiled .= '
						<a href="' . $__templater->fn('link', array('support-tickets/departments', $__vars['department'], array('prefix_id' => $__vars['ticket']['prefix_id'], ), ), true) . '" class="labelLink" rel="nofollow">' . $__templater->fn('prefix', array('mjstTicket', $__vars['ticket'], 'html', '', ), true) . '</a>
					';
		} else {
			$__finalCompiled .= '
						' . $__templater->fn('prefix', array('support_ticket', $__vars['ticket'], 'html', '', ), true) . '
					';
		}
		$__finalCompiled .= '
				';
	}
	$__finalCompiled .= '
				<a href="' . $__templater->fn('link', array('support-tickets' . (($__templater->method($__vars['ticket'], 'isUnread', array()) AND (!$__vars['forceRead'])) ? '/unread' : ''), $__vars['ticket'], ), true) . '" class="" data-tp-primary="on" data-xf-init="' . ($__vars['canPreview'] ? 'preview-tooltip' : '') . '" data-preview-url="' . ($__vars['canPreview'] ? $__templater->fn('link', array('support-tickets/preview', $__vars['ticket'], ), true) : '') . '">' . $__templater->filter($__templater->method($__vars['ticket'], 'getFullTitle', array(true, )), array(array('raw', array()),), true) . '</a>
			</div>

			<div class="structItem-minor">
				';
	$__compilerTemp2 = '';
	$__compilerTemp2 .= '
						';
	if ($__vars['extraInfo']) {
		$__compilerTemp2 .= '
							<li>' . $__templater->escape($__vars['extraInfo']) . '</li>
						';
	}
	$__compilerTemp2 .= '
						';
	if ($__vars['chooseName']) {
		$__compilerTemp2 .= '
							<li>' . $__templater->formCheckBox(array(
			'standalone' => 'true',
		), array(array(
			'name' => $__vars['chooseName'] . '[]',
			'value' => $__vars['ticket']['support_ticket_id'],
			'class' => 'js-chooseItem',
			'_type' => 'option',
		))) . '</li>
						';
	} else if ($__vars['allowInlineMod'] AND $__templater->method($__vars['ticket'], 'canUseInlineModeration', array())) {
		$__compilerTemp2 .= '
							<li>' . $__templater->formCheckBox(array(
			'standalone' => 'true',
		), array(array(
			'value' => $__vars['ticket']['support_ticket_id'],
			'class' => 'js-inlineModToggle',
			'data-xf-init' => 'tooltip',
			'title' => $__templater->filter('Select for moderation', array(array('for_attr', array()),), false),
			'_type' => 'option',
		))) . '</li>
						';
	}
	$__compilerTemp2 .= '
					';
	if (strlen(trim($__compilerTemp2)) > 0) {
		$__finalCompiled .= '
					<ul class="structItem-extraInfo">
					' . $__compilerTemp2 . '
					</ul>
				';
	}
	$__finalCompiled .= '

				<ul class="structItem-parts">
					<li>' . $__templater->fn('username_link', array($__vars['ticket']['User'], false, array(
		'defaultname' => $__vars['ticket']['username'],
	))) . '</li>
					<li class="structItem-startDate"><a href="' . $__templater->fn('link', array('support-tickets', $__vars['ticket'], ), true) . '" rel="nofollow">' . $__templater->fn('date_dynamic', array($__vars['ticket']['open_date'], array(
	))) . '</a></li>
					';
	if ((!$__vars['department']) OR $__templater->method($__vars['department'], 'hasChildren', array())) {
		$__finalCompiled .= '
						<li><a href="' . $__templater->fn('link', array('support-tickets/departments', $__vars['ticket']['Department'], ), true) . '">' . $__templater->escape($__vars['ticket']['Department']['title']) . '</a></li>
					';
	}
	$__finalCompiled .= '
				</ul>
			</div>
		</div>
		<div class="structItem-cell structItem-cell--meta">
			<dl class="pairs pairs--justified structItem-minor structItem-metaItem structItem-metaItem--downloads">
				<dt>' . 'Replies' . '</dt>
				<dd>' . $__templater->filter($__vars['ticket']['reply_count'], array(array('number', array()),), true) . '</dd>
			</dl>
			<dl class="pairs pairs--justified structItem-minor structItem-metaItem structItem-metaItem--lastUpdate">
				<dd>
					<a href="' . $__templater->fn('link', array('support-tickets/latest', $__vars['ticket'], ), true) . '" rel="nofollow">' . $__templater->fn('date_dynamic', array($__vars['ticket']['last_message_date'], array(
		'class' => 'structItem-latestDate',
	))) . '</a>
					<div class="structItem-minor">
						';
	if ($__templater->method($__vars['xf']['visitor'], 'isIgnoring', array($__vars['ticket']['last_message_user_id'], ))) {
		$__finalCompiled .= '
							' . 'Ignored member' . '
						';
	} else {
		$__finalCompiled .= '
							' . $__templater->fn('username_link', array($__vars['ticket']['last_message_cache'], false, array(
		))) . '
						';
	}
	$__finalCompiled .= '
					</div>
				</dd>
			</dl>
		</div>
	</div>
';
	return $__finalCompiled;
},
'ticket_simple' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'ticket' => '!',
		'withMeta' => true,
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="contentRow">
		<div class="contentRow-figure">
			' . $__templater->fn('avatar', array($__vars['ticket']['User'], 'xxs', false, array(
	))) . '
		</div>
		<div class="contentRow-main contentRow-main--close">
			<a href="' . $__templater->fn('link', array('support-tickets', $__vars['ticket'], ), true) . '">' . $__templater->escape($__vars['ticket']['title']) . '</a>
			';
	if ($__vars['withMeta']) {
		$__finalCompiled .= '
				<div class="contentRow-minor contentRow-minor--smaller">
					<ul class="listInline listInline--bullet">
						<li>' . ($__templater->escape($__vars['ticket']['User']['username']) ?: $__templater->escape($__vars['ticket']['username'])) . '</li>
						<li>' . 'Updated' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->fn('date_dynamic', array($__vars['ticket']['last_update'], array(
		))) . '</li>
					</ul>
				</div>
			';
	}
	$__finalCompiled .= '
		</div>
	</div>
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '

';
	return $__finalCompiled;
});