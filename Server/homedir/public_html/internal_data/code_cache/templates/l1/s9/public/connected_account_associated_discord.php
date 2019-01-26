<?php
// FROM HASH: 49b1aad5171070ad36267c536f718e1e
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['providerData']) {
		$__finalCompiled .= '
	<a href="https://discordapp.com/channels/@me" target="_blank">
		<img src="' . $__templater->escape($__vars['providerData']['avatar_url']) . '" width="48" alt="" />
	</a>
	<div><a href="https://discordapp.com/channels/@me" target="_blank">' . $__templater->escape($__vars['providerData']['username']) . ' ' . $__templater->filter($__vars['providerData']['username'], array(array('parens', array()),), true) . '</a></div>
';
	} else {
		$__finalCompiled .= '
	' . 'Unknown account' . '
';
	}
	return $__finalCompiled;
});