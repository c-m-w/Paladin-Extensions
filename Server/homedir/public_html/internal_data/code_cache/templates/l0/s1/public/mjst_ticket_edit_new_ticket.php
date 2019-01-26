<?php
// FROM HASH: c4439a4c4379256bc6f92613e8dcd09f
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->callMacro('mjst_ticket_list_macros', 'item', array(
		'ticket' => $__vars['ticket'],
		'allowInlineMod' => ($__vars['noInlineMod'] ? false : true),
		'department' => ($__vars['departmentName'] ? null : $__vars['department']),
	), $__vars);
	return $__finalCompiled;
});