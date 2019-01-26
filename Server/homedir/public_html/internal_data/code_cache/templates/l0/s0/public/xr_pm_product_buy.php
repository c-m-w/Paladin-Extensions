<?php
// FROM HASH: 46dade5561fec0482873e89e4e5f90fb
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Confirm purchase' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['product']['product_title']));
	$__finalCompiled .= '

';
	$__templater->includeJs(array(
		'addon' => 'XR/PM',
		'dev' => 'xf/payment.js, xr/pm/buy.js',
		'prod' => 'xf/payment.min.js, xr/pm/buy.min.js',
	));
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formInfoRow('
				' . 'Please confirm you wish to buy the following product and customize any extras (if any) below' . ':
				<strong><a href="' . $__templater->fn('link', array('products', $__vars['product'], ), true) . '">' . $__templater->escape($__vars['product']['product_title']) . '</a></strong>
			', array(
		'rowtype' => 'confirm',
	)) . '

			' . $__templater->callMacro('xr_pm_purchase_macros', 'extras', array(
		'product' => $__vars['product'],
	), $__vars) . '

			' . $__templater->callMacro('xr_pm_purchase_macros', 'coupons', array(
		'product' => $__vars['product'],
		'coupons' => $__vars['coupons'],
		'couponIds' => $__vars['couponIds'],
		'checker' => $__templater->fn('link', array('products/buy/coupon-checker', $__vars['product'], ), false),
	), $__vars) . '

			' . $__templater->callMacro('xr_pm_purchase_macros', 'payment_profiles', array(
		'product' => $__vars['product'],
		'profiles' => $__vars['profiles'],
	), $__vars) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'purchase',
		'class' => 'js-payButton',
		'submit' => 'Buy for ' . $__templater->filter($__vars['product']['price'], array(array('currency', array($__vars['product']['currency'], )),), true) . '',
	), array(
		'rowtype' => '',
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('products/buy', $__vars['product'], ), false),
		'ajax' => 'true',
		'class' => 'block',
		'data-xf-init' => 'xrpm-product-buy',
		'data-price' => $__vars['product']['price'],
		'data-currency-data' => $__templater->filter($__templater->fn('xr_pm_currency_data', array($__vars['product']['currency'], ), false), array(array('json', array()),), false),
	));
	return $__finalCompiled;
});