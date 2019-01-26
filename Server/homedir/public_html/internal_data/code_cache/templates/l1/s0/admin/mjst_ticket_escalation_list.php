<?php
// FROM HASH: 1566b2dc4ebd2de8a99be126aa7aa4ed
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Escalations');
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('Add escalation', array(
		'href' => $__templater->fn('link', array('mjst-support/escalations/add', ), false),
		'icon' => 'add',
	), '', array(
	)) . '
');
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['ticketEscalations'], 'empty', array())) {
		$__finalCompiled .= '
	';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['ticketEscalations'])) {
			foreach ($__vars['ticketEscalations'] AS $__vars['ticketEscalation']) {
				$__compilerTemp1 .= '
						' . $__templater->dataRow(array(
				), array(array(
					'class' => 'dataList-cell--link dataList-cell--main',
					'hash' => $__vars['ticketEscalation']['ticket_escalation_id'],
					'_type' => 'cell',
					'html' => '
								<a href="' . $__templater->fn('link', array('mjst-support/escalations/edit', $__vars['ticketEscalation'], ), true) . '">
									<div class="dataList-mainRow">' . $__templater->escape($__vars['ticketEscalation']['title']) . '</div>
								</a>
							',
				),
				array(
					'href' => $__templater->fn('link', array('mjst-support/escalations/delete', $__vars['ticketEscalation'], ), false),
					'_type' => 'delete',
					'html' => '',
				))) . '
					';
			}
		}
		$__finalCompiled .= $__templater->form('
		<div class="block-outer">
			' . $__templater->callMacro('filter_macros', 'quick_filter', array(
			'key' => 'mjst-escalation',
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
			'action' => $__templater->fn('link', array('mjst-support/escalations/toggle', ), false),
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