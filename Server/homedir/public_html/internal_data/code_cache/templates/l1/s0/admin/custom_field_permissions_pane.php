<?php
// FROM HASH: aeee5679ca7cbaaa673ed89040db0313
return array('macros' => array('permission' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'field' => '!',
		'fieldName' => '!',
		'headerPhrase' => '!',
		'headerDescPhrase' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<h3 class="block-formSectionHeader">
		<span class="collapseTrigger collapseTrigger--block" data-xf-click="toggle" data-target="< :up:next">
			<span class="block-formSectionHeader-aligner">' . $__templater->escape($__vars['headerPhrase']) . '</span>
		</span>
	</h3>
	';
	$__vars['fieldEnable'] = (('cfp_' . $__vars['fieldName']) . '_enable');
	$__finalCompiled .= '
	';
	$__vars['fieldVal'] = (('cfp_' . $__vars['fieldName']) . '_val');
	$__finalCompiled .= '
	<div class="block-body block-body--collapsible">
		' . $__templater->formSelectRow(array(
		'name' => $__vars['fieldEnable'],
		'value' => $__vars['field'][$__vars['fieldEnable']],
	), array(array(
		'label' => 'No',
		'value' => '0',
		'_type' => 'option',
	),
	array(
		'label' => 'Yes',
		'value' => '1',
		'_type' => 'option',
	)), array(
		'label' => 'Enable',
		'explain' => $__templater->escape($__vars['headerDescPhrase']),
	)) . '

		';
	$__compilerTemp1 = array();
	$__compilerTemp2 = $__vars['field'][$__vars['fieldVal']];
	if ($__templater->isTraversable($__compilerTemp2)) {
		foreach ($__compilerTemp2 AS $__vars['list']) {
			$__compilerTemp1[] = array(
				'name' => $__vars['fieldVal'] . '[]',
				'value' => $__vars['list']['value'],
				'selected' => $__vars['list']['selected'],
				'label' => $__templater->escape($__vars['list']['label']),
				'hint' => '',
				'_type' => 'option',
			);
		}
	}
	$__finalCompiled .= $__templater->formCheckBoxRow(array(
	), $__compilerTemp1, array(
		'label' => 'Select Usergroups',
		'explain' => 'Select which usergroups can access this custom field
',
	)) . '
	</div>
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->isA($__vars['field'], '\\SV\\CustomFieldPerms\\IFieldPerm')) {
		$__finalCompiled .= '
	';
		if ($__templater->method($__vars['field'], 'hasCustomFieldPerm', array('v_input', ))) {
			$__finalCompiled .= '
		' . $__templater->callMacro(null, 'permission', array(
				'field' => $__vars['field'],
				'fieldName' => 'v_input',
				'headerPhrase' => 'Input permissions (Viewer)',
				'headerDescPhrase' => 'Activate these permissions to select which usergroups can access and edit this custom field ',
			), $__vars) . '
	';
		}
		$__finalCompiled .= '
	';
		if ($__templater->method($__vars['field'], 'hasCustomFieldPerm', array('v_output_pp', ))) {
			$__finalCompiled .= '
		' . $__templater->callMacro(null, 'permission', array(
				'field' => $__vars['field'],
				'fieldName' => 'v_output_pp',
				'headerPhrase' => 'Output permissions: Profile (Viewer)',
				'headerDescPhrase' => 'Activate these permissions to select which usergroups can view this custom field on profile pages',
			), $__vars) . '
	';
		}
		$__finalCompiled .= '
	';
		if ($__templater->method($__vars['field'], 'hasCustomFieldPerm', array('v_output_ui', ))) {
			$__finalCompiled .= '
		' . $__templater->callMacro(null, 'permission', array(
				'field' => $__vars['field'],
				'fieldName' => 'v_output_ui',
				'headerPhrase' => (($__templater->isA($__vars['field'], '\\XF\\Entity\\UserField')) ? 'Output permissions: User info (Viewer)' : 'Output permissions (Viewer)'),
				'headerDescPhrase' => (($__templater->isA($__vars['field'], '\\XF\\Entity\\UserField')) ? 'Activate these permissions to select which usergroups can view this custom field in message user info.' : 'Activate these permissions to select which usergroups can view this custom field'),
			), $__vars) . '
	';
		}
		$__finalCompiled .= '
	';
		if ($__templater->method($__vars['field'], 'hasCustomFieldPerm', array('c_output_ui', ))) {
			$__finalCompiled .= '
		' . $__templater->callMacro(null, 'permission', array(
				'field' => $__vars['field'],
				'fieldName' => 'c_output_ui',
				'headerPhrase' => 'Output permissions (Content)',
				'headerDescPhrase' => 'Activate these permissions to enable viewing this custom field based off content user\'s usergroups',
			), $__vars) . '
	';
		}
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	return $__finalCompiled;
});