<?php
// FROM HASH: a8bc9d3a02a995a35a320c86431c338c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->callMacro('multi_quote_macros', 'block', array(
		'quotes' => $__vars['quotes'],
		'messages' => $__vars['messages'],
		'containerRelation' => 'Ticket',
		'dateKey' => 'message_date',
		'bbCodeContext' => 'support_ticket_message',
	), $__vars);
	return $__finalCompiled;
});