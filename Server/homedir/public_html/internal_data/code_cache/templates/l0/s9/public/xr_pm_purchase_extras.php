<?php
// FROM HASH: a126e08ff4ca27c42a487cb2a3a79cb5
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Confirm extras purchase' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['product']['product_title']) . ' - ' . $__templater->escape($__vars['purchase']['purchase_key']));
	$__finalCompiled .= '

';
	$__templater->includeJs(array(
		'addon' => 'XR/PM',
		'dev' => 'xf/payment.js, xr/pm/buy.js',
		'prod' => 'xf/payment.min.js, xr/pm/buy.min.js',
	));
	$__finalCompiled .= '

';
	$__templater->breadcrumbs($__templater->method($__vars['purchase'], 'getBreadcrumbs', array(true, )));
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formInfoRow('
				' . 'Please select the optional extras you would like to buy for the following existing purchase:' . '
				<strong><a href="' . $__templater->fn('link', array('products/purchase', $__vars['purchase'], ), true) . '">' . $__templater->escape($__vars['product']['product_title']) . ' - ' . $__templater->escape($__vars['purchase']['purchase_key']) . '</a></strong>
			', array(
		'rowtype' => 'confirm',
	)) . '

			' . $__templater->callMacro('xr_pm_purchase_macros', 'extras', array(
		'product' => $__vars['product'],
		'purchase' => $__vars['purchase'],
		'value' => $__vars['extraId'],
	), $__vars) . '

			' . $__templater->callMacro('xr_pm_purchase_macros', 'coupons', array(
		'product' => $__vars['product'],
		'coupons' => $__vars['coupons'],
		'couponIds' => $__vars['couponIds'],
		'checker' => $__templater->fn('link', array('products/purchase/extras/coupon-checker', $__vars['purchase'], ), false),
	), $__vars) . '

			' . $__templater->callMacro('xr_pm_purchase_macros', 'payment_profiles', array(
		'product' => $__vars['product'],
		'profiles' => $__vars['profiles'],
	), $__vars) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'purchase',
		'class' => 'js-payButton',
		'submit' => 'Buy for ' . $__templater->filter(0, array(array('currency', array($__vars['product']['currency'], )),), true) . '',
	), array(
		'rowtype' => '',
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('products/purchase/extras', $__vars['purchase'], ), false),
		'ajax' => 'true',
		'class' => 'block',
		'data-xf-init' => 'xrpm-product-buy',
		'data-currency-data' => $__templater->filter($__templater->fn('xr_pm_currency_data', array($__vars['purchase']['purchase_currency'], ), false), array(array('json', array()),), false),
		'data-purchase-type' => 'extra',
	));
	return $__finalCompiled;
});