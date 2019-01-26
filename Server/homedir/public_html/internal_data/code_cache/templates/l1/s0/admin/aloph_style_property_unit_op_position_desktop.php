<?php
// FROM HASH: 558c2a57499cae5319dd182ab27a58cb
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<input type="hidden" name="checkboxes[]" value="' . $__templater->escape($__vars['property']['property_id']) . '" />
    ' . $__templater->formRadioRow(array(
		'name' => 'properties[' . $__vars['property']['property_id'] . ']',
		'value' => $__vars['property']['property_value'],
	), array(array(
		'value' => 'textPublicControlsDesktop',
		'label' => 'Text: Public Controls',
		'_type' => 'option',
	),
	array(
		'value' => 'leftCornerDesktop',
		'label' => 'Avatar Ribbon: Top Left Corner',
		'_type' => 'option',
	),
	array(
		'value' => 'rightCornerDesktop',
		'label' => 'Avatar Ribbon: Top Right Corner',
		'_type' => 'option',
	),
	array(
		'value' => 'topDesktop',
		'label' => 'Avatar Ribbon: Top',
		'_type' => 'option',
	),
	array(
		'value' => 'bottomDesktop',
		'label' => 'Avatar Ribbon: Bottom',
		'_type' => 'option',
	)), array(
		'label' => $__templater->escape($__vars['property']['title']),
		'explain' => $__templater->escape($__vars['property']['description']),
	));
	return $__finalCompiled;
});