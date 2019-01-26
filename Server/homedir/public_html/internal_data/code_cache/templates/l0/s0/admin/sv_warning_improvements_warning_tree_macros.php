<?php
// FROM HASH: 1455db47b7ec68350089914734545b08
return array('macros' => array('sortable_form' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'categoryTree' => '!',
		'warnings' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__templater->includeCss('sv_warning_improvements_nestable.less');
	$__finalCompiled .= '

	' . $__templater->callMacro('public:nestable_macros', 'setup', array(), $__vars) . '

	' . $__templater->form('
		<div class="block-container">
			<div class="block-body">
				' . $__templater->callMacro(null, 'sortable_list', array(
		'children' => $__vars['categoryTree'],
		'warnings' => $__vars['warnings'],
	), $__vars) . '
			</div>
			' . $__templater->formSubmitRow(array(
		'icon' => 'save',
	), array(
		'rowtype' => 'simple',
	)) . '
		</div>
	', array(
		'action' => $__templater->fn('link', array('warnings/sort', ), false),
		'class' => 'block',
		'ajax' => 'true',
	)) . '
';
	return $__finalCompiled;
},
'sortable_list' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'children' => '!',
		'warnings' => null,
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="category-container">
		<ol class="category-list">
			';
	if ($__templater->isTraversable($__vars['children'])) {
		foreach ($__vars['children'] AS $__vars['id'] => $__vars['child']) {
			$__finalCompiled .= '
				' . $__templater->callMacro(null, 'sortable_list_entry', array(
				'child' => $__vars['child'],
				'children' => $__vars['child']['children'],
				'warnings' => $__vars['warnings'],
			), $__vars) . '
			';
		}
	}
	$__finalCompiled .= '
		</ol>
	</div>
';
	return $__finalCompiled;
},
'sortable_warning_list' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'warnings' => '!',
		'category' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="nestable-container" data-xf-init="nestable" data-parent-id="' . $__templater->escape($__vars['category']['warning_category_id']) . '" data-value-target="#js-category-' . $__templater->escape($__vars['category']['warning_category_id']) . '-Data">
		';
	$__compilerTemp1 = '';
	$__compilerTemp1 .= '
			';
	if ($__templater->isTraversable($__vars['warnings'])) {
		foreach ($__vars['warnings'] AS $__vars['warning']) {
			$__compilerTemp1 .= '
				<li class="nestable-item" data-id="' . $__templater->escape($__vars['warning']['warning_definition_id']) . '">
					<div class="nestable-handle" aria-label="' . $__templater->filter('Drag handle', array(array('for_attr', array()),), true) . '"><i class="fa fa-bars" aria-hidden="true"></i></div>
					<div class="nestable-content">' . $__templater->escape($__vars['warning']['MasterTitle']['phrase_text']) . '</div>
				</li>
			';
		}
	}
	$__compilerTemp1 .= '
			';
	if (strlen(trim($__compilerTemp1)) > 0) {
		$__finalCompiled .= '
		<ol class="nestable-list">
			' . $__compilerTemp1 . '
		</ol>
			';
	}
	$__finalCompiled .= '
		' . $__templater->formHiddenVal('category-' . $__vars['category']['warning_category_id'], '', array(
		'id' => 'js-category-' . $__vars['category']['warning_category_id'] . '-Data',
	)) . '
	</div>
';
	return $__finalCompiled;
},
'sortable_list_entry' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'child' => '!',
		'children' => '!',
		'warnings' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<li class="category-item" data-id="' . $__templater->escape($__vars['child']['id']) . '">
		<div class="category-content block-minorHeader">' . $__templater->escape($__vars['child']['record']['title']) . '</div>
		' . $__templater->callMacro(null, 'sortable_warning_list', array(
		'warnings' => $__vars['warnings'][$__vars['child']['id']],
		'category' => $__vars['child']['record'],
	), $__vars) . '

		';
	if (!$__templater->test($__vars['child']['children'], 'empty', array())) {
		$__finalCompiled .= '
			' . $__templater->callMacro(null, 'sortable_list', array(
			'children' => $__vars['child']['children'],
			'warnings' => $__vars['warnings'],
		), $__vars) . '
		';
	}
	$__finalCompiled .= '
	</li>
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '

' . '

' . '

';
	return $__finalCompiled;
});