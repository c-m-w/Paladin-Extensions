<?php
// FROM HASH: 7c6aa8b7d00a48a171177438be13cc61
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if (!$__vars['providerData']) {
		$__finalCompiled .= '
	' . $__templater->callMacro('connected_account_provider_test_macros', 'explain', array(
			'providerTitle' => $__vars['provider']['title'],
			'keyName' => 'Client ID',
			'keyValue' => $__vars['provider']['options']['client_id'],
		), $__vars) . '
';
	} else {
		$__finalCompiled .= '
	' . $__templater->callMacro('connected_account_provider_test_macros', 'success', array(), $__vars) . '

	' . $__templater->callMacro('connected_account_provider_test_macros', 'display_name', array(
			'name' => $__vars['providerData']['username'],
		), $__vars) . '

	' . $__templater->callMacro('connected_account_provider_test_macros', 'email', array(
			'email' => $__vars['providerData']['email'],
		), $__vars) . '

	' . $__templater->callMacro('connected_account_provider_test_macros', 'picture', array(
			'url' => $__vars['providerData']['avatar_url'],
		), $__vars) . '
';
	}
	return $__finalCompiled;
});