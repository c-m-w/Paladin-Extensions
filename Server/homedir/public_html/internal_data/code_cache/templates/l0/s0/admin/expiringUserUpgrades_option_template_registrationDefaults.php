<?php
// FROM HASH: aceb5dc0a07bad02d765f7c78ad764d1
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->formCheckBox(array(
	), array(array(
		'name' => $__vars['inputName'] . '[sv_exup_email_on_expiring_expired_upgrade]',
		'selected' => $__vars['option']['option_value']['sv_exup_email_on_expiring_expired_upgrade'],
		'label' => 'Receive expiring and expired user upgrade emails',
		'_type' => 'option',
	),
	array(
		'name' => $__vars['inputName'] . '[sv_exup_email_on_upgrade_purchase]',
		'selected' => $__vars['option']['option_value']['sv_exup_email_on_upgrade_purchase'],
		'label' => 'Receive user upgrade purchase emails',
		'_type' => 'option',
	),
	array(
		'name' => $__vars['inputName'] . '[sv_exup_email_on_upgrade_reversal]',
		'selected' => $__vars['option']['option_value']['sv_exup_email_on_upgrade_reversal'],
		'label' => 'Receive user upgrade payment reverseal emails',
		'_type' => 'option',
	)));
	return $__finalCompiled;
});