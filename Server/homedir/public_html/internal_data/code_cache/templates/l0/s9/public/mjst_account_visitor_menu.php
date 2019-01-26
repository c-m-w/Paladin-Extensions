<?php
// FROM HASH: c14c7897a8808e666ece2343bb63730f
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['xf']['visitor'], 'canViewSupportTickets', array()) AND $__vars['xf']['options']['mjstDisplayOption']['nav_visitor_tab']) {
		$__finalCompiled .= '
	<li><a href="' . $__templater->fn('link', array('support-tickets/yours', ), true) . '" class="menu-linkRow">' . 'Your tickets' . '</a></li>
';
	}
	return $__finalCompiled;
});