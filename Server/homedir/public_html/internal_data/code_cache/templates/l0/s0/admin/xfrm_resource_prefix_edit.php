<?php
// FROM HASH: bc2871eafa6d098b4114862b5ddf6842
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__compilerTemp1 = $__vars;
	$__compilerTemp1['extraOptions'] = $__templater->preEscaped('
		' . $__templater->callMacro('xfrm_resource_prefix_edit_macros', 'category_ids', array(
		'categoryIds' => $__vars['prefix']['resource_category_ids'],
		'categoryTree' => $__vars['categoryTree'],
	), $__vars) . '
	');
	$__finalCompiled .= $__templater->includeTemplate('base_prefix_edit', $__compilerTemp1);
	return $__finalCompiled;
});