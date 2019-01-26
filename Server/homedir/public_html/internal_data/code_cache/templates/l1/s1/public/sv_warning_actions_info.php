<?php
// FROM HASH: 073a7c18a19d84e58beff5a0356404c4
return array('macros' => array('expire' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'user' => '!',
		'warningAction' => '!',
		'redirect' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	' . $__templater->form('
		' . $__templater->formRadioRow(array(
		'name' => 'expire',
		'value' => 'now',
	), array(array(
		'value' => 'now',
		'label' => 'Expire now',
		'_type' => 'option',
	),
	array(
		'value' => 'future',
		'label' => 'Expire in' . $__vars['xf']['language']['label_separator'],
		'_dependent' => array('
					<div class="inputGroup">
						' . $__templater->formNumberBox(array(
		'name' => 'expiry_value',
		'value' => '1',
		'min' => '0',
	)) . '
						<span class="inputGroup-splitter"></span>
						' . $__templater->formSelect(array(
		'name' => 'expiry_unit',
		'value' => 'days',
		'class' => 'input--inline',
	), array(array(
		'value' => 'hours',
		'label' => 'Hours',
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
	)) . '

		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
		'value' => 'Update Warning Action',
	), array(
	)) . '

		' . $__templater->fn('redirect_input', array($__vars['redirect'], null, true)) . '
	', array(
		'action' => $__templater->fn('link', array('members/warning-actions/expire', $__vars['user'], array('warning_action_id' => $__vars['warningAction']['user_change_temp_id'], ), ), false),
	)) . '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Warning action for ' . $__templater->escape($__vars['user']['username']) . '');
	$__finalCompiled .= '

<div class="form block">
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formRow('
				' . $__templater->escape($__vars['warningAction']['name']) . ', ' . $__templater->fn('date_time', array($__vars['warningAction']['create_date'], ), true) . '
			', array(
		'label' => 'Action Type',
	)) . '

			' . $__templater->formRow('
				' . $__templater->escape($__vars['warningAction']['result']) . '
			', array(
		'label' => 'Result',
	)) . '

			';
	$__compilerTemp1 = '';
	if ($__vars['warningAction']['effective_expiry_date']) {
		$__compilerTemp1 .= '
					' . $__templater->fn('date_dynamic', array($__vars['warningAction']['effective_expiry_date'], array(
		))) . '
				';
	} else if ($__vars['warningAction']['is_permanent']) {
		$__compilerTemp1 .= '
					' . 'Permanent' . '
				';
	} else {
		$__compilerTemp1 .= '
					' . 'N/A' . '
				';
	}
	$__finalCompiled .= $__templater->formRow('
				' . $__compilerTemp1 . '
			', array(
		'label' => 'Warning Action Expiry',
	)) . '
		</div>

		';
	if ($__templater->method($__vars['warningAction'], 'canEditWarningAction', array())) {
		$__finalCompiled .= '
			<h2 class="block-tabHeader tabs" data-xf-init="tabs" role="tablist">
				<a class="tabs-tab is-active" role="tab" tabindex="0" aria-controls="' . $__templater->fn('unique_id', array('warning-action', ), true) . '">' . 'Update Warning Action' . '</a>
			</h2>
			<ul class="tabPanes">
				<li role="tabpanel" id="' . $__templater->fn('unique_id', array('warning-action', ), true) . '">
					' . $__templater->callMacro(null, 'expire', array(
			'user' => $__vars['user'],
			'warningAction' => $__vars['warningAction'],
		), $__vars) . '
				</li>
			</ul>
		';
	}
	$__finalCompiled .= '
	</div>
</div>

';
	return $__finalCompiled;
});