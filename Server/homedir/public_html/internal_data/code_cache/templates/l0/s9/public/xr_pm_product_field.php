<?php
// FROM HASH: ea8b29f832b9e0bc81a864229eeac7bc
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->escape($__vars['product']['product_title']) . ' - ' . $__templater->escape($__vars['fieldDefinition']['title']));
	$__finalCompiled .= '

';
	$__compilerTemp1 = $__vars;
	$__compilerTemp1['pageSelected'] = 'field-' . $__vars['fieldId'];
	$__templater->wrapTemplate('xr_pm_product_wrapper', $__compilerTemp1);
	$__finalCompiled .= '

<div class="block">
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