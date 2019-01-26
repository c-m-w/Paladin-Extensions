<?php
// FROM HASH: 4be23ff8292a5e703c73fa6c38ec68d7
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Manage watched departments');
	$__finalCompiled .= '

';
	$__templater->includeCss('department_list.less');
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['watchedDepartments'], 'empty', array())) {
		$__finalCompiled .= '
	';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['departments'])) {
			foreach ($__vars['departments'] AS $__vars['id'] => $__vars['department']) {
				$__compilerTemp1 .= '
					';
				$__vars['departmentWatch'] = $__vars['watchedDepartments'][$__vars['department']['department_id']];
				$__compilerTemp1 .= '
					';
				if ($__vars['departmentWatch']) {
					$__compilerTemp1 .= '
						';
					$__compilerTemp2 = '';
					if ($__vars['departmentWatch']['notify_on'] == 'ticket') {
						$__compilerTemp2 .= '
									<li>' . 'New tickets' . '</li>
								';
					} else if ($__vars['departmentWatch']['notify_on'] == 'message') {
						$__compilerTemp2 .= '
									<li>' . 'New messages' . '</li>
								';
					}
					$__compilerTemp3 = '';
					if ($__vars['departmentWatch']['send_alert']) {
						$__compilerTemp3 .= '<li>' . 'Alerts' . '</li>';
					}
					$__compilerTemp4 = '';
					if ($__vars['departmentWatch']['send_email']) {
						$__compilerTemp4 .= '<li>' . 'Emails' . '</li>';
					}
					$__vars['bonusInfo'] = $__templater->preEscaped('
							<ul class="listInline listInline--bullet">
								' . $__compilerTemp2 . '
								' . $__compilerTemp3 . '
								' . $__compilerTemp4 . '
							</ul>
						');
					$__compilerTemp1 .= '
						' . $__templater->callMacro('mjst_department_list_macros', 'department', array(
						'department' => $__vars['department'],
						'chooseName' => 'department_ids',
						'bonusInfo' => $__vars['bonusInfo'],
					), $__vars) . '
					';
				}
				$__compilerTemp1 .= '
				';
			}
		}
		$__finalCompiled .= $__templater->form('

		<div class="block-outer">

			<div class="block-outer-opposite">
				' . $__templater->button('Manage watched departments', array(
			'class' => 'button--link menuTrigger',
			'data-xf-click' => 'menu',
			'aria-expanded' => 'false',
			'aria-haspopup' => 'true',
		), '', array(
		)) . '
				<div class="menu" data-menu="menu" aria-hidden="true">
					<div class="menu-content">
						<h3 class="menu-header">' . 'Manage watched departments' . '</h3>
						' . '
						<a href="' . $__templater->fn('link', array('watched/departments/manage', null, array('state' => 'watch_no_email', ), ), true) . '" data-xf-click="overlay" class="menu-linkRow">' . 'Disable email notification' . '</a>
						<a href="' . $__templater->fn('link', array('watched/departments/manage', null, array('state' => 'delete', ), ), true) . '" data-xf-click="overlay" class="menu-linkRow">' . 'Stop watching ticket departments' . '</a>
						' . '
					</div>
				</div>
			</div>
		</div>

		<div class="block-container">
			<div class="block-body">
				' . $__compilerTemp1 . '
			</div>
			<div class="block-footer block-footer--split">
				<span class="block-footer-counter"></span>
				<span class="block-footer-select">' . $__templater->formCheckBox(array(
			'standalone' => 'true',
		), array(array(
			'class' => 'input--inline',
			'check-all' => '< .block-container',
			'label' => 'Select all',
			'_type' => 'option',
		))) . '</span>
				<span class="block-footer-controls">
					' . $__templater->formSelect(array(
			'name' => 'action',
			'class' => 'input--inline',
		), array(array(
			'label' => 'With selected' . $__vars['xf']['language']['ellipsis'],
			'_type' => 'option',
		),
		array(
			'value' => 'email',
			'label' => 'Enable email notification',
			'_type' => 'option',
		),
		array(
			'value' => 'no_email',
			'label' => 'Disable email notification',
			'_type' => 'option',
		),
		array(
			'value' => 'alert',
			'label' => 'Enable alerts',
			'_type' => 'option',
		),
		array(
			'value' => 'no_alert',
			'label' => 'Disable alerts',
			'_type' => 'option',
		),
		array(
			'value' => 'delete',
			'label' => 'Stop watching',
			'_type' => 'option',
		))) . '
					' . $__templater->button('Go', array(
			'type' => 'submit',
		), '', array(
		)) . '
				</span>
			</div>
		</div>
	', array(
			'action' => $__templater->fn('link', array('watched/ticket-departments/update', ), false),
			'ajax' => 'true',
			'class' => 'block',
			'autocomplete' => 'off',
		)) . '
';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'You are not watching any departments.' . '</div>
';
	}
	return $__finalCompiled;
});