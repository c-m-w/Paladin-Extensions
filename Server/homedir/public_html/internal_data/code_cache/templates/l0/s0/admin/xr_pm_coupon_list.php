<?php
// FROM HASH: d8deecf7a51880dabe436be2bf55f867
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Product coupons');
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('
		' . 'Add coupon' . '
	', array(
		'icon' => 'add',
		'href' => $__templater->fn('link', array('product-manager/products/coupons/add', ), false),
	), '', array(
	)) . '
');
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['coupons'], 'empty', array())) {
		$__finalCompiled .= '
	';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['coupons'])) {
			foreach ($__vars['coupons'] AS $__vars['coupon']) {
				$__compilerTemp1 .= '
						' . $__templater->dataRow(array(
					'label' => $__templater->escape($__vars['coupon']['coupon_title']),
					'href' => $__templater->fn('link', array('product-manager/products/coupons/edit', $__vars['coupon'], ), false),
					'delete' => $__templater->fn('link', array('product-manager/products/coupons/delete', $__vars['coupon'], ), false),
					'explain' => $__templater->escape($__vars['coupon']['coupon_description']),
				), array(array(
					'class' => 'dataList-cell--separated dataList-cell--min dataList-cell--alt',
					'_type' => 'cell',
					'html' => $__templater->escape($__vars['coupon']['coupon_code']),
				),
				array(
					'name' => 'active[' . $__vars['coupon']['coupon_id'] . ']',
					'selected' => $__vars['coupon']['active'],
					'class' => 'dataList-cell--separated',
					'submit' => 'true',
					'tooltip' => 'Enable / disable \'' . $__vars['coupon']['coupon_title'] . '\'',
					'_type' => 'toggle',
					'html' => '',
				))) . '
					';
			}
		}
		$__finalCompiled .= $__templater->form('
		<div class="block-container">
			<div class="block-body">
				' . $__templater->dataList('
					<tbody class="dataList-rowGroup">
					' . $__compilerTemp1 . '
					</tbody>
				', array(
		)) . '
			</div>
		</div>
	', array(
			'action' => $__templater->fn('link', array('product-manager/products/coupons/toggle', ), false),
			'class' => 'block',
			'ajax' => 'true',
		)) . '
';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'No items have been created yet.' . '</div>
';
	}
	return $__finalCompiled;
});