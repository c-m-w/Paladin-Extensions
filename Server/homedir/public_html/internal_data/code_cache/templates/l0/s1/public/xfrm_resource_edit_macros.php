<?php
// FROM HASH: 8e485c09a886fe1f4d8f235f5d2dfa1d
return array('macros' => array('title' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'resource' => '!',
		'prefixes' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	' . $__templater->formPrefixInputRow($__vars['prefixes'], array(
		'type' => 'resource',
		'prefix-value' => $__vars['resource']['prefix_id'],
		'textbox-value' => $__vars['resource']['title_'],
		'maxlength' => $__templater->fn('max_length', array($__vars['resource'], 'title', ), false),
		'placeholder' => 'Title' . $__vars['xf']['language']['ellipsis'],
	), array(
		'label' => 'Title',
	)) . '
';
	return $__finalCompiled;
},
'tag_line' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'resource' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	' . $__templater->formTextBoxRow(array(
		'name' => 'tag_line',
		'value' => $__vars['resource']['tag_line_'],
		'maxlength' => $__templater->fn('max_length', array($__vars['resource'], 'tag_line', ), false),
	), array(
		'label' => 'Tag line',
		'explain' => 'Provide a very brief, one-line description of your resource.',
	)) . '
';
	return $__finalCompiled;
},
'type' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'currentType' => '!',
		'resource' => '!',
		'category' => '!',
		'versionAttachData' => '!',
		'allowCurrentType' => false,
	), $__arguments, $__vars);
	$__finalCompiled .= '

	';
	$__compilerTemp1 = array();
	if ($__vars['category']['allow_local'] OR (($__vars['currentType'] == 'download_local') AND $__vars['allowCurrentType'])) {
		$__compilerTemp1[] = array(
			'value' => 'download_local',
			'label' => 'Uploaded files' . $__vars['xf']['language']['label_separator'],
			'_dependent' => array($__templater->callMacro('helper_attach_upload', 'upload_block', array(
			'attachmentData' => $__vars['versionAttachData'],
			'hiddenName' => 'version_attachment_hash',
		), $__vars)),
			'_type' => 'option',
		);
	}
	if ($__vars['category']['allow_external'] OR (($__vars['currentType'] == 'download_external') AND $__vars['allowCurrentType'])) {
		$__compilerTemp1[] = array(
			'value' => 'download_external',
			'label' => 'External download URL' . $__vars['xf']['language']['label_separator'],
			'_dependent' => array($__templater->formTextBox(array(
			'name' => 'external_download_url',
			'value' => $__vars['category']['draft_resource']['external_download_url'],
			'maxlength' => $__templater->fn('max_length', array('XFRM:ResourceVersion', 'download_url', ), false),
		))),
			'_type' => 'option',
		);
	}
	if ($__vars['category']['allow_commercial_external'] OR (($__vars['currentType'] == 'external_purchase') AND $__vars['allowCurrentType'])) {
		$__compilerTemp1[] = array(
			'value' => 'external_purchase',
			'label' => 'External purchase' . $__vars['xf']['language']['label_separator'],
			'_dependent' => array($__templater->callMacro('xfrm_resource_edit_macros', 'purchase_inputs', array(
			'resource' => $__vars['resource'],
			'withUrl' => true,
		), $__vars)),
			'_type' => 'option',
		);
	}
	if ($__vars['category']['allow_fileless'] OR (($__vars['currentType'] == 'fileless') AND $__vars['allowCurrentType'])) {
		$__compilerTemp1[] = array(
			'value' => 'fileless',
			'label' => 'Does not have a file',
			'hint' => 'The description will contain the contents of this resource.',
			'_type' => 'option',
		);
	}
	$__finalCompiled .= $__templater->formRadioRow(array(
		'name' => 'resource_type',
		'value' => $__vars['currentType'],
		'data-xf-init' => 'attachment-manager',
	), $__compilerTemp1, array(
		'label' => 'Type',
	)) . '
';
	return $__finalCompiled;
},
'purchase_inputs' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'resource' => '!',
		'withUrl' => false,
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="inputGroup">
		';
	if ($__vars['withUrl']) {
		$__finalCompiled .= '
			' . $__templater->formTextBox(array(
			'name' => 'external_purchase_url',
			'value' => $__vars['resource']['external_purchase_url'],
			'placeholder' => 'External purchase URL',
		)) . '
			<span class="inputGroup-splitter"></span>
		';
	}
	$__finalCompiled .= '
		' . $__templater->formTextBox(array(
		'name' => 'price',
		'value' => ($__vars['resource']['price'] ?: ''),
		'placeholder' => 'Price',
		'style' => 'width: 120px',
	)) . '
		<span class="inputGroup-splitter"></span>
		';
	$__compilerTemp1 = array();
	$__compilerTemp2 = $__templater->method($__templater->method($__vars['xf']['app']['em'], 'getRepository', array('XFRM:ResourceItem', )), 'getAvailableCurrencies', array($__vars['resource'], ));
	if ($__templater->isTraversable($__compilerTemp2)) {
		foreach ($__compilerTemp2 AS $__vars['currency']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['currency']['code'],
				'label' => $__templater->escape($__vars['currency']['code']),
				'_type' => 'option',
			);
		}
	}
	$__finalCompiled .= $__templater->formSelect(array(
		'name' => 'currency',
		'value' => $__templater->filter($__vars['resource']['currency'], array(array('to_upper', array()),), false),
		'style' => 'width: 110px',
	), $__compilerTemp1) . '
	</div>
';
	return $__finalCompiled;
},
'description' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'description' => '',
		'attachmentData' => array(),
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div data-xf-init="attachment-manager">
		' . $__templater->formEditorRow(array(
		'name' => 'description',
		'value' => $__vars['description'],
		'data-min-height' => '200',
		'attachments' => $__vars['attachmentData']['attachments'],
	), array(
		'label' => 'Description',
	)) . '

		';
	$__compilerTemp1 = '';
	if ($__vars['attachmentData']) {
		$__compilerTemp1 .= '
				' . $__templater->callMacro('helper_attach_upload', 'upload_block', array(
			'attachmentData' => $__vars['attachmentData'],
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
	</div>
';
	return $__finalCompiled;
},
'external_url' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'resource' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	' . $__templater->formTextBoxRow(array(
		'name' => 'external_url',
		'value' => $__vars['resource']['external_url_'],
		'maxlength' => $__templater->fn('max_length', array($__vars['resource'], 'external_url', ), false),
	), array(
		'label' => 'Additional information URL',
		'explain' => 'If you have your own web site with more information, enter its URL here.',
	)) . '
';
	return $__finalCompiled;
},
'alt_support_url' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'resource' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__vars['xf']['options']['xfrmAllowSupportUrl']) {
		$__finalCompiled .= '
		' . $__templater->formTextBoxRow(array(
			'name' => 'alt_support_url',
			'value' => $__vars['resource']['alt_support_url_'],
			'maxlength' => $__templater->fn('max_length', array($__vars['resource'], 'alt_support_url', ), false),
		), array(
			'label' => 'Alternative support URL',
			'explain' => 'If you have a specific location where you will be providing support or answering questions, please enter the URL here.',
		)) . '
	';
	}
	$__finalCompiled .= '
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

' . '

';
	return $__finalCompiled;
});