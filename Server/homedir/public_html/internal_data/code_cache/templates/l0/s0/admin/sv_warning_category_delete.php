<?php
// FROM HASH: cc4ac41a8ed9b6d42bc6e60a1ab5cebb
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Confirm Deletion of Warning Category');
	$__finalCompiled .= '

' . $__templater->callMacro('sv_warning_improvements_category_tree_macros', 'category_delete_form', array(
		'category' => $__vars['category'],
	), $__vars);
	return $__finalCompiled;
});