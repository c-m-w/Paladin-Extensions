<?php
// FROM HASH: ff13cd277903cff3d97db8701c961053
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Support department permissions');
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['departments'], 'empty', array())) {
		$__finalCompiled .= '
	<div class="block">
		<div class="block-outer">
			' . $__templater->callMacro('filter_macros', 'quick_filter', array(
			'key' => 'mjst-department',
			'class' => 'block-outer-opposite',
		), $__vars) . '
		</div>
		<div class="block-container">
			<div class="block-body">
				';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['departments'])) {
			foreach ($__vars['departments'] AS $__vars['department']) {
				$__compilerTemp1 .= '
						' . $__templater->dataRow(array(
					'rowclass' => ($__vars['customPermissions'][$__vars['department']['department_id']] ? 'dataList-row--custom' : ''),
				), array(array(
					'class' => 'dataList-cell--link dataList-cell--main',
					'hash' => $__vars['department']['department_id'],
					'_type' => 'cell',
					'html' => '
								<a href="' . $__templater->fn('link', array('permissions/mjst-departments', $__vars['department'], ), true) . '">
									<div class="dataList-mainRow">' . $__templater->escape($__vars['department']['title']) . '</div>
								</a>
							',
				),
				array(
					'href' => $__templater->fn('link', array('mjst-support/departments/edit', $__vars['department'], ), false),
					'_type' => 'action',
					'html' => 'Edit',
				))) . '
					';
			}
		}
		$__finalCompiled .= $__templater->dataList('
					' . $__compilerTemp1 . '
				', array(
		)) . '
			</div>
		</div>
	</div>
';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'No items have been created yet.' . '</div>
';
	}
	return $__finalCompiled;
});