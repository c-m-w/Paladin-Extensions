<?php
// FROM HASH: ce3cde208f6b872bc6f3cbcb66b2adcc
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<div>
';
	if ($__vars['xf']['options']['tmdbthreads_show_forum']['1']) {
		$__finalCompiled .= '<b>' . 'Title' . ':</b> ' . $__templater->escape($__vars['thread']['Movie']['tmdb_title']) . '<br />';
	}
	$__finalCompiled .= '
';
	if ($__vars['thread']['Movie']['tmdb_tagline'] AND $__vars['xf']['options']['tmdbthreads_show_forum']['2']) {
		$__finalCompiled .= '<b>' . 'snog_movies_tagline' . ':</b> ' . $__templater->escape($__vars['thread']['Movie']['tmdb_tagline']) . '<br />';
	}
	$__finalCompiled .= '
';
	if ($__vars['thread']['Movie']['tmdb_genres'] AND $__vars['xf']['options']['tmdbthreads_show_forum']['3']) {
		$__finalCompiled .= '<b>' . 'snog_movies_genre' . ':</b> ' . $__templater->escape($__vars['thread']['Movie']['tmdb_genres']) . '<br />';
	}
	$__finalCompiled .= '
';
	if ($__vars['thread']['Movie']['tmdb_director'] AND $__vars['xf']['options']['tmdbthreads_show_forum']['4']) {
		$__finalCompiled .= '<b>' . 'snog_movies_director' . ':</b> ' . $__templater->escape($__vars['thread']['Movie']['tmdb_director']) . '<br />';
	}
	$__finalCompiled .= '
';
	if ($__vars['thread']['Movie']['tmdb_runtime'] AND $__vars['xf']['options']['tmdbthreads_show_forum']['5']) {
		$__finalCompiled .= '<b>' . 'snog_movies_runtime' . ':</b> ' . $__templater->escape($__vars['thread']['Movie']['tmdb_runtime']) . '<br />';
	}
	$__finalCompiled .= '
';
	if ($__vars['thread']['Movie']['tmdb_release'] AND $__vars['xf']['options']['tmdbthreads_show_forum']['6']) {
		$__finalCompiled .= '<b>' . 'snog_movies_release' . ':</b> ' . $__templater->escape($__vars['thread']['Movie']['tmdb_release']) . '<br />';
	}
	$__finalCompiled .= '
<ul class="structItem-parts">
	<li>' . $__templater->fn('username_link', array($__vars['thread']['User'], false, array(
		'defaultname' => $__vars['thread']['username'],
	))) . '</li>
	<li class="structItem-startDate"><a href="' . $__templater->fn('link', array('threads', $__vars['thread'], ), true) . '" rel="nofollow">' . $__templater->fn('date_dynamic', array($__vars['thread']['post_date'], array(
	))) . '</a></li>
	';
	if (!$__vars['forum']) {
		$__finalCompiled .= '
		<li><a href="' . $__templater->fn('link', array('forums', $__vars['thread']['Forum'], ), true) . '">' . $__templater->escape($__vars['thread']['Forum']['title']) . '</a></li>
	';
	}
	$__finalCompiled .= '
</ul>
</div>';
	return $__finalCompiled;
});