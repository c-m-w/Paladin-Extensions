<?php
// FROM HASH: a3f125ac026179019bd910e03680c78f
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->callMacro('prefix_macros', 'select', array(
		'name' => 'na',
		'prefixes' => $__vars['prefixes'],
		'type' => 'support_ticket',
	), $__vars);
	return $__finalCompiled;
});