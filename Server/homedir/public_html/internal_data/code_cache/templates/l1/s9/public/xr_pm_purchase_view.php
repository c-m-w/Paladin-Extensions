<?php
// FROM HASH: eafc792ea03b1d60bc463ba603ffbb71
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->escape($__vars['purchase']['Product']['product_title']) . ' - ' . $__templater->escape($__vars['purchase']['purchase_key']));
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__templater->method($__vars['purchase'], 'hasLicenseDetails', array())) {
		$__compilerTemp1 .= '
		<ul class="listInline listInline--bullet">
			<li>' . $__templater->escape($__vars['purchase']['license_name']) . '</li>
			<li><a href="' . $__templater->escape($__vars['purchase']['license_url']) . '" target="_blank">' . $__templater->escape($__vars['purchase']['license_url']) . '</a></li>
		</ul>
	';
	}
	$__templater->pageParams['pageDescription'] = $__templater->preEscaped(trim('
	' . $__compilerTemp1 . '
'));
	$__templater->pageParams['pageDescriptionMeta'] = true;
	$__finalCompiled .= '

';
	$__templater->breadcrumbs($__templater->method($__vars['purchase'], 'getBreadcrumbs', array()));
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->callMacro('xr_pm_purchase_macros', 'purchase_buttons', array(
		'purchase' => $__vars['purchase'],
		'forceRenewButton' => $__templater->method($__vars['purchase'], 'isRenewableEarly', array()),
	), $__vars) . '
');
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['purchase'], 'doesRequireActivation', array())) {
		$__finalCompiled .= '
	<div class="blockMessage blockMessage--important">
		' . 'Before you are able to download this product, you must activate the purchase by <a href="' . $__templater->fn('link', array('products/purchase/activate', $__vars['purchase'], ), true) . '" data-xf-click="overlay">clicking here</a>.' . '
	</div>
';
	}
	$__finalCompiled .= '

';
	if ($__vars['renewPurchase']) {
		$__finalCompiled .= '
	<div class="blockMessage blockMessage--success blockMessage--iconic">
		' . 'Thank you for renewing this purchase. The purchase details will be updated once the payment is processed.' . '
	</div>
';
	} else if ($__templater->method($__vars['purchase'], 'doesRequireRenewal', array())) {
		$__finalCompiled .= '
	<div class="blockMessage blockMessage--important">
		' . 'This product has expired. You may be missing out on the latest changes. You can renew the purchase by <a href="' . $__templater->fn('link', array('products/purchase/renew', $__vars['purchase'], ), true) . '" data-xf-click="overlay">clicking here</a>.' . '
	</div>
';
	}
	$__finalCompiled .= '

';
	if ($__vars['extrasPurchase']) {
		$__finalCompiled .= '
	<div class="blockMessage blockMessage--success blockMessage--iconic">
		' . 'Thank you for buying extras for this purchase. The purchase details will be updated once the payment is processed.' . '
	</div>
';
	}
	$__finalCompiled .= '

<div class="blockMessage">
	<div class="pairJustifier">
		<dl class="pairs pairs--rows pairs--rows--centered">
			<dt>' . 'Purchase date' . '</dt>
			<dd>
				' . $__templater->fn('date_dynamic', array($__vars['purchase']['purchase_date'], array(
	))) . '
			</dd>
		</dl>
		<dl class="pairs pairs--rows pairs--rows--centered">
			<dt>' . 'Expiry date' . '</dt>
			<dd>
				';
	if ($__vars['purchase']['expiry_date'] > 0) {
		$__finalCompiled .= '
					' . $__templater->fn('date_dynamic', array($__vars['purchase']['expiry_date'], array(
		))) . '
					';
	} else {
		$__finalCompiled .= '
					' . 'Never' . '
				';
	}
	$__finalCompiled .= '
			</dd>
		</dl>
		<dl class="pairs pairs--rows pairs--rows--centered">
			<dt>' . 'Purchase state' . '</dt>
			<dd>
				' . $__templater->escape($__vars['purchaseStates'][$__vars['purchase']['purchase_state']]['label']) . '
			</dd>
		</dl>
		<dl class="pairs pairs--rows pairs--rows--centered">
			<dt>' . 'Purchase price' . '</dt>
			<dd>
				' . $__templater->filter($__vars['purchase']['total_price'], array(array('xr_pm_currency', array($__vars['purchase']['purchase_currency'], )),), true) . '
			</dd>
		</dl>
		';
	if ($__templater->method($__vars['purchase']['Product'], 'isRenewable', array())) {
		$__finalCompiled .= '
			<dl class="pairs pairs--rows pairs--rows--centered">
				<dt>' . 'Price' . '</dt>
				<dd>
					' . $__templater->filter($__vars['purchase']['renew_price'], array(array('currency', array($__vars['purchase']['purchase_currency'], )),), true) . '
				</dd>
			</dl>
		';
	}
	$__finalCompiled .= '
		';
	if ($__templater->method($__vars['purchase'], 'hasCoupons', array())) {
		$__finalCompiled .= '
			<dl class="pairs pairs--rows pairs--rows--centered">
				<dt>' . 'Discount total' . '</dt>
				<dd>
					' . $__templater->filter($__vars['purchase']['discount_total'], array(array('currency', array($__vars['purchase']['purchase_currency'], )),), true) . '
				</dd>
			</dl>
		';
	}
	$__finalCompiled .= '
	</div>
</div>

';
	if ($__vars['purchase']['extras']) {
		$__finalCompiled .= '
	<div class="block">
		<div class="block-container">
			<h3 class="block-minorHeader">' . 'Purchased extras' . '</h3>
			<div class="block-body block-body--purchase">
				';
		if ($__templater->isTraversable($__vars['purchase']['extras'])) {
			foreach ($__vars['purchase']['extras'] AS $__vars['extraId'] => $__vars['extra']) {
				$__finalCompiled .= '
					';
				$__vars['fullExtra'] = $__vars['purchase']['Product']['extras'][$__vars['extraId']];
				$__finalCompiled .= '
					';
				if ($__vars['fullExtra']) {
					$__finalCompiled .= '
						<div class="block-row block-row--separated">
							<div class="contentRow">
								<div class="contentRow-main">
									<h2 class="contentRow-title">' . $__templater->escape($__vars['fullExtra']['extra_title']) . ' <span class="label label--primary">' . $__templater->filter($__vars['extra']['extra_price'], array(array('xr_pm_currency', array($__vars['purchase']['purchase_currency'], )),), true) . '</span></h2>
									<div class="contentRow-minor">' . $__templater->escape($__templater->method($__vars['purchase']['Product'], 'getExtraDescription', array($__vars['fullExtra'], ))) . '</div>
								</div>
							</div>
							';
					if (($__vars['fullExtra']['extra_reward'] == 'instructions') AND $__vars['fullExtra']['instructions']) {
						$__finalCompiled .= '
								<h2 class="block-textHeader block-textHeader--scaled">
									<span class="collapseTrigger collapseTrigger--block" data-xf-click="toggle" data-target="< :up :next">' . 'Click for usage instructions' . '</span>
								</h2>
								<article class="block-body block-body--collapsible">
									' . $__templater->fn('bb_code', array($__templater->method($__vars['fullExtra'], 'getInstructions', array($__vars['purchase']['Product']['product_title'], )), 'xr_pm_purchase_extra', $__vars['purchase'], ), true) . '
								</article>
							';
					}
					$__finalCompiled .= '
							';
					if (($__vars['fullExtra']['extra_reward'] == 'file') AND $__vars['fullExtra']['Extra']) {
						$__finalCompiled .= '
								<h2 class="block-textHeader block-textHeader--scaled">
									<span class="collapseTrigger collapseTrigger--block" data-xf-click="toggle" data-target="< :up :next">' . 'Click for your additional file' . '</span>
								</h2>
								<article class="block-body block-body--collapsible">
									' . $__templater->callMacro('xr_pm_attachment_macros', 'displayer', array(
							'attachment' => $__vars['fullExtra']['Extra'],
							'row' => false,
							'link' => 'attachments',
						), $__vars) . '
								</article>
							';
					}
					$__finalCompiled .= '
						</div>
					';
				}
				$__finalCompiled .= '
				';
			}
		}
		$__finalCompiled .= '
			</div>
		</div>
	</div>
';
	}
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['purchase'], 'canPurchaseExtras', array())) {
		$__finalCompiled .= '
	<div class="block">
		<div class="block-container">
			<h3 class="block-minorHeader">' . 'Available extras' . '</h3>
			<div class="block-body">
				';
		if ($__templater->isTraversable($__vars['purchase']['Product']['extras'])) {
			foreach ($__vars['purchase']['Product']['extras'] AS $__vars['extraId'] => $__vars['extra']) {
				$__finalCompiled .= '
					';
				if ($__templater->arrayKey($__templater->method($__vars['purchase'], 'getUnpurchasedExtras', array()), $__vars['extraId'])) {
					$__finalCompiled .= '
						<div class="block-row block-row--separated">
							<div class="contentRow">
								<div class="contentRow-main">
									<h2 class="contentRow-title">' . $__templater->escape($__vars['extra']['extra_title']) . ' <span class="label label--primary">' . $__templater->filter($__vars['extra']['extra_price'], array(array('xr_pm_currency', array($__vars['purchase']['purchase_currency'], )),), true) . '</span></h2>
									<div class="contentRow-minor">' . $__templater->escape($__templater->method($__vars['purchase']['Product'], 'getExtraDescription', array($__vars['extra'], ))) . '</div>
								</div>
								<div class="contentRow-extra">
									';
					$__compilerTemp2 = '';
					if ($__vars['extra']['extra_price']) {
						$__compilerTemp2 .= '
											' . 'Buy now' . '
										';
					} else {
						$__compilerTemp2 .= '
											' . 'Get FREE now!' . '
										';
					}
					$__finalCompiled .= $__templater->button('
										' . $__compilerTemp2 . '
									', array(
						'icon' => 'purchase',
						'href' => $__templater->fn('link', array('products/purchase/extras', $__vars['purchase'], array('extra_id' => $__vars['extraId'], ), ), false),
						'class' => '',
						'overlay' => 'true',
					), '', array(
					)) . '
								</div>
							</div>
						</div>
					';
				}
				$__finalCompiled .= '
				';
			}
		}
		$__finalCompiled .= '
			</div>
		</div>
	</div>
';
	}
	$__finalCompiled .= '

';
	$__templater->setPageParam('searchConstraints', array('Extensions' => array('search_type' => 'xr_pm_product', ), ));
	return $__finalCompiled;
});