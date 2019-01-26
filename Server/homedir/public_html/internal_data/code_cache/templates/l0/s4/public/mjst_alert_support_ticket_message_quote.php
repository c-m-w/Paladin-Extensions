<?php
// FROM HASH: 619b50eb79ba24fe8374aecf5d42e7c8
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['alert']['username'], ), ), true) . ' quoted your message in the ticket ' . ((((('<a href="' . $__templater->fn('link', array('support-tickets/messages', $__vars['content'], ), true)) . '" class="fauxBlockLink-blockLink">') . $__templater->fn('prefix', array('support_ticket', $__vars['content']['Ticket'], ), true)) . $__templater->escape($__vars['content']['Ticket']['full_title'])) . '</a>') . '.';
	return $__finalCompiled;
});