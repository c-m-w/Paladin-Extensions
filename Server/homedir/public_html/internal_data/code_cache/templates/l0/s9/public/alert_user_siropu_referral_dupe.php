<?php
// FROM HASH: ec8920e4e097499da22762c94d73d84e
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['alert']['username'], ), ), true) . ' was referred by ' . $__templater->fn('username_link', array($__vars['user']['SRC_Referrer'], ), true) . ' and has been added to approval queue. You should check their IPs.';
	return $__finalCompiled;
});