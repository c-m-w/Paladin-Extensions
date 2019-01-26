<?php
// FROM HASH: f9fb1eacad41b3a4b15a93a6701cd1f2
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('th_reactions.less');
	$__finalCompiled .= '

';
	$__vars['fallbackName'] = 'Unknown member';
	$__finalCompiled .= '

<div class="contentRow-title">
	';
	if ($__vars['content']['user_id'] == $__vars['xf']['visitor']['user_id']) {
		$__finalCompiled .= '
		' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['fallbackName'], ), ), true) . ' reacted ' . $__templater->fn('reaction', array($__vars['newsFeed']['extra_data']['reaction_id'], 'newsfeed', ), true) . ' to <a ' . (('href="' . $__templater->fn('link', array('profile-posts/comments', $__vars['content'], ), true)) . '"') . '>your comment</a> on ' . $__templater->escape($__vars['content']['ProfilePost']['username']) . '\'s profile post.' . '
		';
	} else if ($__vars['content']['ProfilePost']['user_id'] == $__vars['xf']['visitor']['user_id']) {
		$__finalCompiled .= '
		' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['fallbackName'], ), ), true) . ' reacted ' . $__templater->fn('reaction', array($__vars['newsFeed']['extra_data']['reaction_id'], 'newsfeed', ), true) . ' to <a ' . (('href="' . $__templater->fn('link', array('profile-posts/comments', $__vars['content'], ), true)) . '"') . '>your comment</a> on ' . $__templater->escape($__vars['content']['ProfilePost']['username']) . '\'s profile post.' . '
		';
	} else {
		$__finalCompiled .= '
		' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['fallbackName'], ), ), true) . ' reacted ' . $__templater->fn('reaction', array($__vars['newsFeed']['extra_data']['reaction_id'], 'newsfeed', ), true) . ' to <a ' . (('href="' . $__templater->fn('link', array('profile-posts/comments', $__vars['content'], ), true)) . '"') . '>' . $__templater->escape($__vars['content']['username']) . '\'s comment</a> on ' . $__templater->escape($__vars['content']['ProfilePost']['username']) . '\'s profile post' . '
	';
	}
	$__finalCompiled .= '
</div>

<div class="contentRow-snippet">' . $__templater->fn('snippet', array($__vars['content']['message'], $__vars['xf']['options']['newsFeedMessageSnippetLength'], array('stripQuote' => true, ), ), true) . '</div>

<div class="contentRow-minor">' . $__templater->fn('date_dynamic', array($__vars['newsFeed']['event_date'], array(
	))) . '</div>';
	return $__finalCompiled;
});