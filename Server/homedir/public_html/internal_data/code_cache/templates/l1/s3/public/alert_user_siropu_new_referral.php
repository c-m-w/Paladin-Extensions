<?php
// FROM HASH: 95e7478f92a5e15dc449ce584933ec71
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['alert']['username'], ), ), true) . ' has registered using your referral link!';
	return $__finalCompiled;
});