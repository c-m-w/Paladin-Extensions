<?php
// FROM HASH: cbf6b4363d678da4e44b3d231d2aa531
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Confirm action');
	$__finalCompiled .= '

' . $__templater->callMacro('category_tree_macros', 'category_delete_form', array(
		'linkPrefix' => 'product-manager/categories',
		'category' => $__vars['category'],
	), $__vars);
	return $__finalCompiled;
});