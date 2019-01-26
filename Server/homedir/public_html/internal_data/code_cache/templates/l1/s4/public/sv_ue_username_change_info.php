<?php
// FROM HASH: dbcd53a2bc3e9d15918a439aa114fbca
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('User name change for ' . $__templater->escape($__vars['user']['username']) . '');
	$__finalCompiled .= '

<div class="form block">
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formRow('
				' . $__templater->escape($__vars['usernameChange']['to_username']) . '
			', array(
		'label' => 'Name',
	)) . '

			';
	$__compilerTemp1 = '';
	if ($__templater->method($__vars['xf']['visitor'], 'canViewIps', array()) AND $__vars['usernameChange']['ip_address']) {
		$__compilerTemp1 .= '
						<li><a href="' . $__templater->fn('link', array('misc/ip-info', null, array('ip' => $__templater->filter($__vars['usernameChange']['ip_address'], array(array('ip', array()),), false), ), ), true) . '" target="_blank">
							' . $__templater->filter($__vars['usernameChange']['ip_address'], array(array('ip', array()),), true) . '
						</a></li>
					';
	}
	$__compilerTemp2 = '';
	if ($__vars['usernameChange']['user_note']) {
		$__compilerTemp2 .= '
					<div class="u-muted">' . $__templater->escape($__vars['usernameChange']['user_note']) . '</div>
				';
	}
	$__finalCompiled .= $__templater->formRow('
				<ul class="listInline listInline--bullet">
					<li>' . $__templater->fn('username_link', array($__vars['user'], true, array(
		'username' => $__vars['usernameChange']['from_username'],
	))) . '</li>
					' . $__compilerTemp1 . '
					<li>' . $__templater->fn('date_dynamic', array($__vars['usernameChange']['date'], array(
	))) . '</li>
				</ul>

				' . $__compilerTemp2 . '
			', array(
		'label' => 'Requester',
	)) . '

			';
	$__compilerTemp3 = '';
	if ($__vars['usernameChange']['status'] == 'approved') {
		$__compilerTemp3 .= '
					' . 'Approved' . '
				';
	} else if ($__vars['usernameChange']['status'] == 'denied') {
		$__compilerTemp3 .= '
					' . 'Rejected' . '
				';
	} else {
		$__compilerTemp3 .= '
					' . 'Pending' . '
				';
	}
	$__finalCompiled .= $__templater->formRow('
				' . $__compilerTemp3 . '
			', array(
		'label' => 'Status',
	)) . '

			';
	if ($__templater->method($__vars['xf']['visitor'], 'canApproveRejectUsername', array()) AND $__vars['moderator']) {
		$__finalCompiled .= '
				';
		$__compilerTemp4 = '';
		if ($__vars['usernameChange']['moderator_note']) {
			$__compilerTemp4 .= '
						<div class="u-muted">' . $__templater->escape($__vars['usernameChange']['moderator_note']) . '</div>
					';
		}
		$__finalCompiled .= $__templater->formRow('
					<ul class="listInline listInline--bullet">
						<li>' . $__templater->fn('username_link', array($__vars['moderator'], true, array(
		))) . '</li>
						<li>' . $__templater->fn('date_dynamic', array($__vars['usernameChange']['moderation_date'], array(
		))) . '</li>
					</ul>

					' . $__compilerTemp4 . '
				', array(
			'label' => 'Moderator',
		)) . '
			';
	}
	$__finalCompiled .= '
		</div>

		';
	if ($__templater->method($__vars['usernameChange'], 'canEditPrivacy', array())) {
		$__finalCompiled .= '
			' . $__templater->form('
				' . $__templater->formCheckBoxRow(array(
		), array(array(
			'label' => 'Private',
			'name' => 'is_private',
			'selected' => $__vars['usernameChange']['is_private'],
			'_type' => 'option',
		)), array(
			'explain' => 'If selected, this user name change will only be visible to staff and the user.',
		)) . '

				' . $__templater->formSubmitRow(array(
			'icon' => 'save',
		), array(
		)) . '
				' . $__templater->fn('redirect_input', array($__vars['redirect'], null, true)) . '
			', array(
			'action' => $__templater->fn('link', array('members/username-change', $__vars['user'], array('unc_id' => $__vars['usernameChange']['unc_id'], ), ), false),
		)) . '
		';
	} else if ($__vars['usernameChange']['is_private'] AND ($__vars['xf']['options']['useressDisplayProfileTab'] !== 'nobody')) {
		$__finalCompiled .= '
				' . $__templater->formCheckBoxRow(array(
		), array(array(
			'label' => 'Private',
			'name' => 'is_private',
			'selected' => $__vars['usernameChange']['is_private'],
			'readonly' => 'readonly',
			'disabled' => 'disabled',
			'_type' => 'option',
		)), array(
			'explain' => 'If selected, this user name change will only be visible to staff and the user.',
		)) . '
		';
	}
	$__finalCompiled .= '
	</div>
</div>';
	return $__finalCompiled;
});