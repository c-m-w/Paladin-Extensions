<?php
// FROM HASH: e17cecf310dae36338e6981cbaf7364e
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => $__vars['inputName'] . '[alert][active]',
		'value' => 'alert',
		'selected' => $__vars['option']['option_value']['alert']['active'],
		'label' => 'Alert',
		'_type' => 'option',
	),
	array(
		'name' => $__vars['inputName'] . '[email][active]',
		'value' => 'email',
		'selected' => $__vars['option']['option_value']['email']['active'],
		'label' => 'Email',
		'_type' => 'option',
	),
	array(
		'name' => $__vars['inputName'] . '[conversation][active]',
		'value' => 'conversation',
		'label' => 'Conversation',
		'selected' => $__vars['option']['option_value']['conversation']['active'],
		'_dependent' => array('
            ' . $__templater->formTextBoxRow(array(
		'name' => $__vars['inputName'] . '[conversation][sender_username]',
		'value' => $__vars['option']['option_value']['conversation']['sender_username'],
		'ac' => 'single',
		'autocomplete' => 'off',
		'maxlength' => $__templater->fn('max_length', array($__vars['xf']['visitor'], 'username', ), false),
	), array(
		'label' => 'Sender (Username)',
		'hint' => 'Required',
	)) . '
        '),
		'_type' => 'option',
	)), array(
		'label' => $__templater->escape($__vars['option']['title']),
		'hint' => $__templater->escape($__vars['hintHtml']),
		'explain' => $__templater->escape($__vars['explainHtml']),
		'html' => $__templater->escape($__vars['listedHtml']),
	));
	return $__finalCompiled;
});