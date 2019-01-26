<?php
// FROM HASH: a133c61b18eb1f3c43601cf7b36cb6a2
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['album'], 'canChangeOwner', array())) {
		$__finalCompiled .= '
										<a href="' . $__templater->fn('link', array('media/albums/change-owner', $__vars['album'], ), true) . '"
											class="actionBar-action actionBar-action--changeXFMGAlbumOwner actionBar-action--menuItem"
											data-xf-click="overlay">' . 'Change album owner' . '</a>
									';
	}
	return $__finalCompiled;
});