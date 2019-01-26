<?php
// FROM HASH: f6bae43398e589e5a8090a067c944bbb
return array('macros' => array('category_list' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'warnings' => '!',
		'categoryTree' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if (!$__templater->test($__vars['warnings'], 'empty', array())) {
		$__finalCompiled .= '
		<div class="block">
			<div class="block-outer">
				' . $__templater->callMacro('filter_macros', 'quick_filter', array(
			'key' => 'warning-category',
			'class' => 'block-outer-opposite',
		), $__vars) . '
			</div>
			<div class="block-container">
				<div class="block-body">
					';
		$__templater->includeCss('sv_warning_improvements_category_list.less');
		$__finalCompiled .= '

					';
		$__compilerTemp1 = '';
		$__compilerTemp2 = $__templater->method($__vars['categoryTree'], 'getFlattened', array(0, ));
		if ($__templater->isTraversable($__compilerTemp2)) {
			foreach ($__compilerTemp2 AS $__vars['treeEntry']) {
				$__compilerTemp1 .= '
							';
				$__vars['category'] = $__vars['treeEntry']['record'];
				$__compilerTemp1 .= '
							' . $__templater->dataRow(array(
				), array(array(
					'class' => 'dataList-cell--link dataList-cell--main',
					'hash' => $__vars['category']['warning_category_id'],
					'_type' => 'cell',
					'html' => '
									<a href="' . $__templater->fn('link', array('warnings/category-edit', null, array('warning_category_id' => $__vars['category']['warning_category_id'], ), ), true) . '">
										<div class="u-depth' . $__templater->escape($__vars['treeEntry']['depth']) . '">
											<div class="dataList-mainRow"><i class="warningImprovementsListingIcons warningImprovementsListingIcons--Category"></i> ' . $__templater->escape($__vars['category']['title']) . '</div>
										</div>
									</a>
								',
				),
				array(
					'class' => 'dataList-cell--action u-hideMedium',
					'label' => 'Add' . $__vars['xf']['language']['ellipsis'],
					'_type' => 'popup',
					'html' => '
									<div class="menu" data-menu="menu" aria-hidden="true">
										<div class="menu-content">
											<h3 class="menu-header">' . 'Add' . $__vars['xf']['language']['ellipsis'] . '</h3>
											<a href="' . $__templater->fn('link', array('warnings/category-add', null, array('parent_category_id' => $__vars['category']['parent_category_id'], ), ), true) . '" class="menu-linkRow">' . 'Sibling' . '</a>
											<a href="' . $__templater->fn('link', array('warnings/category-add', null, array('parent_category_id' => $__vars['category']['warning_category_id'], ), ), true) . '" class="menu-linkRow">' . 'Child' . '</a>
										</div>
									</div>
								',
				),
				array(
					'href' => (($__vars['category']['warning_category_id'] > 1) ? $__templater->fn('link', array('warnings/category-delete', null, array('warning_category_id' => $__vars['category']['warning_category_id'], ), ), false) : ''),
					'_type' => 'delete',
					'html' => '',
				))) . '
							';
				if (!$__templater->test($__vars['warnings'][$__vars['category']['warning_category_id']], 'empty', array())) {
					$__compilerTemp1 .= '
								';
					if ($__templater->isTraversable($__vars['warnings'][$__vars['category']['warning_category_id']])) {
						foreach ($__vars['warnings'][$__vars['category']['warning_category_id']] AS $__vars['warningDefinition']) {
							$__compilerTemp1 .= '
									';
							$__compilerTemp3 = array(array(
								'class' => 'dataList-cell--link dataList-cell--main',
								'hash' => 'warning_definition' . $__vars['warningDefinition']['warning_definition_id'],
								'_type' => 'cell',
								'html' => '
											<a href="' . $__templater->fn('link', array('warnings/edit', $__vars['warningDefinition'], ), true) . '">
												<div class="u-depth' . ($__vars['treeEntry']['depth'] + 1) . '">
													<div class="dataList-mainRow"><i class="warningImprovementsListingIcons warningImprovementsListingIcons--Warning"></i> ' . $__templater->escape($__vars['warningDefinition']['title']) . '</div>
												</div>
											</a>
										',
							)
,array(
								'_type' => 'cell',
								'html' => '&nbsp;',
							));
							if (!$__vars['warningDefinition']['is_custom']) {
								$__compilerTemp3[] = array(
									'href' => $__templater->fn('link', array('warnings/delete', $__vars['warningDefinition'], ), false),
									'_type' => 'delete',
									'html' => '',
								);
							} else {
								$__compilerTemp3[] = array(
									'_type' => 'cell',
									'html' => '&nbsp;',
								);
							}
							$__compilerTemp1 .= $__templater->dataRow(array(
							), $__compilerTemp3) . '
								';
						}
					}
					$__compilerTemp1 .= '
							';
				}
				$__compilerTemp1 .= '
						';
			}
		}
		$__finalCompiled .= $__templater->dataList('
						' . $__compilerTemp1 . '
					', array(
		)) . '
				</div>
			</div>
		</div>
	';
	} else {
		$__finalCompiled .= '
		<div class="blockMessage">' . 'no_warnings_have_been_defined' . '</div>
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'sortable_form' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'categoryTree' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	' . $__templater->callMacro('public:nestable_macros', 'setup', array(), $__vars) . '

	' . $__templater->form('
		<div class="block-container">
			<div class="block-body">
				<div class="nestable-container" data-xf-init="nestable">
					' . $__templater->callMacro(null, 'sortable_list', array(
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
		'action' => $__templater->fn('link', array('warnings/category-sort', ), false),
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
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<ol class="nestable-list">
		';
	if ($__templater->isTraversable($__vars['children'])) {
		foreach ($__vars['children'] AS $__vars['id'] => $__vars['child']) {
			$__finalCompiled .= '
			' . $__templater->callMacro(null, 'sortable_list_entry', array(
				'child' => $__vars['child'],
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
'sortable_list_entry' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'child' => '!',
		'children' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<li class="nestable-item" data-id="' . $__templater->escape($__vars['child']['id']) . '">
		<div class="nestable-handle" aria-label="' . $__templater->filter('Drag handle', array(array('for_attr', array()),), true) . '"><i class="fa fa-bars" aria-hidden="true"></i></div>
		<div class="nestable-content">' . $__templater->escape($__vars['child']['record']['title']) . '</div>
		';
	if (!$__templater->test($__vars['child']['children'], 'empty', array())) {
		$__finalCompiled .= '
			' . $__templater->callMacro(null, 'sortable_list', array(
			'children' => $__vars['child']['children'],
		), $__vars) . '
		';
	}
	$__finalCompiled .= '
	</li>
';
	return $__finalCompiled;
},
'parent_category_select_row' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'category' => '!',
		'categoryTree' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '

	';
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
		'name' => 'parent_category_id',
		'value' => $__vars['category']['parent_category_id'],
	), $__compilerTemp1, array(
		'label' => 'Parent category',
	)) . '
';
	return $__finalCompiled;
},
'category_delete_form' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'category' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__compilerTemp1 = '';
	if ($__templater->method($__vars['category'], 'hasChildren', array())) {
		$__compilerTemp1 .= '
					' . $__templater->formRadioRow(array(
			'name' => 'child_nodes_action',
		), array(array(
			'value' => 'move',
			'selected' => true,
			'label' => 'Move this category\'s children to its parent',
			'_type' => 'option',
		),
		array(
			'value' => 'delete',
			'label' => 'Delete this category\'s children' . ' ',
			'_type' => 'option',
		)), array(
		)) . '
				';
	}
	$__finalCompiled .= $__templater->form('

		<div class="block-container">
			<div class="block-body">
				' . $__templater->formInfoRow('
					' . 'Please confirm that you want to delete the following' . $__vars['xf']['language']['label_separator'] . '
					<strong><a href="' . $__templater->fn('link', array('warnings/category-edit', null, array('warning_category_id' => $__vars['category']['warning_category_id'], ), ), true) . '">' . $__templater->escape($__vars['category']['title']) . '</a></strong>
				', array(
		'rowtype' => 'confirm',
	)) . '

				' . $__compilerTemp1 . '
			</div>
			' . $__templater->formSubmitRow(array(
		'icon' => 'delete',
	), array(
		'rowtype' => ((!$__templater->method($__vars['category'], 'hasChildren', array())) ? 'simple' : ''),
	)) . '
		</div>
		' . $__templater->fn('redirect_input', array(null, null, true)) . '

	', array(
		'action' => $__templater->fn('link', array('warnings/category-delete', null, array('warning_category_id' => $__vars['category']['warning_category_id'], ), ), false),
		'class' => 'block',
		'ajax' => 'true',
	)) . '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '

' . '

' . '

' . '

' . '

';
	return $__finalCompiled;
});