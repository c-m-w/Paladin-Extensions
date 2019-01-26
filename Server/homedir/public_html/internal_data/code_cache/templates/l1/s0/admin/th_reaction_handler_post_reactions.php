<?php
// FROM HASH: 3df7cfbeb45a5f573fa6205a1700c4dc
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__compilerTemp1 = array(array(
		'value' => 'all',
		'selected' => $__vars['reaction']['options']['allowed_node_ids'] == 'all',
		'label' => $__vars['xf']['language']['parenthesis_open'] . 'All' . $__vars['xf']['language']['parenthesis_close'],
		'_type' => 'option',
	));
	$__compilerTemp2 = $__templater->method($__vars['nodeTree'], 'getFlattened', array(0, ));
	if ($__templater->isTraversable($__compilerTemp2)) {
		foreach ($__compilerTemp2 AS $__vars['treeEntry']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['treeEntry']['record']['node_id'],
				'disabled' => ($__vars['treeEntry']['record']['node_type_id'] == 'Category'),
				'label' => $__templater->filter($__templater->fn('repeat', array('&nbsp;&nbsp;', $__vars['treeEntry']['depth'], ), false), array(array('raw', array()),), true) . ' ' . $__templater->escape($__vars['treeEntry']['record']['title']),
				'selected' => ($__vars['treeEntry']['record']['node_type_id'] == 'Forum') AND (($__vars['reaction']['options']['allowed_node_ids'] == 'all') OR $__templater->fn('in_array', array($__vars['treeEntry']['record']['node_id'], $__vars['reaction']['options']['allowed_node_ids'], ), false)),
				'_type' => 'option',
			);
		}
	}
	$__finalCompiled .= $__templater->formRow('
	<ul class="inputList">
		<li>
			' . $__templater->formSelect(array(
		'name' => 'options[allowed_node_ids][]',
		'value' => $__vars['reaction']['options']['allowed_node_ids'],
		'size' => '7',
		'multiple' => 'multiple',
		'class' => 'js-applicableForums',
	), $__compilerTemp1) . '
		</li>

		' . $__templater->formHiddenVal('nodeCount', $__templater->fn('count', array($__templater->method($__vars['nodeTree'], 'getFlattened', array(0, )), ), false), array(
	)) . '
	</ul>
', array(
		'rowtype' => 'input',
		'label' => 'Allowed forums',
	)) . '

';
	$__compilerTemp3 = array(array(
		'value' => 'none',
		'selected' => ($__vars['reaction']['options']['disabled_node_ids'] == 'none') OR (!$__vars['reaction']['options']['disabled_node_ids']),
		'label' => $__vars['xf']['language']['parenthesis_open'] . 'None' . $__vars['xf']['language']['parenthesis_close'],
		'_type' => 'option',
	));
	$__compilerTemp4 = $__templater->method($__vars['nodeTree'], 'getFlattened', array(0, ));
	if ($__templater->isTraversable($__compilerTemp4)) {
		foreach ($__compilerTemp4 AS $__vars['treeEntry']) {
			$__compilerTemp3[] = array(
				'value' => $__vars['treeEntry']['record']['node_id'],
				'disabled' => ($__vars['treeEntry']['record']['node_type_id'] == 'Category'),
				'label' => $__templater->filter($__templater->fn('repeat', array('&nbsp;&nbsp;', $__vars['treeEntry']['depth'], ), false), array(array('raw', array()),), true) . ' ' . $__templater->escape($__vars['treeEntry']['record']['title']),
				'selected' => ($__vars['treeEntry']['record']['node_type_id'] == 'Forum') AND (($__vars['reaction']['options']['allowed_node_ids'] != 'none') AND $__templater->fn('in_array', array($__vars['treeEntry']['record']['node_id'], $__vars['reaction']['options']['disabled_node_ids'], ), false)),
				'_type' => 'option',
			);
		}
	}
	$__finalCompiled .= $__templater->formRow('
	<ul class="inputList">
		<li>
			' . $__templater->formSelect(array(
		'name' => 'options[disabled_node_ids][]',
		'value' => $__vars['reaction']['options']['disabled_node_ids'],
		'size' => '7',
		'multiple' => 'multiple',
		'class' => 'js-applicableForums',
	), $__compilerTemp3) . '
		</li>

		' . $__templater->formHiddenVal('nodeCount', $__templater->fn('count', array($__templater->method($__vars['nodeTree'], 'getFlattened', array(0, )), ), false), array(
	)) . '
	</ul>
', array(
		'rowtype' => 'input',
		'label' => 'Disabled forums',
	));
	return $__finalCompiled;
});