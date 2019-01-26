<?php
// FROM HASH: 4c1d626261f3ef2f359f5a32aecc606c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->escape($__vars['product']['product_title']) . ' - ' . 'Your purchases');
	$__finalCompiled .= '

';
	$__compilerTemp1 = $__vars;
	$__compilerTemp1['pageSelected'] = 'purchases';
	$__templater->wrapTemplate('xr_pm_product_wrapper', $__compilerTemp1);
	$__finalCompiled .= '

' . $__templater->callMacro('xr_pm_product_purchases', 'purchase_list', array(
		'purchaseStates' => $__vars['purchaseStates'],
		'purchasesGrouped' => $__vars['purchasesGrouped'],
	), $__vars);
	return $__finalCompiled;
});