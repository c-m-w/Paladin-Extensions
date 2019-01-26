<?php
// FROM HASH: bc3611f012b5bf38037f9b4b0d84a3e5
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['captcha']) {
		$__finalCompiled .= '
	' . $__templater->fn('captcha', array(true)) . '
';
	}
	return $__finalCompiled;
});