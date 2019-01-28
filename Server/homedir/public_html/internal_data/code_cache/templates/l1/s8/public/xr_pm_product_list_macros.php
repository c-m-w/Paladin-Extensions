<?php
// FROM HASH: cfed9aadd8bb746186cc80d187ad2fdd
return array('macros' => array('product' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'product' => '!',
		'category' => null,
	), $__arguments, $__vars);
	$__finalCompiled .= '

	';
	$__templater->includeCss('structured_list.less');
	$__finalCompiled .= '

	';
	if ($__templater->fn('property', array('xm_xrProductManagerOn', ), false) == '1') {
		$__finalCompiled .= '
	<div class="structItem structItem--product js-productListItem-' . $__templater->escape($__vars['product']['product_id']) . ' gridCol gridSpan" data-author="' . ($__templater->escape($__vars['product']['User']['username']) ?: $__templater->escape($__vars['product']['username'])) . '">
	';
	} else {
		$__finalCompiled .= '
	<div class="structItem structItem--product js-productListItem-' . $__templater->escape($__vars['product']['product_id']) . '" data-author="' . ($__templater->escape($__vars['product']['User']['username']) ?: $__templater->escape($__vars['product']['username'])) . '">	
';
	}
	$__finalCompiled .= '	
		<div class="structItem-cell structItem-cell--productThumb">
			<div class="structItem-iconContainer">
				';
	if ($__templater->fn('property', array('xm_xrProductManagerOn', ), false) == '1') {
		$__finalCompiled .= '
				';
		if ($__templater->fn('property', array('xm_productRibbonPrice', ), false) == '1') {
			$__finalCompiled .= '
				<div class="price">' . $__templater->filter($__vars['product']['price'], array(array('xr_pm_currency', array($__vars['product']['currency'], )),), true) . '</div>
				';
		}
		$__finalCompiled .= '
				';
	}
	$__finalCompiled .= '
				';
	if ($__templater->fn('property', array('xm_xrProductManagerOn', ), false) == '1') {
		$__finalCompiled .= '
		<div class="' . $__templater->fn('property', array('xm_xrImageHoverEffect', ), true) . '">
			<div class="img-box">
				' . $__templater->fn('xr_pm_thumbnail', array($__vars['product'], $__templater->fn('link', array('products', $__vars['product'], ), false), ), true) . '
			</div>
			<div class="info-box">
				<div class="info-content">
					<h3><a href="' . $__templater->fn('link', array('products', $__vars['product'], ), true) . '" data-tp-primary="on">' . $__templater->escape($__vars['product']['product_title']) . '</a> <span class="u-muted">' . $__templater->escape($__vars['product']['Version']['version_string']) . '</span></h3>
					<span class="separator"></span>
					<p>' . $__templater->escape($__vars['product']['product_tag_line']) . '</p>
					<span class="separator"></span>
					<div class="smallest-content">
					';
		if ($__templater->fn('property', array('xm_productCustomFieldsButtons', ), false) == '1') {
			$__finalCompiled .= '
						';
			$__compilerTemp1 = $__templater->method($__vars['xf']['app'], 'getCustomFields', array('xr_pm_products', 'tab_link', ));
			if ($__templater->isTraversable($__compilerTemp1)) {
				foreach ($__compilerTemp1 AS $__vars['fieldId'] => $__vars['fieldDefinition']) {
					$__finalCompiled .= '
							';
					if ($__templater->method($__vars['fieldDefinition'], 'hasValue', array($__vars['product']['custom_fields'][$__vars['fieldDefinition']['field_id']], ))) {
						$__finalCompiled .= '
								' . $__templater->button('<span class="linkText">' . $__templater->escape($__vars['fieldDefinition']['title']) . '</span>
								', array(
							'icon' => 'preview',
							'class' => 'button--product Tooltip',
							'target' => $__templater->fn('property', array('xm_xrCustomFieldsButtonsOpen', ), false),
							'href' => $__vars['product']['custom_fields'][$__vars['fieldDefinition']['field_id']],
							'data-xf-init' => 'tooltip',
							'title' => $__vars['fieldDefinition']['title'],
							'rel' => 'nofollow',
						), '', array(
						)) . '	
							';
					}
					$__finalCompiled .= '
						';
				}
			}
			$__finalCompiled .= '
					';
		}
		$__finalCompiled .= '
					';
		if ($__templater->method($__vars['product'], 'canPurchase', array())) {
			$__finalCompiled .= '
						';
			$__compilerTemp2 = '';
			if ($__vars['product']['price']) {
				$__compilerTemp2 .= '
								<span class="linkText">' . 'Buy now' . '</span>
							';
			} else {
				$__compilerTemp2 .= '
								<span class="linkText">' . 'Get FREE now!' . '</span>
							';
			}
			$__finalCompiled .= $__templater->button('
							' . $__compilerTemp2 . '
						', array(
				'icon' => 'purchase',
				'class' => 'button--product button--cta Tooltip',
				'href' => $__templater->fn('link', array('products/buy', $__vars['product'], ), false),
				'data-xf-click' => 'overlay',
				'data-xf-init' => 'tooltip',
				'title' => $__templater->filter('Buy now', array(array('for_attr', array()),), false),
				'rel' => 'nofollow',
			), '', array(
			)) . '
					';
		}
		$__finalCompiled .= '					
					</div>
				</div>
			</div>
		</div>
	';
	} else {
		$__finalCompiled .= '
		' . $__templater->fn('xr_pm_thumbnail', array($__vars['product'], $__templater->fn('link', array('products', $__vars['product'], ), false), ), true) . '		
';
	}
	$__finalCompiled .= '
			</div>
		</div>
		<div class="structItem-cell structItem-cell--main structItem-cell--productMain" data-xf-init="touch-proxy">
			<div class="structItem-title">
				<a href="' . $__templater->fn('link', array('products', $__vars['product'], ), true) . '" data-tp-primary="on">' . $__templater->escape($__vars['product']['product_title']) . '</a>
				<span class="u-muted">' . $__templater->escape($__vars['product']['Version']['version_string']) . '</span>
				<span class="label label--primary label--smallest">' . $__templater->filter($__vars['product']['price'], array(array('xr_pm_currency', array($__vars['product']['currency'], )),), true) . '</span>
			</div>

			<div class="structItem-minor">
				';
	$__compilerTemp3 = '';
	$__compilerTemp3 .= '
							';
	if ($__vars['extraInfo']) {
		$__compilerTemp3 .= '
								<li>' . $__templater->escape($__vars['extraInfo']) . '</li>
							';
	}
	$__compilerTemp3 .= '
						';
	if (strlen(trim($__compilerTemp3)) > 0) {
		$__finalCompiled .= '
					<ul class="structItem-extraInfo">
						' . $__compilerTemp3 . '
					</ul>
				';
	}
	$__finalCompiled .= '

				<ul class="structItem-parts">
					<li>' . $__templater->fn('username_link', array($__vars['product']['User'], false, array(
		'defaultname' => $__vars['product']['username'],
	))) . '</li>
					<li class="structItem-startDate"><a href="' . $__templater->fn('link', array('products', $__vars['product'], ), true) . '" rel="nofollow">' . $__templater->fn('date_dynamic', array($__vars['product']['product_date'], array(
	))) . '</a></li>
					';
	if ($__vars['product']['category_id']) {
		$__finalCompiled .= '
						<li><a href="' . $__templater->fn('link', array('products/categories', $__vars['product']['Category'], ), true) . '">' . $__templater->escape($__vars['product']['Category']['title']) . '</a></li>
					';
	}
	$__finalCompiled .= '
				</ul>
			</div>

			<div class="structItem-productInfo">
				' . $__templater->escape($__vars['product']['product_tag_line']) . '
				';
	if ($__vars['product']['features']) {
		$__finalCompiled .= '
					<ul>
						';
		$__vars['i'] = 0;
		if ($__templater->isTraversable($__vars['product']['features'])) {
			foreach ($__vars['product']['features'] AS $__vars['feature']) {
				$__vars['i']++;
				$__finalCompiled .= '
							';
				if ($__vars['i'] <= 4) {
					$__finalCompiled .= '
								<li>' . $__templater->escape($__vars['feature']) . '</li>
							';
				}
				$__finalCompiled .= '
						';
			}
		}
		$__finalCompiled .= '
					</ul>
				';
	}
	$__finalCompiled .= '
			</div>
		</div>
		<div class="structItem-cell structItem-cell--productMeta">
			';
	if ($__templater->method($__vars['product'], 'canPurchase', array())) {
		$__finalCompiled .= '
				';
		$__compilerTemp4 = '';
		if ($__vars['product']['price']) {
			$__compilerTemp4 .= '
						' . 'Buy now' . '
					';
		} else {
			$__compilerTemp4 .= '
						' . 'Get FREE now!' . '
					';
		}
		$__finalCompiled .= $__templater->button('
					' . $__compilerTemp4 . '
				', array(
			'icon' => 'purchase',
			'class' => 'button--product button--cta',
			'href' => $__templater->fn('link', array('products/buy', $__vars['product'], ), false),
			'data-xf-click' => 'overlay',
		), '', array(
		)) . '
			';
	}
	$__finalCompiled .= '
			' . $__templater->button('More info', array(
		'class' => 'button--product',
		'href' => $__templater->fn('link', array('products', $__vars['product'], ), false),
	), '', array(
	)) . '
			<dl class="pairs pairs--justified structItem-minor">
				<dt>' . 'Updated' . '</dt>
				<dd><a href="' . $__templater->fn('link', array('products/changelog', $__vars['product'], ), true) . '" class="u-concealed">' . $__templater->fn('date_dynamic', array($__vars['product']['last_update'], array(
	))) . '</a></dd>
			</dl>
			';
	if ($__vars['product']['duration']) {
		$__finalCompiled .= '
				<dl class="pairs pairs--justified structItem-minor">
					<dt>' . 'License duration' . '</dt>
					<dd>
						';
		if ($__vars['product']['duration_unit'] == 'days') {
			$__finalCompiled .= '
							' . '' . $__templater->escape($__vars['product']['duration']) . ' days' . '
						';
		} else if ($__vars['product']['duration_unit'] == 'months') {
			$__finalCompiled .= '
							' . '' . $__templater->escape($__vars['product']['duration']) . ' months' . '
						';
		} else if ($__vars['product']['duration_unit'] == 'years') {
			$__finalCompiled .= '
							' . '' . $__templater->escape($__vars['product']['duration']) . ' years' . '
						';
		}
		$__finalCompiled .= '
					</dd>
				</dl>
			';
	}
	$__finalCompiled .= '
			';
	if ($__templater->method($__vars['product'], 'isRenewable', array())) {
		$__finalCompiled .= '
				<dl class="pairs pairs--justified structItem-minor">
					<dt>' . 'Price' . '</dt>
					<dd>
						' . $__templater->filter($__vars['product']['renew_price'], array(array('currency', array($__vars['product']['currency'], )),), true) . '
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

	return $__finalCompiled;
});