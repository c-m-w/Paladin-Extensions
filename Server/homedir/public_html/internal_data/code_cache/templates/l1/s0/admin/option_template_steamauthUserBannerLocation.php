<?php
// FROM HASH: d090a89c5c7f65b6835ada2d90bf08d2
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->formRadioRow(array(
		'name' => $__vars['inputName'],
		'value' => $__vars['option']['option_value'],
	), array(array(
		'value' => '0',
		'label' => 'Hide Steam Profile Banner',
		'_type' => 'option',
	),
	array(
		'value' => '1',
		'label' => 'Display Above User Extras',
		'_type' => 'option',
	),
	array(
		'value' => '2',
		'label' => 'Display Below User Extras',
		'_type' => 'option',
	)), array(
		'hint' => $__templater->escape($__vars['hintHtml']),
		'explain' => $__templater->escape($__vars['explainHtml']),
		'html' => $__templater->escape($__vars['listedHtml']),
	));
	return $__finalCompiled;
});