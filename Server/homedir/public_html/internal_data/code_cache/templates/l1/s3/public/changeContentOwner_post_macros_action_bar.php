<?php
// FROM HASH: c0c4fcc6f985a8a396b7a6b5ce68ec80
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['post'], 'canChangeAuthor', array())) {
		$__finalCompiled .= '
												<a href="' . $__templater->fn('link', array('posts/change-author', $__vars['post'], ), true) . '"
													class="actionBar-action actionBar-action--changePostAuthor"
													data-xf-click="overlay">' . 'Change post author' . '</a>
											';
	}
	return $__finalCompiled;
});