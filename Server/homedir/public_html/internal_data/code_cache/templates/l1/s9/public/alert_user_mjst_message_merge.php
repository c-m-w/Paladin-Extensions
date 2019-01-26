<?php
// FROM HASH: 1dbb4fdd100a15349cc8ddb7f08c90bb
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= 'Your messages in ticket ' . ((((('<a href="' . $__templater->fn('base_url', array($__vars['extra']['ticketLink'], ), true)) . '" class="fauxBlockLink-blockLink">') . $__templater->fn('prefix', array('support_ticket', $__vars['extra']['prefix_id'], ), true)) . $__templater->escape($__vars['extra']['full_title'])) . '</a>') . ' were merged together' . '
';
	if ($__vars['extra']['reason']) {
		$__finalCompiled .= 'Reason' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['extra']['reason']);
	}
	return $__finalCompiled;
});