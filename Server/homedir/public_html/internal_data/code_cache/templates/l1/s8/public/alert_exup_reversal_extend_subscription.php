<?php
// FROM HASH: 6077dae2a075d2ba59f559f4fdbde5da
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '' . $__templater->escape($__vars['extra']['username']) . ', your payment for extending the account subscription named <i><b>' . $__templater->escape($__vars['extra']['upgrade_title']) . '</b></i> has been reversed.<br />Therefore the upgrade expiry date has been adjusted accordingly.<br />You may view your account upgrades <a href="' . $__templater->escape($__vars['upgradeUrl']) . '" class="PopupItemLink">here</a>.';
	return $__finalCompiled;
});