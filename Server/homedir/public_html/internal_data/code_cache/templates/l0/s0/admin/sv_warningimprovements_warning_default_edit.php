<?php
// FROM HASH: f1d8b4ca748895b0a458cf12adcc5c88
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['default'], 'isInsert', array())) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Create New Warning Defaults');
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit Warning Default' . $__vars['xf']['language']['label_separator'] . ' ' . 'Points threshold' . ' ' . $__templater->escape($__vars['default']['threshold_points']));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('', array(
		'href' => $__templater->fn('link', array('warnings/default/delete', null, array('warning_default_id' => $__vars['default']['warning_default_id'], ), ), false),
		'icon' => 'delete',
		'data-xf-click' => 'overlay',
	), '', array(
	)) . '
');
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formNumberBoxRow(array(
		'name' => 'threshold_points',
		'value' => $__vars['default']['threshold_points'],
		'min' => '1',
	), array(
		'label' => 'Points threshold',
		'explain' => 'This warning default will only be applied when a user is issued a warning with their total warning points above this points threshold. ',
	)) . '

			' . $__templater->formRadioRow(array(
		'name' => 'expiry_type_base',
	), array(array(
		'value' => 'never',
		'selected' => $__vars['default']['expiry_type'] == 'never',
		'label' => 'Never',
		'_type' => 'option',
	),
	array(
		'value' => 'other',
		'selected' => $__vars['default']['expiry_type'] != 'never',
		'label' => 'After time' . $__vars['xf']['language']['label_separator'],
		'_dependent' => array('
						<div class="inputGroup">
							' . $__templater->formNumberBox(array(
		'name' => 'expiry_extension',
		'value' => $__vars['default']['expiry_extension'],
		'min' => '0',
	)) . '
							<span class="inputGroup-splitter"></span>
							' . $__templater->formSelect(array(
		'name' => 'expiry_type',
		'value' => $__vars['default']['expiry_type'],
		'class' => 'input--inline',
	), array(array(
		'value' => 'days',
		'label' => 'Never',
		'_type' => 'option',
	),
	array(
		'value' => 'days',
		'label' => 'Days',
		'_type' => 'option',
	),
	array(
		'value' => 'weeks',
		'label' => 'Weeks',
		'_type' => 'option',
	),
	array(
		'value' => 'months',
		'label' => 'Months',
		'_type' => 'option',
	),
	array(
		'value' => 'years',
		'label' => 'Years',
		'_type' => 'option',
	))) . '
						</div>
					'),
		'_type' => 'option',
	)), array(
		'label' => 'Expiry Extension',
		'explain' => 'The duration to add to the warning\'s default expiry period when above the threshold',
	)) . '

			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'active',
		'value' => '1',
		'selected' => $__vars['default']['active'],
		'label' => 'Is active',
		'_type' => 'option',
	)), array(
	)) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'sticky' => 'true',
		'icon' => 'save',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('warnings/default/save', null, array('warning_default_id' => $__vars['default']['warning_default_id'], ), ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});