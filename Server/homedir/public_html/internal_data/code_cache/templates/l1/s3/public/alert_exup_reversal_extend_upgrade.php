<?php
// FROM HASH: 4ff5d366e96e4c2d5b414899d33239eb
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '' . $__templater->escape($__vars['extra']['username']) . ', your payment for extending the account upgrade named <i><b>' . $__templater->escape($__vars['extra']['upgrade_title']) . '</b></i> has been reversed.<br />Therefore the upgrade expiry date has been adjusted accordingly.<br />You may view your account upgrades <a href="' . $__templater->escape($__vars['upgradeUrl']) . '" class="PopupItemLink">here</a>.';
	return $__finalCompiled;
});