<?php
// FROM HASH: e6d4ac3d6cd7c89ccfaee25206bb5f6e
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '' . $__templater->escape($__vars['extra']['username']) . ', your account upgrade named <i><b>' . $__templater->escape($__vars['extra']['upgrade_title']) . '</b></i> will expire in ' . $__templater->escape($__vars['extra']['num_days']) . ' days.<br />Thank you for having purchased this upgrade and we hope you have enjoyed the benefits it offered.<br />You may extend or renew your account upgrades <a href="' . $__templater->escape($__vars['upgradeUrl']) . '" class="PopupItemLink">here</a>.' . '

';
	if ($__vars['extra']['upgradeDenied']) {
		$__finalCompiled .= '
    ' . 'Your current upgrade is no longer available.' . '
';
	}
	return $__finalCompiled;
});