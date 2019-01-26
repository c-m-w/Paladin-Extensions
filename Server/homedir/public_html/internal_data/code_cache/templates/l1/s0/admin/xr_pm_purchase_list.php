<?php
// FROM HASH: 71f41d76ef12faa30c4aa1b630b21fcc
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Customer purchases');
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('Add new purchase', array(
		'icon' => 'add',
		'href' => $__templater->fn('link', array('product-manager/purchases/add', ), false),
	), '', array(
	)) . '
');
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['purchases'], 'empty', array())) {
		$__finalCompiled .= '
	<div class="block">
		<div class="block-outer">
			<div class="block-outer-main">
				' . $__templater->button('
					' . 'Sort by' . $__vars['xf']['language']['label_separator'] . ' ' . ($__templater->escape($__vars['sortOptions'][$__vars['order']]) ?: 'Purchase date') . '
				', array(
			'class' => 'button--link menuTrigger',
			'data-xf-click' => 'menu',
			'aria-expanded' => 'false',
			'aria-haspopup' => 'true',
		), '', array(
		)) . '

				<div class="menu" data-menu="menu" aria-hidden="true">
					<div class="menu-content">
						<h3 class="menu-header">' . 'Sort by' . $__vars['xf']['language']['ellipsis'] . '</h3>
						';
		if ($__templater->isTraversable($__vars['sortOptions'])) {
			foreach ($__vars['sortOptions'] AS $__vars['sortKey'] => $__vars['sortName']) {
				$__finalCompiled .= '
							<a href="' . $__templater->fn('link', array('product-manager/purchases', null, array('criteria' => $__vars['criteria'], 'order' => $__vars['sortKey'], ), ), true) . '"
								class="menu-linkRow ' . (($__vars['order'] == $__vars['sortKey']) ? 'is-selected' : '') . '">
								' . $__templater->escape($__vars['sortName']) . '
							</a>
						';
			}
		}
		$__finalCompiled .= '
					</div>
				</div>
			</div>
			' . $__templater->callMacro('filter_macros', 'quick_filter', array(
			'key' => 'xr_pm_purchases',
			'ajax' => $__templater->fn('link', array('product-manager/purchases', null, array('criteria' => $__vars['criteria'], 'order' => $__vars['order'], 'direction' => $__vars['direction'], ), ), false),
			'class' => 'block-outer-opposite',
		), $__vars) . '
		</div>
		<div class="block-container">
			<div class="block-body">
				';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['purchases'])) {
			foreach ($__vars['purchases'] AS $__vars['purchase']) {
				$__compilerTemp1 .= '
						';
				$__compilerTemp2 = '';
				if ($__vars['purchase']['old_cart_key']) {
					$__compilerTemp2 .= '
											<li><b>' . 'Cart key' . ':</b> ' . $__templater->escape($__vars['purchase']['old_cart_key']) . '</li>
										';
				}
				$__compilerTemp3 = '';
				if ($__vars['purchase']['parent_purchase_key']) {
					$__compilerTemp3 .= '
											<li><b>' . 'Parent key' . ':</b> ' . $__templater->escape($__vars['purchase']['parent_purchase_key']) . '</li>
										';
				}
				$__compilerTemp4 = '';
				if ($__vars['purchase']['license_name'] AND $__vars['purchase']['license_url']) {
					$__compilerTemp4 .= '
												' . $__templater->escape($__vars['purchase']['license_name']) . ' - ' . $__templater->escape($__vars['purchase']['license_url']) . '
											';
				} else {
					$__compilerTemp4 .= '
												' . 'N/A' . '
											';
				}
				$__compilerTemp1 .= $__templater->dataRow(array(
				), array(array(
					'class' => 'dataList-cell--min dataList-cell--image dataList-cell--imageMedium',
					'href' => $__templater->fn('link', array('product-manager/purchases/edit', $__vars['purchase'], ), false),
					'_type' => 'cell',
					'html' => '
								' . $__templater->fn('xr_pm_thumbnail', array($__vars['purchase']['Product'], '', 'xrpmThumbnail--dataList', ), true) . '
							',
				),
				array(
					'href' => $__templater->fn('link', array('product-manager/purchases/edit', $__vars['purchase'], ), false),
					'label' => $__templater->escape($__vars['purchase']['Product']['product_title']) . ' - ' . $__templater->escape($__vars['purchase']['purchase_key']),
					'explain' => '
									<ul class="listInline listInline--bullet">
										<li><b>' . 'User' . ':</b> ' . $__templater->fn('username_link', array($__vars['purchase']['User'], false, array(
					'href' => '',
					'defaultname' => $__vars['purchase']['username'],
				))) . '</li>
										' . $__compilerTemp2 . '
										' . $__compilerTemp3 . '
										<li><b>' . 'Product' . ':</b> ' . $__templater->escape($__vars['purchase']['Product']['product_title']) . '</li>
										<li><b>' . 'Licensed to' . ':</b>
											' . $__compilerTemp4 . '
										</li>
									</ul>
								',
					'_type' => 'main',
					'html' => '',
				))) . '
					';
			}
		}
		$__compilerTemp5 = '';
		if ($__vars['filter'] AND ($__vars['total'] > $__vars['perPage'])) {
			$__compilerTemp5 .= '
						' . $__templater->dataRow(array(
				'rowclass' => 'dataList-row--note dataList-row--noHover js-filterForceShow',
			), array(array(
				'colspan' => '3',
				'_type' => 'cell',
				'html' => 'There are more records matching your filter. Please be more specific.',
			))) . '
					';
		}
		$__finalCompiled .= $__templater->dataList('
					' . $__compilerTemp1 . '
					' . $__compilerTemp5 . '
				', array(
		)) . '
			</div>
			<div class="block-footer block-footer--split">
				<span class="block-footer-counter">' . $__templater->fn('display_totals', array($__vars['users'], $__vars['total'], ), true) . '</span>
			</div>
		</div>

		' . $__templater->fn('page_nav', array(array(
			'page' => $__vars['page'],
			'total' => $__vars['total'],
			'link' => 'product-manager/purchases',
			'params' => array('criteria' => $__vars['criteria'], 'order' => $__vars['order'], 'direction' => $__vars['direction'], ),
			'wrapperclass' => 'js-filterHide block-outer block-outer--after',
			'perPage' => $__vars['perPage'],
		))) . '
	</div>
';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'No records matched.' . '</div>
';
	}
	return $__finalCompiled;
});