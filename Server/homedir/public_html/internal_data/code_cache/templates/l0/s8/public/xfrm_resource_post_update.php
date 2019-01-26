<?php
// FROM HASH: acf6aad1a77eed146e3b1516c646c5ea
return array('macros' => array('new_version' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, true);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__templater->method($__vars['resource'], 'isVersioned', array())) {
		$__finalCompiled .= '
		' . $__templater->formTextBoxRow(array(
			'name' => 'version_string',
			'maxlength' => $__templater->fn('max_length', array('XFRM:ResourceVersion', 'version_string', ), false),
		), array(
			'label' => 'New version number',
		)) . '
	';
	}
	$__finalCompiled .= '

	';
	if ($__templater->method($__vars['resource'], 'isDownloadable', array())) {
		$__finalCompiled .= '
		';
		$__compilerTemp1 = array();
		if ($__vars['resource']['Category']['allow_local'] OR ($__templater->method($__vars['resource'], 'getResourceTypeDetailed', array()) == 'download_local')) {
			$__compilerTemp1[] = array(
				'value' => 'local',
				'label' => 'Uploaded files' . $__vars['xf']['language']['label_separator'],
				'_dependent' => array($__templater->callMacro('helper_attach_upload', 'upload_block', array(
				'attachmentData' => $__vars['versionAttachData'],
				'hiddenName' => 'version_attachment_hash',
			), $__vars)),
				'_type' => 'option',
			);
		}
		if ($__vars['resource']['Category']['allow_external'] OR ($__templater->method($__vars['resource'], 'getResourceTypeDetailed', array()) == 'download_external')) {
			$__compilerTemp1[] = array(
				'value' => 'external',
				'label' => 'External download URL' . $__vars['xf']['language']['label_separator'],
				'_dependent' => array($__templater->formTextBox(array(
				'name' => 'external_download_url',
				'value' => ($__templater->method($__vars['resource'], 'isExternalDownload', array()) ? $__vars['resource']['CurrentVersion']['download_url'] : ''),
				'type' => 'url',
				'maxlength' => $__templater->fn('max_length', array('XFRM:ResourceVersion', 'download_url', ), false),
			))),
				'_type' => 'option',
			);
		}
		$__finalCompiled .= $__templater->formRadioRow(array(
			'name' => 'version_type',
			'value' => ($__templater->method($__vars['resource'], 'isExternalDownload', array()) ? 'external' : 'local'),
		), $__compilerTemp1, array(
			'label' => 'New content',
		)) . '
	';
	}
	$__finalCompiled .= '

	';
	if ($__templater->method($__vars['resource'], 'isExternalPurchasable', array())) {
		$__finalCompiled .= '
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
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'new_update' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, true);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(), $__arguments, $__vars);
	$__finalCompiled .= '
	' . $__templater->formTextBoxRow(array(
		'name' => 'update_title',
		'value' => $__vars['resource']['draft_update']['update_title'],
		'maxlength' => $__templater->fn('max_length', array($__vars['resource'], 'title', ), false),
	), array(
		'label' => 'Update title',
	)) . '

	' . $__templater->formEditorRow(array(
		'name' => 'update_message',
		'data-min-height' => '200',
		'value' => $__vars['resource']['draft_update']['message'],
		'attachments' => $__vars['updateAttachData']['attachments'],
	), array(
		'label' => 'Update message',
	)) . '

	';
	$__compilerTemp1 = '';
	if ($__vars['updateAttachData']) {
		$__compilerTemp1 .= '
			' . $__templater->callMacro('helper_attach_upload', 'upload_block', array(
			'attachmentData' => $__vars['updateAttachData'],
		), $__vars) . '
		';
	}
	$__finalCompiled .= $__templater->formRow('
		' . $__compilerTemp1 . '
		' . $__templater->button('', array(
		'class' => 'button--link u-jsOnly',
		'data-xf-click' => 'preview-click',
		'icon' => 'preview',
	), '', array(
	)) . '
	', array(
	)) . '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Update resource');
	$__finalCompiled .= '

';
	$__templater->breadcrumbs($__templater->method($__vars['resource'], 'getBreadcrumbs', array()));
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__templater->method($__vars['resource'], 'hasUpdatableVersionData', array())) {
		$__compilerTemp1 .= '
			<h2 class="block-formSectionHeader"><span class="block-formSectionHeader-aligner">' . ($__templater->method($__vars['resource'], 'isVersioned', array()) ? 'Release a new version' : 'Replace download') . '</span></h2>
			<div class="block-body" data-xf-init="' . ($__templater->method($__vars['resource'], 'isDownloadable', array()) ? 'attachment-manager' : '') . '">
				' . $__templater->formCheckBoxRow(array(
		), array(array(
			'name' => 'new_version',
			'value' => '1',
			'data-xf-init' => 'disabler',
			'data-container' => '#js-ResourceNewVersion',
			'data-hide' => 'true',
			'label' => '
						' . ($__templater->method($__vars['resource'], 'isVersioned', array()) ? 'Release a new version' : 'Replace download') . '
					',
			'_type' => 'option',
		)), array(
		)) . '

				<div id="js-ResourceNewVersion">
					' . $__templater->callMacro(null, 'new_version', array(), $__vars) . '
				</div>
			</div>

			<h2 class="block-formSectionHeader"><span class="block-formSectionHeader-aligner">' . 'Post an update' . '</span></h2>
			<div class="block-body" data-xf-init="attachment-manager">
				' . $__templater->formCheckBoxRow(array(
		), array(array(
			'name' => 'new_update',
			'value' => '1',
			'selected' => true,
			'data-xf-init' => 'disabler',
			'data-container' => '#js-ResourceNewUpdate',
			'data-hide' => 'true',
			'label' => '
						' . 'Post an update' . '
					',
			'_type' => 'option',
		)), array(
		)) . '

				<div id="js-ResourceNewUpdate">
					' . $__templater->callMacro(null, 'new_update', array(), $__vars) . '
				</div>

			</div>
		';
	} else {
		$__compilerTemp1 .= '
			<div class="block-body" data-xf-init="attachment-manager">
				' . $__templater->callMacro(null, 'new_update', array(), $__vars) . '
				' . $__templater->formHiddenVal('new_update', '1', array(
		)) . '
			</div>
		';
	}
	$__finalCompiled .= $__templater->form('

	<div class="block-container">
		' . $__compilerTemp1 . '

		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
		'sticky' => 'true',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('resources/post-update', $__vars['resource'], ), false),
		'ajax' => 'true',
		'class' => 'block',
		'draft' => $__templater->fn('link', array('resources/post-update/draft', $__vars['resource'], ), false),
		'data-preview-url' => $__templater->fn('link', array('resources/post-update/preview', $__vars['resource'], ), false),
	)) . '

' . '

';
	return $__finalCompiled;
});