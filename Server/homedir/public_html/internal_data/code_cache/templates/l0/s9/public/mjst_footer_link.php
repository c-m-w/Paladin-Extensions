<?php
// FROM HASH: 9195d6464a8e827a2ba06798098ada66
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['xf']['visitor'], 'canViewSupportTickets', array()) AND $__vars['xf']['options']['mjstDisplayOption']['footer']) {
		$__finalCompiled .= '
	<li><a href="' . $__templater->fn('link', array('support-tickets', ), true) . '">' . 'Support tickets' . '</a></li>
';
	}
	return $__finalCompiled;
});