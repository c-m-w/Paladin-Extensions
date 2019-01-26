<?php
// FROM HASH: 8a8c6f2dfebc8770327a86993f2fd586
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Permissions' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['record']['title']));
	$__finalCompiled .= '

' . $__templater->callMacro('permission_category_macros', 'list', array(
		'category' => $__vars['record'],
		'isPrivate' => $__vars['isPrivate'],
		'userGroups' => $__vars['userGroups'],
		'users' => $__vars['users'],
		'entries' => $__vars['entries'],
		'routeBase' => 'resource-manager/categories/permissions',
	), $__vars) . '
';
	return $__finalCompiled;
});