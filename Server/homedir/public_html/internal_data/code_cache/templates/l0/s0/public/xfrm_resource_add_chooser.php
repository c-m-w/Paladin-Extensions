<?php
// FROM HASH: d7577f098a1052e27b365c8d455d3788
return array('macros' => array('category_list' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'children' => '!',
		'extras' => '!',
		'depth' => '0',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__templater->isTraversable($__vars['children'])) {
		foreach ($__vars['children'] AS $__vars['id'] => $__vars['child']) {
			$__finalCompiled .= '
		' . $__templater->callMacro(null, 'category_list_entry', array(
				'category' => $__vars['child']['record'],
				'extras' => $__vars['extras'][$__vars['id']],
				'children' => $__vars['child']['children'],
				'childExtras' => $__vars['extras'],
				'depth' => $__vars['depth'],
			), $__vars) . '
	';
		}
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'category_list_entry' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'category' => '!',
		'extras' => '!',
		'children' => '!',
		'childExtras' => '!',
		'depth' => '0',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__templater->method($__vars['category'], 'canAddResource', array())) {
		$__finalCompiled .= '
		' . $__templater->callMacro(null, (($__vars['depth'] == 0) ? 'category_list_entry_add_level_0' : 'category_list_entry_add'), array(
			'category' => $__vars['category'],
			'extras' => $__vars['extras'],
			'children' => $__vars['children'],
			'childExtras' => $__vars['childExtras'],
			'depth' => $__vars['depth'],
		), $__vars) . '
	';
	} else {
		$__finalCompiled .= '
		' . $__templater->callMacro(null, (($__vars['depth'] == 0) ? 'category_list_entry_no_add_level_0' : 'category_list_entry_no_add'), array(
			'category' => $__vars['category'],
			'extras' => $__vars['extras'],
			'children' => $__vars['children'],
			'childExtras' => $__vars['childExtras'],
			'depth' => $__vars['depth'],
		), $__vars) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'category_list_entry_no_add_level_0' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'category' => '!',
		'extras' => '!',
		'children' => '!',
		'childExtras' => '!',
		'depth' => '0',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="block block--treeEntryChooser">
		<div class="block-container">
			<h2 class="block-header">
				' . $__templater->escape($__vars['category']['title']) . '
				';
	if ($__vars['category']['description']) {
		$__finalCompiled .= '
					<span class="block-desc">
						' . $__templater->filter($__vars['category']['description'], array(array('strip_tags', array()),), true) . '
					</span>
				';
	}
	$__finalCompiled .= '
			</h2>
			<div class="block-body">
				' . $__templater->callMacro(null, 'category_list', array(
		'children' => $__vars['children'],
		'extras' => $__vars['childExtras'],
		'depth' => ($__vars['depth'] + 1),
	), $__vars) . '
			</div>
		</div>
	</div>
';
	return $__finalCompiled;
},
'category_list_entry_add_level_0' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'category' => '!',
		'extras' => '!',
		'children' => '!',
		'childExtras' => '!',
		'depth' => '0',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="block block--treeEntryChooser">
		<div class="block-container">
			' . $__templater->callMacro(null, 'category_list_entry_add', array(
		'category' => $__vars['category'],
		'extras' => $__vars['extras'],
		'children' => $__vars['children'],
		'childExtras' => $__vars['childExtras'],
		'depth' => $__vars['depth'],
	), $__vars) . '
		</div>
	</div>
';
	return $__finalCompiled;
},
'category_list_entry_add' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'category' => '!',
		'extras' => '!',
		'children' => '!',
		'childExtras' => '!',
		'depth' => '0',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="block-row block-row--clickable block-row--separated fauxBlockLink">
		<div class="contentRow contentRow--alignMiddle' . (($__vars['depth'] > 1) ? (' u-depth' . ($__vars['depth'] - 1)) : '') . '">
			<div class="contentRow-main">
				<h2 class="contentRow-title">
					<a href="' . $__templater->fn('link', array('resources/categories/add', $__vars['category'], ), true) . '" class="fauxBlockLink-blockLink">
						' . $__templater->escape($__vars['category']['title']) . '
					</a>
				</h2>
				';
	if ($__vars['category']['description']) {
		$__finalCompiled .= '
					<div class="contentRow-minor contentRow-minor--singleLine">
						' . $__templater->filter($__vars['category']['description'], array(array('strip_tags', array()),), true) . '
					</div>
				';
	}
	$__finalCompiled .= '
			</div>
			<div class="contentRow-suffix">
				<dl class="pairs pairs--rows pairs--rows--centered">
					<dt>' . 'Resources' . '</dt>
					<dd>' . $__templater->filter($__vars['extras']['resource_count'], array(array('number_short', array()),), true) . '</dd>
				</dl>
			</div>
		</div>
	</div>
	' . $__templater->callMacro(null, 'category_list', array(
		'children' => $__vars['children'],
		'extras' => $__vars['childExtras'],
		'depth' => ($__vars['depth'] + 1),
	), $__vars) . '
';
	return $__finalCompiled;
},
'category_list_entry_no_add' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'category' => '!',
		'extras' => '!',
		'children' => '!',
		'childExtras' => '!',
		'depth' => '0',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="block-row block-row--separated">
		<div class="contentRow contentRow--alignMiddle' . (($__vars['depth'] > 1) ? (' u-depth' . ($__vars['depth'] - 1)) : '') . ' is-disabled">
			<div class="contentRow-main">
				<h2 class="contentRow-title">
					' . $__templater->escape($__vars['category']['title']) . '
				</h2>
				<div class="contentRow-minor contentRow-minor--singleLine">
					' . 'You may not add resources to this category.' . '
				</div>
			</div>
			<div class="contentRow-suffix">
				<dl class="pairs pairs--rows pairs--rows--centered">
					<dt>' . 'Resources' . '</dt>
					<dd>' . $__templater->filter($__vars['extras']['resource_count'], array(array('number_short', array()),), true) . '</dd>
				</dl>
			</div>
		</div>
	</div>
	' . $__templater->callMacro(null, 'category_list', array(
		'children' => $__vars['children'],
		'extras' => $__vars['childExtras'],
		'depth' => ($__vars['depth'] + 1),
	), $__vars) . '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Post resource in' . $__vars['xf']['language']['ellipsis']);
	$__finalCompiled .= '

' . $__templater->callMacro(null, 'category_list', array(
		'children' => $__vars['categoryTree'],
		'extras' => $__vars['categoryExtras'],
	), $__vars) . '

' . '

' . '

' . '

' . '

' . '

';
	return $__finalCompiled;
});