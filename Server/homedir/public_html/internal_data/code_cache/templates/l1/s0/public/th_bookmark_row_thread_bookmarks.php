<?php
// FROM HASH: f8e8c9da582a30209252a24e552452b1
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<a href="' . $__templater->fn('link', array('threads', $__vars['thread'], ), true) . '" class="fauxBlockLink-blockLink">' . $__templater->escape($__vars['thread']['title']) . '</a>

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