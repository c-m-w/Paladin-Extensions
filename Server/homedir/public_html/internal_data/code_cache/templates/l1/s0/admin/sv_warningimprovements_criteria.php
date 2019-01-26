<?php
// FROM HASH: a3a94f273e0058a3f0ab3b88965e6e18
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'user_criteria[warning_points_l][rule]',
		'value' => 'warning_points_l',
		'selected' => $__vars['criteria']['warning_points_l'],
		'label' => 'User has received at least X warnings points' . $__vars['xf']['language']['label_separator'],
		'_dependent' => array('
			<div class="inputGroup">
				' . $__templater->formNumberBox(array(
		'name' => 'user_criteria[warning_points_l][data][points]',
		'value' => $__vars['criteria']['warning_points_l']['points'],
		'size' => '5',
		'min' => '0',
		'step' => '1',
	)) . '
				<span class="inputGroup-text">
					' . 'Days' . $__vars['xf']['language']['label_separator'] . '
				</span>
				<span class="inputGroup" dir="ltr">
					' . $__templater->formNumberBox(array(
		'name' => 'user_criteria[warning_points_l][data][days]',
		'value' => $__vars['criteria']['warning_points_l']['days'],
		'size' => '5',
		'min' => '0',
		'step' => '1',
	)) . '
				</span>
			</div>

			' . $__templater->formCheckBox(array(
	), array(array(
		'name' => 'user_criteria[warning_points_l][data][expired]',
		'value' => '1',
		'selected' => $__vars['criteria']['warning_points_l']['expired'],
		'label' => 'Include Expired',
		'_type' => 'option',
	))) . '
		'),
		'_type' => 'option',
	),
	array(
		'name' => 'user_criteria[warning_points_m][rule]',
		'value' => 'warning_points_m',
		'selected' => $__vars['criteria']['warning_points_m'],
		'label' => 'User has received at most X warnings points' . $__vars['xf']['language']['label_separator'],
		'_dependent' => array('
			<div class="inputGroup">
				' . $__templater->formNumberBox(array(
		'name' => 'user_criteria[warning_points_m][data][points]',
		'value' => $__vars['criteria']['warning_points_m']['points'],
		'size' => '5',
		'min' => '0',
		'step' => '1',
	)) . '
				<span class="inputGroup-text">
					' . 'Days' . $__vars['xf']['language']['label_separator'] . '
				</span>
				<span class="inputGroup" dir="ltr">
					' . $__templater->formNumberBox(array(
		'name' => 'user_criteria[warning_points_m][data][days]',
		'value' => $__vars['criteria']['warning_points_m']['days'],
		'size' => '5',
		'min' => '0',
		'step' => '1',
	)) . '
				</span>
			</div>

			' . $__templater->formCheckBox(array(
	), array(array(
		'name' => 'user_criteria[warning_points_m][data][expired]',
		'value' => '1',
		'selected' => $__vars['criteria']['warning_points_m']['expired'],
		'label' => 'Include Expired',
		'_type' => 'option',
	))) . '
		'),
		'_type' => 'option',
	),
	array(
		'name' => 'user_criteria[sv_warning_minimum][rule]',
		'value' => 'sv_warning_minimum',
		'selected' => $__vars['criteria']['sv_warning_minimum'],
		'label' => 'User has received at least X warnings' . $__vars['xf']['language']['label_separator'],
		'_dependent' => array('
			<div class="inputGroup">
				' . $__templater->formNumberBox(array(
		'name' => 'user_criteria[sv_warning_minimum][data][points]',
		'value' => $__vars['criteria']['sv_warning_minimum']['points'],
		'size' => '5',
		'min' => '0',
		'step' => '1',
	)) . '
				<span class="inputGroup-text">
					' . 'Days' . $__vars['xf']['language']['label_separator'] . '
				</span>
				<span class="inputGroup" dir="ltr">
					' . $__templater->formNumberBox(array(
		'name' => 'user_criteria[sv_warning_minimum][data][days]',
		'value' => $__vars['criteria']['sv_warning_minimum']['days'],
		'size' => '5',
		'min' => '0',
		'step' => '1',
	)) . '
				</span>
			</div>

			' . $__templater->formCheckBox(array(
	), array(array(
		'name' => 'user_criteria[sv_warning_minimum][data][expired]',
		'value' => '1',
		'selected' => $__vars['criteria']['sv_warning_minimum']['expired'],
		'label' => 'Include Expired',
		'_type' => 'option',
	))) . '
		'),
		'_type' => 'option',
	),
	array(
		'name' => 'user_criteria[sv_warning_maximum][rule]',
		'value' => 'sv_warning_maximum',
		'selected' => $__vars['criteria']['sv_warning_maximum'],
		'label' => 'User has received at most X warnings' . $__vars['xf']['language']['label_separator'],
		'_dependent' => array('
			<div class="inputGroup">
				' . $__templater->formNumberBox(array(
		'name' => 'user_criteria[sv_warning_maximum][data][points]',
		'value' => $__vars['criteria']['sv_warning_maximum']['points'],
		'size' => '5',
		'min' => '0',
		'step' => '1',
	)) . '
				<span class="inputGroup-text">
					' . 'Days' . $__vars['xf']['language']['label_separator'] . '
				</span>
				<span class="inputGroup" dir="ltr">
					' . $__templater->formNumberBox(array(
		'name' => 'user_criteria[sv_warning_maximum][data][days]',
		'value' => $__vars['criteria']['sv_warning_maximum']['days'],
		'size' => '5',
		'min' => '0',
		'step' => '1',
	)) . '
				</span>
			</div>

			' . $__templater->formCheckBox(array(
	), array(array(
		'name' => 'user_criteria[sv_warning_maximum][data][expired]',
		'value' => '1',
		'selected' => $__vars['criteria']['sv_warning_maximum']['expired'],
		'label' => 'Include Expired',
		'_type' => 'option',
	))) . '
		'),
		'_type' => 'option',
	)), array(
		'label' => 'Warnings',
	));
	return $__finalCompiled;
});