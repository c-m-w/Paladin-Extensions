<?php
// FROM HASH: e5395f16c9530468ecc652da65078cfc
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->formTextBoxRow(array(
		'name' => 'options[client_id]',
		'value' => $__vars['options']['client_id'],
	), array(
		'label' => 'Client ID',
		'hint' => 'Required',
		'explain' => 'The client ID that is associated with your <a href="https://discordapp.com/developers/applications/me" target="_blank">Discord developer application</a> for this domain.',
	)) . '

' . $__templater->formTextBoxRow(array(
		'name' => 'options[client_secret]',
		'value' => $__vars['options']['client_secret'],
	), array(
		'label' => 'Client secret',
		'hint' => 'Required',
		'explain' => 'The secret for the Discord application you created for this domain.',
	)) . '

' . $__templater->formTextBoxRow(array(
		'name' => 'options[bot_token]',
		'value' => $__vars['options']['bot_token'],
	), array(
		'label' => 'Bot token',
		'hint' => 'Required',
		'explain' => 'The token for the "App Bot User" you created for this domain.',
	));
	return $__finalCompiled;
});