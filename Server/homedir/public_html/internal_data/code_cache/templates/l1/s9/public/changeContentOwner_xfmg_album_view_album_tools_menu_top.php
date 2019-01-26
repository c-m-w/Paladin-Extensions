<?php
// FROM HASH: e353757b97b59a1648aca1656f7748ce
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['album'], 'canChangeOwner', array())) {
		$__finalCompiled .= '
														<a href="' . $__templater->fn('link', array('media/albums/change-owner', $__vars['album'], ), true) . '" data-xf-click="overlay" class="menu-linkRow">' . 'Change album owner' . '</a>
													';
	}
	return $__finalCompiled;
});