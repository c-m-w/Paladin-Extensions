<?php
// FROM HASH: eebf02068f46f2daa5a1d1683d6bfa24
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => $__vars['inputName'] . '[enabled]',
		'selected' => $__vars['option']['option_value']['enabled'],
		'data-hide' => 'true',
		'label' => 'Enable',
		'_dependent' => array('
			' . $__templater->formCheckBox(array(
	), array(array(
		'name' => $__vars['inputName'] . '[only_guest]',
		'value' => '1',
		'selected' => $__vars['option']['option_value']['only_guest'],
		'label' => 'Captcha use only guest',
		'hint' => 'If this option is disabled, the captcha will be required with both users and anonymous guest',
		'_type' => 'option',
	))) . '
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