<?php
// FROM HASH: bee5a5d015bcf9f1e4be5df286c4f3f7
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Categories');
	$__finalCompiled .= '

' . $__templater->callMacro('category_tree_macros', 'page_action', array(
		'linkPrefix' => 'product-manager/categories',
	), $__vars) . '

' . $__templater->callMacro('category_tree_macros', 'category_list', array(
		'categoryTree' => $__vars['categoryTree'],
		'filterKey' => 'xr-pm-categories',
		'linkPrefix' => 'product-manager/categories',
		'idKey' => 'category_id',
	), $__vars);
	return $__finalCompiled;
});