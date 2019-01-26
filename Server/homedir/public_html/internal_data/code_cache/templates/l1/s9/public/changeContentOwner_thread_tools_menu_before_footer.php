<?php
// FROM HASH: 8f7bf31427dd55ab436308643efe0c1b
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['thread'], 'canChangeAuthor', array())) {
		$__finalCompiled .= '
											<a href="' . $__templater->fn('link', array('threads/change-author', $__vars['thread'], ), true) . '" data-xf-click="overlay" class="menu-linkRow">' . 'Change thread author' . '</a>
										';
	}
	return $__finalCompiled;
});