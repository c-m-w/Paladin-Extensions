<?php
// FROM HASH: 30932e4e06858a98b16319554d5af1d1
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Resource prefixes');
	$__finalCompiled .= '

' . $__templater->includeTemplate('base_prefix_list', $__vars);
	return $__finalCompiled;
});