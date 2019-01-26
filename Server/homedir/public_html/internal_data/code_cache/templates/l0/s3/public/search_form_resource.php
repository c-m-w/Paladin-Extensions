<?php
// FROM HASH: fb70c3b902fd1d9461a6de9f41c69ff3
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Search resources');
	$__finalCompiled .= '

' . $__templater->callMacro('search_form_macros', 'keywords', array(
		'input' => $__vars['input'],
	), $__vars) . '
' . $__templater->callMacro('search_form_macros', 'user', array(
		'input' => $__vars['input'],
	), $__vars) . '
' . $__templater->callMacro('search_form_macros', 'date', array(
		'input' => $__vars['input'],
	), $__vars) . '

';
	if (!$__templater->test($__vars['prefixesGrouped'], 'empty', array())) {
		$__finalCompiled .= '
	';
		$__compilerTemp1 = array(array(
			'value' => '',
			'label' => $__vars['xf']['language']['parenthesis_open'] . 'Any' . $__vars['xf']['language']['parenthesis_close'],
			'_type' => 'option',
		));
		if ($__templater->isTraversable($__vars['prefixGroups'])) {
			foreach ($__vars['prefixGroups'] AS $__vars['groupId'] => $__vars['prefixGroup']) {
				if (($__templater->fn('count', array($__vars['prefixesGrouped'][$__vars['groupId']], ), false) > 0)) {
					$__compilerTemp1[] = array(
						'label' => $__templater->fn('prefix_group', array('resource', $__vars['groupId'], ), false),
						'_type' => 'optgroup',
						'options' => array(),
					);
					end($__compilerTemp1); $__compilerTemp2 = key($__compilerTemp1);
					if ($__templater->isTraversable($__vars['prefixesGrouped'][$__vars['groupId']])) {
						foreach ($__vars['prefixesGrouped'][$__vars['groupId']] AS $__vars['prefixId'] => $__vars['prefix']) {
							$__compilerTemp1[$__compilerTemp2]['options'][] = array(
								'value' => $__vars['prefixId'],
								'label' => $__templater->fn('prefix_title', array('resource', $__vars['prefixId'], ), true),
								'_type' => 'option',
							);
						}
					}
				}
			}
		}
		$__finalCompiled .= $__templater->formSelectRow(array(
			'name' => 'c[prefixes][]',
			'size' => '7',
			'multiple' => 'true',
			'value' => $__templater->filter($__vars['input']['c']['prefixes'], array(array('default', array(array(0, ), )),), false),
		), $__compilerTemp1, array(
			'label' => 'Prefixes',
		)) . '
';
	}
	$__finalCompiled .= '

';
	$__compilerTemp3 = array(array(
		'value' => '',
		'label' => 'All categories',
		'_type' => 'option',
	));
	$__compilerTemp4 = $__templater->method($__vars['categoryTree'], 'getFlattened', array(0, ));
	if ($__templater->isTraversable($__compilerTemp4)) {
		foreach ($__compilerTemp4 AS $__vars['treeEntry']) {
			$__compilerTemp3[] = array(
				'value' => $__vars['treeEntry']['record']['resource_category_id'],
				'label' => $__templater->filter($__templater->fn('repeat', array('&nbsp;&nbsp;', $__vars['treeEntry']['depth'], ), false), array(array('raw', array()),), true) . ' ' . $__templater->escape($__vars['treeEntry']['record']['title']),
				'_type' => 'option',
			);
		}
	}
	$__finalCompiled .= $__templater->formRow('

	<ul class="inputList">
		<li>' . $__templater->formSelect(array(
		'name' => 'c[categories][]',
		'size' => '7',
		'multiple' => 'multiple',
		'value' => $__templater->filter($__vars['input']['c']['categories'], array(array('default', array(array(0, ), )),), false),
	), $__compilerTemp3) . '</li>
		<li>' . $__templater->formCheckBox(array(
		'standalone' => 'true',
	), array(array(
		'name' => 'c[child_categories]',
		'selected' => ((!$__vars['input']['c']) OR $__vars['input']['c']['child_categories']),
		'label' => 'Search child categories as well',
		'_type' => 'option',
	))) . '</li>
	</ul>
', array(
		'rowtype' => 'input',
		'label' => 'Search in categories',
	)) . '

' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'c[include_updates]',
		'label' => 'Include resource updates',
		'_type' => 'option',
	)), array(
	)) . '

' . $__templater->callMacro('search_form_macros', 'order', array(
		'isRelevanceSupported' => $__vars['isRelevanceSupported'],
		'input' => $__vars['input'],
	), $__vars);
	return $__finalCompiled;
});