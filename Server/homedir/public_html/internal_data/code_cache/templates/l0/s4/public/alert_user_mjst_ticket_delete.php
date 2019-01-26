<?php
// FROM HASH: dd04f925b2dc546794e2c6cd19f3466d
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= 'Your ticket ' . ($__templater->fn('prefix', array('support_ticket', $__vars['extra']['prefix_id'], ), true) . $__templater->escape($__vars['extra']['full_title'])) . ' was deleted.' . '
';
	if ($__vars['extra']['reason']) {
		$__finalCompiled .= 'Reason' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['extra']['reason']);
	}
	return $__finalCompiled;
});