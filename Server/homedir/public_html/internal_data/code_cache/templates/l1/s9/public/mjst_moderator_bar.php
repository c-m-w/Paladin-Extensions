<?php
// FROM HASH: 88e676aa6c9c4703423811a321916d22
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['xf']['visitor']['is_moderator'] AND $__templater->method($__vars['xf']['visitor'], 'canViewSupportTickets', array())) {
		$__finalCompiled .= '
	';
		$__vars['ticketCounts'] = $__templater->method($__vars['xf']['visitor'], 'getTicketCounts', array());
		$__finalCompiled .= '
	';
		if ($__vars['ticketCounts']) {
			$__finalCompiled .= '
		<a href="' . $__templater->fn('link', array('support-tickets', ), true) . '" class="p-staffBar-link badgeContainer badgeContainer--' . (($__vars['ticketCounts']['waitReply'] > 0) ? 'highlighted' : 'visible') . '" data-badge="' . $__templater->filter($__vars['ticketCounts']['waitReply'], array(array('number', array()),), true) . '/' . $__templater->filter($__vars['ticketCounts']['active'], array(array('number', array()),), true) . '">
			' . '<font size="3"><i class="fa fa-life-ring"></i></font>' . '
		</a>
	';
		}
		$__finalCompiled .= '
';
	}
	return $__finalCompiled;
});