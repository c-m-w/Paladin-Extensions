<?php
// FROM HASH: 5d78e54c45ba3df37c2e0d731ad3e508
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->escape($__vars['category']['title']));
	$__templater->pageParams['pageNumber'] = $__vars['page'];
	$__finalCompiled .= '
';
	$__templater->pageParams['pageDescription'] = $__templater->preEscaped($__templater->filter($__vars['category']['description'], array(array('raw', array()),), true));
	$__templater->pageParams['pageDescriptionMeta'] = true;
	$__finalCompiled .= '

' . $__templater->callMacro('metadata_macros', 'canonical_url', array(
		'canonicalUrl' => $__templater->fn('link', array('canonical:products/categories', $__vars['category'], array('page' => $__vars['page'], ), ), false),
	), $__vars) . '

';
	$__templater->breadcrumbs($__templater->method($__vars['category'], 'getBreadcrumbs', array(false, )));
	$__finalCompiled .= '

<div class="block">
	<div class="block-outer">' . trim('
		' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => $__vars['total'],
		'link' => 'products/categories',
		'data' => $__vars['category'],
		'params' => $__vars['filters'],
		'wrapperclass' => 'block-outer-main',
		'perPage' => $__vars['perPage'],
	))) . '
	') . '</div>

	<div class="block-container">
		' . $__templater->callMacro('xr_pm_overview_macros', 'list_filter_bar', array(
		'filters' => $__vars['filters'],
		'baseLinkPath' => 'products',
		'creatorFilter' => $__vars['creatorFilter'],
	), $__vars) . '

		<div class="block-body">
			';
	if (!$__templater->test($__vars['products'], 'empty', array())) {
		$__finalCompiled .= '
				';
		if ($__templater->fn('property', array('xm_xrProductManagerOn', ), false) == '1') {
			$__finalCompiled .= '
	<div class="structItemContainer gridSection gridGroup">
		';
		} else {
			$__finalCompiled .= '
	<div class="structItemContainer">	
';
		}
		$__finalCompiled .= '
					';
		if ($__templater->isTraversable($__vars['products'])) {
			foreach ($__vars['products'] AS $__vars['product']) {
				$__finalCompiled .= '
						' . $__templater->callMacro('xr_pm_product_list_macros', 'product', array(
					'product' => $__vars['product'],
				), $__vars) . '
					';
			}
		}
		$__finalCompiled .= '
				</div>
			';
	} else if ($__vars['filters']) {
		$__finalCompiled .= '
				<div class="block-row">' . 'There are no products matching your filters.' . '</div>
			';
	} else {
		$__finalCompiled .= '
				<div class="block-row">' . 'No products have been created yet.' . '</div>
			';
	}
	$__finalCompiled .= '
		</div>
	</div>

	<div class="block-outer block-outer--after">
		' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => $__vars['total'],
		'link' => 'products/categories',
		'data' => $__vars['category'],
		'params' => $__vars['filters'],
		'wrapperclass' => 'block-outer-main',
		'perPage' => $__vars['perPage'],
	))) . '
		' . $__templater->fn('show_ignored', array(array(
		'wrapperclass' => 'block-outer-opposite',
	))) . '
	</div>
</div>

' . '

';
	$__templater->setPageParam('searchConstraints', array('Products' => array('search_type' => 'xr_pm_product', ), 'This category' => array('search_type' => 'xr_pm_product', 'c' => array('categories' => array($__vars['category']['category_id'], ), 'child_categories' => 1, ), ), ));
	return $__finalCompiled;
});