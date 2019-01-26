<?php
// FROM HASH: b9731c35960a05907a3b1ab2a1290cf2
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['content'], 'isFirstMessage', array())) {
		$__finalCompiled .= '
	' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['alert']['username'], ), ), true) . ' created a ticket called ' . ((((('<a href="' . $__templater->fn('link', array('support-tickets', $__vars['content']['Ticket'], ), true)) . '" class="fauxBlockLink-blockLink">') . $__templater->fn('prefix', array('support_ticket', $__vars['content']['Ticket'], ), true)) . $__templater->escape($__vars['content']['Ticket']['title'])) . '</a>') . '. There may be more messages after this.' . '
';
	} else {
		$__finalCompiled .= '
	' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['alert']['username'], ), ), true) . ' replied to the ticket ' . ((((('<a href="' . $__templater->fn('link', array('support-tickets/messages', $__vars['content'], ), true)) . '" class="fauxBlockLink-blockLink">') . $__templater->fn('prefix', array('support_ticket', $__vars['content']['Ticket'], ), true)) . $__templater->escape($__vars['content']['Ticket']['title'])) . '</a>') . '. There may be more messages after this.' . '
';
	}
	return $__finalCompiled;
});