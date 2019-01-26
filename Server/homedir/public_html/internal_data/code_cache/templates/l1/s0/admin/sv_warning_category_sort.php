<?php
// FROM HASH: 8678d18225e1323fe9da8dd43f8232c5
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Sort categories');
	$__finalCompiled .= '

' . $__templater->callMacro('sv_warning_improvements_category_tree_macros', 'sortable_form', array(
		'categoryTree' => $__vars['categoryTree'],
	), $__vars);
	return $__finalCompiled;
});