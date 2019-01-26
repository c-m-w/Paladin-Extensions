<?php
// FROM HASH: 884cc9bdc4a71d59880d692289608bb5
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Product versions');
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['groupedVersions'], 'empty', array())) {
		$__finalCompiled .= '
	';
		if ($__templater->isTraversable($__vars['products'])) {
			foreach ($__vars['products'] AS $__vars['productId'] => $__vars['productTitle']) {
				if (!$__templater->test($__vars['groupedVersions'][$__vars['productId']], 'empty', array())) {
					$__finalCompiled .= '
		<div class="block">
			<div class="block-container">
				<h3 class="block-header">
					<span class="collapseTrigger collapseTrigger--block ' . ((!$__templater->fn('is_toggled', array('_product-' . $__vars['productId'], ), false)) ? ' is-active' : '') . '" data-xf-click="toggle" data-target="< :up:next" data-xf-init="toggle-storage" data-storage-type="cookie" data-storage-key="_product-' . $__templater->escape($__vars['productId']) . '">
						<a href="' . $__templater->fn('link', array('product-manager/products/edit', array('product_id' => $__vars['productId'], 'product_title' => $__vars['productTitle'], ), ), true) . '">' . $__templater->escape($__vars['productTitle']) . '</a>
					</span>
					<span class="block-desc">
						<a href="' . $__templater->fn('link', array('product-manager/products/add-version', array('product_id' => $__vars['productId'], 'product_title' => $__vars['productTitle'], ), ), true) . '" data-xf-click="overlay">' . 'Add version' . '</a>
					</span>
				</h3>
				';
					$__compilerTemp1 = '';
					if ($__templater->isTraversable($__vars['groupedVersions'][$__vars['productId']])) {
						foreach ($__vars['groupedVersions'][$__vars['productId']] AS $__vars['version']) {
							$__compilerTemp1 .= '
						' . $__templater->dataRow(array(
								'label' => $__templater->escape($__vars['version']['version_string']),
								'href' => $__templater->fn('link', array('product-manager/products/versions/edit', $__vars['version'], ), false),
								'overlay' => 'true',
								'delete' => $__templater->fn('link', array('product-manager/products/versions/delete', $__vars['version'], ), false),
								'explain' => 'Release date' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->fn('date_dynamic', array($__vars['version']['release_date'], array(
							))),
							), array(array(
								'href' => $__templater->fn('link', array('product-manager/products/versions/download-log', $__vars['version'], ), false),
								'overlay' => 'true',
								'_type' => 'action',
								'html' => '
								' . 'Download log' . '
							',
							))) . '
					';
						}
					}
					$__finalCompiled .= $__templater->dataList('
					<tbody>
					' . $__compilerTemp1 . '
					</tbody>
				', array(
						'class' => 'block-body block-body--collapsible ' . ((!$__templater->fn('is_toggled', array('_product-' . $__vars['productId'], ), false)) ? ' is-active' : ''),
					)) . '
			</div>
		</div>
	';
				}
			}
		}
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'No items have been created yet.' . '</div>
';
	}
	return $__finalCompiled;
});