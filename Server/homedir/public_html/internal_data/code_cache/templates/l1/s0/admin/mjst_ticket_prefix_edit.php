<?php
// FROM HASH: 3af2d7c9e5ac983a8d47cb8d0a156956
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__compilerTemp1 = $__vars;
	$__compilerTemp1['extraOptions'] = $__templater->preEscaped('
		' . $__templater->callMacro('mjst_ticket_prefix_edit_macros', 'department_ids', array(
		'departmentIds' => $__vars['prefix']['department_ids'],
		'departments' => $__vars['departments'],
	), $__vars) . '
	');
	$__finalCompiled .= $__templater->includeTemplate('base_prefix_edit', $__compilerTemp1);
	return $__finalCompiled;
});