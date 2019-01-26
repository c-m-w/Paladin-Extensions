<?php
// FROM HASH: b3b4de0ba76d5eda04ae5e1b79e85fa3
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '
        
' . $__templater->formTextBoxRow(array(
		'name' => 'options[client_id]',
		'value' => $__vars['options']['client_id'],
	), array(
		'label' => 'Domain Name',
		'hint' => 'Required',
		'explain' => '        Base domain WITH "https://" (e.g. https://example.com)',
	)) . '
' . $__templater->formTextBoxRow(array(
		'name' => 'options[client_secret]',
		'value' => $__vars['options']['client_secret'],
	), array(
		'label' => 'API Key',
		'hint' => 'Required',
		'explain' => '
        Steam Web API Key',
	)) . '
        
    ';
	return $__finalCompiled;
});