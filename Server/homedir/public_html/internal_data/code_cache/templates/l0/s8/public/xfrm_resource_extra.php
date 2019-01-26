<?php
// FROM HASH: 2ae40deff5c01d663d37bcf9db8b6795
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->fn('prefix', array('resource', $__vars['resource'], 'escaped', ), true) . $__templater->escape($__vars['resource']['title']) . ' - ' . 'Extra info');
	$__finalCompiled .= '

';
	$__compilerTemp1 = $__vars;
	$__compilerTemp1['pageSelected'] = 'extra';
	$__templater->wrapTemplate('xfrm_resource_wrapper', $__compilerTemp1);
	$__finalCompiled .= '

<div class="block">
	';
	$__compilerTemp2 = '';
	$__compilerTemp2 .= '
				' . $__templater->callMacro('xfrm_resource_wrapper_macros', 'action_buttons', array(
		'resource' => $__vars['resource'],
	), $__vars) . '
			';
	if (strlen(trim($__compilerTemp2)) > 0) {
		$__finalCompiled .= '
		<div class="block-outer">
			<div class="block-outer-opposite">
			' . $__compilerTemp2 . '
			</div>
		</div>
	';
	}
	$__finalCompiled .= '

	<div class="block-container">
		<div class="block-body block-row">
			' . $__templater->callMacro('custom_fields_macros', 'custom_fields_view', array(
		'type' => 'resources',
		'group' => 'extra_tab',
		'onlyInclude' => $__vars['category']['field_cache'],
		'set' => $__vars['resource']['custom_fields'],
	), $__vars) . '
		</div>
	</div>
</div>';
	return $__finalCompiled;
});