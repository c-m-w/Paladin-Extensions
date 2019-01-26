<?php
// FROM HASH: e95b132be2f90429052383e8d8d5542b
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['resource'], 'canBookmark', array())) {
		$__finalCompiled .= '
	' . $__templater->callMacro('th_bookmark_macros_bookmarks', 'bookmark_content', array(
			'bookmarkTooltip' => 'Bookmark resource',
			'unbookmarkTooltip' => 'Unbookmark resource',
			'currentBookmark' => $__vars['resource']['Bookmark'],
			'contentType' => 'resource',
			'isButton' => '1',
			'aClass' => 'button--link',
			'contentId' => $__vars['resource']['resource_id'],
		), $__vars) . '
';
	}
	return $__finalCompiled;
});