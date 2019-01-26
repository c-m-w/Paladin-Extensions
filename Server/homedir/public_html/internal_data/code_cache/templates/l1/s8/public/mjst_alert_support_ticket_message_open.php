<?php
// FROM HASH: 2bed97318eb3c90d7ba79787001f3396
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['alert']['username'], ), ), true) . ' opened a ticket called ' . ((((('<a href="' . $__templater->fn('link', array('support-tickets/messages', $__vars['content'], ), true)) . '" class="fauxBlockLink-blockLink">') . $__templater->fn('prefix', array('support_ticket', $__vars['content']['Ticket'], ), true)) . $__templater->escape($__vars['content']['Ticket']['title'])) . '</a>') . ' for you.';
	return $__finalCompiled;
});