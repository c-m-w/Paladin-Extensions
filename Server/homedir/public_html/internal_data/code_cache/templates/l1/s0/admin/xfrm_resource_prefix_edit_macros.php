<?php
// FROM HASH: 362275cbf14c5b60f2de4cc67bd4d034
return array('macros' => array('category_ids' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'categoryIds' => '!',
		'categoryTree' => '!',
		'withRow' => '1',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__compilerTemp1 = array(array(
		'value' => '',
		'selected' => !$__vars['categoryIds'],
		'label' => $__vars['xf']['language']['parenthesis_open'] . 'None' . $__vars['xf']['language']['parenthesis_close'],
		'_type' => 'option',
	));
	$__compilerTemp2 = $__templater->method($__vars['categoryTree'], 'getFlattened', array(0, ));
	if ($__templater->isTraversable($__compilerTemp2)) {
		foreach ($__compilerTemp2 AS $__vars['treeEntry']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['treeEntry']['record']['resource_category_id'],
				'label' => $__templater->filter($__templater->fn('repeat', array('&nbsp;&nbsp;', $__vars['treeEntry']['depth'], ), false), array(array('raw', array()),), true) . ' ' . $__templater->escape($__vars['treeEntry']['record']['title']),
				'_type' => 'option',
			);
		}
	}
	$__vars['inner'] = $__templater->preEscaped('
		<ul class="inputList">
			<li>' . $__templater->formSelect(array(
		'name' => 'resource_category_ids[]',
		'size' => '7',
		'multiple' => 'multiple',
		'value' => $__vars['categoryIds'],
		'id' => 'js-applicableCategories',
	), $__compilerTemp1) . '</li>
			' . $__templater->formCheckBox(array(
	), array(array(
		'id' => 'js-selectAllCategories',
		'label' => 'Select all',
		'_type' => 'option',
	))) . '
		</ul>
	');
	$__finalCompiled .= '

	';
	if ($__vars['withRow']) {
		$__finalCompiled .= '
		' . $__templater->formRow('

			' . $__templater->filter($__vars['inner'], array(array('raw', array()),), true) . '
		', array(
			'rowtype' => 'input',
			'label' => 'Applicable categories',
		)) . '
	';
	} else {
		$__finalCompiled .= '
		' . $__templater->filter($__vars['inner'], array(array('raw', array()),), true) . '
	';
	}
	$__finalCompiled .= '

	';
	$__templater->inlineJs('
		$(function()
		{
			$(\'#js-selectAllCategories\').click(function(e)
			{
				$(\'#js-applicableCategories\').find(\'option:enabled:not([value=""])\').prop(\'selected\', this.checked);
			});
		});
	');
	$__finalCompiled .= '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';

	return $__finalCompiled;
});