<?php
// FROM HASH: c95810538e052783ad027c1052980e51
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->formEditorRow(array(
		'name' => $__vars['inputName'],
		'value' => $__vars['option']['option_value'],
		'data-min-height' => '100',
	), array(
		'label' => $__templater->escape($__vars['option']['title']),
		'hint' => $__templater->escape($__vars['hintHtml']),
		'explain' => $__templater->escape($__vars['explainHtml']),
		'html' => $__templater->escape($__vars['listedHtml']),
	));
	return $__finalCompiled;
});