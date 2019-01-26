<?php
// FROM HASH: 504fc23cb543678803ae0136c7865712
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('th_reactions.less');
	$__finalCompiled .= '

' . '' . $__templater->fn('username_link', array($__vars['sender'], false, array('defaultname' => $__vars['alert']['username'], ), ), true) . ' reacted ' . $__templater->fn('reaction', array($__vars['alert']['extra_data']['reaction_id'], 'alert', ), true) . ' to your message in the conversation ' . (((('<a href="' . $__templater->fn('link', array('conversations/messages', $__vars['content'], ), true)) . '">') . $__templater->escape($__vars['content']['Conversation']['title'])) . '</a>') . '.';
	return $__finalCompiled;
});