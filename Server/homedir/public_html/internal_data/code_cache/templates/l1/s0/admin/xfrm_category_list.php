<?php
// FROM HASH: 20a5f5aca13318892ca4001118708625
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Extension categories');
	$__finalCompiled .= '

' . $__templater->callMacro('category_tree_macros', 'page_action', array(
		'linkPrefix' => 'resource-manager/categories',
	), $__vars) . '

' . $__templater->callMacro('category_tree_macros', 'category_list', array(
		'categoryTree' => $__vars['categoryTree'],
		'filterKey' => 'xfrm-categories',
		'linkPrefix' => 'resource-manager/categories',
		'idKey' => 'resource_category_id',
	), $__vars);
	return $__finalCompiled;
});