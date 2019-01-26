<?php
// FROM HASH: 564f0cb181e0ec80cd353f7fbce92311
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= 'Your message in the ticket ' . ((((('<a href="' . $__templater->fn('base_url', array($__vars['extra']['ticketLink'], ), true)) . '" class="fauxBlockLink-blockLink">') . $__templater->fn('prefix', array('ticket', $__vars['extra']['prefix_id'], ), true)) . $__templater->escape($__vars['extra']['full_title'])) . '</a>') . ' was deleted.' . '
';
	if ($__vars['extra']['reason']) {
		$__finalCompiled .= 'Reason' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['extra']['reason']);
	}
	return $__finalCompiled;
});