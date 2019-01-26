<?php
// FROM HASH: 72b281b6008c87374d40b058e93d5b85
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('th_reactions.less');
	$__finalCompiled .= '

' . '' . $__templater->fn('username_link', array($__vars['sender'], false, array('defaultname' => $__vars['alert']['username'], ), ), true) . ' reacted ' . $__templater->fn('reaction', array($__vars['alert']['extra_data']['reaction_id'], 'alert', ), true) . ' to a post in the thread ' . ((((('<a href="' . $__templater->fn('link', array('posts', $__vars['content'], ), true)) . '" class="fauxBlockLink-blockLink">') . $__templater->fn('prefix', array('thread', $__vars['content']['Thread'], ), true)) . $__templater->escape($__vars['content']['Thread']['title'])) . '</a>') . '.';
	return $__finalCompiled;
});