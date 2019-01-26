<?php
// FROM HASH: c404769d4e8ff624d2b290681e0d2f97
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Search purchases');
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('Add purchase', array(
		'href' => $__templater->fn('link', array('product-manager/purchases/add', ), false),
		'icon' => 'add',
	), '', array(
	)) . '
');
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		';
	$__compilerTemp1 = array(array(
		'label' => $__vars['xf']['language']['parenthesis_open'] . 'Any' . $__vars['xf']['language']['parenthesis_close'],
		'_type' => 'option',
	));
	if ($__templater->isTraversable($__vars['products'])) {
		foreach ($__vars['products'] AS $__vars['product']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['product']['product_id'],
				'label' => $__templater->escape($__vars['product']['product_title']),
				'_type' => 'option',
			);
		}
	}
	$__compilerTemp2 = $__templater->mergeChoiceOptions(array(), $__vars['purchaseStates']);
	$__compilerTemp3 = $__templater->mergeChoiceOptions(array(), $__vars['purchaseTypes']);
	$__compilerTemp4 = $__templater->mergeChoiceOptions(array(), $__vars['sortOrders']);
	$__finalCompiled .= $__templater->form('
			<div class="block-body">
				' . $__templater->formTextBoxRow(array(
		'name' => 'criteria[username]',
		'value' => $__vars['criteria']['username'],
	), array(
		'label' => 'User name',
	)) . '

				' . $__templater->formTextBoxRow(array(
		'name' => 'criteria[license_name]',
		'value' => $__vars['criteria']['license_name'],
	), array(
		'label' => 'License name',
	)) . '

				' . $__templater->formTextBoxRow(array(
		'name' => 'criteria[license_url]',
		'value' => $__vars['criteria']['license_url'],
	), array(
		'label' => 'License URL',
	)) . '

				<hr class="formRowSep" />

				' . $__templater->formTextBoxRow(array(
		'name' => 'criteria[purchase_key]',
		'value' => $__vars['criteria']['purchase_key'],
	), array(
		'label' => 'Purchase key',
	)) . '

				' . $__templater->formTextBoxRow(array(
		'name' => 'criteria[old_cart_key]',
		'value' => $__vars['criteria']['old_cart_key'],
	), array(
		'label' => 'Old cart key',
	)) . '

				' . $__templater->formTextBoxRow(array(
		'name' => 'criteria[parent_purchase_key]',
		'value' => $__vars['criteria']['parent_purchase_key'],
	), array(
		'label' => 'Parent purchase key',
	)) . '

				<hr class="formRowSep" />

				' . $__templater->formSelectRow(array(
		'name' => 'criteria[product_id]',
		'value' => $__vars['criteria']['product_id'],
	), $__compilerTemp1, array(
		'label' => 'Product',
	)) . '

				<hr class="formRowSep" />

				' . $__templater->formRow('

					<div class="inputGroup">
						' . $__templater->formDateInput(array(
		'name' => 'criteria[purchase_date][start]',
		'value' => $__vars['criteria']['purchase_date']['start'],
		'size' => '15',
	)) . '
						<span class="inputGroup-text">-</span>
						' . $__templater->formDateInput(array(
		'name' => 'criteria[purchase_date][end]',
		'value' => $__vars['criteria']['purchase_date']['end'],
		'size' => '15',
	)) . '
					</div>
				', array(
		'rowtype' => 'input',
		'label' => 'Purchased between',
	)) . '

				' . $__templater->formRow('

					<div class="inputGroup">
						' . $__templater->formDateInput(array(
		'name' => 'criteria[expiry_date][start]',
		'value' => $__vars['criteria']['expiry_date']['start'],
		'size' => '15',
	)) . '
						<span class="inputGroup-text">-</span>
						' . $__templater->formDateInput(array(
		'name' => 'criteria[expiry_date][end]',
		'value' => $__vars['criteria']['expiry_date']['end'],
		'size' => '15',
	)) . '
					</div>
				', array(
		'rowtype' => 'input',
		'label' => 'Expires between',
	)) . '

				<hr class="formRowSep" />

				' . $__templater->formCheckBoxRow(array(
		'name' => 'criteria[purchase_state]',
		'value' => $__vars['criteria']['purchase_state'],
	), $__compilerTemp2, array(
		'label' => 'Purchase state',
	)) . '

				' . $__templater->formCheckBoxRow(array(
		'name' => 'criteria[purchase_type]',
		'value' => $__vars['criteria']['purchase_type'],
	), $__compilerTemp3, array(
		'label' => 'Purchase type',
	)) . '

				<hr class="formRowSep" />

				' . $__templater->formRow('

					<div class="inputPair">
						' . $__templater->formSelect(array(
		'name' => 'order',
	), $__compilerTemp4) . '
						' . $__templater->formSelect(array(
		'name' => 'direction',
	), array(array(
		'value' => 'asc',
		'label' => 'Ascending',
		'_type' => 'option',
	),
	array(
		'value' => 'desc',
		'label' => 'Descending',
		'_type' => 'option',
	))) . '
					</div>
				', array(
		'rowtype' => 'input',
		'label' => 'Sort',
	)) . '
			</div>
			' . $__templater->formSubmitRow(array(
		'sticky' => 'true',
		'icon' => 'search',
	), array(
	)) . '
		', array(
		'action' => $__templater->fn('link', array('product-manager/purchases', ), false),
	)) . '
	</div>
</div>';
	return $__finalCompiled;
});