<?php
// FROM HASH: 314184ab38be504685f1523b83968a5f
return array('macros' => array('header' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'product' => '!',
		'showMeta' => true,
	), $__arguments, $__vars);
	$__finalCompiled .= '

	';
	$__templater->setPageParam('searchConstraints', array('Extensions' => array('search_type' => 'xr_pm_product', ), 'This category' => array('search_type' => 'xr_pm_product', 'c' => array('categories' => array($__vars['product']['Category']['category_id'], ), 'child_categories' => 1, ), ), ));
	$__finalCompiled .= '

	';
	$__compilerTemp1 = '';
	if ($__templater->method($__vars['product'], 'canDownload', array())) {
		$__compilerTemp1 .= '
							' . $__templater->button('Download', array(
			'icon' => 'download',
			'class' => 'button--product button--cta',
			'href' => $__templater->fn('link', array('products/download', $__vars['product'], ), false),
			'data-xf-click' => 'overlay',
		), '', array(
		)) . '
						';
	}
	$__compilerTemp2 = '';
	if ($__templater->method($__vars['product'], 'canPurchase', array())) {
		$__compilerTemp2 .= '
							';
		$__compilerTemp3 = '';
		if ($__vars['product']['price']) {
			$__compilerTemp3 .= '
									' . 'Buy now' . '
								';
		} else {
			$__compilerTemp3 .= '
									' . 'Get FREE now!' . '
								';
		}
		$__compilerTemp2 .= $__templater->button('
								' . $__compilerTemp3 . '
							', array(
			'icon' => 'purchase',
			'class' => 'button--product button--cta',
			'href' => $__templater->fn('link', array('products/buy', $__vars['product'], ), false),
			'data-xf-click' => 'overlay',
		), '', array(
		)) . '
						';
	}
	$__compilerTemp4 = '';
	if ($__vars['showMeta']) {
		$__compilerTemp4 .= '
					<div class="p-description">
						<ul class="listInline listInline--bullet">
							<li>
								<i class="fa fa-user" aria-hidden="true" title="' . $__templater->filter('Author', array(array('for_attr', array()),), true) . '"></i>
								<span class="u-srOnly">' . 'Author' . '</span>

								' . $__templater->fn('username_link', array($__vars['product']['User'], false, array(
			'defaultname' => $__vars['product']['username'],
			'class' => 'u-concealed',
		))) . '
							</li>
							<li>
								<i class="fa fa-clock-o" aria-hidden="true" title="' . $__templater->filter('First release', array(array('for_attr', array()),), true) . '"></i>
								<span class="u-srOnly">' . 'First release' . '</span>

								<a href="' . $__templater->fn('link', array('products', $__vars['product'], ), true) . '" class="u-concealed">' . $__templater->fn('date_dynamic', array($__vars['product']['product_date'], array(
		))) . '</a>
							</li>
						</ul>
					</div>
				';
	}
	$__templater->setPageParam('headerHtml', '
		<div class="contentRow contentRow--alignMiddle contentRow--hideFigureNarrow">
			<span class="contentRow-figure">
				' . $__templater->fn('xr_pm_thumbnail', array($__vars['product'], '', 'xrpmThumbnail--small', ), true) . '
			</span>
			<div class="contentRow-main">
				<div class="p-title">
					<h1 class="p-title-value">
						' . $__templater->escape($__vars['product']['product_title']) . '
						<span class="u-muted">' . $__templater->escape($__vars['product']['Version']['version_string']) . '</span>
					</h1>
					<div class="p-title-pageAction">
						' . $__compilerTemp1 . '
						' . $__compilerTemp2 . '
					</div>
				</div>
				' . $__compilerTemp4 . '
			</div>
		</div>
	');
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'tabs' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'product' => '!',
		'selected' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="tabs tabs--standalone tabs--product">
		<div class="hScroller" data-xf-init="h-scroller">
			<span class="hScroller-scroll">
				<a class="tabs-tab ' . (($__vars['selected'] == 'overview') ? 'is-active' : '') . '" href="' . $__templater->fn('link', array('products', $__vars['product'], ), true) . '">' . 'Overview' . '</a>
				';
	$__compilerTemp1 = '';
	$__compilerTemp1 .= '
						';
	$__compilerTemp2 = $__templater->method($__vars['xf']['app'], 'getCustomFields', array('xr_pm_products', 'tab_content', ));
	if ($__templater->isTraversable($__compilerTemp2)) {
		foreach ($__compilerTemp2 AS $__vars['fieldId'] => $__vars['fieldDefinition']) {
			$__compilerTemp1 .= '
							';
			if ($__templater->method($__vars['fieldDefinition'], 'hasValue', array($__vars['product']['custom_fields'][$__vars['fieldDefinition']['field_id']], ))) {
				$__compilerTemp1 .= '
								<a class="tabs-tab ' . (($__vars['selected'] == ('field-' . $__vars['fieldId'])) ? 'is-active' : '') . '" href="' . $__templater->fn('link', array('products/field', $__vars['product'], array('field' => $__vars['fieldId'], ), ), true) . '">
									' . $__templater->escape($__vars['fieldDefinition']['title']) . '
								</a>
							';
			}
			$__compilerTemp1 .= '
						';
		}
	}
	$__compilerTemp1 .= '
					';
	if (strlen(trim($__compilerTemp1)) > 0) {
		$__finalCompiled .= '
					' . $__compilerTemp1 . '
				';
	}
	$__finalCompiled .= '
				<a class="tabs-tab ' . (($__vars['selected'] == 'updates') ? 'is-active' : '') . '" href="' . $__templater->fn('link', array('products/updates', $__vars['product'], ), true) . '">' . 'Updates' . '</a>
				';
	if ($__vars['xf']['visitor']['user_id']) {
		$__finalCompiled .= '
					<a class="tabs-tab ' . (($__vars['selected'] == 'purchases') ? 'is-active' : '') . '" href="' . $__templater->fn('link', array('products/product-purchases', $__vars['product'], ), true) . '">' . 'Your purchases' . '</a>
				';
	}
	$__finalCompiled .= '
				<a class="tabs-tab ' . (($__vars['selected'] == 'terms') ? 'is-active' : '') . '" href="' . $__templater->fn('link', array('products/terms', $__vars['product'], ), true) . '">' . 'Terms and conditions' . '</a>
			</span>
		</div>
		';
	$__compilerTemp3 = '';
	$__compilerTemp3 .= '
					';
	$__compilerTemp4 = $__templater->method($__vars['xf']['app'], 'getCustomFields', array('xr_pm_products', 'tab_link', ));
	if ($__templater->isTraversable($__compilerTemp4)) {
		foreach ($__compilerTemp4 AS $__vars['fieldId'] => $__vars['fieldDefinition']) {
			$__compilerTemp3 .= '
						';
			if ($__templater->method($__vars['fieldDefinition'], 'hasValue', array($__vars['product']['custom_fields'][$__vars['fieldDefinition']['field_id']], ))) {
				$__compilerTemp3 .= '
							<a class="tabs-tab" target="_blank" href="' . $__templater->escape($__vars['product']['custom_fields'][$__vars['fieldDefinition']['field_id']]) . '">
								<i class="fa fa-external-link-square"></i> ' . $__templater->escape($__vars['fieldDefinition']['title']) . '
							</a>
						';
			}
			$__compilerTemp3 .= '
					';
		}
	}
	$__compilerTemp3 .= '
				';
	if (strlen(trim($__compilerTemp3)) > 0) {
		$__finalCompiled .= '
			<div class="tabs-extra">
				' . $__compilerTemp3 . '
			</div>
		';
	}
	$__finalCompiled .= '
	</div>
';
	return $__finalCompiled;
},
'sidebar' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'product' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__templater->modifySidebarHtml('productInfo', '
		<div class="block">
			<div class="block-container">
				<h3 class="block-minorHeader">' . 'Product information' . '</h3>
				<div class="block-body block-row">
					<dl class="pairs pairs--justified">
						<dt>' . 'Release date' . '</dt>
						<dd>
							' . $__templater->fn('date_dynamic', array($__vars['product']['product_date'], array(
	))) . '
						</dd>
					</dl>
					<dl class="pairs pairs--justified">
						<dt>' . 'Last update' . '</dt>
						<dd>
							' . $__templater->fn('date_dynamic', array($__vars['product']['last_update'], array(
	))) . '
						</dd>
					</dl>
				</div>
			</div>
		</div>
	', 'replace');
	$__finalCompiled .= '

	';
	$__compilerTemp1 = '';
	if ($__vars['product']['renew_price']) {
		$__compilerTemp1 .= '
						<dl class="pairs pairs--justified">
							<dt>' . 'Price' . '</dt>
							<dd>
								' . $__templater->filter($__vars['product']['renew_price'], array(array('currency', array($__vars['product']['currency'], )),), true) . '
							</dd>
						</dl>
					';
	}
	$__compilerTemp2 = '';
	if ($__vars['product']['duration']) {
		$__compilerTemp2 .= '
						<dl class="pairs pairs--justified">
							<dt>' . 'Initial support' . '</dt>
							<dd>
								';
		if ($__vars['product']['duration_unit'] == 'days') {
			$__compilerTemp2 .= '
									' . '' . $__templater->escape($__vars['product']['duration']) . ' days' . '
								';
		} else if ($__vars['product']['duration_unit'] == 'months') {
			$__compilerTemp2 .= '
									' . '' . $__templater->escape($__vars['product']['duration']) . ' months' . '
								';
		} else if ($__vars['product']['duration_unit'] == 'years') {
			$__compilerTemp2 .= '
									' . '' . $__templater->escape($__vars['product']['duration']) . ' years' . '
								';
		}
		$__compilerTemp2 .= '
							</dd>
						</dl>
					';
	}
	$__templater->modifySidebarHtml('licenseInfo', '
		<div class="block">
			<div class="block-container">
				<h3 class="block-minorHeader">' . 'License information' . '</h3>
				<div class="block-body block-row">
					<dl class="pairs pairs--justified">
						<dt>' . 'Price' . '</dt>
						<dd>
							' . $__templater->filter($__vars['product']['price'], array(array('xr_pm_currency', array($__vars['product']['currency'], )),), true) . '
						</dd>
					</dl>
					' . $__compilerTemp1 . '
					' . $__compilerTemp2 . '
				</div>
			</div>
		</div>
	', 'replace');
	$__finalCompiled .= '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '

' . '

';
	return $__finalCompiled;
});