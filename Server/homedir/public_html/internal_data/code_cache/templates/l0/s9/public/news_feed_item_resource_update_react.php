<?php
// FROM HASH: 350ed6255a6e2a29e64f1cc2c72757a5
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('th_reactions.less');
	$__finalCompiled .= '

<div class="contentRow-title">
	';
	if ($__vars['content']['user_id'] == $__vars['xf']['visitor']['user_id']) {
		$__finalCompiled .= '
		' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['fallbackName'], ), ), true) . ' reacted ' . $__templater->fn('reaction', array($__vars['newsFeed']['extra_data']['reaction_id'], 'newsfeed', ), true) . ' to your resource ' . (((('<a href="' . $__templater->fn('link', array('resources', $__vars['content']['Resource'], ), true)) . '">') . $__templater->escape($__vars['content']['Resource']['title'])) . '</a>') . '.' . '
		';
	} else {
		$__finalCompiled .= '
		' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['fallbackName'], ), ), true) . ' reacted ' . $__templater->fn('reaction', array($__vars['newsFeed']['extra_data']['reaction_id'], 'newsfeed', ), true) . ' to ' . $__templater->escape($__vars['content']['Resource']['username']) . '\'s resource ' . (((('<a href="' . $__templater->fn('link', array('resources', $__vars['content']['Resource'], ), true)) . '">') . $__templater->escape($__vars['content']['Resource']['title'])) . '</a>') . '.' . '
	';
	}
	$__finalCompiled .= '
</div>

' . '

<div class="contentRow-minor">' . $__templater->fn('date_dynamic', array($__vars['newsFeed']['event_date'], array(
	))) . '</div>';
	return $__finalCompiled;
});