<?php
// FROM HASH: ec654b6e749ca97a8ba8c0e151367169
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '' . $__templater->escape($__vars['extra']['username']) . ', your subscription to <i><b>' . $__templater->escape($__vars['extra']['upgrade_title']) . '</b></i> has now expired.<br />Thank you for having purchased premium and we hope you have enjoyed the extensions it offered.<br />You may view account upgrades <a href="' . $__templater->escape($__vars['upgradeUrl']) . '" class="PopupItemLink">here</a>.' . '

';
	if ($__vars['extra']['upgradeDenied']) {
		$__finalCompiled .= '
	' . 'Your current upgrade is full on slots.' . '
';
	}
	return $__finalCompiled;
});