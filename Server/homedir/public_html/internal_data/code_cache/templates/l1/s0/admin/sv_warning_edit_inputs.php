<?php
// FROM HASH: 1972d14996f83976a173de269f4d92f5
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__compilerTemp1 = array(array(
		'value' => '0',
		'label' => $__vars['xf']['language']['parenthesis_open'] . 'None' . $__vars['xf']['language']['parenthesis_close'],
		'_type' => 'option',
	));
	$__compilerTemp2 = $__templater->method($__vars['categoryTree'], 'getFlattened', array(0, ));
	if ($__templater->isTraversable($__compilerTemp2)) {
		foreach ($__compilerTemp2 AS $__vars['treeEntry']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['treeEntry']['record']['warning_category_id'],
				'label' => $__templater->fn('repeat', array('--', $__vars['treeEntry']['depth'], ), true) . ' ' . $__templater->escape($__vars['treeEntry']['record']['title']),
				'_type' => 'option',
			);
		}
	}
	$__finalCompiled .= $__templater->formSelectRow(array(
		'name' => 'sv_warning_category_id',
		'value' => $__vars['warning']['sv_warning_category_id'],
	), $__compilerTemp1, array(
		'label' => 'Warning Category' . $__vars['xf']['language']['label_separator'],
	)) . '

' . $__templater->callMacro('display_order_macros', 'row', array(
		'name' => 'sv_display_order',
		'value' => $__vars['warning']['sv_display_order'],
	), $__vars);
	return $__finalCompiled;
});