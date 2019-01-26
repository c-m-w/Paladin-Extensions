<?php
// FROM HASH: 76d3d68bf10606678c9b9e17ad98051e
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '' . $__templater->escape($__vars['extra']['username']) . ', thank you for purchasing the account subscription named <i><b>' . $__templater->escape($__vars['extra']['upgrade_title']) . '</b></i>.<br />We hope you will take advantage of and enjoy all the benefits it has to offer.<br />You may view your account upgrades <a href="' . $__templater->escape($__vars['upgradeUrl']) . '" class="PopupItemLink">here</a>.';
	return $__finalCompiled;
});