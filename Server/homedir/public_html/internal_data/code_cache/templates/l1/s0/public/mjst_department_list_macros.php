<?php
// FROM HASH: c74849cccfc73cf20f7d7813f1e40c0f
return array('macros' => array('simple_list_block' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'departments' => '!',
		'selected' => 0,
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="block">
		<div class="block-container">
			<h3 class="block-header">' . 'Departments' . '</h3>
			<div class="block-body">
				';
	if (!$__templater->test($__vars['departments'], 'empty', array())) {
		$__finalCompiled .= '
					<ol class="categoryList is-active">
						';
		if ($__templater->isTraversable($__vars['departments'])) {
			foreach ($__vars['departments'] AS $__vars['id'] => $__vars['department']) {
				$__finalCompiled .= '
							';
				$__vars['isSelected'] = ($__vars['department']['department_id'] == $__vars['selected']);
				$__finalCompiled .= '
							<li class="categoryList-item">
								<div class="categoryList-itemRow">
									<a href="' . $__templater->fn('link', array('support-tickets/departments', $__vars['department'], ), true) . '" class="categoryList-link' . ($__vars['isSelected'] ? ' is-selected' : '') . '">
										' . $__templater->escape($__vars['department']['title']) . '
									</a>
									';
				if ($__templater->method($__vars['department'], 'canViewAnyTicket', array())) {
					$__finalCompiled .= '
										<span class="categoryList-label">
											<span class="label label--subtle label--smallest">' . $__templater->filter($__vars['department']['wait_reply_count'], array(array('number_short', array()),), true) . '/' . $__templater->filter($__vars['department']['active_count'], array(array('number_short', array()),), true) . '/' . $__templater->filter($__vars['department']['ticket_count'], array(array('number_short', array()),), true) . '</span>
										</span>
									';
				}
				$__finalCompiled .= '
								</div>
							</li>
						';
			}
		}
		$__finalCompiled .= '
					</ol>
				';
	} else {
		$__finalCompiled .= '
					<div class="block-row">' . 'N/A' . '</div>
				';
	}
	$__finalCompiled .= '
			</div>
		</div>
	</div>
';
	return $__finalCompiled;
},
'department' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'department' => '!',
		'chooseName' => '',
		'bonusInfo' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__templater->includeCss('mjst_department_list.less');
	$__finalCompiled .= '
	<div class="department department--ticketDepartment department--ticketDepartment' . $__templater->escape($__vars['department']['department_id']) . '">
		<div class="department-body">
			<div class="department-main js-departmentMain">
				';
	if ($__vars['chooseName']) {
		$__finalCompiled .= '
					' . $__templater->formCheckBox(array(
			'standalone' => 'true',
		), array(array(
			'labelclass' => 'u-pullRight',
			'class' => 'js-chooseItem',
			'name' => $__vars['chooseName'] . '[]',
			'value' => $__vars['department']['department_id'],
			'_type' => 'option',
		))) . '
				';
	}
	$__finalCompiled .= '

				<h3 class="department-title">
					<a href="' . $__templater->fn('link', array('support-tickets/departments', $__vars['department'], ), true) . '" data-xf-init="element-tooltip" data-shortcut="department-description">' . $__templater->escape($__vars['department']['title']) . '</a>
				</h3>
				';
	if ($__vars['department']['short_description']) {
		$__finalCompiled .= '
					<div class="department-description department-description--tooltip js-departmentDescTooltip">' . $__templater->filter($__vars['department']['short_description'], array(array('raw', array()),), true) . '</div>
				';
	}
	$__finalCompiled .= '
				';
	if ($__templater->method($__vars['department'], 'canViewAnyTicket', array())) {
		$__finalCompiled .= '
				<div class="department-meta">
					<div class="department-statsMeta">
						<dl class="pairs pairs--inline">
							<dt>' . 'Tickets' . '</dt>
							<dd>' . $__templater->filter($__vars['department']['ticket_count'], array(array('number', array()),), true) . '</dd>
						</dl>
					</div>
				</div>
				';
	}
	$__finalCompiled .= '

				';
	if (!$__templater->test($__vars['bonusInfo'], 'empty', array())) {
		$__finalCompiled .= '
					<div class="department-bonus">' . $__templater->escape($__vars['bonusInfo']) . '</div>
				';
	}
	$__finalCompiled .= '
			</div>

			<div class="department-stats department-stats--single">
				<dl class="pairs pairs--rows">
					<dt>' . 'Tickets' . '</dt>
					<dd>' . $__templater->filter($__vars['department']['ticket_count'], array(array('number', array()),), true) . '</dd>
				</dl>
			</div>
		</div>
	</div>

';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '

';
	return $__finalCompiled;
});