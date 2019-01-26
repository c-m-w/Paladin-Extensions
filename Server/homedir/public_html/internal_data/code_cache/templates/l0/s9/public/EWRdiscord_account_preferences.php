<?php
// FROM HASH: f246147e8f19d1c565848b3dea72c753
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['xf']['options']['EWRdiscord_widgetbot'] AND $__templater->method($__vars['xf']['visitor'], 'hasPermission', array('EWRdiscord', 'viewCrate', ))) {
		$__finalCompiled .= '
	' . $__templater->formCheckBoxRow(array(
		), array(array(
			'name' => 'discord_options[crate]',
			'checked' => (!$__vars['xf']['visitor']['Option']['discord_options']['crate']),
			'label' => 'Enable Discord chat pop-up button' . $__vars['xf']['language']['ellipsis'],
			'_dependent' => array($__templater->formCheckBox(array(
		), array(array(
			'name' => 'discord_options[count]',
			'checked' => (!$__vars['xf']['visitor']['Option']['discord_options']['count']),
			'label' => 'and enable new message counter',
			'_type' => 'option',
		),
		array(
			'name' => 'discord_options[toast]',
			'checked' => (!$__vars['xf']['visitor']['Option']['discord_options']['toast']),
			'label' => 'and enable toast notifications',
			'_type' => 'option',
		)))),
			'_type' => 'option',
		)), array(
		)) . '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['xf']['visitor']['ConnectedAccounts']['discord']['provider_key']) {
		$__finalCompiled .= '
	' . $__templater->formCheckBoxRow(array(
		), array(array(
			'name' => 'discord_options[alert]',
			'checked' => (!$__vars['xf']['visitor']['Option']['discord_options']['alert']),
			'label' => 'Receive direct messages and updates on Discord' . $__vars['xf']['language']['ellipsis'],
			'_type' => 'option',
		)), array(
		)) . '
';
	}
	return $__finalCompiled;
});