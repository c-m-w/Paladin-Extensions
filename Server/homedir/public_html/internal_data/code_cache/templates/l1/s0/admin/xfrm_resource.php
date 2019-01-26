<?php
// FROM HASH: e6005a72195a774d42a700751a20f4b1
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Extensions');
	$__finalCompiled .= '

' . $__templater->callMacro('section_nav_macros', 'section_nav', array(
		'section' => 'xfrm',
	), $__vars);
	return $__finalCompiled;
});