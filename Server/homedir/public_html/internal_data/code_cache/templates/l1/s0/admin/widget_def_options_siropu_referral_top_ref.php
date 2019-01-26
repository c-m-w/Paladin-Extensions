<?php
// FROM HASH: 88c4d156b1cec76e8bcb19b361972442
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<hr class="formRowSep" />

' . $__templater->formRadioRow(array(
		'name' => 'options[type]',
	), array(array(
		'value' => 'allTime',
		'selected' => $__vars['options']['type'] == 'allTime',
		'label' => 'All time',
		'_type' => 'option',
	),
	array(
		'value' => 'currentMonth',
		'selected' => $__vars['options']['type'] == 'currentMonth',
		'label' => 'Current month',
		'_type' => 'option',
	)), array(
	)) . '

' . $__templater->formNumberBoxRow(array(
		'name' => 'options[limit]',
		'value' => $__vars['options']['limit'],
		'min' => '3',
	), array(
		'label' => 'Maximum entries',
	)) . '

' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'options[compact]',
		'value' => '1',
		'selected' => $__vars['options']['compact'],
		'label' => 'Use compact mode',
		'_type' => 'option',
	)), array(
	));
	return $__finalCompiled;
});