<?php
// FROM HASH: a46fbd9a712c98758afca8f5730c3915
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->callMacro('th_bookmark_macros_bookmarks', 'watch_thread', array(
		'thread' => $__vars['thread'],
		'watch' => $__vars['watch'],
	), $__vars);
	return $__finalCompiled;
});