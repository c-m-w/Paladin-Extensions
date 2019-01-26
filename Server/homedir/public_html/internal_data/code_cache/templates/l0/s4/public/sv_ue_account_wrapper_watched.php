<?php
// FROM HASH: cfc9859f02517e782965d2ef8315e366
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['xf']['options']['useress_watchedWrapper']) {
		$__finalCompiled .= '
	<a class="blockLink ' . (($__vars['pageSelected'] == 'watched_threads') ? 'is-selected' : '') . '" href="' . $__templater->fn('link', array('watched/threads', ), true) . '">
		' . 'Watched threads' . '
	</a>

	<a class="blockLink ' . (($__vars['pageSelected'] == 'watched_forums') ? 'is-selected' : '') . '" href="' . $__templater->fn('link', array('watched/forums', ), true) . '">
		' . 'Watched forums' . '
	</a>
';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
});