<?php
// FROM HASH: 96480e836fde5ff120574a2a175dfea8
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['coupon'], 'isInsert', array())) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add coupon');
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit coupon' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['coupon']['coupon_title']));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['coupon'], 'isUpdate', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('', array(
			'href' => $__templater->fn('link', array('product-manager/products/coupons/delete', $__vars['coupon'], ), false),
			'icon' => 'delete',
			'overlay' => 'true',
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

';
	$__compilerTemp1 = $__templater->mergeChoiceOptions(array(), $__vars['products']);
	$__compilerTemp2 = $__templater->mergeChoiceOptions(array(), $__vars['extras']);
	$__compilerTemp3 = $__templater->mergeChoiceOptions(array(), $__vars['products']);
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formTextBoxRow(array(
		'name' => 'coupon_title',
		'value' => $__vars['coupon']['coupon_title'],
	), array(
		'label' => 'Coupon title',
	)) . '

			' . $__templater->formTextAreaRow(array(
		'name' => 'coupon_description',
		'value' => $__vars['coupon']['coupon_description'],
	), array(
		'label' => 'Coupon description',
	)) . '

			' . $__templater->formTextBoxRow(array(
		'name' => 'coupon_code',
		'value' => $__vars['coupon']['coupon_code'],
	), array(
		'label' => 'Coupon code',
	)) . '

			<hr class="formRowSep" />

			' . $__templater->formRadioRow(array(
		'name' => 'coupon_type',
		'value' => $__vars['coupon']['coupon_type'],
	), array(array(
		'label' => 'Entire purchase',
		'value' => 'purchase',
		'_type' => 'option',
	),
	array(
		'label' => 'Purchasing specific extensions',
		'value' => 'product',
		'data-hide' => 'on',
		'_dependent' => array($__templater->formCheckBox(array(
		'name' => 'coupon_product_ids',
		'value' => $__vars['coupon']['coupon_product_ids'],
	), $__compilerTemp1)),
		'_type' => 'option',
	),
	array(
		'label' => 'Purchasing specific extras',
		'value' => 'extra',
		'data-hide' => 'on',
		'_dependent' => array($__templater->formCheckBox(array(
		'name' => 'coupon_extra_ids',
		'value' => $__vars['coupon']['coupon_extra_ids'],
	), $__compilerTemp2)),
		'_type' => 'option',
	),
	array(
		'label' => 'Renewals',
		'value' => 'renewal',
		'data-hide' => 'on',
		'_dependent' => array($__templater->formRadio(array(
		'name' => 'renewal_coupon_type',
	), array(array(
		'label' => 'Any product',
		'value' => 'any',
		'selected' => !$__vars['coupon']['coupon_product_ids'],
		'_type' => 'option',
	),
	array(
		'label' => 'Specific extensions',
		'value' => 'product',
		'selected' => $__vars['coupon']['coupon_product_ids'],
		'data-hide' => 'on',
		'_dependent' => array($__templater->formCheckBox(array(
		'name' => 'coupon_product_ids',
		'value' => $__vars['coupon']['coupon_product_ids'],
	), $__compilerTemp3)),
		'_type' => 'option',
	)))),
		'_type' => 'option',
	)), array(
		'label' => 'Coupon applies to',
	)) . '

			' . $__templater->callMacro('helper_user_group_edit', 'checkboxes', array(
		'label' => 'Coupon usable by',
		'id' => 'coupon_usable_by',
		'selectedUserGroups' => ($__vars['coupon']['coupon_id'] ? $__vars['coupon']['coupon_usable_by'] : array(-1, )),
	), $__vars) . '

			' . $__templater->callMacro('helper_user_group_edit', 'checkboxes', array(
		'label' => 'Coupon automatically assigned to',
		'id' => 'coupon_auto_assign_to',
		'selectedUserGroups' => ($__vars['coupon']['coupon_id'] ? $__vars['coupon']['coupon_auto_assign_to'] : array()),
	), $__vars) . '

			' . $__templater->formRow('
				<div class="inputGroup">
					' . $__templater->formNumberBox(array(
		'name' => 'coupon_reduction',
		'value' => $__vars['coupon']['coupon_reduction'],
		'min' => '1',
	)) . '
					<span class="inputGroup-splitter"></span>
					' . $__templater->formSelect(array(
		'name' => 'coupon_unit',
		'value' => $__vars['coupon']['coupon_unit'],
		'class' => 'input--autoSize',
	), array(array(
		'value' => 'currency',
		'label' => 'Monetary discount',
		'_type' => 'option',
	),
	array(
		'value' => 'percent',
		'label' => 'Percent discount',
		'_type' => 'option',
	))) . '
				</div>
				<div class="formRow-explain">' . '"Monetary discount" is based on the selected currency for the product being purchased.' . '</div>
			', array(
		'label' => 'Coupon discount',
		'rowtype' => 'input',
	)) . '

			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'active',
		'value' => '1',
		'selected' => $__vars['coupon']['active'],
		'label' => 'Coupon is active',
		'_type' => 'option',
	),
	array(
		'name' => 'coupon_set_limit',
		'value' => '1',
		'selected' => $__vars['coupon']['coupon_set_limit'],
		'label' => 'Limit coupon uses',
		'_dependent' => array('
						' . $__templater->formNumberBox(array(
		'name' => 'coupon_limit',
		'value' => $__vars['coupon']['coupon_limit'],
		'min' => '0',
	)) . '
					'),
		'_type' => 'option',
	),
	array(
		'selected' => $__vars['coupon']['coupon_valid_to'] > 0,
		'label' => 'Coupon expires',
		'_dependent' => array('
						' . $__templater->formDateInput(array(
		'name' => 'coupon_valid_to',
		'value' => ($__vars['coupon']['coupon_valid_to'] ? $__templater->fn('date', array($__vars['coupon']['coupon_valid_to'], 'picker', ), false) : ''),
	)) . '
					'),
		'_type' => 'option',
	)), array(
		'label' => 'Options',
	)) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('product-manager/products/coupons/save', $__vars['coupon'], ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});