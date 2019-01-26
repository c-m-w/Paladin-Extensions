<?php
// FROM HASH: 784ce6bb59d323d85bc78739a8b7bd87
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['comment'], 'canChangeAuthor', array())) {
		$__finalCompiled .= '
													<a href="' . $__templater->fn('link', array('media/comments/change-author', $__vars['comment'], ), true) . '"
														class="actionBar-action actionBar-action--changeXFMGCommentAuthor">' . 'Change comment author' . '</a>
												';
	}
	return $__finalCompiled;
});