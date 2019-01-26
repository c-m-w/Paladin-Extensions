<?php
// FROM HASH: 3d672e087e541a03a2c8081aa2d7e9b8
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['noH1'] = true;
	$__finalCompiled .= '

';
	if ($__vars['product']['category_id']) {
		$__finalCompiled .= '
	';
		$__templater->breadcrumbs($__templater->method($__vars['product']['Category'], 'getBreadcrumbs', array()));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

' . $__templater->callMacro('xr_pm_product_page_macros', 'product_page_options', array(
		'category' => $__vars['product']['Category'],
		'product' => $__vars['product'],
	), $__vars) . '

' . $__templater->callMacro('xr_pm_product_wrapper_macros', 'header', array(
		'product' => $__vars['product'],
	), $__vars) . '

' . $__templater->callMacro('xr_pm_product_wrapper_macros', 'tabs', array(
		'product' => $__vars['product'],
		'selected' => $__vars['pageSelected'],
	), $__vars) . '

' . $__templater->filter($__vars['innerContent'], array(array('raw', array()),), true);
	return $__finalCompiled;
});