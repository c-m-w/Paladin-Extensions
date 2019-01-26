<?php
// FROM HASH: 52cfdcc9d730e5135fcd6be21c90e101
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['userGroup']) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->escape($__vars['userGroup']['title']));
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->escape($__vars['user']['username']));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	$__templater->breadcrumb($__templater->preEscaped($__templater->escape($__vars['record']['title'])), $__templater->fn('link', array('permissions/product-manager-categories', $__vars['record'], ), false), array(
	));
	$__finalCompiled .= '

' . $__templater->callMacro('permission_category_macros', 'edit', array(
		'category' => $__vars['record'],
		'permissionData' => $__vars['permissionData'],
		'typeEntries' => $__vars['typeEntries'],
		'routeBase' => 'permissions/product-manager-categories',
		'saveParams' => $__vars['saveParams'],
	), $__vars) . '
';
	return $__finalCompiled;
});