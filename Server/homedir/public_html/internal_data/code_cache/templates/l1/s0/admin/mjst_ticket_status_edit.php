<?php
// FROM HASH: fa03c66d68f4e866f3454b1fdc990861
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['ticketStatus'], 'isInsert', array())) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add ticket status');
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit ticket status' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['ticketStatus']['title']));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['ticketStatus'], 'isUpdate', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('', array(
			'href' => $__templater->fn('link', array('mjst-support/statuses/delete', $__vars['ticketStatus'], ), false),
			'icon' => 'delete',
			'overlay' => 'true',
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formTextBoxRow(array(
		'name' => 'title',
		'value' => ($__templater->method($__vars['ticketStatus'], 'exists', array()) ? $__vars['ticketStatus']['MasterTitle']['phrase_text'] : ''),
	), array(
		'label' => 'Title',
	)) . '

			' . $__templater->callMacro('public:color_picker_macros', 'color_picker', array(
		'name' => 'status_color',
		'value' => $__vars['ticketStatus']['status_color'],
		'label' => 'Status color',
		'rowClass' => 'formRow-styleProperty',
	), $__vars) . '
			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'group_active',
		'selected' => $__vars['ticketStatus']['group_active'],
		'label' => 'Group active',
		'_type' => 'option',
	),
	array(
		'name' => 'group_waiting_reply',
		'selected' => $__vars['ticketStatus']['group_waiting_reply'],
		'label' => 'Group waiting reply',
		'_type' => 'option',
	)), array(
		'label' => '',
	)) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
		'sticky' => 'true',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('mjst-support/statuses/save', $__vars['ticketStatus'], ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});