<?php
// FROM HASH: 97182fe7d525605a73478d97d57571ee
return array('macros' => array('ticket_alert' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'selected' => false,
		'alertName' => 'starter_alert',
		'reasonName' => 'starter_alert_reason',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => $__vars['alertName'],
		'selected' => $__vars['selected'],
		'label' => 'Notify ticket starter of this action.' . ' ' . 'Reason' . $__vars['xf']['language']['label_separator'],
		'_dependent' => array($__templater->formTextBox(array(
		'name' => $__vars['reasonName'],
		'placeholder' => 'Optional',
	))),
		'afterhint' => 'Note that the ticket starter will see this alert even if they can no longer view their ticket.',
		'_type' => 'option',
	)), array(
	)) . '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';

	return $__finalCompiled;
});