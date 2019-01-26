<?php
// FROM HASH: 7e8b1b20ac494c2374d00f63fa3bed2a
return array('macros' => array('category_list' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'children' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<ol class="nestable-list">
		';
	if ($__templater->isTraversable($__vars['children'])) {
		foreach ($__vars['children'] AS $__vars['id'] => $__vars['child']) {
			$__finalCompiled .= '
			' . $__templater->callMacro(null, 'category_list_entry', array(
				'category' => $__vars['child'],
				'children' => $__vars['child']['children'],
			), $__vars) . '
		';
		}
	}
	$__finalCompiled .= '
	</ol>
';
	return $__finalCompiled;
},
'category_list_entry' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'category' => '!',
		'children' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<li class="nestable-item" data-id="' . $__templater->escape($__vars['category']['id']) . '">
		<div class="nestable-handle"><i class="fa fa-bars" aria-hidden="true"></i></div>
		<div class="nestable-content">' . $__templater->escape($__vars['category']['record']['title']) . '</div>
		';
	if (!$__templater->test($__vars['category']['children'], 'empty', array())) {
		$__finalCompiled .= '
			' . $__templater->callMacro(null, 'category_list', array(
			'children' => $__vars['category']['children'],
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
	$__templater->includeJs(array(
		'src' => 'vendor/nestable/jquery.nestable.min.js',
	));
	$__finalCompiled .= '
';
	$__templater->includeJs(array(
		'src' => 'xf/nestable.js',
		'min' => '1',
	));
	$__finalCompiled .= '
';
	$__templater->includeCss('public:nestable.less');
	$__finalCompiled .= '

';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Sort categories');
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">
		<div class="block-body">
			<div class="nestable-container" data-xf-init="nestable">
				' . $__templater->callMacro(null, 'category_list', array(
		'children' => $__vars['categoryTree'],
	), $__vars) . '
				' . $__templater->formHiddenVal('categories', '', array(
	)) . '
			</div>
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
	), array(
		'rowtype' => 'simple',
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('product-manager/categories/sort', ), false),
		'class' => 'block',
		'ajax' => 'true',
	)) . '

' . '

';
	return $__finalCompiled;
});