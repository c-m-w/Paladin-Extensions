<?php
// FROM HASH: ad453e8b833a49928284b8c9ebe0079a
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->callMacro('sv_warning_improvements_action_tree_macros', 'action_list', array(
		'globalActions' => $__vars['globalActions'],
		'actions' => $__vars['actions'],
		'categoryTree' => $__vars['categoryTree'],
	), $__vars);
	return $__finalCompiled;
});