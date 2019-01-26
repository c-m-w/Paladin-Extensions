<?php
// FROM HASH: e8bb098082421fc0bc4bbc6367091ef1
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->formRow('
	<div class="inputGroup">
		' . $__templater->formTextBox(array(
		'name' => $__vars['formBaseKey'] . '[width]',
		'value' => $__vars['property']['property_value']['width'],
		'min' => '1',
		'title' => 'Width',
		'type' => 'number',
		'data-xf-init' => 'tooltip',
	)) . '
		<span class="inputGroup-text">x</span>
		' . $__templater->formTextBox(array(
		'name' => $__vars['formBaseKey'] . '[height]',
		'value' => $__vars['property']['property_value']['height'],
		'min' => '1',
		'title' => 'Height',
		'type' => 'number',
		'data-xf-init' => 'tooltip',
	)) . '
		<span class="inputGroup-text">|</span>
		' . $__templater->formTextBox(array(
		'name' => $__vars['formBaseKey'] . '[unit]',
		'value' => $__vars['property']['property_value']['unit'],
		'placeholder' => 'Unit',
	)) . '
	</div>
', array(
		'label' => $__templater->escape($__vars['titleHtml']),
		'hint' => $__templater->escape($__vars['hintHtml']),
		'rowclass' => $__vars['rowClass'],
		'explain' => $__templater->escape($__vars['property']['description']),
		'rowtype' => 'input',
	));
	return $__finalCompiled;
});