<?php
// FROM HASH: 02953b26a0ef7fe8db77667dc9e24c0c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit extension');
	$__finalCompiled .= '

';
	$__templater->breadcrumbs($__templater->method($__vars['resource'], 'getBreadcrumbs', array()));
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__templater->method($__vars['category'], 'hasVersioningSupport', array()) AND ($__vars['resource']['CurrentVersion'] AND $__templater->method($__vars['resource']['CurrentVersion'], 'canEditVersionString', array()))) {
		$__compilerTemp1 .= '
				';
		$__compilerTemp2 = '';
		if ($__templater->method($__vars['resource'], 'canReleaseUpdate', array())) {
			$__compilerTemp2 .= '
						' . 'If you need to release a new version of this extension, you should <a href="' . $__templater->fn('link', array('resources/post-update', $__vars['resource'], ), true) . '">post an update</a>.' . '
					';
		}
		$__compilerTemp1 .= $__templater->formTextBoxRow(array(
			'name' => 'version_string',
			'value' => $__vars['resource']['CurrentVersion']['version_string'],
		), array(
			'label' => 'Version number',
			'explain' => $__compilerTemp2,
		)) . '
			';
	}
	$__compilerTemp3 = '';
	if ($__templater->method($__vars['resource'], 'isExternalPurchasable', array())) {
		$__compilerTemp3 .= '
				' . $__templater->formTextBoxRow(array(
			'name' => 'external_purchase_url',
			'value' => $__vars['resource']['external_purchase_url'],
		), array(
			'label' => 'External purchase URL',
		)) . '

				' . $__templater->formRow('
					' . $__templater->callMacro('xfrm_resource_edit_macros', 'purchase_inputs', array(
			'resource' => $__vars['resource'],
		), $__vars) . '
				', array(
			'rowtype' => 'input',
			'label' => 'Price',
		)) . '
			';
	} else if ($__templater->method($__vars['resource'], 'isExternalDownload', array())) {
		$__compilerTemp3 .= '
				' . $__templater->formTextBoxRow(array(
			'name' => 'external_download_url',
			'value' => $__vars['resource']['CurrentVersion']['download_url'],
		), array(
			'label' => 'External download URL',
		)) . '
			';
	}
	$__compilerTemp4 = '';
	$__compilerTemp5 = '';
	$__compilerTemp5 .= '
					' . $__templater->callMacro('custom_fields_macros', 'custom_fields_edit', array(
		'type' => 'resources',
		'set' => $__vars['resource']['custom_fields'],
		'group' => 'above_info',
		'editMode' => $__templater->method($__vars['resource'], 'getFieldEditMode', array()),
		'onlyInclude' => $__vars['category']['field_cache'],
	), $__vars) . '
				';
	if (strlen(trim($__compilerTemp5)) > 0) {
		$__compilerTemp4 .= '
				' . $__compilerTemp5 . '

				<hr class="formRowSep" />
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
	$__compilerTemp8 = '';
	if ($__templater->method($__vars['resource'], 'canSendModeratorActionAlert', array())) {
		$__compilerTemp8 .= '
				<hr class="formRowSep" />

				' . $__templater->formRow('
					' . $__templater->callMacro('helper_action', 'author_alert', array(
			'row' => false,
		), $__vars) . '
				', array(
		)) . '
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

			' . $__compilerTemp1 . '

			' . $__compilerTemp3 . '

			' . $__compilerTemp4 . '

			' . $__templater->callMacro('xfrm_resource_edit_macros', 'description', array(
		'description' => $__vars['resource']['Description']['message_'],
		'attachmentData' => $__vars['attachmentData'],
	), $__vars) . '

			' . $__compilerTemp6 . '

			<hr class="formRowSep" />

			' . $__templater->callMacro('xfrm_resource_edit_macros', 'external_url', array(
		'resource' => $__vars['resource'],
	), $__vars) . '
			' . $__templater->callMacro('xfrm_resource_edit_macros', 'alt_support_url', array(
		'resource' => $__vars['resource'],
	), $__vars) . '

			' . $__compilerTemp8 . '
		</div>

		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
		'sticky' => 'true',
	), array(
		'html' => '
				' . $__templater->button('', array(
		'class' => 'u-jsOnly',
		'data-xf-click' => 'preview-click',
		'icon' => 'preview',
	), '', array(
	)) . '
			',
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('resources/edit', $__vars['resource'], ), false),
		'ajax' => 'true',
		'class' => 'block',
		'data-preview-url' => $__templater->fn('link', array('resources/preview', $__vars['resource'], ), false),
	));
	return $__finalCompiled;
});