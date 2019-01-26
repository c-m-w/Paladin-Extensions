<?php
// FROM HASH: 0c8d77c12c5b642db3ced2b806190f61
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'user_criteria[threact_min_reactions][rule]',
		'value' => 'threact_min_reactions',
		'selected' => $__vars['criteria']['threact_min_reactions'],
		'label' => 'User has received at least X reactions' . $__vars['xf']['language']['label_separator'],
		'_dependent' => array($__templater->formNumberBox(array(
		'name' => 'user_criteria[threact_min_reactions][data][reactions]',
		'value' => $__vars['criteria']['threact_min_reactions']['reactions'],
		'size' => '5',
		'min' => '0',
		'step' => '1',
	))),
		'_type' => 'option',
	),
	array(
		'name' => 'user_criteria[threact_max_reactions][rule]',
		'value' => 'threact_max_reactions',
		'selected' => $__vars['criteria']['threact_max_reactions'],
		'label' => 'User has received no more than X reactions' . $__vars['xf']['language']['label_separator'],
		'_dependent' => array($__templater->formNumberBox(array(
		'name' => 'user_criteria[threact_max_reactions][data][reactions]',
		'value' => $__vars['criteria']['threact_max_reactions']['reactions'],
		'size' => '5',
		'min' => '0',
		'step' => '1',
	))),
		'_type' => 'option',
	)), array(
		'label' => 'Reactions',
	)) . '

<hr class="formRowSep" />';
	return $__finalCompiled;
});