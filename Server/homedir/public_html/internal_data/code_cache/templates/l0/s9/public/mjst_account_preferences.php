<?php
// FROM HASH: 5bd0473eb80b9a60361b30befa1ae19e
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__compilerTemp1 = array();
	if ($__vars['xf']['options']['mjstDisableEmail']) {
		$__compilerTemp1[] = array(
			'name' => 'option[disable_email_on_support_ticket]',
			'checked' => (!$__vars['xf']['visitor']['Option']['disable_email_on_support_ticket']),
			'label' => 'Receive email when a new support ticket message is received',
			'_type' => 'option',
		);
	} else {
		$__compilerTemp1[] = array(
			'name' => 'option[email_on_support_ticket]',
			'checked' => $__vars['xf']['visitor']['Option']['email_on_support_ticket'],
			'label' => 'Receive email when a new support ticket message is received',
			'_type' => 'option',
		);
	}
	$__finalCompiled .= $__templater->formCheckBoxRow(array(
	), $__compilerTemp1, array(
		'label' => '',
		'explain' => 'Email notifications for new support tickets, replies to existing support tickets, and being added to an existing support ticket.',
	));
	return $__finalCompiled;
});