<?php
// FROM HASH: 17dd022c41f84ffa39bfaa67b6e8b510
return array('macros' => array('resource_page_options' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'category' => '!',
		'resource' => null,
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__templater->setPageParam('resourceCategory', $__vars['category']);
	$__finalCompiled .= '

	';
	$__templater->setPageParam('searchConstraints', array('Extensions' => array('search_type' => 'resource', ), 'This category' => array('search_type' => 'resource', 'c' => array('categories' => array($__vars['category']['resource_category_id'], ), 'child_categories' => 1, ), ), ));
	$__finalCompiled .= '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';

	return $__finalCompiled;
});