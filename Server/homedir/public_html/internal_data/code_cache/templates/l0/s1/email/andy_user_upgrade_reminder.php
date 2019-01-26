<?php
// FROM HASH: 041cec11ee8c07bcf9e6010068f95f66
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<mail:subject>
	' . 'Upgrade reminder' . ' (' . 'userupgradereminder_from' . ' ' . $__templater->escape($__vars['xf']['options']['boardTitle']) . ')
</mail:subject>

<h2>' . 'Upgrade reminder' . '</h2>

';
	if ($__templater->isTraversable($__vars['members'])) {
		foreach ($__vars['members'] AS $__vars['member']) {
			$__finalCompiled .= '
	<br />
	' . 'Dear' . '&nbsp;' . $__templater->escape($__vars['member']['username']) . ',<br /><br />
	' . 'Please note that your account upgrade at' . '&nbsp;' . $__templater->escape($__vars['xf']['options']['boardTitle']) . '
	' . 'is about to expire in' . '&nbsp;' . $__templater->escape($__vars['xf']['options']['userUpgradeReminderDays']) . '
	' . 'days.' . '<br /><br />
	' . 'Once your account has expired you can upgrade again.' . '<br /><br />
	<a href="' . $__templater->fn('link', array('canonical:account/upgrades', ), true) . '">' . $__templater->fn('link', array('canonical:account/upgrades', ), true) . '</a><br /><br />
	' . 'Thank you for your support. ' . '<br /><br />
	' . $__templater->escape($__vars['xf']['options']['boardTitle']) . '
';
		}
	}
	return $__finalCompiled;
});