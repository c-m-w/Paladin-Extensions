<?php
// FROM HASH: cffc7d92fc882d14b20d0608d863a803
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->callMacro('sv_warning_improvements_category_tree_macros', 'category_list', array(
		'warnings' => $__vars['warnings'],
		'categoryTree' => $__vars['categoryTree'],
	), $__vars);
	return $__finalCompiled;
});