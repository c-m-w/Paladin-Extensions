<?php
// FROM HASH: b9a9651413a794334d0ca12d46e48404
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__compilerTemp1 = $__templater->mergeChoiceOptions(array(), $__vars['rewardTypes']);
	$__finalCompiled .= $__templater->formRow('

	<div class="inputGroup">
		' . $__templater->formNumberBox(array(
		'name' => $__vars['inputName'] . '[reward_amount]',
		'value' => $__vars['option']['option_value']['reward_amount'],
		'min' => '0',
	)) . '
		<span class="inputGroup-splitter"></span>
		' . $__templater->formSelect(array(
		'name' => $__vars['inputName'] . '[reward_type_id]',
		'value' => $__vars['option']['option_value']['reward_type_id'],
		'class' => 'input--autoSize',
	), $__compilerTemp1) . '
	</div>
', array(
		'rowtype' => 'input',
		'hint' => $__templater->escape($__vars['hintHtml']),
		'explain' => $__templater->escape($__vars['explainHtml']),
		'html' => $__templater->escape($__vars['listedHtml']),
		'label' => $__templater->escape($__vars['option']['title']),
	));
	return $__finalCompiled;
});