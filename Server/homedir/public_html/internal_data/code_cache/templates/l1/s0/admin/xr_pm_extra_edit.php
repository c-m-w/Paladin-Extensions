<?php
// FROM HASH: ca12a0bca8b09009f0c15d85d9b7a5ab
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['extra'], 'isInsert', array())) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add extra');
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit extra' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['extra']['extra_title']));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['extra'], 'isUpdate', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('', array(
			'href' => $__templater->fn('link', array('product-manager/products/extras/delete', $__vars['extra'], ), false),
			'icon' => 'delete',
			'overlay' => 'true',
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

';
	$__compilerTemp1 = $__templater->mergeChoiceOptions(array(), $__vars['userGroups']);
	if ($__templater->method($__vars['extra'], 'isInsert', array())) {
		$__compilerTemp1[] = array(
			'selected' => $__templater->method($__vars['extra'], 'isInsert', array()),
			'label' => '<b>' . 'Create new group' . '</b>',
			'value' => '__new',
			'_type' => 'option',
		);
	}
	$__compilerTemp2 = '';
	if ($__templater->method($__vars['extra'], 'isInsert', array())) {
		$__compilerTemp2 .= ' ' . 'If you wish to create a new user group specifically for this extra, select &quot;Create new group&quot;. It will be created with the name &quot;@ Extra reward: &lt;Extra name&gt;&quot;.';
	}
	$__compilerTemp3 = '';
	if ($__templater->method($__vars['extra'], 'isUpdate', array()) AND $__vars['extra']['Extra']) {
		$__compilerTemp3 .= '
							<div class="inputChoices-spacer">' . 'Existing file' . $__vars['xf']['language']['label_separator'] . '</div>
							' . $__templater->callMacro('public:xr_pm_attachment_macros', 'displayer', array(
			'label' => 'Existing file',
			'attachment' => $__vars['extra']['Extra'],
			'row' => false,
		), $__vars) . '
						';
	}
	$__compilerTemp4 = '';
	if ($__vars['products']) {
		$__compilerTemp4 .= '
				<hr class="formRowSep" />

				';
		$__compilerTemp5 = $__templater->mergeChoiceOptions(array(), $__vars['products']);
		$__compilerTemp4 .= $__templater->formCheckBoxRow(array(
			'value' => $__vars['productIds'],
			'name' => 'product_ids',
		), $__compilerTemp5, array(
			'label' => 'Purchasable with products',
		)) . '
			';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formTextBoxRow(array(
		'name' => 'extra_title',
		'value' => $__vars['extra']['extra_title'],
	), array(
		'label' => 'Extra title',
	)) . '

			' . $__templater->formTextAreaRow(array(
		'name' => 'extra_description',
		'value' => $__vars['extra']['extra_description_'],
	), array(
		'label' => 'Extra description',
		'explain' => 'You may use the {product} placeholder. This will be replaced with the product name (where applicable).',
	)) . '

			<hr class="formRowSep" />

			' . $__templater->formTextBoxRow(array(
		'name' => 'extra_price',
		'value' => $__vars['extra']['extra_price'],
		'class' => 'input--autoSize',
	), array(
		'label' => 'Purchase price',
		'explain' => 'The currency used for the price given here will be inherited from the product/purchase it is applied to.',
	)) . '

			' . $__templater->formTextBoxRow(array(
		'name' => 'extra_renew_price',
		'value' => $__vars['extra']['extra_renew_price'],
		'class' => 'input--autoSize',
	), array(
		'label' => 'Renewal price',
		'explain' => 'Owners of this optional extra will have this amount added on to their existing purchases when they renew.',
	)) . '

			<hr class="formRowSep" />

			' . $__templater->formRadioRow(array(
		'name' => 'extra_reward',
		'value' => $__vars['extra']['extra_reward'],
	), array(array(
		'value' => 'user_group',
		'label' => 'User group promotion',
		'_dependent' => array($__templater->formRadio(array(
		'name' => 'extra_user_group_id',
		'listclass' => 'listColumns',
		'value' => $__vars['extra']['extra_user_group_id'],
	), $__compilerTemp1)),
		'html' => '
						<div class="formRow-explain">
							' . 'Puts the user in the selected groups while the support duration is active.' . $__compilerTemp2 . '
						</div>
					',
		'_type' => 'option',
	),
	array(
		'value' => 'file',
		'label' => 'Downloadable file',
		'_dependent' => array('
						' . $__compilerTemp3 . '

						<div class="inputChoices-spacer">' . 'Upload new file' . $__vars['xf']['language']['label_separator'] . '</div>
						' . $__templater->callMacro('public:xr_pm_attachment_macros', 'uploader', array(
		'buttonLabel' => 'Upload new file',
		'attachmentData' => $__vars['extraAttachData'],
		'hiddenName' => 'extra_attach_hash',
		'row' => false,
	), $__vars) . '
					'),
		'_type' => 'option',
	),
	array(
		'value' => 'instructions',
		'label' => 'Written instructions',
		'_dependent' => array('
						' . $__templater->formEditor(array(
		'name' => 'instructions',
		'value' => $__vars['extra']['instructions'],
		'data-min-height' => '100',
	)) . '
						<div class="formRow-explain">
							' . 'You may use the {product} placeholder. This will be replaced with the product name (where applicable).' . '
						</div>
					'),
		'_type' => 'option',
	)), array(
		'label' => 'Purchase reward',
	)) . '

			' . $__compilerTemp4 . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('product-manager/products/extras/save', $__vars['extra'], ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});