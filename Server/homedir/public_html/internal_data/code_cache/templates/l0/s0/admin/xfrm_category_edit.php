<?php
// FROM HASH: 9eb1f8333511ad54c5d7374d0f6134ee
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['category'], 'isInsert', array())) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add category');
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit category' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['category']['title']));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['category'], 'isUpdate', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('', array(
			'href' => $__templater->fn('link', array('resource-manager/categories/delete', $__vars['category'], ), false),
			'icon' => 'delete',
			'overlay' => 'true',
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

';
	$__compilerTemp1 = array(array(
		'value' => '0',
		'label' => $__vars['xf']['language']['parenthesis_open'] . 'None' . $__vars['xf']['language']['parenthesis_close'],
		'_type' => 'option',
	));
	if ($__templater->isTraversable($__vars['forumOptions'])) {
		foreach ($__vars['forumOptions'] AS $__vars['forum']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['forum']['value'],
				'disabled' => $__vars['forum']['disabled'],
				'label' => $__templater->escape($__vars['forum']['label']),
				'_type' => 'option',
			);
		}
	}
	$__templater->includeJs(array(
		'src' => 'xf/prefix_menu.js',
		'min' => '1',
	));
	$__compilerTemp2 = '';
	if (!$__templater->test($__vars['availableFields'], 'empty', array())) {
		$__compilerTemp2 .= '
				<hr class="formRowSep" />

				';
		$__compilerTemp3 = $__templater->mergeChoiceOptions(array(), $__vars['availableFields']);
		$__compilerTemp2 .= $__templater->formCheckBoxRow(array(
			'name' => 'available_fields',
			'value' => $__vars['category']['field_cache'],
			'listclass' => 'field listColumns',
		), $__compilerTemp3, array(
			'label' => 'Available fields',
			'hint' => '
						' . $__templater->formCheckBox(array(
			'standalone' => 'true',
		), array(array(
			'check-all' => '.field.listColumns',
			'label' => 'Select all',
			'_type' => 'option',
		))) . '
					',
		)) . '
			';
	} else {
		$__compilerTemp2 .= '
				<hr class="formRowSep" />

				' . $__templater->formRow('
					' . $__templater->filter('None', array(array('parens', array()),), true) . ' <a href="' . $__templater->fn('link', array('resource-manager/fields', ), true) . '" target="_blank">' . 'Add field' . '</a>
				', array(
			'label' => 'Available fields',
		)) . '
			';
	}
	$__compilerTemp4 = '';
	if (!$__templater->test($__vars['availablePrefixes'], 'empty', array())) {
		$__compilerTemp4 .= '
				<hr class="formRowSep" />

				';
		$__compilerTemp5 = $__templater->mergeChoiceOptions(array(), $__vars['availablePrefixes']);
		$__compilerTemp4 .= $__templater->formCheckBoxRow(array(
			'name' => 'available_prefixes',
			'value' => $__vars['category']['prefix_cache'],
			'listclass' => 'prefix listColumns',
		), $__compilerTemp5, array(
			'label' => 'Available prefixes',
			'hint' => '
						' . $__templater->formCheckBox(array(
			'standalone' => 'true',
		), array(array(
			'check-all' => '.prefix.listColumns',
			'label' => 'Select all',
			'_type' => 'option',
		))) . '
					',
		)) . '

				' . $__templater->formCheckBoxRow(array(
			'name' => 'require_prefix',
			'value' => $__vars['category']['require_prefix'],
		), array(array(
			'value' => '1',
			'label' => 'Require users to select a prefix',
			'hint' => 'If selected, users will be required to select a prefix when creating or editing a resource. This will not be enforced for moderators.',
			'_type' => 'option',
		)), array(
		)) . '

			';
	} else {
		$__compilerTemp4 .= '

				<hr class="formRowSep" />

				' . $__templater->formRow('
					' . $__templater->filter('None', array(array('parens', array()),), true) . ' <a href="' . $__templater->fn('link', array('resource-manager/prefixes', ), true) . '" target="_blank">' . 'Add prefix' . '</a>
				', array(
			'label' => 'Available prefixes',
		)) . '

			';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formTextBoxRow(array(
		'name' => 'title',
		'value' => $__vars['category']['title'],
	), array(
		'label' => 'Title',
	)) . '

			' . $__templater->formTextAreaRow(array(
		'name' => 'description',
		'value' => $__vars['category']['description'],
		'autosize' => 'true',
	), array(
		'label' => 'Description',
		'explain' => 'You may use HTML',
	)) . '

			' . $__templater->callMacro('category_tree_macros', 'parent_category_select_row', array(
		'category' => $__vars['category'],
		'categoryTree' => $__vars['categoryTree'],
		'idKey' => 'resource_category_id',
	), $__vars) . '

			' . $__templater->callMacro('display_order_macros', 'row', array(
		'value' => $__vars['category']['display_order'],
	), $__vars) . '

			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'allow_local',
		'selected' => $__vars['category']['allow_local'],
		'label' => 'Uploaded file',
		'_type' => 'option',
	),
	array(
		'name' => 'allow_external',
		'selected' => $__vars['category']['allow_external'],
		'label' => 'External download',
		'_type' => 'option',
	),
	array(
		'name' => 'allow_commercial_external',
		'selected' => $__vars['category']['allow_commercial_external'],
		'label' => 'External purchase',
		'_type' => 'option',
	),
	array(
		'name' => 'allow_fileless',
		'selected' => $__vars['category']['allow_fileless'],
		'label' => 'Fileless',
		'_type' => 'option',
	)), array(
		'label' => 'Allowed resource types',
		'explain' => 'If no resource types are selected, this category will be used to maintain the category hierarchy only.',
	)) . '

			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'enable_versioning',
		'selected' => $__vars['category']['enable_versioning'],
		'label' => 'Enable versioning',
		'hint' => 'If enabled, users will be prompted to enter a version number and a history of previous versions will be displayed.',
		'_type' => 'option',
	)), array(
	)) . '

			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'always_moderate_create',
		'selected' => $__vars['category']['always_moderate_create'],
		'label' => '
					' . 'Always moderate resources posted in this category' . '
				',
		'_type' => 'option',
	),
	array(
		'name' => 'always_moderate_update',
		'selected' => $__vars['category']['always_moderate_update'],
		'label' => '
					' . 'Always moderate resource updates posted in this category' . '
				',
		'_type' => 'option',
	)), array(
	)) . '

			' . $__templater->formTextBoxRow(array(
		'name' => 'min_tags',
		'value' => $__vars['category']['min_tags'],
		'type' => 'number',
		'min' => '0',
		'max' => '100',
	), array(
		'label' => 'Minimum required tags',
		'explain' => 'This will require users to provide at least this many tags when creating a resource.',
	)) . '

			' . $__templater->formSelectRow(array(
		'name' => 'thread_node_id',
		'value' => $__vars['category']['thread_node_id'],
		'id' => 'js-rmThreadNodeList',
	), $__compilerTemp1, array(
		'label' => 'Automatically create thread in forum',
		'explain' => 'If selected, whenever a resource in this category is created, a thread will be posted in this forum.',
	)) . '

			' . $__templater->formRow('
				' . '' . '
				' . $__templater->callMacro('public:prefix_macros', 'select', array(
		'type' => 'thread',
		'prefixes' => $__vars['threadPrefixes'],
		'selected' => $__vars['category']['thread_prefix_id'],
		'name' => 'thread_prefix_id',
		'href' => $__templater->fn('link', array('forums/prefixes', ), false),
		'listenTo' => '#js-rmThreadNodeList',
	), $__vars) . '
			', array(
		'label' => 'Automatically created thread prefix',
		'rowtype' => 'input',
	)) . '

			' . $__compilerTemp2 . '

			' . $__compilerTemp4 . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
		'sticky' => 'true',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('resource-manager/categories/save', $__vars['category'], ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});