<?php
// FROM HASH: aa7b3ac19c8a50dbd85672142a5aaaa9
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => $__vars['inputName'] . '[messageOpenInvite]',
		'value' => '1',
		'selected' => $__vars['option']['option_value']['messageOpenInvite'],
		'label' => '
            ' . 'Allow anyone in the conversation to invite others' . '
        ',
		'_type' => 'option',
	),
	array(
		'name' => $__vars['inputName'] . '[messageLocked]',
		'value' => '1',
		'selected' => $__vars['option']['option_value']['messageLocked'],
		'label' => '
            ' . 'Lock conversation (no responses will be allowed)' . '
        ',
		'_type' => 'option',
	)), array(
		'label' => $__templater->escape($__vars['option']['title']),
		'hint' => $__templater->escape($__vars['hintHtml']),
		'explain' => $__templater->escape($__vars['explainHtml']),
		'html' => $__templater->escape($__vars['listedHtml']),
	));
	return $__finalCompiled;
});