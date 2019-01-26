<?php
// FROM HASH: 5bd287bef3e4d0ef11bda79b76d355e9
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Extensions');
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('Add product', array(
		'href' => $__templater->fn('link', array('product-manager/products/add', ), false),
		'icon' => 'add',
	), '', array(
	)) . '
');
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if (!$__templater->test($__vars['products'], 'empty', array())) {
		$__compilerTemp1 .= '
			<div class="block-body">
				';
		$__compilerTemp2 = '';
		if ($__templater->isTraversable($__vars['products'])) {
			foreach ($__vars['products'] AS $__vars['product']) {
				$__compilerTemp2 .= '
						' . $__templater->dataRow(array(
				), array(array(
					'class' => 'dataList-cell--min dataList-cell--image dataList-cell--imageMedium',
					'href' => $__templater->fn('link', array('product-manager/products/edit', $__vars['product'], ), false),
					'_type' => 'cell',
					'html' => '
								' . $__templater->fn('xr_pm_thumbnail', array($__vars['product'], null, 'xrpmThumbnail--dataList', ), true) . '
							',
				),
				array(
					'href' => $__templater->fn('link', array('product-manager/products/edit', $__vars['product'], ), false),
					'class' => 'dataList-cell--main',
					'_type' => 'cell',
					'html' => '
								<div class="dataList-mainRow">' . $__templater->escape($__vars['product']['product_title']) . '</div>
								<div class="dataList-subRow">
									<ul class="listInline listInline--bullet">
										<li>' . 'Release date' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->fn('date_dynamic', array($__vars['product']['product_date'], array(
				))) . '</li>
										<li>' . 'Last update' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->fn('date_dynamic', array($__vars['product']['last_update'], array(
				))) . '</li>
									</ul>
								</div>
							',
				),
				array(
					'name' => 'active[' . $__vars['product']['product_id'] . ']',
					'selected' => $__vars['product']['active'],
					'class' => 'dataList-cell--separated',
					'submit' => 'true',
					'tooltip' => 'Enable / disable \'' . $__vars['product']['product_title'] . '\'',
					'_type' => 'toggle',
					'html' => '',
				),
				array(
					'label' => '&#8226;&#8226;&#8226;',
					'_type' => 'popup',
					'html' => '
								<div class="menu" data-menu="menu" aria-hidden="true" data-menu-builder="dataList">
									<div class="menu-content">
										<h3 class="menu-header">' . 'More options' . '</h3>
										<a href="' . $__templater->fn('link', array('product-manager/products/add-version', $__vars['product'], ), true) . '" class="menu-linkRow" data-xf-click="overlay">' . 'Release new version' . '</a>
										<a href="' . $__templater->fn('link', array('product-manager/products/edit-thumbnail', $__vars['product'], ), true) . '" class="menu-linkRow" data-xf-click="overlay">' . 'Add/edit thumbnail' . '</a>
									</div>
								</div>
							',
				),
				array(
					'href' => $__templater->fn('link', array('product-manager/products/delete', $__vars['product'], ), false),
					'_type' => 'delete',
					'html' => '',
				))) . '
					';
			}
		}
		$__compilerTemp1 .= $__templater->dataList('
					' . $__compilerTemp2 . '
				', array(
		)) . '
			</div>
			<div class="block-footer block-footer--split">
				<span class="block-footer-counter">' . $__templater->fn('display_totals', array($__vars['products'], $__vars['total'], ), true) . '</span>
			</div>
		';
	} else {
		$__compilerTemp1 .= '
			<div class="block-body block-row">' . 'No results found.' . '</div>
		';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		' . $__compilerTemp1 . '
	</div>
', array(
		'action' => $__templater->fn('link', array('product-manager/products/toggle', ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});