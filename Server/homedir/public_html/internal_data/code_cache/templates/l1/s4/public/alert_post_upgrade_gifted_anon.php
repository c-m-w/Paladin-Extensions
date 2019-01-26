<?php
// FROM HASH: 8e4d37171a29f6fb2528180052d7d215
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '{xen:phrase nf_alert_post_upgrade_gifted_anon,
	\'title=<a href="{xen:link posts, $content}" class="PopupItemLink">{xen:helper threadPrefix, $content}' . $__templater->escape($__vars['content']['title']) . '</a>\'
}';
	return $__finalCompiled;
});