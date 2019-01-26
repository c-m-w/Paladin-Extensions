<?php
// FROM HASH: a43d479af29d8ee5f914a3f5275dc71e
return array('macros' => array('field_view' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'group' => '!',
		'product' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__compilerTemp1 = $__templater->method($__vars['xf']['app'], 'getCustomFields', array('xr_pm_products', $__vars['group'], ));
	if ($__templater->isTraversable($__compilerTemp1)) {
		foreach ($__compilerTemp1 AS $__vars['fieldId'] => $__vars['fieldDefinition']) {
			$__finalCompiled .= '
		';
			$__compilerTemp2 = '';
			$__compilerTemp2 .= '
							';
			if ($__templater->method($__vars['fieldDefinition'], 'hasValue', array($__vars['product']['custom_fields'][$__vars['fieldDefinition']['field_id']], ))) {
				$__compilerTemp2 .= '
								' . $__templater->callMacro('custom_fields_macros', 'custom_field_value', array(
					'definition' => $__vars['fieldDefinition'],
					'value' => $__vars['product']['custom_fields'][$__vars['fieldDefinition']['field_id']],
				), $__vars) . '
							';
			}
			$__compilerTemp2 .= '
						';
			if (strlen(trim($__compilerTemp2)) > 0) {
				$__finalCompiled .= '
			<div class="block">
				<div class="block-container">
					<div class="block-minorHeader">
						' . $__templater->escape($__vars['fieldDefinition']['title']) . '
					</div>
					<div class="block-body block-row">
						' . $__compilerTemp2 . '
					</div>
				</div>
			</div>
		';
			}
			$__finalCompiled .= '
	';
		}
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';

	return $__finalCompiled;
});