<?php
// FROM HASH: b70cfef405e7e237a89aa65e13b681b3
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->callMacro('xfrm_resource_update_macros', 'resource_update', array(
		'update' => $__vars['update'],
		'resource' => $__vars['resource'],
	), $__vars) . '
';
	return $__finalCompiled;
});