<?php
// FROM HASH: 5ae234a91fe4de2f66ff8235d0de8726
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['alert']['username'], ), ), true) . ' mentioned your message in the ticket ' . ((((('<a href="' . $__templater->fn('link', array('support-tickets/messages', $__vars['content'], ), true)) . '" class="fauxBlockLink-blockLink">') . $__templater->fn('prefix', array('support_ticket', $__vars['content']['Ticket'], ), true)) . $__templater->escape($__vars['content']['Ticket']['full_title'])) . '</a>') . '.';
	return $__finalCompiled;
});