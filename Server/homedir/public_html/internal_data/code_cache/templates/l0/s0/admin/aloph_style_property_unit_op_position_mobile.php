<?php
// FROM HASH: d5d9fc22096cb154303b8d303b0eba55
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<input type="hidden" name="checkboxes[]" value="' . $__templater->escape($__vars['property']['property_id']) . '" />
    ' . $__templater->formRadioRow(array(
		'name' => 'properties[' . $__vars['property']['property_id'] . ']',
		'value' => $__vars['property']['property_value'],
	), array(array(
		'value' => 'textPublicControlsMobile',
		'label' => 'Text: Public Controls',
		'_type' => 'option',
	),
	array(
		'value' => 'leftCornerMobile',
		'label' => 'Avatar Ribbon: Top Left Corner',
		'_type' => 'option',
	),
	array(
		'value' => 'rightCornerMobile',
		'label' => 'Avatar Ribbon: Top Right Corner',
		'_type' => 'option',
	),
	array(
		'value' => 'topMobile',
		'label' => 'Avatar Ribbon: Top',
		'_type' => 'option',
	),
	array(
		'value' => 'bottomMobile',
		'label' => 'Avatar Ribbon: Bottom',
		'_type' => 'option',
	)), array(
		'label' => $__templater->escape($__vars['property']['title']),
		'explain' => $__templater->escape($__vars['property']['description']),
	));
	return $__finalCompiled;
});