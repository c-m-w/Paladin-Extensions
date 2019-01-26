<?php
// FROM HASH: 9c5444b69603659954ee91d0e54a1ec1
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= 'Your ticket ' . ((((('<a href="' . $__templater->fn('base_url', array($__vars['extra']['link'], ), true)) . '" class="fauxBlockLink-blockLink">') . $__templater->fn('prefix', array('support_ticket', $__vars['extra']['prefix_id'], ), true)) . $__templater->escape($__vars['extra']['full_title'])) . '</a>') . ' was moved to a different department.' . '
';
	if ($__vars['extra']['reason']) {
		$__finalCompiled .= 'Reason' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['extra']['reason']);
	}
	return $__finalCompiled;
});