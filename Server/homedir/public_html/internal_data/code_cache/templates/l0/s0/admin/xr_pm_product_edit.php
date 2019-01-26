<?php
// FROM HASH: e64a7f588aa722d2d2a2d516ee98c9fb
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['product'], 'isInsert', array())) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add product');
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit product' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['product']['product_title']));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['product'], 'isUpdate', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('', array(
			'href' => $__templater->fn('link', array('product-manager/products/delete', $__vars['product'], ), false),
			'icon' => 'delete',
			'overlay' => 'true',
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

';
	$__compilerTemp1 = array();
	if ($__templater->isTraversable($__vars['categories'])) {
		foreach ($__vars['categories'] AS $__vars['category']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['category']['value'],
				'label' => $__templater->escape($__vars['category']['label']),
				'_type' => 'option',
			);
		}
	}
	$__compilerTemp2 = '';
	if ($__templater->isTraversable($__vars['product']['features'])) {
		foreach ($__vars['product']['features'] AS $__vars['counter'] => $__vars['feature']) {
			$__compilerTemp2 .= '
						<li>' . $__templater->formTextBox(array(
				'name' => 'product[features][' . $__vars['counter'] . ']',
				'value' => $__vars['feature'],
			)) . '</li>
					';
		}
	}
	$__vars['productExtra'] = $__templater->preEscaped('
				<div class="contentRow-minor contentRow-spaced">
					' . $__templater->button('', array(
		'icon' => 'edit',
		'href' => $__templater->fn('link', array('product-manager/products/versions/edit', $__vars['product']['Version'], ), false),
		'class' => 'button--link button--small',
		'data-xf-click' => 'overlay',
	), '', array(
	)) . '
				</div>
			');
	$__vars['thumbnailExtra'] = $__templater->preEscaped('
				<div class="contentRow-minor contentRow-spaced">
					' . $__templater->button('', array(
		'icon' => 'edit',
		'href' => $__templater->fn('link', array('product-manager/products/edit-thumbnail', $__vars['product'], ), false),
		'class' => 'button--link button--small',
		'data-xf-click' => 'overlay',
	), '', array(
	)) . '
				</div>
			');
	$__compilerTemp3 = array();
	if ($__templater->isTraversable($__vars['profiles'])) {
		foreach ($__vars['profiles'] AS $__vars['profileId'] => $__vars['profile']) {
			$__compilerTemp3[] = array(
				'value' => $__vars['profileId'],
				'label' => (($__vars['profile']['Provider']['title'] !== $__vars['profile']['title']) ? (($__templater->escape($__vars['profile']['Provider']['title']) . ' - ') . $__templater->escape($__vars['profile']['title'])) : $__templater->escape($__vars['profile']['Provider']['title'])),
				'_type' => 'option',
			);
		}
	}
	$__compilerTemp4 = $__templater->mergeChoiceOptions(array(), $__vars['userGroups']);
	if ($__templater->method($__vars['product'], 'isInsert', array())) {
		$__compilerTemp4[] = array(
			'label' => '<b>' . 'Create new group' . '</b>',
			'value' => '__new',
			'_type' => 'option',
		);
	}
	$__compilerTemp5 = '';
	if ($__templater->method($__vars['product'], 'isInsert', array())) {
		$__compilerTemp5 .= ' ' . 'If you wish to create a new user group specifically for this product, select &quot;Create new group&quot;. It will be created with the name &quot;@ Licensed customer: &lt;Product name&gt;&quot;.';
	}
	$__compilerTemp6 = '';
	if (!$__templater->test($__vars['extras'], 'empty', array())) {
		$__compilerTemp6 .= '
				';
		$__compilerTemp7 = array();
		if ($__templater->isTraversable($__vars['extras'])) {
			foreach ($__vars['extras'] AS $__vars['extraId'] => $__vars['extra']) {
				$__compilerTemp7[] = array(
					'value' => $__vars['extraId'],
					'label' => $__templater->escape($__vars['extra']['extra_title']),
					'hint' => $__templater->escape($__vars['extra']['extra_description']),
					'_type' => 'option',
				);
			}
		}
		$__compilerTemp6 .= $__templater->formCheckBoxRow(array(
			'name' => 'product[optional_extras]',
			'value' => $__vars['product']['optional_extras'],
		), $__compilerTemp7, array(
			'label' => 'Available extras',
		)) . '

				<hr class="formRowSep" />
			';
	}
	$__compilerTemp8 = '';
	$__compilerTemp9 = '';
	$__compilerTemp9 .= '
					' . $__templater->callMacro('public:custom_fields_macros', 'custom_fields_edit', array(
		'type' => 'xr_pm_products',
		'set' => $__vars['product']['custom_fields'],
	), $__vars) . '
				';
	if (strlen(trim($__compilerTemp9)) > 0) {
		$__compilerTemp8 .= '
				' . $__compilerTemp9 . '

				<hr class="formRowSep" />
			';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formSelectRow(array(
		'name' => 'product[category_id]',
		'value' => $__vars['product']['category_id'],
	), $__compilerTemp1, array(
		'label' => 'Category',
	)) . '

			' . $__templater->formRow('
				<div class="inputGroup inputGroup--auto">
					' . $__templater->formTextBox(array(
		'name' => 'product[product_title]',
		'value' => $__vars['product']['product_title'],
		'maxlength' => $__templater->fn('max_length', array($__vars['product'], 'product_title', ), false),
		'size' => '75',
	)) . '

					<span class="inputGroup-splitter"></span>

					' . $__templater->formTextBox(array(
		'name' => 'version[version_string]',
		'value' => $__vars['version']['version_string'],
		'maxlength' => $__templater->fn('max_length', array($__vars['version'], 'version_string', ), false),
		'size' => '25',
	)) . '
				</div>
			', array(
		'rowtype' => 'input',
		'label' => ($__templater->method($__vars['product'], 'isInsert', array()) ? 'Title and initial version' : 'Title and current version'),
	)) . '

			' . $__templater->formTextBoxRow(array(
		'name' => 'product[product_tag_line]',
		'value' => $__vars['product']['product_tag_line'],
		'maxlength' => $__templater->fn('max_length', array($__vars['product'], 'product_tag_line', ), false),
	), array(
		'label' => 'Tag line',
		'explain' => 'The tag line should be a brief sentence about what this product is for.',
	)) . '

			<div data-xf-init="attachment-manager">
				' . $__templater->formEditorRow(array(
		'name' => 'product[product_details]',
		'value' => $__vars['product']['product_details'],
		'attachments' => $__vars['imageAttachData']['attachments'],
	), array(
		'label' => 'Product details',
	)) . '

				' . $__templater->formRow('
					' . $__templater->callMacro('public:xr_pm_attach_upload_macros', 'upload_block', array(
		'initAttachmentManager' => false,
		'attachmentData' => $__vars['imageAttachData'],
		'hiddenName' => 'image_attach_hash',
		'label' => 'Upload images',
	), $__vars) . '
				', array(
		'rowtype' => 'button',
	)) . '
			</div>

			' . $__templater->formRow('
				<ul class="inputList">
					' . $__compilerTemp2 . '

					<li data-xf-init="field-adder" data-increment-format="product[features][{counter}]">
						' . $__templater->formTextBox(array(
		'name' => 'product[features][' . $__templater->fn('count', array($__vars['product']['features'], ), false) . ']',
	)) . '
					</li>
				</ul>
			', array(
		'rowtype' => 'input',
		'label' => 'Main features',
		'explain' => 'Describe the main features of your product in just a few words. New fields will be added as you type.',
	)) . '

			' . '' . '
			' . $__templater->callMacro('public:xr_pm_attachment_macros', 'upload_editor', array(
		'isInsert' => $__templater->method($__vars['product'], 'isInsert', array()),
		'label' => 'Product',
		'buttonLabel' => 'Upload product',
		'attachmentData' => $__vars['productAttachData'],
		'hiddenName' => 'product_attach_hash',
		'attachment' => $__vars['version']['Version'],
		'extra' => $__vars['productExtra'],
	), $__vars) . '

			' . '' . '
			' . $__templater->callMacro('public:xr_pm_attachment_macros', 'upload_editor', array(
		'isInsert' => $__templater->method($__vars['product'], 'isInsert', array()),
		'label' => 'Thumbnail',
		'buttonLabel' => 'Upload thumbnail',
		'attachmentData' => $__vars['thumbAttachData'],
		'hiddenName' => 'thumb_attach_hash',
		'iconUrl' => ($__vars['product']['has_thumbnail'] ? $__vars['product']['thumbnail_url'] : ''),
		'title' => $__vars['product']['product_title'],
		'attachment' => $__vars['product']['Thumbnail'],
		'extra' => $__vars['thumbnailExtra'],
	), $__vars) . '

			<hr class="formRowSep" />

			' . $__templater->formRow('
				' . $__templater->callMacro('public:currency_macros', 'currency_list', array(
		'value' => ($__vars['product']['currency'] ?: 'USD'),
		'name' => 'product[currency]',
		'class' => 'input--autoSize',
	), $__vars) . '
				<div class="formRow-explain">
					' . 'This currency will be used for all price formatting and payments related to this product.' . '
					' . '<strong>Note:</strong> Ensure your merchant account with the selected payment profiles supports the above currencies. Currency support may vary by region.' . '
				</div>
			', array(
		'rowtype' => 'input',
		'label' => 'Product currency',
	)) . '

			' . $__templater->formTextBoxRow(array(
		'name' => 'product[price]',
		'value' => $__vars['product']['price'],
		'class' => 'input--autoSize',
	), array(
		'label' => 'Purchase price',
	)) . '

			' . $__templater->formTextBoxRow(array(
		'name' => 'product[renew_price]',
		'value' => $__vars['product']['renew_price'],
		'class' => 'input--autoSize',
	), array(
		'label' => 'Renewal price',
		'explain' => 'This is the cost for renewing a purchase after the initial support duration has expired (if one is defined below).',
	)) . '

			' . $__templater->formRow('

				<div class="inputGroup">
					' . $__templater->formNumberBox(array(
		'name' => 'product[duration]',
		'value' => $__vars['product']['duration'],
		'min' => '0',
		'max' => '255',
	)) . '
					<span class="inputGroup-splitter"></span>
					' . $__templater->formSelect(array(
		'name' => 'product[duration_unit]',
		'value' => $__vars['product']['duration_unit'],
		'class' => 'input--inline',
	), array(array(
		'value' => 'days',
		'label' => 'Days',
		'_type' => 'option',
	),
	array(
		'value' => 'months',
		'label' => 'Months',
		'_type' => 'option',
	),
	array(
		'value' => 'years',
		'label' => 'Years',
		'_type' => 'option',
	))) . '
				</div>
			', array(
		'rowtype' => 'input',
		'label' => 'Initial support duration',
	)) . '

			' . $__templater->formCheckBoxRow(array(
		'value' => $__vars['product']['allow_early_extension'],
	), array(array(
		'name' => 'product[allow_early_extension]',
		'value' => '1',
		'label' => 'Allow early extension',
		'_type' => 'option',
	)), array(
		'label' => '',
		'explain' => 'If enabled, purchasers will be allowed to extend their support duration at any time. Additional time will be added to the end of their existing support duration.',
	)) . '

			' . $__templater->formCheckBoxRow(array(
		'name' => 'product[payment_profile_ids]',
		'value' => $__vars['product']['payment_profile_ids'],
	), $__compilerTemp3, array(
		'label' => 'Payment profile',
	)) . '

			<hr class="formRowSep" />

			' . $__templater->formCheckBoxRow(array(
		'name' => 'product[user_group_ids]',
		'value' => $__vars['product']['user_group_ids'],
		'listclass' => 'listColumns',
	), $__compilerTemp4, array(
		'label' => 'Licensed user groups',
		'explain' => 'Puts the user in the selected groups while the support duration is active.' . $__compilerTemp5,
	)) . '

			<hr class="formRowSep" />

			' . $__compilerTemp6 . '

			' . $__templater->formEditorRow(array(
		'name' => 'product[terms_conditions]',
		'value' => $__vars['product']['terms_conditions'],
		'data-min-height' => '100',
	), array(
		'label' => 'Terms and conditions',
		'explain' => 'Enter the terms and conditions relating to the purchase of this product.',
	)) . '

			' . $__compilerTemp8 . '

			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'product[confirm_license]',
		'selected' => $__vars['product']['confirm_license'],
		'label' => 'Agree to terms and conditions before download',
		'_type' => 'option',
	)), array(
		'explain' => 'If enabled, the user will need to agree to the above terms and conditions (or the <a href="' . $__templater->fn('link', array('options/groups/xrpm/', ), true) . '" target="_blank">default terms</a>) before downloading.',
	)) . '

			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'product[requires_activation]',
		'selected' => $__vars['product']['requires_activation'],
		'label' => 'Requires activation before download',
		'_type' => 'option',
	)), array(
		'explain' => 'If a license requires activation before download then the purchaser will be required to provide their site name and URL before being able to download.',
	)) . '

			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'product[active]',
		'selected' => $__vars['product']['active'],
		'label' => 'Product is active',
		'_type' => 'option',
	)), array(
		'explain' => 'Products which are no longer active can no longer be purchased, but they will remain visible in any user\'s existing purchases. It will not be possible for inactive products to be purchased, by extras for them or renew expired purchases.',
	)) . '
		</div>

		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
		'sticky' => 'true',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('product-manager/products/save', $__vars['product'], ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});