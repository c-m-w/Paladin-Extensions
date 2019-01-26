<?php
// FROM HASH: 8ad6727315086510335771a03877ab5f
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '' . $__templater->escape($__vars['extra']['username']) . ', your payment for the account upgrade named <i><b>' . $__templater->escape($__vars['extra']['upgrade_title']) . '</b></i> has been reversed.<br />Therefore the upgrade has been removed.<br />You may view your account upgrades <a href="' . $__templater->escape($__vars['upgradeUrl']) . '" class="PopupItemLink">here</a>.';
	return $__finalCompiled;
});