<?php
// FROM HASH: 6909f2a3823aee3293c65a56f3e51e1c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__compilerTemp1 = $__vars;
	$__compilerTemp1['extraOptions'] = $__templater->preEscaped('
		' . $__templater->formCheckBoxRow(array(
		'name' => 'apply_department_ids',
	), array(array(
		'label' => 'Apply department options',
		'_dependent' => array('
					' . $__templater->callMacro('mjst_ticket_prefix_edit_macros', 'department_ids', array(
		'departmentIds' => $__vars['prefix']['department_ids'],
		'departments' => $__vars['departments'],
		'withRow' => false,
	), $__vars) . '
				'),
		'_type' => 'option',
	)), array(
		'label' => 'Applicable departments',
	)) . '
	');
	$__finalCompiled .= $__templater->includeTemplate('base_prefix_quickset_editor', $__compilerTemp1);
	return $__finalCompiled;
});