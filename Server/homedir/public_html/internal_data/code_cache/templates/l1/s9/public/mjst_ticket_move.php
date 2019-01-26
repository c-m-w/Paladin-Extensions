<?php
// FROM HASH: fa60a0eb5af83c81a1ed302bb4ce884e
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Move ticket' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->fn('prefix', array('support_ticket', $__vars['ticket'], 'escaped', ), true) . $__templater->escape($__vars['ticket']['title']));
	$__finalCompiled .= '
';
	$__templater->pageParams['pageH1'] = $__templater->preEscaped('Move ticket' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->fn('prefix', array('support_ticket', $__vars['ticket'], ), true) . $__templater->escape($__vars['ticket']['title']));
	$__finalCompiled .= '

';
	$__templater->breadcrumbs($__templater->method($__vars['ticket'], 'getBreadcrumbs', array()));
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
	if ($__templater->method($__vars['ticket'], 'canSendModeratorActionAlert', array())) {
		$__compilerTemp2 .= '
				' . $__templater->callMacro('mjst_helper_action', 'ticket_alert', array(
			'selected' => true,
		), $__vars) . '
			';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body js-prefixListenContainer">
			' . $__templater->formPrefixInputRow($__vars['prefixes'], array(
		'type' => 'support_ticket',
		'prefix-value' => $__vars['ticket']['prefix_id'],
		'textbox-value' => $__vars['ticket']['title'],
		'href' => $__templater->fn('link', array('support-tickets/departments/prefixes', ), false),
		'listen-to' => '< .js-prefixListenContainer | .js-departmentList',
		'autofocus' => 'autofocus',
		'maxlength' => $__templater->fn('max_length', array($__vars['ticket'], 'title', ), false),
	), array(
		'label' => 'Title',
	)) . '

			' . $__templater->formSelectRow(array(
		'name' => 'target_department_id',
		'value' => $__vars['ticket']['department_id'],
	), $__compilerTemp1, array(
		'label' => 'Destination department',
	)) . '

			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'notify_watchers',
		'value' => '1',
		'selected' => true,
		'label' => 'Notify members watching the destination department',
		'_type' => 'option',
	)), array(
	)) . '

			' . $__compilerTemp2 . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
		'sticky' => 'true',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('support-tickets/move', $__vars['ticket'], ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});