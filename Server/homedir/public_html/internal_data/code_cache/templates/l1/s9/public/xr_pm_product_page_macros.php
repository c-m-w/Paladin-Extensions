<?php
// FROM HASH: f76d1171b25ba188c4a9617a3c61b852
return array('macros' => array('product_page_options' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'category' => '!',
		'product' => null,
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__templater->setPageParam('productCategory', $__vars['category']);
	$__finalCompiled .= '

	' . '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';

	return $__finalCompiled;
});