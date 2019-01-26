<?php
// FROM HASH: d61bb8e87c7f99ff84ad1bb5f58042ab
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
	$__templater->breadcrumb($__templater->preEscaped($__templater->escape($__vars['record']['title'])), $__templater->fn('link', array('permissions/mjst-departments', $__vars['record'], ), false), array(
	));
	$__finalCompiled .= '

' . $__templater->callMacro('mjst_permission_department_macros', 'edit', array(
		'department' => $__vars['record'],
		'permissionData' => $__vars['permissionData'],
		'typeEntries' => $__vars['typeEntries'],
		'routeBase' => 'permissions/mjst-departments',
		'saveParams' => $__vars['saveParams'],
	), $__vars);
	return $__finalCompiled;
});