<?php
// FROM HASH: 005813b67c276b0f3b9fda5adb125455
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['ticketEscalation'], 'isInsert', array())) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add escalation');
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit escalation' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['ticketEscalation']['title']));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['ticketEscalation'], 'isUpdate', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('', array(
			'href' => $__templater->fn('link', array('mjst-support/escalations/delete', $__vars['ticketEscalation'], ), false),
			'icon' => 'delete',
			'overlay' => 'true',
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

';
	$__compilerTemp1 = array();
	if ($__templater->isTraversable($__vars['departments'])) {
		foreach ($__vars['departments'] AS $__vars['department']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['department']['department_id'],
				'label' => ' ' . $__templater->escape($__vars['department']['title']),
				'_type' => 'option',
			);
		}
	}
	$__compilerTemp2 = array();
	if ($__templater->isTraversable($__vars['ticketStatuses'])) {
		foreach ($__vars['ticketStatuses'] AS $__vars['ticketStatus']) {
			$__compilerTemp2[] = array(
				'value' => $__vars['ticketStatus']['ticket_status_id'],
				'label' => ' ' . $__templater->escape($__vars['ticketStatus']['title']),
				'_type' => 'option',
			);
		}
	}
	$__compilerTemp3 = array(array(
		'value' => '0',
		'label' => 'No change',
		'_type' => 'option',
	));
	if ($__templater->isTraversable($__vars['departments'])) {
		foreach ($__vars['departments'] AS $__vars['department']) {
			$__compilerTemp3[] = array(
				'value' => $__vars['department']['department_id'],
				'label' => ' ' . $__templater->escape($__vars['department']['title']),
				'_type' => 'option',
			);
		}
	}
	$__compilerTemp4 = array(array(
		'value' => '0',
		'label' => 'No change',
		'_type' => 'option',
	));
	if ($__templater->isTraversable($__vars['ticketStatuses'])) {
		foreach ($__vars['ticketStatuses'] AS $__vars['ticketStatus']) {
			$__compilerTemp4[] = array(
				'value' => $__vars['ticketStatus']['ticket_status_id'],
				'label' => ' ' . $__templater->escape($__vars['ticketStatus']['title']),
				'_type' => 'option',
			);
		}
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formTextBoxRow(array(
		'name' => 'title',
		'value' => $__vars['ticketEscalation']['title'],
	), array(
		'label' => 'Title',
	)) . '
		</div>
		<h3 class="block-formSectionHeader">
			<span class="block-formSectionHeader-aligner">' . 'Conditions' . '</span>
		</h3>
		<div class="block-body">
			' . $__templater->formSelectRow(array(
		'name' => 'department_ids[]',
		'value' => $__vars['ticketEscalation']['department_ids'],
		'multiple' => 'true',
	), $__compilerTemp1, array(
		'label' => 'Departments',
	)) . '
			' . $__templater->formSelectRow(array(
		'name' => 'ticket_status_ids[]',
		'value' => $__vars['ticketEscalation']['ticket_status_ids'],
		'multiple' => 'true',
	), $__compilerTemp2, array(
		'label' => 'Statuses',
	)) . '
			' . $__templater->formSelectRow(array(
		'name' => 'priorities[]',
		'value' => $__vars['ticketEscalation']['priorities'],
		'multiple' => 'true',
	), array(array(
		'value' => '1',
		'label' => 'High',
		'_type' => 'option',
	),
	array(
		'value' => '2',
		'label' => 'Medium',
		'_type' => 'option',
	),
	array(
		'value' => '3',
		'label' => 'Low',
		'_type' => 'option',
	)), array(
		'label' => 'Priorities',
	)) . '
			' . $__templater->formNumberBoxRow(array(
		'name' => 'time_elapsed',
		'value' => $__vars['ticketEscalation']['time_elapsed'],
		'min' => '0',
		'step' => '1',
	), array(
		'label' => 'Time elapsed',
		'explain' => 'Minutes since last reply',
	)) . '
		</div>
		<h3 class="block-formSectionHeader">
			<span class="block-formSectionHeader-aligner">' . 'Actions' . '</span>
		</h3>
		<div class="block-body">
			' . $__templater->formSelectRow(array(
		'name' => 'new_department_id',
		'value' => $__vars['ticketEscalation']['new_department_id'],
	), $__compilerTemp3, array(
		'label' => 'Departments',
	)) . '
			' . $__templater->formSelectRow(array(
		'name' => 'new_ticket_status_id',
		'value' => $__vars['ticketEscalation']['new_ticket_status_id'],
	), $__compilerTemp4, array(
		'label' => 'Statuses',
	)) . '
			' . $__templater->formSelectRow(array(
		'name' => 'new_priority',
		'value' => $__vars['ticketEscalation']['new_priority'],
	), array(array(
		'value' => '0',
		'label' => 'No change',
		'_type' => 'option',
	),
	array(
		'value' => '1',
		'label' => 'High',
		'_type' => 'option',
	),
	array(
		'value' => '2',
		'label' => 'Medium',
		'_type' => 'option',
	),
	array(
		'value' => '3',
		'label' => 'Low',
		'_type' => 'option',
	)), array(
		'label' => 'Priorities',
	)) . '
		</div>
		<h3 class="block-formSectionHeader">
			<span class="block-formSectionHeader-aligner">' . 'Add reply' . '</span>
		</h3>
		<div class="block-body">
			' . $__templater->formTextBoxRow(array(
		'name' => 'username',
		'ac' => 'single',
		'value' => $__vars['ticketEscalation']['User']['username'],
	), array(
		'label' => 'User',
	)) . '
			' . $__templater->formEditorRow(array(
		'name' => 'reply_message',
		'value' => $__vars['ticketEscalation']['reply_message'],
		'data-min-height' => '200',
	), array(
		'label' => 'Reply message',
	)) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
		'sticky' => 'true',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('mjst-support/escalations/save', $__vars['ticketEscalation'], ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});