<?php
// FROM HASH: fa68b54b0ad5488d137cdc3f7c95f4bb
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<hr class="formRowSep" />

' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'options[tools]',
		'selected' => $__vars['options']['tools'],
		'label' => 'Enable tools footer block',
		'_type' => 'option',
	)), array(
		'explain' => 'This option allows you to display a widget footer with links to referral tools.',
	));
	return $__finalCompiled;
});