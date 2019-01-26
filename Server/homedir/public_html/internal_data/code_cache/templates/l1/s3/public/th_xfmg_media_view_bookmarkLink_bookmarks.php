<?php
// FROM HASH: 6066bea0ab10e450b30f4e2971ed6d96
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['mediaItem'], 'canBookmark', array())) {
		$__finalCompiled .= '
	' . $__templater->callMacro('th_bookmark_macros_bookmarks', 'bookmark_content', array(
			'bookmarkTooltip' => 'Bookmark media',
			'unbookmarkTooltip' => 'Unbookmark media',
			'currentBookmark' => $__vars['mediaItem']['Bookmark'],
			'contentType' => 'xfmg_media',
			'contentId' => $__vars['mediaItem']['media_id'],
		), $__vars) . '
';
	}
	return $__finalCompiled;
});