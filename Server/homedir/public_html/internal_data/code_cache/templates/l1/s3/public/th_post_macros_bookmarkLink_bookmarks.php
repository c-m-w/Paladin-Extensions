<?php
// FROM HASH: 6c9c9e0eaa10cfa199bac5dd80d74450
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['post'], 'isFirstPost', array())) {
		$__finalCompiled .= '
	';
		if ($__templater->method($__vars['thread'], 'canBookmark', array())) {
			$__finalCompiled .= '
		' . $__templater->callMacro('th_bookmark_macros_bookmarks', 'bookmark_content', array(
				'bookmarkTooltip' => 'Bookmark thread',
				'unbookmarkTooltip' => 'Unbookmark thread',
				'currentBookmark' => $__vars['thread']['Bookmark'],
				'contentType' => 'thread',
				'contentId' => $__vars['thread']['thread_id'],
			), $__vars) . '
	';
		}
		$__finalCompiled .= '
	';
	} else {
		$__finalCompiled .= '
	';
		if ($__templater->method($__vars['post'], 'canBookmark', array())) {
			$__finalCompiled .= '
		' . $__templater->callMacro('th_bookmark_macros_bookmarks', 'bookmark_content', array(
				'bookmarkTooltip' => 'Bookmark post',
				'unbookmarkTooltip' => 'Unbookmark post',
				'currentBookmark' => $__vars['post']['Bookmark'],
				'contentType' => 'post',
				'contentId' => $__vars['post']['post_id'],
			), $__vars) . '
	';
		}
		$__finalCompiled .= '
';
	}
	return $__finalCompiled;
});