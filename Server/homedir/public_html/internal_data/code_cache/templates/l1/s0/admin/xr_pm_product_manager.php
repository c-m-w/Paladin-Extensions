<?php
// FROM HASH: b22fa69e5886f0e7bf8fbfe0520e31fc
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Product manager');
	$__finalCompiled .= '

' . $__templater->callMacro('section_nav_macros', 'section_nav', array(
		'section' => 'xr_pm',
	), $__vars);
	return $__finalCompiled;
});