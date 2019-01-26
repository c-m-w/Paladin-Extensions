<?php
// FROM HASH: 1bbb55eeda56927de8c740ab920362ff
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('th_reactions.less');
	$__finalCompiled .= '

' . '' . $__templater->fn('username_link', array($__vars['sender'], false, array('defaultname' => $__vars['alert']['username'], ), ), true) . ' reacted ' . $__templater->fn('reaction', array($__vars['alert']['extra_data']['reaction_id'], 'alert', ), true) . ' to your media ' . (((('<a href="' . $__templater->fn('link', array('media', $__vars['content'], ), true)) . '" class="fauxBlockLink-blockLink">') . $__templater->escape($__vars['content']['title'])) . '</a>') . '.';
	return $__finalCompiled;
});