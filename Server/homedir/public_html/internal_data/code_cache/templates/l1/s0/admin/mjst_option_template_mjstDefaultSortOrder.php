<?php
// FROM HASH: 0c69df83c22c4fc7910d11b3df3cefdc
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->formRow('
	<div class="inputPair">
		' . $__templater->formSelect(array(
		'name' => $__vars['inputName'] . '[order]',
		'value' => $__vars['option']['option_value']['order'],
		'class' => 'input--inline',
	), array(array(
		'value' => 'last_update',
		'label' => 'Last update',
		'_type' => 'option',
	),
	array(
		'value' => 'open_date',
		'label' => 'First message',
		'_type' => 'option',
	),
	array(
		'value' => 'last_message_date',
		'label' => 'Last message',
		'_type' => 'option',
	),
	array(
		'value' => 'title',
		'label' => 'Title',
		'_type' => 'option',
	),
	array(
		'value' => 'reply_count',
		'label' => 'Replies',
		'_type' => 'option',
	))) . '
		' . $__templater->formSelect(array(
		'name' => $__vars['inputName'] . '[direction]',
		'value' => $__vars['option']['option_value']['direction'],
		'class' => 'input--inline',
	), array(array(
		'value' => 'desc',
		'label' => 'Descending',
		'_type' => 'option',
	),
	array(
		'value' => 'asc',
		'label' => 'Ascending',
		'_type' => 'option',
	))) . '
	</div>
', array(
		'rowtype' => 'input',
		'label' => $__templater->escape($__vars['option']['title']),
		'hint' => $__templater->escape($__vars['hintHtml']),
		'explain' => $__templater->escape($__vars['explainHtml']),
		'html' => $__templater->escape($__vars['listedHtml']),
	));
	return $__finalCompiled;
});