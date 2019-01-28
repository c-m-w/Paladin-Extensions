<?php
// FROM HASH: 29fd5e80af1fa8ba921f2255d291b430
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->escape($__vars['product']['product_title']));
	$__finalCompiled .= '

';
	$__vars['descSnippet'] = $__templater->fn('snippet', array($__vars['product']['product_tag_line'], 250, array('stripBbCode' => true, ), ), false);
	$__finalCompiled .= '

' . $__templater->callMacro('metadata_macros', 'metadata', array(
		'description' => $__vars['descSnippet'],
		'shareUrl' => $__templater->fn('link', array('canonical:products', $__vars['product'], ), false),
		'canonicalUrl' => $__templater->fn('link', array('canonical:products', $__vars['product'], ), false),
	), $__vars) . '

';
	$__compilerTemp1 = '';
	if ($__vars['product']['has_thumbnail']) {
		$__compilerTemp1 .= '
			"image": "' . $__templater->escape($__templater->method($__vars['product'], 'getThumbnailUrl', array(true, ))) . '",
		';
	}
	$__templater->setPageParam('ldJsonHtml', '
	<script type="application/ld+json">
	{
		"@context": "https://schema.org",
		"@type": "Product",
		"@id": "' . $__templater->filter($__templater->fn('link', array('canonical:products', $__vars['product'], ), false), array(array('escape', array('json', )),), true) . '",
		"name": "' . $__templater->filter($__vars['product']['product_title'], array(array('escape', array('json', )),), true) . '",
		"description": "' . $__templater->filter($__vars['descSnippet'], array(array('escape', array('json', )),), true) . '",
		' . $__compilerTemp1 . '
		"releaseDate": "' . $__templater->filter($__templater->fn('date', array($__vars['product']['last_update'], 'c', ), false), array(array('escape', array('json', )),), true) . '"
	}
	</script>
');
	$__finalCompiled .= '

';
	$__compilerTemp2 = $__vars;
	$__compilerTemp2['pageSelected'] = 'overview';
	$__templater->wrapTemplate('xr_pm_product_wrapper', $__compilerTemp2);
	$__finalCompiled .= '

' . $__templater->callMacro('lightbox_macros', 'setup', array(
		'canViewAttachments' => $__templater->method($__vars['product'], 'canViewProductImages', array()),
	), $__vars) . '

<div class="blockMessage">
	<div class="pairJustifier">
		<dl class="pairs pairs--rows pairs--rows--centered">
			<dt>' . 'Release date' . '</dt>
			<dd>
				' . $__templater->fn('date_dynamic', array($__vars['product']['product_date'], array(
	))) . '
			</dd>
		</dl>
		<dl class="pairs pairs--rows pairs--rows--centered">
			<dt>' . 'Last update' . '</dt>
			<dd>
				' . $__templater->fn('date_dynamic', array($__vars['product']['last_update'], array(
	))) . '
			</dd>
		</dl>
		<dl class="pairs pairs--rows pairs--rows--centered">
			<dt>' . 'Price' . '</dt>
			<dd>
				' . $__templater->filter($__vars['product']['price'], array(array('xr_pm_currency', array($__vars['product']['currency'], )),), true) . '
			</dd>
		</dl>
		';
	if ($__vars['product']['duration']) {
		$__finalCompiled .= '
			<dl class="pairs pairs--rows pairs--rows--centered">
				<dt>' . 'Initial support' . '</dt>
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
			<dl class="pairs pairs--rows pairs--rows--centered">
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

<div class="block">
	<div class="block-container">
		<h3 class="block-minorHeader">' . 'Keywords' . '</h3>
		<div class="block-body">
			<ul class="listFeatures">
				';
	if ($__templater->isTraversable($__vars['product']['features'])) {
		foreach ($__vars['product']['features'] AS $__vars['feature']) {
			$__finalCompiled .= '
					<li>' . $__templater->escape($__vars['feature']) . '</li>
				';
		}
	}
	$__finalCompiled .= '
			</ul>
		</div>
	</div>
</div>

' . $__templater->callMacro('xr_pm_product_overview_macros', 'field_view', array(
		'group' => 'above_details',
		'product' => $__vars['product'],
	), $__vars) . '

<div class="block">
	<div class="block-container">
		<h3 class="block-minorHeader">' . 'Product details' . '</h3>
		<div class="block-body block-row lbContainer js-productDetails"
			data-xf-init="lightbox"
			data-lb-id="product-' . $__templater->escape($__vars['product']['product_id']) . '"
			data-lb-caption-desc="' . ($__vars['product']['User'] ? $__templater->escape($__vars['product']['User']['username']) : $__templater->escape($__vars['product']['username'])) . ' &middot; ' . $__templater->fn('date_time', array($__vars['product']['product_date'], ), true) . '">

			<article class="js-lbContainer">
				' . $__templater->fn('bb_code', array($__vars['product']['product_details'], 'xr_pm_product_details', $__vars['product'], ), true) . '

				';
	if ($__vars['product']['attach_count']) {
		$__finalCompiled .= '
					<div class="u-inputSpacer"></div>
					';
		$__compilerTemp3 = '';
		$__compilerTemp3 .= '
								';
		if ($__templater->isTraversable($__vars['product']['Images'])) {
			foreach ($__vars['product']['Images'] AS $__vars['image']) {
				if (!$__templater->method($__vars['product'], 'isAttachmentEmbedded', array($__vars['image'], ))) {
					$__compilerTemp3 .= '
									' . $__templater->callMacro('attachment_macros', 'attachment_list_item', array(
						'attachment' => $__vars['image'],
						'canView' => $__templater->method($__vars['product'], 'canViewProductImages', array()),
					), $__vars) . '
								';
				}
			}
		}
		$__compilerTemp3 .= '
							';
		if (strlen(trim($__compilerTemp3)) > 0) {
			$__finalCompiled .= '
						';
			$__templater->includeCss('attachments.less');
			$__finalCompiled .= '
						<ul class="attachmentList">
							' . $__compilerTemp3 . '
						</ul>
					';
		}
		$__finalCompiled .= '
				';
	}
	$__finalCompiled .= '
			</article>
		</div>
	</div>
</div>

' . $__templater->callMacro('xr_pm_product_overview_macros', 'field_view', array(
		'group' => 'below_details',
		'product' => $__vars['product'],
	), $__vars);
	return $__finalCompiled;
});