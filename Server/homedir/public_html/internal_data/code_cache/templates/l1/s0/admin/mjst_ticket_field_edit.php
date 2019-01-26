<?php
// FROM HASH: 67baed8f590571b03bf97ff961a163fb
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__compilerTemp1 = $__vars;
	$__compilerTemp1['extraOptions'] = $__templater->preEscaped('
		' . $__templater->callMacro('base_custom_field_macros', 'common_options', array(
		'field' => $__vars['field'],
	), $__vars) . '
	');
	$__compilerTemp2 = array(array(
		'value' => '',
		'selected' => !$__vars['departmentIds'],
		'label' => $__vars['xf']['language']['parenthesis_open'] . 'None' . $__vars['xf']['language']['parenthesis_close'],
		'_type' => 'option',
	));
	if ($__templater->isTraversable($__vars['departments'])) {
		foreach ($__vars['departments'] AS $__vars['department']) {
			$__compilerTemp2[] = array(
				'value' => $__vars['department']['department_id'],
				'label' => ' ' . $__templater->escape($__vars['department']['title']),
				'_type' => 'option',
			);
		}
	}
	$__compilerTemp1['displayOptions'] = $__templater->preEscaped('
		' . $__templater->formSelectRow(array(
		'name' => 'department_ids[]',
		'value' => $__vars['departmentIds'],
		'multiple' => 'multiple',
		'size' => '7',
	), $__compilerTemp2, array(
		'label' => 'Applicable departments',
	)) . '
	');
	$__finalCompiled .= $__templater->includeTemplate('base_custom_field_edit', $__compilerTemp1);
	return $__finalCompiled;
});