<?php
// FROM HASH: 47c4bd79f3c72598693ce216bb8960f4
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= 'Your <a href="' . $__templater->fn('link', array('posts', $__vars['extra'], ), true) . '">post</a> in the thread ' . (((('<a href="' . $__templater->fn('link', array('threads', $__vars['extra'], ), true)) . '">') . $__templater->escape($__vars['extra']['title'])) . '</a>') . ' has been merged into your last post.';
	return $__finalCompiled;
});