<?php
// FROM HASH: 1cd8214fd345585a8ee46851b71afb64
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('th_reactions.less');
	$__finalCompiled .= '

<div class="contentRow-title">
	';
	if ($__vars['content']['user_id'] == $__vars['xf']['visitor']['user_id']) {
		$__finalCompiled .= '
		' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['fallbackName'], ), ), true) . ' reacted ' . $__templater->fn('reaction', array($__vars['newsFeed']['extra_data']['reaction_id'], 'newsfeed', ), true) . ' to your post in the thread ' . ((((('<a href="' . $__templater->fn('link', array('posts', $__vars['content'], ), true)) . '">') . $__templater->fn('prefix', array('thread', $__vars['content']['Thread'], ), true)) . $__templater->escape($__vars['content']['Thread']['title'])) . '</a>') . '.' . '
		';
	} else {
		$__finalCompiled .= '
		' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['fallbackName'], ), ), true) . ' reacted ' . $__templater->fn('reaction', array($__vars['newsFeed']['extra_data']['reaction_id'], 'newsfeed', ), true) . ' to <a ' . (('href="' . $__templater->fn('link', array('posts', $__vars['content'], ), true)) . '"') . '>' . $__templater->escape($__vars['content']['username']) . '\'s post</a> in the thread ' . ((((('<a href="' . $__templater->fn('link', array('posts', $__vars['content'], ), true)) . '">') . $__templater->fn('prefix', array('thread', $__vars['content']['Thread'], ), true)) . $__templater->escape($__vars['content']['Thread']['title'])) . '</a>') . '.' . '
	';
	}
	$__finalCompiled .= '
</div>

<div class="contentRow-snippet">' . $__templater->fn('snippet', array($__vars['content']['message'], $__vars['xf']['options']['newsFeedMessageSnippetLength'], array('stripQuote' => true, ), ), true) . '</div>

<div class="contentRow-minor">' . $__templater->fn('date_dynamic', array($__vars['newsFeed']['event_date'], array(
	))) . '</div>';
	return $__finalCompiled;
});