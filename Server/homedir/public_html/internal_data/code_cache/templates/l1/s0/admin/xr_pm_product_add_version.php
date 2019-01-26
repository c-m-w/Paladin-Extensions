<?php
// FROM HASH: 55722aaf18a9722873792fc535d003bb
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add version' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['product']['product_title']));
	$__finalCompiled .= '

';
	$__compilerTemp1 = array();
	if ($__templater->isTraversable($__vars['forums'])) {
		foreach ($__vars['forums'] AS $__vars['forum']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['forum']['value'],
				'disabled' => $__vars['forum']['disabled'],
				'label' => $__templater->escape($__vars['forum']['label']),
				'_type' => 'option',
			);
		}
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-blody">
			' . $__templater->formTextBoxRow(array(
		'name' => 'version_string',
		'value' => '',
		'placeholder' => 'Current version ' . $__vars['product']['Version']['version_string'] . '',
	), array(
		'label' => 'Version string',
	)) . '

			' . $__templater->formEditorRow(array(
		'name' => 'version_details',
		'value' => '',
		'data-min-height' => '100',
	), array(
		'label' => 'Version details',
	)) . '

			' . $__templater->formRow('
				<ul class="inputList">
					<li data-xf-init="field-adder" data-increment-format="changelog[{counter}]">
						' . $__templater->formTextBox(array(
		'name' => 'changelog[0]',
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
		'hint' => 'If checked, the product\'s current version string will not be updated but this version will still be available to download.',
		'_type' => 'option',
	)), array(
	)) . '

			' . $__templater->formCheckBoxRow(array(
		'name' => 'send_notifications[]',
		'listclass' => 'listColumns listColumns--collapsed',
	), array(array(
		'label' => 'Email',
		'value' => 'email',
		'selected' => true,
		'_type' => 'option',
	),
	array(
		'label' => 'Alert',
		'value' => 'alert',
		'selected' => true,
		'_type' => 'option',
	)), array(
		'label' => 'Send notifications',
		'explain' => 'By default, all valid purchasers of this product will receive an alert and an email notifying them of this update. You can opt out of the notifications for this update above.',
	)) . '

			' . $__templater->formSelectRow(array(
		'name' => 'node_id',
	), $__compilerTemp1, array(
		'label' => 'Post update to forum',
		'explain' => 'If you select a forum above, a thread will be posted containing the update details.',
	)) . '

			<hr class="formRowSep" />

			' . $__templater->formRow('
				' . $__templater->callMacro('public:xr_pm_attach_upload_macros', 'upload_block', array(
		'attachmentData' => $__vars['productAttachData'],
		'hiddenName' => 'product_attach_hash',
		'label' => 'Upload product',
	), $__vars) . '
			', array(
		'label' => '',
		'rowtype' => 'button',
	)) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('product-manager/products/add-version', $__vars['product'], ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});