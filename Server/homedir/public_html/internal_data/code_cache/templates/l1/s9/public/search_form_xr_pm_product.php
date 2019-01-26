<?php
// FROM HASH: 01a0de499f43b9ec7a9778d18b6b10c8
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Search extensions');
	$__finalCompiled .= '

' . $__templater->callMacro('search_form_macros', 'keywords', array(
		'input' => $__vars['input'],
	), $__vars) . '
' . $__templater->callMacro('search_form_macros', 'user', array(
		'input' => $__vars['input'],
	), $__vars) . '
' . $__templater->callMacro('search_form_macros', 'date', array(
		'input' => $__vars['input'],
	), $__vars) . '

';
	$__compilerTemp1 = array(array(
		'value' => '',
		'label' => 'All categories',
		'_type' => 'option',
	));
	$__compilerTemp2 = $__templater->method($__vars['categoryTree'], 'getFlattened', array(0, ));
	if ($__templater->isTraversable($__compilerTemp2)) {
		foreach ($__compilerTemp2 AS $__vars['treeEntry']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['treeEntry']['record']['category_id'],
				'label' => $__templater->filter($__templater->fn('repeat', array('&nbsp;&nbsp;', $__vars['treeEntry']['depth'], ), false), array(array('raw', array()),), true) . ' ' . $__templater->escape($__vars['treeEntry']['record']['title']),
				'_type' => 'option',
			);
		}
	}
	$__finalCompiled .= $__templater->formRow('

	<ul class="inputList">
		<li>' . $__templater->formSelect(array(
		'name' => 'c[categories][]',
		'size' => '7',
		'multiple' => 'multiple',
		'value' => $__templater->filter($__vars['input']['c']['categories'], array(array('default', array(array(0, ), )),), false),
	), $__compilerTemp1) . '</li>
		<li>' . $__templater->formCheckBox(array(
		'standalone' => 'true',
	), array(array(
		'name' => 'c[child_categories]',
		'selected' => ((!$__vars['input']['c']) OR $__vars['input']['c']['child_categories']),
		'label' => 'Search child categories as well',
		'_type' => 'option',
	))) . '</li>
	</ul>
', array(
		'rowtype' => 'input',
		'label' => 'Search in categories',
	)) . '

' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'c[include_versions]',
		'label' => 'Include product versions',
		'_type' => 'option',
	)), array(
	)) . '

' . $__templater->callMacro('search_form_macros', 'order', array(
		'isRelevanceSupported' => $__vars['isRelevanceSupported'],
		'input' => $__vars['input'],
	), $__vars);
	return $__finalCompiled;
});