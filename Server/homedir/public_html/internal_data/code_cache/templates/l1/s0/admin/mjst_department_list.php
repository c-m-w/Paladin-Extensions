<?php
// FROM HASH: f6d2b0e611055e1b71f344f6306480c3
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Departments');
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('Add department', array(
		'href' => $__templater->fn('link', array('mjst-support/departments/add', ), false),
		'icon' => 'add',
	), '', array(
	)) . '
');
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['departments'], 'empty', array())) {
		$__finalCompiled .= '
	';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['departments'])) {
			foreach ($__vars['departments'] AS $__vars['department']) {
				$__compilerTemp1 .= '
						' . $__templater->dataRow(array(
				), array(array(
					'class' => 'dataList-cell--link dataList-cell--main',
					'hash' => $__vars['department']['department_id'],
					'_type' => 'cell',
					'html' => '
								<a href="' . $__templater->fn('link', array('mjst-support/departments/edit', $__vars['department'], ), true) . '">
									<div class="dataList-mainRow">' . $__templater->escape($__vars['department']['title']) . '</div>
								</a>
							',
				),
				array(
					'class' => ($__vars['customPermissions'][$__vars['department']['department_id']] ? 'dataList-cell--highlighted' : ''),
					'href' => $__templater->fn('link', array('mjst-support/departments/permissions', $__vars['department'], ), false),
					'_type' => 'action',
					'html' => '
								' . 'Permissions' . '
							',
				),
				array(
					'href' => $__templater->fn('link', array('mjst-support/departments/members', $__vars['department'], ), false),
					'_type' => 'action',
					'html' => '
								' . 'Members' . '
							',
				),
				array(
					'href' => $__templater->fn('link', array('mjst-support/departments/delete', $__vars['department'], ), false),
					'_type' => 'delete',
					'html' => '',
				))) . '
					';
			}
		}
		$__finalCompiled .= $__templater->form('
		<div class="block-outer">
			' . $__templater->callMacro('filter_macros', 'quick_filter', array(
			'key' => 'mjst-department',
			'class' => 'block-outer-opposite',
		), $__vars) . '
		</div>
		<div class="block-container">
			<div class="block-body">
				' . $__templater->dataList('
					' . $__compilerTemp1 . '
				', array(
		)) . '
			</div>
		</div>
	', array(
			'action' => $__templater->fn('link', array('mjst-support/departments/toggle', ), false),
			'class' => 'block',
			'ajax' => 'true',
		)) . '
';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'No items have been created yet.' . '</div>
';
	}
	return $__finalCompiled;
});