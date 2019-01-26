<?php
// FROM HASH: fe51e8d3e482a5b00c342fbf859a5690
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->formNumberBoxRow(array(
		'name' => 'quantity',
		'value' => $__vars['upgrade']['quantity'],
		'min' => '0',
	), array(
		'label' => 'Slots',
		'explain' => 'The maximum number of purchases that can be made for this upgrade. Use 0 to disable.',
	)) . '
';
	return $__finalCompiled;
});