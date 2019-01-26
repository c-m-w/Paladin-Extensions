<?php
// FROM HASH: d2abeec82ac7e916abfcbcb64e18b7f5
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->escape($__vars['product']['product_title']) . ' - ' . 'Terms and conditions');
	$__finalCompiled .= '

';
	$__compilerTemp1 = $__vars;
	$__compilerTemp1['pageSelected'] = 'terms';
	$__templater->wrapTemplate('xr_pm_product_wrapper', $__compilerTemp1);
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		<div class="block-body block-row">
			' . $__templater->fn('bb_code', array($__vars['terms'], 'xr_pm_product_terms', $__vars['product'], ), true) . '
		</div>
	</div>
</div>';
	return $__finalCompiled;
});