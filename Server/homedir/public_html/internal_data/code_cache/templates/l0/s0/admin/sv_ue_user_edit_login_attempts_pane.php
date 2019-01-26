<?php
// FROM HASH: 61654ae458a14977db90fbfc5c811c8f
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['user']['user_id']) {
		$__finalCompiled .= '
	<li data-href="' . $__templater->fn('link', array('users/user-login-attempts', $__vars['user'], ), true) . '" role="tabpanel" id="user-login-attempts">
		<div class="block-body block-row">' . 'Loading' . $__vars['xf']['language']['ellipsis'] . '</div>
	</li>
';
	}
	return $__finalCompiled;
});