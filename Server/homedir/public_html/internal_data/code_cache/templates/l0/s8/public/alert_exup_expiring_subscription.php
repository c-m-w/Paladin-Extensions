<?php
// FROM HASH: 6328233830d28bb6104776c3c7cf2114
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['extra']['upgradeDenied']) {
		$__finalCompiled .= '
	' . $__templater->includeTemplate('alert_exup_expiring_upgrade', $__vars) . '
';
	} else {
		$__finalCompiled .= '
	' . '' . $__templater->escape($__vars['extra']['username']) . ', your account upgrade subscription named <i><b>' . $__templater->escape($__vars['extra']['upgrade_title']) . '</b></i> will automatically renew in ' . $__templater->escape($__vars['extra']['num_days']) . ' days.<br />We hope you have been enjoying the benefits this upgrade offers and thank you in advance for renewing your subscription.<br />You may view your account upgrades <a href="' . $__templater->escape($__vars['upgradeUrl']) . '" class="PopupItemLink">here</a>.' . '
';
	}
	return $__finalCompiled;
});