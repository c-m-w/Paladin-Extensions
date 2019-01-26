<?php
// FROM HASH: b67f2b2bba4cd5ab27f3d26fe89cb676
return array('macros' => array('purchase_list' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'purchaseStates' => '!',
		'purchasesGrouped' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__templater->includeCss('structured_list.less');
	$__finalCompiled .= '

	';
	$__compilerTemp1 = true;
	if ($__templater->isTraversable($__vars['purchaseStates'])) {
		foreach ($__vars['purchaseStates'] AS $__vars['key'] => $__vars['phrases']) {
			if (!$__templater->test($__vars['purchasesGrouped'][$__vars['key']], 'empty', array())) {
				$__compilerTemp1 = false;
				$__finalCompiled .= '
		<div class="block">
			<div class="block-container">
				<h3 class="block-header">
					' . $__templater->escape($__vars['phrases']['label']) . '
					<span class="block-desc">
					' . $__templater->escape($__vars['phrases']['explain']) . '
				</span>
				</h3>
				<div class="block-body">
					<div class="structItemContainer">
						';
				if ($__templater->isTraversable($__vars['purchasesGrouped'][$__vars['key']])) {
					foreach ($__vars['purchasesGrouped'][$__vars['key']] AS $__vars['purchase']) {
						$__finalCompiled .= '
							' . $__templater->callMacro(null, 'purchase', array(
							'purchase' => $__vars['purchase'],
						), $__vars) . '
						';
					}
				}
				$__finalCompiled .= '
					</div>
				</div>
			</div>
		</div>
	';
			}
		}
	}
	if ($__compilerTemp1) {
		$__finalCompiled .= '
		<div class="blockMessage">
			' . 'You haven\'t made any valid purchases yet. If you made a purchase recently, it will appear here once the payment is processed.' . '
		</div>
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'purchase' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'purchase' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="structItem" data-author="' . ($__templater->escape($__vars['purchase']['User']['username']) ?: $__templater->escape($__vars['purchase']['username'])) . '">
		<div class="structItem-cell structItem-cell--productThumb structItem-cell--productThumb--medium">
			<div class="structItem-iconContainer">
				' . $__templater->fn('xr_pm_thumbnail', array($__vars['purchase']['Product'], $__templater->fn('link', array('products/purchase', $__vars['purchase'], ), false), 'xrpmThumbnail--medium', ), true) . '
			</div>
		</div>
		<div class="structItem-cell structItem-cell--main structItem-cell--productMain" data-xf-init="touch-proxy">
			<div class="structItem-title">
				<a href="' . $__templater->fn('link', array('products/purchase', $__vars['purchase'], ), true) . '" data-tp-primary="on">' . $__templater->escape($__vars['purchase']['Product']['product_title']) . ' - ' . $__templater->escape($__vars['purchase']['purchase_key']) . '</a>
				<span class="label label--primary">' . $__templater->filter($__vars['purchase']['total_price'], array(array('xr_pm_currency', array($__vars['purchase']['purchase_currency'], )),), true) . '</span>
			</div>
			<div class="structItem-minor">
				<ul class="structItem-parts">
					<li><a href="' . $__templater->fn('link', array('products', $__vars['purchase']['Product'], ), true) . '">' . $__templater->escape($__vars['purchase']['Product']['product_title']) . '</a></li>
					';
	if ($__templater->method($__vars['purchase'], 'hasLicenseDetails', array())) {
		$__finalCompiled .= '
						<li>' . $__templater->escape($__vars['purchase']['license_name']) . '</li>
						<li><a href="' . $__templater->escape($__vars['purchase']['license_url']) . '" target="_blank">' . $__templater->escape($__vars['purchase']['license_url']) . '</a></li>
					';
	}
	$__finalCompiled .= '
				</ul>
			</div>
			<div class="structItem-productInfo">
				' . $__templater->escape($__vars['purchase']['Product']['product_tag_line']) . '
				<ul>
					';
	if ($__vars['purchase']['displayable_extras']) {
		$__finalCompiled .= '
						';
		if ($__templater->isTraversable($__vars['purchase']['displayable_extras'])) {
			foreach ($__vars['purchase']['displayable_extras'] AS $__vars['extra']) {
				$__finalCompiled .= '
							<li>' . $__templater->escape($__vars['extra']['extra_title']) . '</li>
						';
			}
		}
		$__finalCompiled .= '
					';
	} else if ($__vars['purchase']['purchase_state'] != 'expired') {
		$__finalCompiled .= '
						<li>
							' . 'No optional extras purchased.' . '
						</li>
					';
	}
	$__finalCompiled .= '
					';
	if ($__templater->method($__vars['purchase'], 'canPurchaseExtras', array())) {
		$__finalCompiled .= '
						<li>
							<a href="' . $__templater->fn('link', array('products/purchase/extras', $__vars['purchase'], ), true) . '" data-xf-click="overlay">' . 'Purchase extras' . '</a>
						</li>
					';
	}
	$__finalCompiled .= '
				</ul>
			</div>
		</div>
		<div class="structItem-cell structItem-cell--productMeta">
			' . $__templater->callMacro('xr_pm_purchase_macros', 'purchase_buttons', array(
		'purchase' => $__vars['purchase'],
	), $__vars) . '
			<dl class="pairs pairs--justified structItem-minor">
				<dt>' . 'Purchase date' . '</dt>
				<dd>' . $__templater->fn('date_dynamic', array($__vars['purchase']['purchase_date'], array(
	))) . '</dd>
			</dl>
			';
	if ($__vars['purchase']['expiry_date'] > 0) {
		$__finalCompiled .= '
				<dl class="pairs pairs--justified structItem-minor">
					<dt>' . 'Expiry date' . '</dt>
					<dd>' . $__templater->fn('date_dynamic', array($__vars['purchase']['expiry_date'], array(
		))) . '</dd>
				</dl>
			';
	} else {
		$__finalCompiled .= '
				<dl class="pairs pairs--justified structItem-minor">
					<dt>' . 'Expiry date' . '</dt>
					<dd>' . 'Never' . '</dd>
				</dl>
			';
	}
	$__finalCompiled .= '
			';
	if ($__templater->method($__vars['purchase']['Product'], 'isRenewable', array())) {
		$__finalCompiled .= '
				<dl class="pairs pairs--justified structItem-minor">
					<dt>' . 'Renewal price' . '</dt>
					<dd>
						' . $__templater->filter($__vars['purchase']['renew_price'], array(array('currency', array($__vars['purchase']['purchase_currency'], )),), true) . '
					</dd>
				</dl>
			';
	}
	$__finalCompiled .= '
		</div>
	</div>
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Your purchases');
	$__finalCompiled .= '

' . $__templater->callMacro(null, 'purchase_list', array(
		'purchaseStates' => $__vars['purchaseStates'],
		'purchasesGrouped' => $__vars['purchasesGrouped'],
	), $__vars) . '

' . '

' . '

';
	$__templater->setPageParam('searchConstraints', array('Extensions' => array('search_type' => 'xr_pm_product', ), ));
	return $__finalCompiled;
});