<?php
// FROM HASH: 29d79187df070a001649b1a3f22b850c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->isA($__vars['field'], '\\SV\\CustomFieldPerms\\IFieldPerm')) {
		$__finalCompiled .= '
<h3 class="block-formSectionHeader">
	<span class="collapseTrigger collapseTrigger--block" data-xf-click="toggle" data-target="< :up:next">
		<span class="block-formSectionHeader-aligner">' . 'Custom field permissions' . '</span>
	</span>
</h3>

<div class="block-body block-body--collapsible">
    <fieldset>
        <h4 class="block-formSectionHeader">' . 'Input permissions' . '</h4>
        <p class="explain">' . 'Activate these permissions to select which usergroups can access and edit this custom field ' . '</p>

        ' . $__templater->formSelectRow(array(
			'name' => 'sedo_perms_input_enable',
			'value' => $__vars['field']['sedo_perms_input_enable'],
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
			'explain' => 'Do you want to enable permissions based on below settings?
',
		)) . '

        ';
		$__compilerTemp1 = array();
		if ($__templater->isTraversable($__vars['field']['sedo_perms_input_val'])) {
			foreach ($__vars['field']['sedo_perms_input_val'] AS $__vars['list']) {
				$__compilerTemp1[] = array(
					'name' => 'sedo_perms_input_val[]',
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
	</fieldset>

	<fieldset>
        <h4 class="block-formSectionHeader">' . 'Output permissions on profile pages' . '</h4>
        <p class="explain">' . 'Activate these permissions to select which usergroups can access this custom field on profile pages' . '</p>

        ' . $__templater->formSelectRow(array(
			'name' => 'sedo_perms_output_pp_enable',
			'value' => $__vars['field']['sedo_perms_output_pp_enable'],
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
			'explain' => 'Do you want to enable permissions based on below settings?
',
		)) . '

        ';
		$__compilerTemp2 = array();
		if ($__templater->isTraversable($__vars['field']['sedo_perms_output_pp_val'])) {
			foreach ($__vars['field']['sedo_perms_output_pp_val'] AS $__vars['list']) {
				$__compilerTemp2[] = array(
					'name' => 'sedo_perms_output_pp_val[]',
					'value' => $__vars['list']['value'],
					'selected' => $__vars['list']['selected'],
					'label' => $__templater->escape($__vars['list']['label']),
					'hint' => '',
					'_type' => 'option',
				);
			}
		}
		$__finalCompiled .= $__templater->formCheckBoxRow(array(
		), $__compilerTemp2, array(
			'label' => 'Select Usergroups',
			'explain' => 'Select which usergroups can access this custom field
',
		)) . '
	</fieldset>

	<fieldset>
        <h4 class="block-formSectionHeader">' . 'Output permissions in message user info

' . '</h4>
        <p class="explain">' . 'Activate these permissions to select which usergroups can access this custom field in message user info.' . '</p>

        ' . $__templater->formSelectRow(array(
			'name' => 'sedo_perms_output_ui_enable',
			'value' => $__vars['field']['sedo_perms_output_ui_enable'],
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
			'explain' => 'Do you want to enable permissions based on below settings?
',
		)) . '

        ';
		$__compilerTemp3 = array();
		if ($__templater->isTraversable($__vars['field']['sedo_perms_output_ui_val'])) {
			foreach ($__vars['field']['sedo_perms_output_ui_val'] AS $__vars['list']) {
				$__compilerTemp3[] = array(
					'name' => 'sedo_perms_output_ui_val[]',
					'value' => $__vars['list']['value'],
					'selected' => $__vars['list']['selected'],
					'label' => $__templater->escape($__vars['list']['label']),
					'hint' => '',
					'_type' => 'option',
				);
			}
		}
		$__finalCompiled .= $__templater->formCheckBoxRow(array(
		), $__compilerTemp3, array(
			'label' => 'Select Usergroups',
			'explain' => 'Select which usergroups can access this custom field
',
		)) . '
    </fieldset>

</div>
';
	}
	return $__finalCompiled;
});