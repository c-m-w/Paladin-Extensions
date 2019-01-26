<?php
// FROM HASH: 6ccd89ba73ef41ee15f868d573fa4412
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('th_reactions.less');
	$__finalCompiled .= '

';
	if ($__vars['xf']['visitor']['user_id'] == $__vars['content']['ProfilePost']['user_id']) {
		$__finalCompiled .= '
	' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['alert']['username'], ), ), true) . ' reacted ' . $__templater->fn('reaction', array($__vars['alert']['extra_data']['reaction_id'], 'alert', ), true) . ' to <a ' . (('href="' . $__templater->fn('link', array('profile-posts/comments', $__vars['content'], ), true)) . '" class="fauxBlockLink-blockLink"') . '>your comment</a> on your profile post.' . '
';
	} else {
		$__finalCompiled .= '
	' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['alert']['username'], ), ), true) . ' reacted ' . $__templater->fn('reaction', array($__vars['alert']['extra_data']['reaction_id'], 'alert', ), true) . ' to <a ' . (('href="' . $__templater->fn('link', array('profile-posts/comments', $__vars['content'], ), true)) . '" class="fauxBlockLink-blockLink"') . '>your comment</a> on ' . $__templater->escape($__vars['content']['ProfilePost']['username']) . '\'s profile post.' . '
';
	}
	return $__finalCompiled;
});