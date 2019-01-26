<?php
// FROM HASH: 219e7ef90c563a838de8efa91c3d81e0
return array('macros' => array('department_ids' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'departmentIds' => '!',
		'departments' => '!',
		'withRow' => '1',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__compilerTemp1 = array(array(
		'value' => '',
		'selected' => !$__vars['departmentIds'],
		'label' => $__vars['xf']['language']['parenthesis_open'] . 'None' . $__vars['xf']['language']['parenthesis_close'],
		'_type' => 'option',
	));
	if ($__templater->isTraversable($__vars['departments'])) {
		foreach ($__vars['departments'] AS $__vars['department']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['department']['department_id'],
				'label' => ' ' . $__templater->escape($__vars['department']['title']),
				'_type' => 'option',
			);
		}
	}
	$__vars['inner'] = $__templater->preEscaped('
		<ul class="inputList">
			<li>' . $__templater->formSelect(array(
		'name' => 'department_ids[]',
		'size' => '7',
		'multiple' => 'multiple',
		'value' => $__vars['departmentIds'],
		'id' => 'js-applicableDepartments',
	), $__compilerTemp1) . '</li>
			' . $__templater->formCheckBox(array(
	), array(array(
		'id' => 'js-selectAllDepartments',
		'label' => 'Select all',
		'_type' => 'option',
	))) . '
		</ul>
	');
	$__finalCompiled .= '

	';
	if ($__vars['withRow']) {
		$__finalCompiled .= '
		' . $__templater->formRow('

			' . $__templater->filter($__vars['inner'], array(array('raw', array()),), true) . '
		', array(
			'rowtype' => 'input',
			'label' => 'Applicable departments',
		)) . '
	';
	} else {
		$__finalCompiled .= '
		' . $__templater->filter($__vars['inner'], array(array('raw', array()),), true) . '
	';
	}
	$__finalCompiled .= '

	';
	$__templater->inlineJs('
		$(function()
		{
			$(\'#js-selectAllDepartments\').click(function(e)
			{
				$(\'#js-applicableDepartments\').find(\'option:enabled:not([value=""])\').prop(\'selected\', this.checked);
			});
		});
	');
	$__finalCompiled .= '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';

	return $__finalCompiled;
});