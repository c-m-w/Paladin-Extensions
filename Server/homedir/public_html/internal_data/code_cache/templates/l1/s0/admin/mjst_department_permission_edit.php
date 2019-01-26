<?php
// FROM HASH: 12f427771e4eb47a965cf7ed65756aec
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
	$__templater->breadcrumb($__templater->preEscaped('Permissions' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['record']['title'])), $__templater->fn('link', array('mjst-support/departments/permissions', $__vars['record'], ), false), array(
	));
	$__finalCompiled .= '

' . $__templater->callMacro('mjst_permission_department_macros', 'edit', array(
		'department' => $__vars['record'],
		'permissionData' => $__vars['permissionData'],
		'typeEntries' => $__vars['typeEntries'],
		'routeBase' => 'mjst-support/departments/permissions',
		'saveParams' => $__vars['saveParams'],
	), $__vars);
	return $__finalCompiled;
});