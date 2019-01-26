<?php
// FROM HASH: 6fe770bc9596ec389ab5d565a8797e30
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Sort warning definitions');
	$__finalCompiled .= '

' . $__templater->callMacro('sv_warning_improvements_warning_tree_macros', 'sortable_form', array(
		'categoryTree' => $__vars['categoryTree'],
		'warnings' => $__vars['warnings'],
	), $__vars);
	return $__finalCompiled;
});