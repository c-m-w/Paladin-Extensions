<?php
// FROM HASH: 433df801e393f8144a32be3d484525aa
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['profilePost'], 'canChangeAuthor', array())) {
		$__finalCompiled .= '
												<a href="' . $__templater->fn('link', array('profile-posts/change-author', $__vars['profilePost'], ), true) . '"
													class="actionBar-action actionBar-action--changeProfilePostAuthor"
													data-xf-click="overlay">' . 'Change profile post author' . '</a>
											';
	}
	return $__finalCompiled;
});