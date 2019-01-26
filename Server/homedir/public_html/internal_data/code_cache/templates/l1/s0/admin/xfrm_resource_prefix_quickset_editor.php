<?php
// FROM HASH: a614d6db82ea5e289b60c3793ed832a7
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__compilerTemp1 = $__vars;
	$__compilerTemp1['extraOptions'] = $__templater->preEscaped('
		' . $__templater->formCheckBoxRow(array(
		'name' => 'apply_resource_category_ids',
	), array(array(
		'label' => 'Apply category options',
		'_dependent' => array('
					' . $__templater->callMacro('xfrm_resource_prefix_edit_macros', 'category_ids', array(
		'categoryIds' => $__vars['prefix']['resource_category_ids'],
		'categoryTree' => $__vars['categoryTree'],
		'withRow' => false,
	), $__vars) . '
				'),
		'_type' => 'option',
	)), array(
		'label' => 'Applicable categories',
	)) . '
	');
	$__finalCompiled .= $__templater->includeTemplate('base_prefix_quickset_editor', $__compilerTemp1);
	return $__finalCompiled;
});