<?php
// FROM HASH: 55935cdf346a8dd39cf6ce09a51b6e72
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->formRow('

	' . $__templater->formRadio(array(
		'name' => $__vars['inputName'] . '[action]',
		'value' => $__vars['option']['option_value']['action'],
	), array(array(
		'value' => '',
		'label' => 'No change',
		'_type' => 'option',
	),
	array(
		'value' => 'delete',
		'label' => 'Delete thread',
		'_type' => 'option',
	),
	array(
		'value' => 'close',
		'label' => 'Close thread',
		'_type' => 'option',
	))) . '
	<div class="formRow-explain">' . $__templater->escape($__vars['explainHtml']) . '</div>

	<div class="u-inputSpacer">
		' . $__templater->formCheckBox(array(
	), array(array(
		'name' => $__vars['inputName'] . '[update_title]',
		'selected' => $__vars['option']['option_value']['update_title'],
		'label' => 'Update thread title on extension deletion' . $__vars['xf']['language']['label_separator'],
		'_dependent' => array($__templater->formTextBox(array(
		'name' => $__vars['inputName'] . '[title_template]',
		'value' => $__vars['option']['option_value']['title_template'],
	))),
		'_type' => 'option',
	),
	array(
		'name' => $__vars['inputName'] . '[add_post]',
		'selected' => $__vars['option']['option_value']['add_post'],
		'label' => 'Automatically post in the extension thread on extension deletion',
		'hint' => 'If selected, a post will be made automatically on the creator\'s behalf explaining that the extension is no longer available.',
		'_type' => 'option',
	))) . '
	</div>
', array(
		'label' => $__templater->escape($__vars['option']['title']),
		'hint' => $__templater->escape($__vars['hintHtml']),
		'html' => $__templater->escape($__vars['listedHtml']),
	));
	return $__finalCompiled;
});