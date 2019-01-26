<?php
// FROM HASH: 2f3f50628e2178266b9697ba3ea7138d
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('th_reactions.less');
	$__finalCompiled .= '

<div class="contentRow-title">
	';
	if ($__vars['content']['user_id'] == $__vars['xf']['visitor']['user_id']) {
		$__finalCompiled .= '
		' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['fallbackName'], ), ), true) . ' reacted ' . $__templater->fn('reaction', array($__vars['newsFeed']['extra_data']['reaction_id'], 'newsfeed', ), true) . ' to your comment on ' . (((('<a href="' . $__templater->fn('link', array('media', $__vars['content']['Media'], ), true)) . '">') . $__templater->escape($__vars['content']['Media']['title'])) . '</a>') . '.' . '
		';
	} else {
		$__finalCompiled .= '
		' . 'threactions_w_reacted_x_ys_media_z' . '
	';
	}
	$__finalCompiled .= '
</div>

' . '

<div class="contentRow-minor">' . $__templater->fn('date_dynamic', array($__vars['newsFeed']['event_date'], array(
	))) . '</div>';
	return $__finalCompiled;
});