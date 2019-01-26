<?php
// FROM HASH: 24746de647d3a7d47066b84a0b50bd6a
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->fn('prefix', array('resource', $__vars['resource'], 'escaped', ), true) . $__templater->escape($__vars['resource']['title']) . ' - ' . 'Extra info');
	$__finalCompiled .= '

';
	$__compilerTemp1 = $__vars;
	$__compilerTemp1['pageSelected'] = 'field_' . $__vars['fieldId'];
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
			' . $__templater->callMacro('custom_fields_macros', 'custom_field_value', array(
		'definition' => $__vars['fieldDefinition'],
		'value' => $__vars['fieldValue'],
	), $__vars) . '
		</div>
	</div>
</div>';
	return $__finalCompiled;
});