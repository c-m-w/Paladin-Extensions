<?php
// FROM HASH: 6cb0ae4fbbe09125c8646cc8edfc1537
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
	if ($__vars['content']['user_id'] == $__vars['content']['profile_user_id']) {
		$__finalCompiled .= '
		';
		if ($__vars['content']['user_id'] == $__vars['xf']['visitor']['user_id']) {
			$__finalCompiled .= '
			' . '' . $__templater->fn('username_link', array($__vars['liker'], false, array('defaultname' => $__vars['fallbackName'], ), ), true) . ' reacted ' . $__templater->fn('reaction', array($__vars['newsFeed']['extra_data']['reaction_id'], 'newsfeed', ), true) . ' to your <a ' . (('href="' . $__templater->fn('link', array('profile-posts', $__vars['profilePost'], ), true)) . '"') . '>status</a>.' . '
			';
		} else {
			$__finalCompiled .= '
			' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['fallbackName'], ), ), true) . ' reacted ' . $__templater->fn('reaction', array($__vars['newsFeed']['extra_data']['reaction_id'], 'newsfeed', ), true) . ' to <a ' . (('href="' . $__templater->fn('link', array('profile-posts', $__vars['content'], ), true)) . '"') . '>' . $__templater->escape($__vars['content']['username']) . '\'s status</a>.' . '
		';
		}
		$__finalCompiled .= '
		';
	} else {
		$__finalCompiled .= '
		';
		if ($__vars['content']['user_id'] == $__vars['xf']['visitor']['user_id']) {
			$__finalCompiled .= '
			' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['fallbackName'], ), ), true) . ' reacted ' . $__templater->fn('reaction', array($__vars['newsFeed']['extra_data']['reaction_id'], 'newsfeed', ), true) . ' to <a ' . (('href="' . $__templater->fn('link', array('profile-posts', $__vars['content'], ), true)) . '"') . '>your post</a> on ' . $__templater->escape($__vars['content']['ProfileUser']['username']) . '\'s profile.' . '
			';
		} else if ($__vars['content']['ProfileUser']['user_id'] == $__vars['xf']['visitor']['user_id']) {
			$__finalCompiled .= '
			' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['fallbackName'], ), ), true) . ' reacted ' . $__templater->fn('reaction', array($__vars['newsFeed']['extra_data']['reaction_id'], 'newsfeed', ), true) . ' to <a ' . (('href="' . $__templater->fn('link', array('profile-posts', $__vars['content'], ), true)) . '"') . '>' . $__templater->escape($__vars['content']['username']) . '\'s post</a> on your profile.' . '
			';
		} else {
			$__finalCompiled .= '
			' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['fallbackName'], ), ), true) . ' reacted ' . $__templater->fn('reaction', array($__vars['newsFeed']['extra_data']['reaction_id'], 'newsfeed', ), true) . ' to <a ' . (('href="' . $__templater->fn('link', array('profile-posts', $__vars['content'], ), true)) . '"') . '>' . $__templater->escape($__vars['content']['username']) . '\'s post</a> on ' . $__templater->escape($__vars['content']['ProfileUser']['username']) . '\'s profile.' . '
		';
		}
		$__finalCompiled .= '
	';
	}
	$__finalCompiled .= '
</div>

<div class="contentRow-snippet">' . $__templater->fn('snippet', array($__vars['content']['message'], $__vars['xf']['options']['newsFeedMessageSnippetLength'], array('stripQuote' => true, ), ), true) . '</div>

<div class="contentRow-minor">' . $__templater->fn('date_dynamic', array($__vars['newsFeed']['event_date'], array(
	))) . '</div>';
	return $__finalCompiled;
});