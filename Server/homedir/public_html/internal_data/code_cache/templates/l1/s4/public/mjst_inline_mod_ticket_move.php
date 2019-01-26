<?php
// FROM HASH: 888dc1ce2a63c31a80062f0885bd930f
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeJs(array(
		'src' => 'xf/prefix_menu.js',
		'min' => '1',
	));
	$__finalCompiled .= '

';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Inline moderation - Move tickets');
	$__finalCompiled .= '

';
	$__compilerTemp1 = array();
	if ($__templater->isTraversable($__vars['departments'])) {
		foreach ($__vars['departments'] AS $__vars['department']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['department']['department_id'],
				'label' => $__templater->escape($__vars['department']['title']),
				'_type' => 'option',
			);
		}
	}
	$__compilerTemp2 = '';
	if ($__templater->isTraversable($__vars['tickets'])) {
		foreach ($__vars['tickets'] AS $__vars['ticket']) {
			$__compilerTemp2 .= '
		' . $__templater->formHiddenVal('ids[]', $__vars['ticket']['support_ticket_id'], array(
			)) . '
	';
		}
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body js-prefixListenContainer">
			' . $__templater->formInfoRow('Are you sure you want to move ' . $__templater->escape($__vars['total']) . ' ticket(s)?', array(
		'rowtype' => 'confirm',
	)) . '
			' . $__templater->formSelectRow(array(
		'name' => 'target_department_id',
		'value' => $__vars['first']['department_id'],
		'class' => 'js-departmentList',
	), $__compilerTemp1, array(
		'label' => 'Destination department',
	)) . '

			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'apply_ticket_prefix',
		'label' => 'Apply prefix to selected tickets',
		'_dependent' => array('
						' . $__templater->callMacro('prefix_macros', 'select', array(
		'type' => 'support_ticket',
		'prefixes' => $__vars['prefixes'],
		'href' => $__templater->fn('link', array('support-tickets/departments/prefixes', ), false),
		'listenTo' => '< .js-prefixListenContainer | .js-departmentList',
	), $__vars) . '
					'),
		'_type' => 'option',
	)), array(
	)) . '

			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'notify_watchers',
		'value' => '1',
		'selected' => ($__vars['total'] == 1),
		'label' => 'Notify members watching the destination department',
		'_type' => 'option',
	)), array(
	)) . '

			' . $__templater->callMacro('mjst_helper_action', 'ticket_alert', array(
		'selected' => ($__vars['total'] == 1),
	), $__vars) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'move',
	), array(
	)) . '
	</div>

	' . $__compilerTemp2 . '

	' . $__templater->formHiddenVal('type', 'support_ticket', array(
	)) . '
	' . $__templater->formHiddenVal('action', 'move', array(
	)) . '
	' . $__templater->formHiddenVal('confirmed', '1', array(
	)) . '

	' . $__templater->fn('redirect_input', array($__vars['redirect'], null, true)) . '
', array(
		'action' => $__templater->fn('link', array('inline-mod', ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});