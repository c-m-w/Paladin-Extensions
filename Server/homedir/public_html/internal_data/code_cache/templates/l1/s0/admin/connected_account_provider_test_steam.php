<?php
// FROM HASH: 57e4aeef95dc74e1d404721f766a6a41
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '
        
';
	if (!$__vars['providerData']) {
		$__finalCompiled .= '
	' . $__templater->callMacro('connected_account_provider_test_macros', 'explain', array(
			'providerTitle' => $__vars['provider']['title'],
			'keyName' => 'App ID',
			'keyValue' => $__vars['provider']['options']['app_id'],
		), $__vars) . '
';
	} else {
		$__finalCompiled .= '
    ' . $__templater->callMacro('connected_account_provider_test_macros', 'success', array(), $__vars) . '
    ' . $__templater->callMacro('connected_account_provider_test_macros', 'display_name', array(
			'name' => $__vars['providerData']['username'],
		), $__vars) . '
    ' . $__templater->callMacro('connected_account_provider_test_macros', 'picture', array(
			'url' => $__vars['providerData']['avatar_url'],
		), $__vars) . '
';
	}
	$__finalCompiled .= '
        
    ';
	return $__finalCompiled;
});