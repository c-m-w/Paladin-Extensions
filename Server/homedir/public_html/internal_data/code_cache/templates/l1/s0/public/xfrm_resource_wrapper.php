<?php
// FROM HASH: 4b572af9f8bb28ee6b330717749384c6
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['noH1'] = true;
	$__finalCompiled .= '

';
	$__templater->breadcrumbs($__templater->method($__vars['resource']['Category'], 'getBreadcrumbs', array()));
	$__finalCompiled .= '
';
	$__templater->includeCss('xfrm.less');
	$__finalCompiled .= '

' . $__templater->callMacro('xfrm_resource_page_macros', 'resource_page_options', array(
		'category' => $__vars['resource']['Category'],
		'resource' => $__vars['resource'],
	), $__vars) . '

' . $__templater->callMacro('xfrm_resource_wrapper_macros', 'header', array(
		'resource' => $__vars['resource'],
	), $__vars) . '

' . $__templater->callMacro('xfrm_resource_wrapper_macros', 'tabs', array(
		'resource' => $__vars['resource'],
		'selected' => $__vars['pageSelected'],
	), $__vars) . '

' . $__templater->callMacro('xfrm_resource_wrapper_macros', 'status', array(
		'resource' => $__vars['resource'],
	), $__vars) . '

' . $__templater->filter($__vars['innerContent'], array(array('raw', array()),), true);
	return $__finalCompiled;
});