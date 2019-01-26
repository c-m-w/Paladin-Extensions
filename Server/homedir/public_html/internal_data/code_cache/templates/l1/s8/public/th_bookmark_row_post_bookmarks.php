<?php
// FROM HASH: acbf5ca1fb15ad7bd4c440446a47230f
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= 'Post <a href="' . $__templater->fn('link', array('posts', $__vars['post'], ), true) . '" class="fauxBlockLink-blockLink">#' . ($__vars['post']['position'] + 1) . '</a> in thread <a href="' . $__templater->fn('link', array('threads', $__vars['thread'], ), true) . '">' . $__templater->escape($__vars['thread']['title']) . '</a>' . '

';
	if (!$__vars['options']['hide_container']) {
		$__finalCompiled .= '
	<div class="bookmarkRow-forum">
		<span class="u-muted">' . 'Forum' . $__vars['xf']['language']['label_separator'] . ' <a href="' . $__templater->fn('link', array('forums', $__vars['forum'], ), true) . '">' . $__templater->escape($__vars['forum']['title']) . '</a></span>
	</div>
';
	}
	return $__finalCompiled;
});