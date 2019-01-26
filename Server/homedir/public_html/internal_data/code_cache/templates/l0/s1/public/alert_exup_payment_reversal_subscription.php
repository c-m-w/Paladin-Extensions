<?php
// FROM HASH: 45e5f6cad37ee31c20f9b915c36491c1
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '' . $__templater->escape($__vars['extra']['username']) . ', your payment for the account subscription named <i><b>' . $__templater->escape($__vars['extra']['upgrade_title']) . '</b></i> has been reversed.<br />Therefore the upgrade has been removed.<br />You may view your account upgrades <a href="' . $__templater->escape($__vars['upgradeUrl']) . '" class="PopupItemLink">here</a>.';
	return $__finalCompiled;
});