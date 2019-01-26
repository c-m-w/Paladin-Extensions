<?php
// FROM HASH: 9de246c429a06beca5cb438ffede7277
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= 'Your message in the ticket ' . $__templater->escape($__vars['extra']['title']) . ' was copied to ' . ((((('<a href="' . $__templater->fn('base_url', array($__vars['extra']['targetLink'], ), true)) . '" class="fauxBlockLink-blockLink">') . $__templater->fn('prefix', array('ticket', $__vars['extra']['prefix_id'], ), true)) . $__templater->escape($__vars['extra']['targetTitle'])) . '</a>') . '' . '
';
	if ($__vars['extra']['reason']) {
		$__finalCompiled .= 'Reason' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['extra']['reason']);
	}
	return $__finalCompiled;
});