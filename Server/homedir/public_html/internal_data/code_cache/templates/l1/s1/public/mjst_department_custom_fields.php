<?php
// FROM HASH: 2c8119a7dfcb36419996aea8c118d985
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<hr class="formRowSep" />
' . $__templater->callMacro('custom_fields_macros', 'custom_fields_edit', array(
		'type' => 'tickets',
		'set' => $__vars['ticket']['custom_fields'],
		'editMode' => $__templater->method($__vars['ticket'], 'getFieldEditMode', array()),
		'rowType' => $__vars['rowType'],
		'onlyInclude' => $__vars['department']['field_cache'],
	), $__vars);
	return $__finalCompiled;
});