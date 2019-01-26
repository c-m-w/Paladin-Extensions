<?php
// FROM HASH: 6fa97fdc6eb65e6e9febe1d7ebaaee35
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->formRadioRow(array(
		'name' => $__vars['inputName'] . '[type]',
	), array(array(
		'label' => 'Default URL' . ' (' . $__templater->fn('link_type', array('public', 'canonical:account/upgrades', ), true) . ')',
		'value' => 'default',
		'selected' => $__vars['option']['option_value']['type'] == 'default',
		'_type' => 'option',
	),
	array(
		'label' => 'Custom URL' . $__vars['xf']['language']['label_separator'],
		'value' => 'custom',
		'selected' => $__vars['option']['option_value']['type'] == 'custom',
		'_dependent' => array($__templater->formTextBox(array(
		'name' => $__vars['inputName'] . '[custom]',
		'value' => $__vars['option']['option_value']['custom'],
	))),
		'_type' => 'option',
	)), array(
		'label' => $__templater->escape($__vars['option']['title']),
		'hint' => $__templater->escape($__vars['hintHtml']),
		'explain' => $__templater->escape($__vars['explainHtml']),
		'html' => $__templater->escape($__vars['listedHtml']),
	));
	return $__finalCompiled;
});