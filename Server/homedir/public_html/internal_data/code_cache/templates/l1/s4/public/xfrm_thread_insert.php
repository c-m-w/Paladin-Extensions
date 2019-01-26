<?php
// FROM HASH: d0f7aebb236037b943a7eeddc2c86941
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['resource']) {
		$__finalCompiled .= '
	';
		$__vars['originalH1'] = $__templater->preEscaped($__templater->fn('page_h1', array('')));
		$__finalCompiled .= '
	';
		$__vars['originalDescription'] = $__templater->preEscaped($__templater->fn('page_description'));
		$__finalCompiled .= '

	';
		$__templater->pageParams['noH1'] = true;
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageDescription'] = $__templater->preEscaped('');
		$__templater->pageParams['pageDescriptionMeta'] = true;
		$__finalCompiled .= '

	' . $__templater->callMacro('xfrm_resource_wrapper_macros', 'header', array(
			'resource' => $__vars['resource'],
			'titleHtml' => $__vars['originalH1'],
			'metaHtml' => $__vars['originalDescription'],
		), $__vars) . '

	' . $__templater->callMacro('xfrm_resource_wrapper_macros', 'tabs', array(
			'resource' => $__vars['resource'],
			'selected' => 'discussion',
		), $__vars) . '
';
	}
	return $__finalCompiled;
});