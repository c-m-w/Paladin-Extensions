<?php
// FROM HASH: 0b38a06b13a28f0e1b3c2a00de4816c6
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('th_reactions.less');
	$__finalCompiled .= '

<div class="contentRow-title">
	';
	if ($__vars['content']['user_id'] == $__vars['xf']['visitor']['user_id']) {
		$__finalCompiled .= '
		' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['fallbackName'], ), ), true) . ' reacted ' . $__templater->fn('reaction', array($__vars['newsFeed']['extra_data']['reaction_id'], 'newsfeed', ), true) . ' to your media ' . (((('<a href="' . $__templater->fn('link', array('media', $__vars['content'], ), true)) . '">') . $__templater->escape($__vars['content']['title'])) . '</a>') . '.' . '
		';
	} else {
		$__finalCompiled .= '
		' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['fallbackName'], ), ), true) . ' reacted ' . $__templater->fn('reaction', array($__vars['newsFeed']['extra_data']['reaction_id'], 'newsfeed', ), true) . ' to ' . $__templater->escape($__vars['content']['username']) . '\'s media ' . (((('<a href="' . $__templater->fn('link', array('media', $__vars['content'], ), true)) . '">') . $__templater->escape($__vars['content']['title'])) . '</a>') . '.' . '
	';
	}
	$__finalCompiled .= '
</div>

' . '

<div class="contentRow-minor">' . $__templater->fn('date_dynamic', array($__vars['newsFeed']['event_date'], array(
	))) . '</div>';
	return $__finalCompiled;
});