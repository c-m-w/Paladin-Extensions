<?php
// FROM HASH: 8529731e3c9660fd53b033409a0a31c6
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['content'], 'isDescription', array())) {
		$__finalCompiled .= '
	' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['alert']['username'], ), ), true) . ' liked your extension ' . ((((('<a href="' . $__templater->fn('link', array('resources', $__vars['content']['Resource'], ), true)) . '" class="fauxBlockLink-blockLink">') . $__templater->fn('prefix', array('resource', $__vars['content']['Resource'], ), true)) . $__templater->escape($__vars['content']['Resource']['title'])) . '</a>') . '.' . '
';
	} else {
		$__finalCompiled .= '
	' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['alert']['username'], ), ), true) . ' liked your update to extension ' . ((((('<a href="' . $__templater->fn('link', array('resources/update', $__vars['content'], ), true)) . '" class="fauxBlockLink-blockLink">') . $__templater->fn('prefix', array('resource', $__vars['content']['Resource'], ), true)) . $__templater->escape($__vars['content']['Resource']['title'])) . '</a>') . '.' . '
';
	}
	return $__finalCompiled;
});