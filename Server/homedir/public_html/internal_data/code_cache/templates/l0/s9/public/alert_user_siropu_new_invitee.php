<?php
// FROM HASH: daaec176a1ee07eedcc229a80c89829f
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['alert']['username'], ), ), true) . ' has registered using your invitation!';
	return $__finalCompiled;
});