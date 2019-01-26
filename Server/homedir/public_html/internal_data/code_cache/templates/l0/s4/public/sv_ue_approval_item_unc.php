<?php
// FROM HASH: 20fb4358b0d5a3ca79c77fe9c6276b2d
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->formRow('
	' . $__templater->fn('username_link', array($__vars['user'], true, array(
		'username' => $__vars['content']['to_username'],
	))) . '
', array(
		'label' => 'User name change',
	)) . '

' . $__templater->formRow('
	' . $__templater->fn('username_link', array($__vars['user'], true, array(
	))) . '
', array(
		'label' => 'Requester',
	)) . '

';
	if ($__templater->method($__vars['xf']['visitor'], 'canViewIps', array()) AND $__vars['content']['ip_address']) {
		$__finalCompiled .= '
	' . $__templater->formRow('
		<a href="' . $__templater->fn('link', array('misc/ip-info', null, array('ip' => $__templater->filter($__vars['content']['ip_address'], array(array('ip', array()),), false), ), ), true) . '" target="_blank">
			' . $__templater->filter($__vars['content']['ip_address'], array(array('ip', array()),), true) . '
		</a>
	', array(
			'label' => 'IP address',
		)) . '
';
	}
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['previousUsernameChanges'], 'empty', array())) {
		$__finalCompiled .= '
	';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['previousUsernameChanges'])) {
			foreach ($__vars['previousUsernameChanges'] AS $__vars['uncId'] => $__vars['previousUsernameChange']) {
				$__compilerTemp1 .= trim('
				<li><a href="' . $__templater->fn('link', array('members/username-change', '', array('unc_id' => $__vars['uncId'], ), ), true) . '" data-xf-click="overlay">' . $__templater->escape($__vars['previousUsernameChange']['to_username']) . '</a></li>
			');
			}
		}
		$__compilerTemp2 = '';
		if ($__vars['unseenUsernameChanges']) {
			$__compilerTemp2 .= '
				<li><a href="' . $__templater->fn('link', array('members/username-changes', $__vars['user'], ), true) . '" data-xf-click="overlay">' . 'and ' . $__templater->escape($__vars['unseenUsernameChanges']) . ' more.' . '</a></li>
			';
		}
		$__finalCompiled .= $__templater->formRow('
		<ul class="listInline listInline--comma">
			' . $__compilerTemp1 . '

			' . $__compilerTemp2 . '
		</ul>
	', array(
			'label' => 'Previous names',
		)) . '
';
	}
	$__finalCompiled .= '

' . $__templater->formRow('
	' . $__templater->filter($__vars['user']['message_count'], array(array('number', array()),), true) . '
', array(
		'label' => 'Messages',
	)) . '

' . $__templater->formRow('
	' . $__templater->fn('date_dynamic', array($__vars['content']['date'], array(
	))) . '
', array(
		'label' => 'Request date',
	)) . '

';
	if ($__vars['content']['user_note']) {
		$__finalCompiled .= '
	' . $__templater->formRow('
		' . $__templater->escape($__vars['content']['user_note']) . '
	', array(
			'label' => 'Note',
		)) . '
';
	}
	$__finalCompiled .= '

' . $__templater->formRadioRow(array(
		'name' => 'queue[' . $__vars['unapprovedItem']['content_type'] . '][' . $__vars['unapprovedItem']['content_id'] . ']',
	), array(array(
		'value' => '',
		'checked' => 'checked',
		'label' => 'Do nothing',
		'_type' => 'option',
	),
	array(
		'value' => 'approve',
		'label' => 'Approve',
		'_type' => 'option',
	),
	array(
		'value' => 'reject',
		'label' => 'Reject',
		'_type' => 'option',
	)), array(
		'label' => 'Action',
	)) . '

' . $__templater->formTextBoxRow(array(
		'name' => 'note[' . $__vars['unapprovedItem']['content_type'] . '][' . $__vars['unapprovedItem']['content_id'] . ']',
		'maxlength' => $__templater->fn('max_length', array($__vars['content'], 'moderator_note', ), false),
		'placeholder' => 'Optional',
	), array(
		'label' => 'Note',
		'explain' => 'This note will be included in the notification sent to users.',
	)) . '

';
	if ($__templater->method($__vars['content'], 'canEditPrivacy', array())) {
		$__finalCompiled .= '
	' . $__templater->formCheckBoxRow(array(
		), array(array(
			'label' => 'Private',
			'name' => 'is_private[' . $__vars['unapprovedItem']['content_type'] . '][' . $__vars['unapprovedItem']['content_id'] . ']',
			'selected' => $__vars['content']['is_private'],
			'_type' => 'option',
		)), array(
			'explain' => 'If selected, this user name change will only be visible to staff and the user.',
		)) . '
';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
});