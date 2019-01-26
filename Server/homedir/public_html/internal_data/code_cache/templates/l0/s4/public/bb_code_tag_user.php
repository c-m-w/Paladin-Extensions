<?php
// FROM HASH: fb0c6edf6e905fb60ba8291852992dab
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->fn('avatar', array($__vars['user'], 'xxs', false, array(
	))) . ' ' . $__templater->fn('username_link', array($__vars['user'], true, array(
	))) . '
';
	return $__finalCompiled;
});