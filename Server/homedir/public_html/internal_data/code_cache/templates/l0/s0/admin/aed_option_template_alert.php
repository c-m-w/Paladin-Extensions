<?php
// FROM HASH: a499403fcc9267c1d5d0a42c38cf1a1c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__compilerTemp1 = array(array(
		'value' => '0',
		'label' => '&nbsp;',
		'_type' => 'option',
	));
	$__compilerTemp2 = $__templater->method($__vars['nodeTree'], 'getFlattened', array());
	if ($__templater->isTraversable($__compilerTemp2)) {
		foreach ($__compilerTemp2 AS $__vars['treeEntry']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['treeEntry']['record']['node_id'],
				'disabled' => ($__vars['treeEntry']['record']['node_type_id'] != 'Forum'),
				'label' => '
                        ' . $__templater->fn('repeat', array('--', $__vars['treeEntry']['depth'], ), true) . ' ' . $__templater->escape($__vars['treeEntry']['record']['title']) . '
                    ',
				'_type' => 'option',
			);
		}
	}
	$__compilerTemp1 = $__templater->mergeChoiceOptions($__compilerTemp1, $__vars['formatParams']);
	$__finalCompiled .= $__templater->formRadioRow(array(
		'name' => $__vars['inputName'] . '[mode]',
		'value' => $__vars['option']['option_value']['mode'],
	), array(array(
		'value' => 'log',
		'label' => 'log',
		'_type' => 'option',
	),
	array(
		'value' => 'thread',
		'data-hide' => 'true',
		'label' => 'Thread',
		'_dependent' => array('
            <div>' . 'Thread starter' . $__vars['xf']['language']['label_separator'] . '</div>
            ' . $__templater->formTextBox(array(
		'name' => $__vars['inputName'] . '[thread_user]',
		'value' => $__vars['option']['option_value']['thread_user'],
		'ac' => 'single',
	)) . '
        ', '
            <div>' . 'Forum' . $__vars['xf']['language']['label_separator'] . '</div>
            ' . $__templater->formSelect(array(
		'name' => $__vars['inputName'] . '[node_id]',
		'value' => $__vars['option']['option_value']['node_id'],
	), $__compilerTemp1) . '
        '),
		'_type' => 'option',
	),
	array(
		'value' => 'conversation',
		'data-hide' => 'true',
		'label' => 'Conversation',
		'_dependent' => array('
            <div>' . 'Conversation starter' . $__vars['xf']['language']['label_separator'] . '</div>
            ' . $__templater->formTextBox(array(
		'name' => $__vars['inputName'] . '[con_starter]',
		'value' => $__vars['option']['option_value']['con_starter'],
		'ac' => 'single',
	)) . '
        ', '
            <div>' . 'Conversation participants' . $__vars['xf']['language']['label_separator'] . '</div>
            ' . $__templater->formTextBox(array(
		'name' => $__vars['inputName'] . '[con_participants]',
		'value' => $__vars['option']['option_value']['con_participants'],
		'ac' => 'multiple',
	)) . '
        '),
		'_type' => 'option',
	)), array(
		'label' => $__templater->escape($__vars['option']['title']),
		'hint' => $__templater->escape($__vars['hintHtml']),
		'explain' => $__templater->escape($__vars['explainHtml']),
		'html' => $__templater->escape($__vars['listedHtml']),
	));
	return $__finalCompiled;
});