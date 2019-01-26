<?php
// FROM HASH: 2c957a8b8ee9aa3e432b423eaf986da9
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit version' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['version']['Product']['product_title']) . ' ' . $__templater->escape($__vars['version']['version_string']));
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__templater->isTraversable($__vars['version']['changelog'])) {
		foreach ($__vars['version']['changelog'] AS $__vars['counter'] => $__vars['changelog']) {
			$__compilerTemp1 .= '
						<li>' . $__templater->formTextBox(array(
				'name' => 'changelog[' . $__vars['counter'] . ']',
				'value' => $__vars['changelog'],
			)) . '</li>
					';
		}
	}
	$__vars['extra'] = $__templater->preEscaped('
				<div class="formRow-explain">
					' . 'Replacing the file here does not release an update or notify purchasers. Use the <a href="' . $__templater->fn('link', array('product-manager/products/add-version', $__vars['version']['Product'], ), true) . '" target="_blank" data-xf-click="overlay">Release new version</a> system for that purpose.' . '
				</div>
			');
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formTextBoxRow(array(
		'name' => 'version_string',
		'value' => $__vars['version']['version_string_'],
		'placeholder' => 'Current version ' . $__vars['version']['version_string'] . '',
	), array(
		'label' => 'Version string',
	)) . '

			' . $__templater->formEditorRow(array(
		'name' => 'version_details',
		'value' => $__vars['version']['version_details'],
		'data-min-height' => '100',
	), array(
		'label' => 'Version details',
	)) . '

			' . $__templater->formRow('
				<ul class="inputList">
					' . $__compilerTemp1 . '

					<li data-xf-init="field-adder" data-increment-format="changelog[{counter}]">
						' . $__templater->formTextBox(array(
		'name' => 'changelog[' . $__templater->fn('count', array($__vars['version']['changelog'], ), false) . ']',
	)) . '
					</li>
				</ul>
				<div class="formRow-explain">
					' . 'Add/change change log items to the above fields. New fields will be added automatically.' . '
				</div>
			', array(
		'rowtype' => 'input',
		'label' => 'Change log items',
	)) . '

			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'label' => 'Version is unsupported',
		'name' => 'is_unsupported',
		'selected' => $__vars['version']['is_unsupported'],
		'hint' => 'If checked, the product\'s current version string will not be updated but this version will still be available to download.',
		'_type' => 'option',
	)), array(
	)) . '

			<hr class="formRowSep" />

			' . $__templater->callMacro('public:xr_pm_attachment_macros', 'displayer', array(
		'label' => 'Existing file',
		'attachment' => $__vars['version']['Version'],
	), $__vars) . '

			' . '' . '
			' . $__templater->callMacro('public:xr_pm_attachment_macros', 'uploader', array(
		'buttonLabel' => 'Upload new file',
		'attachmentData' => $__vars['productAttachData'],
		'hiddenName' => 'product_attach_hash',
		'extra' => $__vars['extra'],
	), $__vars) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('product-manager/products/versions/edit', $__vars['version'], ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});