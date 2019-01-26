<?php
// FROM HASH: 7f07eb45c0a91aeb2daa3609b428d229
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__compilerTemp1 = $__templater->mergeChoiceOptions(array(), $__vars['choices']);
	$__finalCompiled .= $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => $__vars['inputName'] . '[enabled]',
		'selected' => $__vars['option']['option_value']['enabled'],
		'data-hide' => 'true',
		'label' => 'Enable',
		'_dependent' => array('
			' . $__templater->formCheckBox(array(
	), array(array(
		'name' => $__vars['inputName'] . '[disable_email]',
		'value' => '1',
		'selected' => $__vars['option']['option_value']['disable_email'],
		'label' => '
					' . 'Disable contact email' . '
				',
		'_type' => 'option',
	))) . '
		', '
			<div>' . 'Defaut department' . $__vars['xf']['language']['label_separator'] . '</div>
			' . $__templater->formSelect(array(
		'name' => $__vars['inputName'] . '[department_id]',
		'value' => $__vars['option']['option_value']['department_id'],
	), $__compilerTemp1) . '
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