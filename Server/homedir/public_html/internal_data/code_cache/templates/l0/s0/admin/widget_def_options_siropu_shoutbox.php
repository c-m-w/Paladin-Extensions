<?php
// FROM HASH: aa8b6f0f4a98000cf17da10134ed6fac
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<hr class="formRowSep" />

' . $__templater->formNumberBoxRow(array(
		'name' => 'options[height]',
		'value' => $__vars['options']['height'],
		'units' => 'Pixels',
		'min' => '0',
	), array(
		'label' => 'Shoutbox content height',
		'explain' => 'This option allows you to set a custom shoutbox content height for this widget.',
	)) . '

' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'options[sidebarStyle]',
		'checked' => $__vars['options']['sidebarStyle'],
		'label' => 'Enable sidebar style',
		'_type' => 'option',
	),
	array(
		'name' => 'options[hideTimestamp]',
		'checked' => $__vars['options']['hideTimestamp'],
		'label' => 'Hide shout date',
		'_type' => 'option',
	)), array(
	));
	return $__finalCompiled;
});