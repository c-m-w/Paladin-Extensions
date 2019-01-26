<?php
// FROM HASH: 54cfcd13d4196a9cf3eed3ec93d0c108
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['forum']['Node'], 'canBookmark', array())) {
		$__finalCompiled .= '
	' . $__templater->callMacro('th_bookmark_macros_bookmarks', 'bookmark_content', array(
			'bookmarkTooltip' => 'Bookmark forum',
			'unbookmarkTooltip' => 'Unbookmark forum',
			'currentBookmark' => $__vars['forum']['Node']['Bookmark'],
			'contentType' => 'node',
			'isButton' => '1',
			'aClass' => 'button--link',
			'contentId' => $__vars['forum']['node_id'],
		), $__vars) . '
';
	}
	return $__finalCompiled;
});