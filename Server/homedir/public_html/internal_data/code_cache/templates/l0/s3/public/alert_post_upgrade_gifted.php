<?php
// FROM HASH: 3eb38c90e137a376df3940845df6b00e
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '{xen:phrase nf_alert_post_upgrade_gifted,
	\'name={xen:helper username, $user, \'subject\'}\',
	\'title=<a href="{xen:link posts, $content}" class="PopupItemLink">{xen:helper threadPrefix, $content}' . $__templater->escape($__vars['content']['title']) . '</a>\'
}';
	return $__finalCompiled;
});