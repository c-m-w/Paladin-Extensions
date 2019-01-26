<?php
// FROM HASH: 039b6a942e678d5ec030366ebf7f191c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__compilerTemp1 = array();
	if ($__templater->isTraversable($__vars['channels'])) {
		foreach ($__vars['channels'] AS $__vars['channel']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['channel']['id'],
				'label' => '# ' . $__templater->escape($__vars['channel']['name']),
				'_type' => 'option',
			);
		}
	}
	$__finalCompiled .= $__templater->formCheckBoxRow(array(
	), array(array(
		'selected' => $__vars['option']['option_value']['channel'],
		'_dependent' => array($__templater->formSelect(array(
		'name' => $__vars['inputName'] . '[channel]',
		'value' => $__vars['option']['option_value']['channel'],
	), $__compilerTemp1), $__templater->formCheckBox(array(
	), array(array(
		'name' => $__vars['inputName'] . '[crate]',
		'value' => '1',
		'selected' => $__vars['option']['option_value']['crate'],
		'label' => 'Enable crate pop-up wrapper',
		'_type' => 'option',
	),
	array(
		'name' => $__vars['inputName'] . '[toast]',
		'value' => '1',
		'selected' => $__vars['option']['option_value']['toast'],
		'label' => 'Enable crate toast notifications',
		'_type' => 'option',
	)))),
		'_type' => 'option',
	)), array(
		'label' => $__templater->escape($__vars['option']['title']),
		'hint' => $__templater->escape($__vars['hintHtml']),
		'explain' => $__templater->escape($__vars['explainHtml']),
		'html' => $__templater->escape($__vars['listedHtml']),
	));
	return $__finalCompiled;
});