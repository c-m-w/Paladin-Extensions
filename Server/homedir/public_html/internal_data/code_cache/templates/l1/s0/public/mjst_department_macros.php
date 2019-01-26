<?php
// FROM HASH: e8670aaf2877b7399b9fb9fd6c5e124c
return array('macros' => array('department_page_options' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'department' => '!',
		'ticket' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__templater->setPageParam('department', $__vars['department']);
	$__finalCompiled .= '

	';
	if ($__vars['ticket']) {
		$__finalCompiled .= '
		';
		$__templater->setPageParam('searchConstraints', array('Tickets' => array('search_type' => 'support_ticket_message', ), 'This department' => array('search_type' => 'support_ticket_message', 'c' => array('departments' => array($__vars['department']['department_id'], ), 'child_departments' => 1, ), ), 'This ticket' => array('search_type' => 'support_ticket_message', 'c' => array('ticket' => $__vars['ticket']['support_ticket_id'], ), ), ));
		$__finalCompiled .= '
	';
	} else {
		$__finalCompiled .= '
		';
		$__templater->setPageParam('searchConstraints', array('Tickets' => array('search_type' => 'support_ticket_message', ), 'This department' => array('search_type' => 'support_ticket_message', 'c' => array('departments' => array($__vars['department']['department_id'], ), 'child_departments' => 1, ), ), ));
		$__finalCompiled .= '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';

	return $__finalCompiled;
});