<?php
// FROM HASH: 7960cd7ffc7d10d6a8ddf9747ff5ea82
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add resource');
	$__finalCompiled .= '

';
	$__templater->breadcrumbs($__templater->method($__vars['category'], 'getBreadcrumbs', array()));
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__templater->method($__vars['category'], 'hasVersioningSupport', array())) {
		$__compilerTemp1 .= '
				' . $__templater->formTextBoxRow(array(
			'name' => 'version_string',
			'value' => $__vars['category']['draft_resource']['version_string'],
		), array(
			'label' => 'Version number',
		)) . '
			';
	}
	$__compilerTemp2 = '';
	$__compilerTemp3 = '';
	$__compilerTemp3 .= '
					' . $__templater->callMacro('custom_fields_macros', 'custom_fields_edit', array(
		'type' => 'resources',
		'set' => $__vars['resource']['custom_fields'],
		'group' => 'above_info',
		'editMode' => $__templater->method($__vars['resource'], 'getFieldEditMode', array()),
		'onlyInclude' => $__vars['category']['field_cache'],
	), $__vars) . '
				';
	if (strlen(trim($__compilerTemp3)) > 0) {
		$__compilerTemp2 .= '
				<hr class="formRowSep" />

				' . $__compilerTemp3 . '
			';
	}
	$__compilerTemp4 = '';
	if ($__templater->method($__vars['category'], 'canEditTags', array())) {
		$__compilerTemp4 .= '
				';
		$__compilerTemp5 = '';
		if ($__vars['category']['min_tags']) {
			$__compilerTemp5 .= '
							' . 'This content must have at least ' . $__templater->escape($__vars['category']['min_tags']) . ' tag(s).' . '
						';
		}
		$__compilerTemp4 .= $__templater->formTokenInputRow(array(
			'name' => 'tags',
			'value' => $__vars['category']['draft_resource']['tags'],
			'href' => $__templater->fn('link', array('misc/tag-auto-complete', ), false),
			'min-length' => $__vars['xf']['options']['tagLength']['min'],
			'max-length' => $__vars['xf']['options']['tagLength']['max'],
			'max-tokens' => $__vars['xf']['options']['maxContentTags'],
		), array(
			'label' => 'Tags',
			'explain' => '
						' . 'Multiple tags may be separated by commas.' . '
						' . $__compilerTemp5 . '
					',
		)) . '
			';
	}
	$__compilerTemp6 = '';
	$__compilerTemp7 = '';
	$__compilerTemp7 .= '
					' . $__templater->callMacro('custom_fields_macros', 'custom_fields_edit_groups', array(
		'type' => 'resources',
		'set' => $__vars['resource']['custom_fields'],
		'groups' => array('below_info', 'extra_tab', 'new_tab', ),
		'editMode' => $__templater->method($__vars['resource'], 'getFieldEditMode', array()),
		'onlyInclude' => $__vars['category']['field_cache'],
	), $__vars) . '
				';
	if (strlen(trim($__compilerTemp7)) > 0) {
		$__compilerTemp6 .= '
				<hr class="formRowSep" />

				' . $__compilerTemp7 . '
			';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->callMacro('xfrm_resource_edit_macros', 'title', array(
		'resource' => $__vars['resource'],
		'prefixes' => $__vars['prefixes'],
	), $__vars) . '

			' . $__templater->callMacro('xfrm_resource_edit_macros', 'tag_line', array(
		'resource' => $__vars['resource'],
	), $__vars) . '

			' . $__templater->callMacro('xfrm_resource_edit_macros', 'type', array(
		'currentType' => ($__vars['category']['draft_resource']['resource_type'] ?: $__templater->method($__vars['category'], 'getDefaultSelectedType', array())),
		'resource' => $__vars['resource'],
		'category' => $__vars['category'],
		'versionAttachData' => $__vars['versionAttachData'],
	), $__vars) . '

			' . $__compilerTemp1 . '

			' . $__compilerTemp2 . '

			<hr class="formRowSep" />

			' . $__templater->callMacro('xfrm_resource_edit_macros', 'description', array(
		'description' => $__vars['category']['draft_resource']['message'],
		'attachmentData' => $__vars['attachmentData'],
	), $__vars) . '

			' . $__compilerTemp4 . '

			' . $__compilerTemp6 . '

			<hr class="formRowSep" />

			' . $__templater->callMacro('xfrm_resource_edit_macros', 'external_url', array(
		'resource' => $__vars['resource'],
	), $__vars) . '
			' . $__templater->callMacro('xfrm_resource_edit_macros', 'alt_support_url', array(
		'resource' => $__vars['resource'],
	), $__vars) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
		'sticky' => 'true',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('resources/categories/add', $__vars['category'], ), false),
		'ajax' => 'true',
		'class' => 'block',
		'draft' => $__templater->fn('link', array('resources/categories/draft', $__vars['category'], ), false),
		'data-preview-url' => $__templater->fn('link', array('resources/categories/preview', $__vars['category'], ), false),
	));
	return $__finalCompiled;
});