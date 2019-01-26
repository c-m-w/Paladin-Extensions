<?php
// FROM HASH: 8ab0767d0bb8c5d155a354093701d37c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Products');
	$__finalCompiled .= '

' . $__templater->callMacro('metadata_macros', 'canonical_url', array(
		'canonicalUrl' => $__templater->fn('link', array('canonical:products', null, array('page' => $__vars['page'], ), ), false),
	), $__vars) . '

<div class="block">
	<div class="block-outer">' . trim('
		' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => $__vars['total'],
		'link' => 'products',
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
		'link' => 'products',
		'params' => $__vars['filters'],
		'wrapperclass' => 'block-outer-main',
		'perPage' => $__vars['perPage'],
	))) . '
		' . $__templater->fn('show_ignored', array(array(
		'wrapperclass' => 'block-outer-opposite',
	))) . '
	</div>
</div>

';
	$__templater->setPageParam('sideNavTitle', 'Product categories');
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__vars['categoryTree']) {
		$__compilerTemp1 .= '
		<div class="block">
			<div class="block-container">
				<h3 class="block-header">' . 'Product categories' . '</h3>
				<div class="block-body">
					';
		if ($__templater->method($__vars['categoryTree'], 'count', array())) {
			$__compilerTemp1 .= '
						' . $__templater->callMacro('xr_pm_category_list_macros', 'category_list', array(
				'selected' => $__vars['selected'],
				'pathToSelected' => $__templater->method($__vars['categoryTree'], 'getPathTo', array($__vars['selected'], )),
				'children' => $__vars['categoryTree'],
				'extras' => $__vars['categoryExtras'],
				'isActive' => true,
			), $__vars) . '
					';
		} else {
			$__compilerTemp1 .= '
						<div class="block-row">' . 'N/A' . '</div>
					';
		}
		$__compilerTemp1 .= '
				</div>
			</div>
		</div>
	';
	}
	$__templater->modifySideNavHtml('xrpmSideNav', '
	' . $__compilerTemp1 . '
', 'replace');
	$__finalCompiled .= '

';
	$__templater->setPageParam('searchConstraints', array('Products' => array('search_type' => 'xr_pm_product', ), ));
	return $__finalCompiled;
});