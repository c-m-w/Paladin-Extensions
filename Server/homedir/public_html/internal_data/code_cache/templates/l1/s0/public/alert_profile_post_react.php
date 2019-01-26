<?php
// FROM HASH: a37d17e25fcaf5082af19d5a7734edb2
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('th_reactions.less');
	$__finalCompiled .= '

';
	if ($__vars['xf']['visitor']['user_id'] == $__vars['content']['ProfileUser']['user_id']) {
		$__finalCompiled .= '
	' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['alert']['username'], ), ), true) . ' reacted ' . $__templater->fn('reaction', array($__vars['alert']['extra_data']['reaction_id'], 'alert', ), true) . ' to your <a ' . (('href="' . $__templater->fn('link', array('profile-posts', $__vars['content'], ), true)) . '" class="fauxBlockLink-blockLink"') . '>status</a>.' . '
';
	} else {
		$__finalCompiled .= '
	' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['alert']['username'], ), ), true) . ' reacted ' . $__templater->fn('reaction', array($__vars['alert']['extra_data']['reaction_id'], 'alert', ), true) . ' to <a ' . (('href="' . $__templater->fn('link', array('profile-posts', $__vars['content'], ), true)) . '" class="fauxBlockLink-blockLink"') . '>your post</a> on ' . $__templater->escape($__vars['content']['ProfileUser']['username']) . '\'s profile.' . '
';
	}
	return $__finalCompiled;
});