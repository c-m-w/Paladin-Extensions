<?php
// FROM HASH: 5b0ec01c787aeec145bcea758e4272bf
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->callMacro('th_bookmark_macros_bookmarks', 'watch_thread', array(
		'thread' => $__vars['content'],
		'watch' => $__vars['watch'],
	), $__vars);
	return $__finalCompiled;
});