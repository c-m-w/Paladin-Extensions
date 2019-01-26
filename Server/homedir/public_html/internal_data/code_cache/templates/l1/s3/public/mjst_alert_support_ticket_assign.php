<?php
// FROM HASH: 7225eec4b109cf320cb3d3ada0b64fae
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= 'Ticket <b>' . ((((('<a href="' . $__templater->fn('link', array('support-tickets', $__vars['content'], ), true)) . '" class="fauxBlockLink-blockLink">') . $__templater->fn('prefix', array('support_ticket', $__vars['content'], ), true)) . $__templater->escape($__vars['content']['title'])) . '</a>') . '</b> has been assigned to you';
	return $__finalCompiled;
});