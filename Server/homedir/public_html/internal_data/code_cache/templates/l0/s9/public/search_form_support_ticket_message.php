<?php
// FROM HASH: af20e6d71cc516c4d059cde07cf43bd0
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Search support tickets');
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

' . $__templater->formNumberBoxRow(array(
		'name' => 'c[min_reply_count]',
		'value' => $__templater->filter($__vars['input']['c']['min_reply_count'], array(array('default', array(0, )),), false),
		'min' => '0',
	), array(
		'label' => 'Minimum number of replies',
	)) . '

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
						'label' => $__templater->fn('prefix_group', array('support_ticket', $__vars['groupId'], ), false),
						'_type' => 'optgroup',
						'options' => array(),
					);
					end($__compilerTemp1); $__compilerTemp2 = key($__compilerTemp1);
					if ($__templater->isTraversable($__vars['prefixesGrouped'][$__vars['groupId']])) {
						foreach ($__vars['prefixesGrouped'][$__vars['groupId']] AS $__vars['prefixId'] => $__vars['prefix']) {
							$__compilerTemp1[$__compilerTemp2]['options'][] = array(
								'value' => $__vars['prefixId'],
								'label' => $__templater->fn('prefix_title', array('support_ticket', $__vars['prefixId'], ), true),
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
		'label' => 'All departments',
		'_type' => 'option',
	));
	if ($__templater->isTraversable($__vars['departments'])) {
		foreach ($__vars['departments'] AS $__vars['department']) {
			$__compilerTemp3[] = array(
				'value' => $__vars['department']['department_id'],
				'label' => $__templater->escape($__vars['department']['title']),
				'_type' => 'option',
			);
		}
	}
	$__finalCompiled .= $__templater->formRow('

	<ul class="inputList">
		<li>' . $__templater->formSelect(array(
		'name' => 'c[departments][]',
		'size' => '7',
		'multiple' => 'multiple',
		'value' => $__templater->filter($__vars['input']['c']['departments'], array(array('default', array(array(0, ), )),), false),
	), $__compilerTemp3) . '</li>
	</ul>
', array(
		'rowtype' => 'input',
		'label' => 'Search in departments',
	)) . '

' . $__templater->callMacro('search_form_macros', 'order', array(
		'isRelevanceSupported' => $__vars['isRelevanceSupported'],
		'options' => array('replies' => 'Most replies', ),
		'input' => $__vars['input'],
	), $__vars) . '

' . $__templater->callMacro('search_form_macros', 'grouped', array(
		'label' => 'Display results as support tickets',
		'input' => $__vars['input'],
	), $__vars);
	return $__finalCompiled;
});