<?php
// FROM HASH: 350fca2371045ca2c9524f9b2cdedb70
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Warnings' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['user']['username']));
	$__finalCompiled .= '

';
	$__templater->breadcrumb($__templater->preEscaped($__templater->escape($__vars['user']['username'])), $__templater->fn('link', array('members', $__vars['user'], ), false), array(
	));
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		<div class="block-body">
			';
	$__compilerTemp1 = '';
	if ($__templater->isTraversable($__vars['user']['warning_actions'])) {
		foreach ($__vars['user']['warning_actions'] AS $__vars['warningAction']) {
			$__compilerTemp1 .= '
					';
			$__compilerTemp2 = '';
			if ($__vars['warningAction']['effective_expiry_date']) {
				$__compilerTemp2 .= '
								' . $__templater->fn('date_dynamic', array($__vars['warningAction']['effective_expiry_date'], array(
				))) . '
							';
			} else if ($__vars['warningAction']['is_permanent']) {
				$__compilerTemp2 .= '
								' . 'Permanent' . '
							';
			} else {
				$__compilerTemp2 .= '
								' . 'N/A' . '
							';
			}
			$__compilerTemp1 .= $__templater->dataRow(array(
				'rowclass' => ($__vars['warningAction']['is_expired'] ? 'dataList-row--disabled' : ''),
			), array(array(
				'href' => $__templater->fn('link', array('members/warning-actions', $__vars['warningAction']['User'], array('warning_action_id' => $__vars['warningAction']['user_change_temp_id'], ), ), false),
				'overlay' => 'true',
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['warningAction']['name']),
			),
			array(
				'href' => $__templater->fn('link', array('members/warning-actions', $__vars['warningAction']['User'], array('warning_action_id' => $__vars['warningAction']['user_change_temp_id'], ), ), false),
				'overlay' => 'true',
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['warningAction']['result']),
			),
			array(
				'href' => $__templater->fn('link', array('members/warning-actions', $__vars['warningAction']['User'], array('warning_action_id' => $__vars['warningAction']['user_change_temp_id'], ), ), false),
				'overlay' => 'true',
				'_type' => 'cell',
				'html' => '
							' . $__compilerTemp2 . '
						',
			),
			array(
				'href' => $__templater->fn('link', array('members/warning-actions', $__vars['warningAction']['User'], array('warning_action_id' => $__vars['warningAction']['user_change_temp_id'], ), ), false),
				'overlay' => 'true',
				'_type' => 'cell',
				'html' => 'View',
			))) . '
				';
		}
	}
	$__finalCompiled .= $__templater->dataList('
				' . $__templater->dataRow(array(
		'rowtype' => 'header',
	), array(array(
		'width' => '20%',
		'_type' => 'cell',
		'html' => 'Action Type',
	),
	array(
		'_type' => 'cell',
		'html' => 'Result',
	),
	array(
		'_type' => 'cell',
		'html' => 'Warning Action Expiry',
	),
	array(
		'_type' => 'cell',
		'html' => '&nbsp;',
	))) . '
				' . $__compilerTemp1 . '
			', array(
		'data-xf-init' => 'responsive-data-list',
	)) . '
		</div>
		<div class="block-footer">
			<ul class="listInline listInline--bullet">
				<li>' . 'Total warning actions' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->filter($__templater->fn('count', array($__vars['user']['warning_actions'], ), false), array(array('number', array()),), true) . '</li>
			</ul>
		</div>
	</div>
</div>';
	return $__finalCompiled;
});