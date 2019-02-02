<?php
// FROM HASH: 4c20d3ef39f29cccbef424a61e253864
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['purchase'], 'isInsert', array())) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add purchase');
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit purchase' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['purchase']['Product']['product_title']) . ' - ' . $__templater->escape($__vars['purchase']['purchase_key']));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['purchase'], 'isTransferrable', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('Transfer purchase', array(
			'href' => $__templater->fn('link', array('product-manager/purchases/transfer', $__vars['purchase'], ), false),
			'data-xf-click' => 'overlay',
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__templater->method($__vars['purchase'], 'isInsert', array())) {
		$__compilerTemp1 .= '
				';
		$__compilerTemp2 = array(array(
			'_type' => 'option',
		));
		$__compilerTemp2 = $__templater->mergeChoiceOptions($__compilerTemp2, $__vars['products']);
		$__compilerTemp1 .= $__templater->formSelectRow(array(
			'name' => 'product_id',
		), $__compilerTemp2, array(
			'label' => 'Extension',
		)) . '

				' . $__templater->formTextBoxRow(array(
			'name' => 'username',
			'ac' => 'single',
		), array(
			'label' => 'Purchaser',
			'explain' => 'If you are creating this purchase for yourself, you may leave the username blank. The user cannot be edited once assigned to a user.',
		)) . '
			';
	} else {
		$__compilerTemp1 .= '
				' . $__templater->formRow('
					<a href="' . $__templater->fn('link', array('product-manager/products/edit', $__vars['purchase']['Product'], ), true) . '">' . $__templater->escape($__vars['purchase']['Product']['product_title']) . '</a>
				', array(
			'label' => 'Extension',
			'rowtype' => 'text',
		)) . '

				' . $__templater->formRow('
					' . $__templater->escape($__vars['purchase']['purchase_key']) . '
					<div class="formRow-explain">
						' . 'This is a generated key which uniquely identifies this purchase.' . '
					</div>
				', array(
			'label' => 'Purchase key',
			'rowtype' => 'text',
		)) . '

				';
		if ($__vars['purchase']['old_cart_key']) {
			$__compilerTemp1 .= '
					' . $__templater->formRow('
						' . $__templater->escape($__vars['purchase']['old_cart_key']) . '
						<div class="formRow-explain">
							' . 'This key previously uniquely identified a specific cart. It will not appear on new purchases.' . '
						</div>
					', array(
				'label' => 'Old cart key (legacy)',
				'rowtype' => 'text',
			)) . '
				';
		}
		$__compilerTemp1 .= '

				' . $__templater->formRow('
					' . $__templater->fn('username_link', array($__vars['purchase']['User'], false, array(
			'defaultname' => $__vars['purchase']['username'],
		))) . '
				', array(
			'label' => 'Purchaser',
			'rowtype' => 'text',
		)) . '
			';
	}
	$__compilerTemp3 = array();
	if ($__templater->isTraversable($__vars['purchaseStates'])) {
		foreach ($__vars['purchaseStates'] AS $__vars['key'] => $__vars['phrases']) {
			$__compilerTemp3[] = array(
				'value' => $__vars['key'],
				'label' => $__templater->escape($__vars['phrases']['label']),
				'title' => $__vars['phrases']['explain'],
				'_type' => 'option',
			);
		}
	}
	$__compilerTemp4 = '';
	if ($__templater->method($__vars['purchase'], 'isInsert', array())) {
		$__compilerTemp4 .= '
					' . $__templater->escape($__vars['purchaseTypes']['product']) . '
					' . $__templater->formHiddenVal('purchase_type', 'product', array(
		)) . '
				';
	} else {
		$__compilerTemp4 .= '
					' . $__templater->escape($__vars['purchaseTypes'][$__vars['purchase']['purchase_type']]) . '
				';
	}
	$__compilerTemp5 = '';
	if ($__templater->method($__vars['purchase'], 'isUpdate', array()) AND $__vars['parentPurchase']) {
		$__compilerTemp5 .= '
				' . $__templater->formRow('
					<a href="' . $__templater->fn('link', array('product-manager/purchases/edit', $__vars['parentPurchase'], ), true) . '">
						' . $__templater->escape($__vars['parentPurchase']['Product']['product_title']) . ' - ' . $__templater->escape($__vars['parentPurchase']['purchase_key']) . '
					</a>
					<div class="formRow-explain">' . 'This was a renewal or extra purchase so the details of the purchase this updated are above.' . '</div>
				', array(
			'label' => 'Parent purchase',
			'rowtype' => 'text',
		)) . '
			';
	}
	$__compilerTemp6 = '';
	if (!$__templater->test($__vars['coupons'], 'empty', array())) {
		$__compilerTemp6 .= '
				';
		$__compilerTemp7 = '';
		if ($__templater->isTraversable($__vars['coupons'])) {
			foreach ($__vars['coupons'] AS $__vars['coupon']) {
				$__compilerTemp7 .= '
							<li>
								<a href="' . $__templater->fn('link', array('product-manager/products/coupons/edit', $__vars['coupon'], ), true) . '" class="labelLink">
									<span class="label label--primary"
										data-xf-init="tooltip"
										title="' . $__templater->escape($__vars['coupon']['coupon_description']) . '">
										' . $__templater->escape($__vars['coupon']['coupon_code']) . ' - ' . $__templater->escape($__vars['coupon']['coupon_title']) . '
									</span>
								</a>
							</li>
						';
			}
		}
		$__compilerTemp6 .= $__templater->formRow('
					<ul class="listInline">
						' . $__compilerTemp7 . '
					</ul>
				', array(
			'label' => 'Coupons applied',
			'rowtype' => 'text',
		)) . '
			';
	}
	$__compilerTemp8 = '';
	if (!$__templater->test($__vars['extras'], 'empty', array())) {
		$__compilerTemp8 .= '
				';
		$__compilerTemp9 = $__templater->mergeChoiceOptions(array(), $__vars['extras']);
		$__compilerTemp8 .= $__templater->formCheckBoxRow(array(
			'name' => 'extras',
			'listclass' => 'listColumns',
			'value' => $__templater->fn('array_keys', array($__vars['purchase']['extras'], ), false),
		), $__compilerTemp9, array(
			'label' => 'Associated extras',
		)) . '
			';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__compilerTemp1 . '

			' . $__templater->formDateInputRow(array(
		'name' => 'purchase_date',
		'value' => ($__templater->method($__vars['purchase'], 'isInsert', array()) ? $__templater->fn('date', array($__vars['xf']['time'], 'picker', ), false) : $__templater->fn('date', array($__vars['purchase']['purchase_date'], 'picker', ), false)),
	), array(
		'label' => 'Purchase date',
	)) . '

			' . $__templater->formDateInputRow(array(
		'name' => 'expiry_date',
		'value' => ($__templater->method($__vars['purchase'], 'isInsert', array()) ? $__templater->fn('date', array($__vars['xf']['time'] + (86400 * 365), 'picker', ), false) : ($__vars['purchase']['expiry_date'] ? $__templater->fn('date', array($__vars['purchase']['expiry_date'], 'picker', ), false) : '')),
	), array(
		'label' => 'Expiry date',
	)) . '

			' . $__templater->formSelectRow(array(
		'name' => 'purchase_state',
		'value' => $__vars['purchase']['purchase_state'],
		'data-xf-init' => 'desc-loader',
		'data-desc-url' => $__templater->fn('link', array('product-manager/purchases/get-state-explain', ), false),
	), $__compilerTemp3, array(
		'label' => 'Purchase state',
		'html' => '
					<div class="js-descTarget formRow-explain">' . $__templater->escape($__vars['purchaseStates'][$__vars['purchase']['purchase_state']]['explain']) . '</div>
				',
	)) . '

			' . $__templater->formRow('
				' . $__compilerTemp4 . '
				<div class="formRow-explain">' . 'Indicates the type of purchase. Product purchases are new purchases, whereas extras and renewals are additional updates to existing purchases.' . '</div>
			', array(
		'label' => 'Purchase type',
		'rowtype' => 'text',
	)) . '

			' . $__compilerTemp5 . '

			' . $__templater->formTextBoxRow(array(
		'name' => 'license_name',
		'value' => $__vars['purchase']['license_name'],
	), array(
		'label' => 'License name',
	)) . '

			' . $__templater->formTextBoxRow(array(
		'type' => 'url',
		'name' => 'license_url',
		'value' => $__vars['purchase']['license_url'],
	), array(
		'label' => 'License URL',
	)) . '

			' . $__templater->formRow('
				' . $__templater->callMacro('public:currency_macros', 'currency_list', array(
		'value' => ($__vars['purchase']['purchase_currency'] ?: 'USD'),
		'name' => 'purchase_currency',
		'class' => 'input--autoSize',
	), $__vars) . '
				<div class="formRow-explain">
					' . 'This currency will be used for all price formatting and payments related to this product.' . '
				</div>
			', array(
		'rowtype' => 'input',
		'label' => 'Purchase currency',
	)) . '

			' . $__templater->formNumberBoxRow(array(
		'name' => 'product_price',
		'value' => $__vars['purchase']['product_price'],
		'min' => '0',
		'step' => 'any',
	), array(
		'label' => 'Product price',
	)) . '

			' . $__templater->formNumberBoxRow(array(
		'name' => 'extras_price',
		'value' => $__vars['purchase']['extras_price'],
		'min' => '0',
		'step' => 'any',
	), array(
		'label' => 'Extras price',
	)) . '

			' . $__templater->formNumberBoxRow(array(
		'name' => 'discount_total',
		'value' => $__vars['purchase']['discount_total'],
		'min' => '0',
		'step' => 'any',
	), array(
		'label' => 'Discount total',
	)) . '

			' . $__templater->formNumberBoxRow(array(
		'name' => 'total_price',
		'value' => $__vars['purchase']['total_price'],
		'min' => '0',
		'step' => 'any',
	), array(
		'label' => 'Total price',
		'explain' => 'These values can be independently edited and the total values etc. are not calculated automatically.',
	)) . '

			' . $__compilerTemp6 . '

			' . $__compilerTemp8 . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
		'sticky' => 'true',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('product-manager/purchases/save', $__vars['purchase'], ), false),
		'ajax' => 'true',
		'class' => 'block',
		'data-force-flash-message' => 'on',
	));
	return $__finalCompiled;
});