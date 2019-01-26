<?php
// FROM HASH: f32b8c109e7e809427c259c5a062ea36
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['isWatched']) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Unwatch category');
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Watch category');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	$__templater->breadcrumbs($__templater->method($__vars['category'], 'getBreadcrumbs', array()));
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__vars['isWatched']) {
		$__compilerTemp1 .= '
				' . $__templater->formInfoRow('
					' . 'Are you sure you want to unwatch this category?' . '
				', array(
			'rowtype' => 'confirm',
		)) . '
				' . $__templater->formHiddenVal('stop', '1', array(
		)) . '
			';
	} else {
		$__compilerTemp1 .= '
				' . $__templater->formRadioRow(array(
			'name' => 'notify_on',
			'value' => 'resource',
		), array(array(
			'value' => 'resource',
			'label' => 'New resources only',
			'_type' => 'option',
		),
		array(
			'value' => 'update',
			'label' => 'New resources and updates',
			'_type' => 'option',
		),
		array(
			'value' => '',
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

				' . $__templater->formCheckBoxRow(array(
		), array(array(
			'name' => 'include_children',
			'selected' => true,
			'label' => 'Include notifications for content in sub-categories',
			'_type' => 'option',
		)), array(
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
		'action' => $__templater->fn('link', array('resources/categories/watch', $__vars['category'], ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});