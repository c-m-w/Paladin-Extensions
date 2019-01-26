<?php
// FROM HASH: 111eb8ea17f096fdd92b082d0b11ebf3
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Confirm renewal' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['product']['product_title']) . ' - ' . $__templater->escape($__vars['purchase']['purchase_key']));
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

';
	$__compilerTemp1 = '';
	if ($__templater->method($__vars['purchase'], 'isVeryEarlyRenewal', array())) {
		$__compilerTemp1 .= '
				<div class="block-row">
					<div class="block-rowMessage block-rowMessage--warning">
						' . 'This purchase has been renewed recently. If you\'d like to renew again so soon, additional time will be added onto the existing expiry date.' . '
					</div>
				</div>
			';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__compilerTemp1 . '

			' . $__templater->formInfoRow('
				' . 'Please confirm you wish to renew the following purchase and extras (if any)' . ':
				<strong><a href="' . $__templater->fn('link', array('products/purchase', $__vars['purchase'], ), true) . '">' . $__templater->escape($__vars['product']['product_title']) . ' - ' . $__templater->escape($__vars['purchase']['purchase_key']) . '</a></strong>
			', array(
		'rowtype' => 'confirm',
	)) . '

			' . $__templater->callMacro('xr_pm_purchase_macros', 'coupons', array(
		'product' => $__vars['product'],
		'coupons' => $__vars['coupons'],
		'couponIds' => $__vars['couponIds'],
		'checker' => $__templater->fn('link', array('products/purchase/renew/coupon-checker', $__vars['purchase'], ), false),
	), $__vars) . '

			' . $__templater->callMacro('xr_pm_purchase_macros', 'payment_profiles', array(
		'product' => $__vars['product'],
		'profiles' => $__vars['profiles'],
	), $__vars) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'purchase',
		'class' => 'js-payButton',
		'submit' => 'Renew for ' . $__templater->filter($__vars['purchase']['renew_price'], array(array('currency', array($__vars['purchase']['purchase_currency'], )),), true) . '',
	), array(
		'rowtype' => '',
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('products/purchase/renew', $__vars['purchase'], ), false),
		'ajax' => 'true',
		'class' => 'block',
		'data-xf-init' => 'xrpm-product-buy',
		'data-price' => $__vars['purchase']['renew_price'],
		'data-phrase' => 'xr_pm_renew_for_x',
		'data-currency-data' => $__templater->filter($__templater->fn('xr_pm_currency_data', array($__vars['purchase']['purchase_currency'], ), false), array(array('json', array()),), false),
	));
	return $__finalCompiled;
});