<?php
// FROM HASH: e8a788ee7e0866b3efc5d58d027f1458
return array('macros' => array('purchase_buttons' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'purchase' => '!',
		'forceRenewButton' => false,
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__templater->method($__vars['purchase'], 'doesRequireRenewal', array()) OR $__vars['forceRenewButton']) {
		$__finalCompiled .= '
		' . $__templater->button('Renew', array(
			'icon' => 'refresh',
			'class' => 'button--product button--cta',
			'href' => $__templater->fn('link', array('products/purchase/renew', $__vars['purchase'], ), false),
			'data-xf-click' => 'overlay',
		), '', array(
		)) . '
	';
	}
	$__finalCompiled .= '
	';
	if ($__templater->method($__vars['purchase'], 'isDownloadable', array())) {
		$__finalCompiled .= '
		' . $__templater->button('xr_pm_download', array(
			'icon' => 'download',
			'class' => 'button--product button--cta',
			'href' => $__templater->fn('link', array('products/purchase/download', $__vars['purchase'], ), false),
			'data-xf-click' => 'overlay',
		), '', array(
		)) . '
	';
	}
	$__finalCompiled .= '
	';
	if ($__templater->method($__vars['purchase'], 'doesRequireActivation', array())) {
		$__finalCompiled .= '
		' . $__templater->button('Activate', array(
			'icon' => 'vote',
			'class' => 'button--product button--cta',
			'href' => $__templater->fn('link', array('products/purchase/activate', $__vars['purchase'], ), false),
			'data-xf-click' => 'overlay',
		), '', array(
		)) . '
	';
	}
	$__finalCompiled .= '
	';
	if ($__templater->method($__vars['purchase'], 'isActivatable', array()) AND (($__vars['purchase']['purchase_state'] != 'inactive') AND ($__vars['purchase']['purchase_state'] != 'expired'))) {
		$__finalCompiled .= '
		' . $__templater->button('Edit details', array(
			'icon' => 'edit',
			'class' => 'button--product',
			'href' => $__templater->fn('link', array('products/purchase/activate', $__vars['purchase'], ), false),
			'data-xf-click' => 'overlay',
		), '', array(
		)) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'coupons' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'product' => '!',
		'checker' => '!',
		'coupons' => '',
		'couponIds' => array(),
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__templater->method($__vars['product'], 'canUseCoupons', array())) {
		$__finalCompiled .= '
		';
		$__templater->includeCss('xr_pm_purchase_coupons.less');
		$__finalCompiled .= '

		' . $__templater->formRow('
			<div class="inputGroup">
				' . $__templater->formTextBox(array(
			'name' => 'coupon_code',
			'class' => 'js-couponCode',
		)) . '
				<div class="inputGroup-splitter"></div>
				' . $__templater->button('', array(
			'icon' => 'confirm',
			'class' => 'button--small js-checkCoupon',
		), '', array(
		)) . '
			</div>
			<div class="formRow-explain">
				<ul class="js-couponList listInline"></ul>
			</div>
			' . $__templater->formHiddenVal('coupon_ids', $__templater->filter($__vars['couponIds'], array(array('json', array()),), false), array(
			'class' => 'js-coupons',
		)) . '
		', array(
			'rowtype' => 'input',
			'label' => 'Coupon code',
			'rowclass' => 'js-coupon',
			'data-checker' => $__vars['checker'],
		)) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'extras' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'product' => '!',
		'purchase' => '',
		'value' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__compilerTemp1 = array();
	if ($__templater->isTraversable($__vars['product']['extras'])) {
		foreach ($__vars['product']['extras'] AS $__vars['extraId'] => $__vars['extra']) {
			if ((!$__vars['purchase']) OR $__templater->fn('in_array', array($__vars['extraId'], $__templater->method($__vars['purchase'], 'getUnpurchasedExtras', array()), ), false)) {
				$__compilerTemp2 = '';
				if ($__templater->method($__vars['product'], 'isRenewable', array()) AND $__vars['extra']['extra_renew_price']) {
					$__compilerTemp2 .= '
							<div class="inputChoices-spacer u-featuredText">' . 'Purchasing this extra item will add an additional ' . $__templater->filter($__vars['extra']['extra_renew_price'], array(array('currency', array(($__vars['purchase'] ? $__vars['purchase']['purchase_currency'] : $__vars['product']['currency']), )),), true) . ' charge on future renewals.' . '</div>
						';
				}
				$__compilerTemp1[] = array(
					'value' => $__vars['extraId'],
					'data-price' => $__vars['extra']['extra_price'],
					'label' => '<span class="label label--primary label--smallest">' . $__templater->filter($__vars['extra']['extra_price'], array(array('xr_pm_currency', array(($__vars['purchase'] ? $__vars['purchase']['purchase_currency'] : $__vars['product']['currency']), )),), true) . '</span> ' . $__templater->escape($__vars['extra']['extra_title']),
					'hint' => '
						' . $__templater->escape($__templater->method($__vars['product'], 'getExtraDescription', array($__vars['extra'], ))) . '
						' . $__compilerTemp2 . '
					',
					'_type' => 'option',
				);
			}
		}
	}
	$__vars['extras'] = $__templater->preEscaped('
		' . $__templater->formCheckBoxRow(array(
		'name' => 'extras',
		'listclass' => 'js-extras',
		'value' => $__vars['value'],
	), $__compilerTemp1, array(
		'label' => 'Customize purchase',
		'explain' => 'You can purchase extras at a later date if you do not wish to purchase them now.',
	)) . '
	');
	$__finalCompiled .= '
	';
	if ($__vars['purchase'] AND $__templater->method($__vars['purchase'], 'getUnpurchasedExtras', array())) {
		$__finalCompiled .= '
		' . $__templater->filter($__vars['extras'], array(array('raw', array()),), true) . '
	';
	} else if ((!$__vars['purchase']) AND !$__templater->test($__vars['product']['extras'], 'empty', array())) {
		$__finalCompiled .= '
		' . $__templater->filter($__vars['extras'], array(array('raw', array()),), true) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'payment_profiles' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'product' => '!',
		'profiles' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if (($__templater->fn('count', array($__vars['product']['payment_profile_ids'], ), false) > 1)) {
		$__finalCompiled .= '
		';
		$__compilerTemp1 = array(array(
			'label' => $__vars['xf']['language']['parenthesis_open'] . 'Choose a payment method' . $__vars['xf']['language']['parenthesis_close'],
			'_type' => 'option',
		));
		if ($__templater->isTraversable($__vars['product']['payment_profile_ids'])) {
			foreach ($__vars['product']['payment_profile_ids'] AS $__vars['profileId']) {
				$__compilerTemp1[] = array(
					'value' => $__vars['profileId'],
					'label' => $__templater->escape($__vars['profiles'][$__vars['profileId']]),
					'_type' => 'option',
				);
			}
		}
		$__finalCompiled .= $__templater->formSelectRow(array(
			'name' => 'payment_profile_id',
		), $__compilerTemp1, array(
			'label' => 'Pay using',
		)) . '
	';
	} else {
		$__finalCompiled .= '
		' . $__templater->formHiddenVal('payment_profile_id', $__templater->filter($__vars['product']['payment_profile_ids'], array(array('first', array()),), false), array(
		)) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '

' . '

' . '

';
	return $__finalCompiled;
});