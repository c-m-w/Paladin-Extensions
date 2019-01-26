<?php
// FROM HASH: 613c53f606253260954596b6cfae251a
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['mediaItem'], 'canChangeAuthor', array())) {
		$__finalCompiled .= '
														<a href="' . $__templater->fn('link', array('media/change-author', $__vars['mediaItem'], ), true) . '" data-xf-click="overlay" class="menu-linkRow">' . 'Change media author' . '</a>
													';
	}
	return $__finalCompiled;
});