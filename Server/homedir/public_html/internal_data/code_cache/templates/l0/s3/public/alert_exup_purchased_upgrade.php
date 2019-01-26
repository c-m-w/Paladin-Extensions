<?php
// FROM HASH: 4644ddf20c8bcdbcd1bda072d46f7afb
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '' . $__templater->escape($__vars['extra']['username']) . ', thank you for purchasing the account upgrade named <i><b>' . $__templater->escape($__vars['extra']['upgrade_title']) . '</b></i>.<br />We hope you will take advantage of and enjoy all the benefits it has to offer.<br />You may view your account upgrades <a href="' . $__templater->escape($__vars['upgradeUrl']) . '" class="PopupItemLink">here</a>.';
	return $__finalCompiled;
});