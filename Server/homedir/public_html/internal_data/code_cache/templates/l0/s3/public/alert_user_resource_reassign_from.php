<?php
// FROM HASH: 3439d65edd1e734cac39a39aebe95d5f
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= 'Your resource ' . ((((('<a href="' . $__templater->fn('base_url', array($__vars['extra']['link'], ), true)) . '" class="fauxBlockLink-blockLink">') . $__templater->fn('prefix', array('resource', $__vars['extra']['prefix_id'], ), true)) . $__templater->escape($__vars['extra']['title'])) . '</a>') . ' was reassigned to ' . $__templater->escape($__vars['extra']['to']) . '.' . '
';
	if ($__vars['extra']['reason']) {
		$__finalCompiled .= 'Reason' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['extra']['reason']);
	}
	return $__finalCompiled;
});