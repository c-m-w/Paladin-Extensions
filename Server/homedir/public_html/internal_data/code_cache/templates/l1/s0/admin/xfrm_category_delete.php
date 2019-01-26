<?php
// FROM HASH: 24c90bdca13e71cc176cbc0c2f543956
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Confirm action');
	$__finalCompiled .= '

' . $__templater->callMacro('category_tree_macros', 'category_delete_form', array(
		'linkPrefix' => 'resource-manager/categories',
		'category' => $__vars['category'],
	), $__vars);
	return $__finalCompiled;
});