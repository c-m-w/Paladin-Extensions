<?php
// FROM HASH: 9af4816209a1fca7c0717f92af0d3ccd
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('th_reactions.less');
	$__finalCompiled .= '

' . '' . $__templater->fn('username_link', array($__vars['sender'], false, array('defaultname' => $__vars['alert']['username'], ), ), true) . ' reacted ' . $__templater->fn('reaction', array($__vars['alert']['extra_data']['reaction_id'], 'alert', ), true) . ' to your comment on ' . (((('<a href="' . $__templater->fn('link', array((($__vars['content']['content_type'] === 'xfmg_media') ? 'media/comments' : 'album/comments'), $__vars['content'], ), true)) . '">') . (($__vars['content']['content_type'] === 'xfmg_media') ? $__templater->escape($__vars['content']['Media']['title']) : $__templater->escape($__vars['content']['Album']['title']))) . '</a>') . '.';
	return $__finalCompiled;
});