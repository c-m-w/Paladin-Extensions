<?php
// FROM HASH: 33c973c2cbcb464e1900484341c31356
return array('macros' => array('ticket_page_options' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'department' => '!',
		'ticket' => null,
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__templater->setPageParam('ticketDepartment', $__vars['department']);
	$__finalCompiled .= '

	';
	$__templater->setPageParam('searchConstraints', array('Tickets' => array('search_type' => 'support_ticket', ), 'This department' => array('search_type' => 'support_ticket', 'd' => array('categories' => array($__vars['department']['department_id'], ), ), ), ));
	$__finalCompiled .= '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';

	return $__finalCompiled;
});