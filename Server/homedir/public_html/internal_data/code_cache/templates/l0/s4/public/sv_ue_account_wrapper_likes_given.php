<?php
// FROM HASH: ad1d7bb258ab3d9358e2d19c6292b704
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<a class="blockLink ' . (($__vars['pageSelected'] == 'likes_given') ? 'is-selected' : '') . '" href="' . $__templater->fn('link', array('account/likes-given', ), true) . '">
	' . 'Likes given' . '
</a>
';
	return $__finalCompiled;
});