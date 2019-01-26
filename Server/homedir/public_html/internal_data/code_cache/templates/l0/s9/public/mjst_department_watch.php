<?php
// FROM HASH: 9a33e8828092b6922c059db7946c3918
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['isWatched']) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Unwatch department');
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Watch department');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	$__templater->breadcrumbs($__templater->method($__vars['department'], 'getBreadcrumbs', array()));
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__vars['isWatched']) {
		$__compilerTemp1 .= '
				' . $__templater->formInfoRow('
					' . 'Are you sure you want to unwatch this department?' . '
				', array(
			'rowtype' => 'confirm',
		)) . '
				' . $__templater->formHiddenVal('stop', '1', array(
		)) . '
			';
	} else {
		$__compilerTemp1 .= '
				' . $__templater->formRadioRow(array(
			'name' => 'notify',
			'value' => 'ticket',
		), array(array(
			'value' => 'ticket',
			'label' => 'New tickets',
			'_type' => 'option',
		),
		array(
			'value' => 'message',
			'label' => 'New messages',
			'_type' => 'option',
		),
		array(
			'value' => '',
			'hint' => 'The department will still be listed on the watched departments page, which can be used to list only the departments you\'re interested in.',
			'label' => 'Don\'t send notifications',
			'_type' => 'option',
		)), array(
			'label' => 'Send notifications for',
		)) . '

				' . $__templater->formCheckBoxRow(array(
		), array(array(
			'name' => 'send_alert',
			'value' => '1',
			'selected' => true,
			'label' => 'Alerts',
			'_type' => 'option',
		),
		array(
			'name' => 'send_email',
			'value' => '1',
			'label' => 'Emails',
			'_type' => 'option',
		)), array(
			'label' => 'Send notifications via',
		)) . '
			';
	}
	$__compilerTemp2 = '';
	if ($__vars['isWatched']) {
		$__compilerTemp2 .= '
			' . $__templater->formSubmitRow(array(
			'submit' => 'Unwatch',
			'icon' => 'notificationsOff',
		), array(
			'rowtype' => 'simple',
		)) . '
		';
	} else {
		$__compilerTemp2 .= '
			' . $__templater->formSubmitRow(array(
			'submit' => 'Watch',
			'icon' => 'notificationsOn',
		), array(
		)) . '
		';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__compilerTemp1 . '
		</div>
		' . $__compilerTemp2 . '
	</div>
', array(
		'action' => $__templater->fn('link', array('support-tickets/departments/watch', $__vars['department'], ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});