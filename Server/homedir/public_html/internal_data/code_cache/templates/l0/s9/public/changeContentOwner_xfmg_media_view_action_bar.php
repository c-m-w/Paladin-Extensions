<?php
// FROM HASH: 30c0914855cd1f7c3d1e859b3fa6860a
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['mediaItem'], 'canChangeAuthor', array())) {
		$__finalCompiled .= '
										<a href="' . $__templater->fn('link', array('media/change-author', $__vars['mediaItem'], ), true) . '"
											class="actionBar-action actionBar-action--changeXFMGMediaAuthor actionBar-action--menuItem"
											data-xf-click="overlay">' . 'Change media author' . '</a>
									';
	}
	return $__finalCompiled;
});