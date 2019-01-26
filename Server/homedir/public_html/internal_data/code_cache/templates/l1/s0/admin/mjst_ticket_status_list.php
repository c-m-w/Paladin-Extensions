<?php
// FROM HASH: 70bc0d5fc2f671db661eaecffb8fb2f9
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Ticket statuses');
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('Add ticket status', array(
		'href' => $__templater->fn('link', array('mjst-support/statuses/add', ), false),
		'icon' => 'add',
	), '', array(
	)) . '
');
	$__finalCompiled .= '
';
	$__templater->inlineCss('
	.tsColor{
		display: inline-block;
		width: 30px;
		height: 15px;
	}
	.dataList-cell.dataList-cell--min.tsType{
		text-align: right;
	}
');
	$__finalCompiled .= '
';
	if (!$__templater->test($__vars['ticketStatuses'], 'empty', array())) {
		$__finalCompiled .= '
	';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['ticketStatuses'])) {
			foreach ($__vars['ticketStatuses'] AS $__vars['ticketStatus']) {
				$__compilerTemp1 .= '
						';
				$__compilerTemp2 = '';
				if ($__vars['ticketStatus']['group_waiting_reply']) {
					$__compilerTemp2 .= '
									<span class="tagItem">' . 'Group waiting reply' . '</span>
								';
				}
				$__compilerTemp3 = '';
				if ($__vars['ticketStatus']['group_active']) {
					$__compilerTemp3 .= '
									<span class="tagItem">' . 'Group active' . '</span>
								';
				}
				$__compilerTemp1 .= $__templater->dataRow(array(
				), array(array(
					'class' => 'dataList-cell--link dataList-cell--main',
					'hash' => $__vars['ticketStatus']['ticket_status_id'],
					'_type' => 'cell',
					'html' => '
								<a href="' . $__templater->fn('link', array('mjst-support/statuses/edit', $__vars['ticketStatus'], ), true) . '">
									<div class="dataList-mainRow">
										' . $__templater->escape($__vars['ticketStatus']['title']) . '
										<span class="dataList-hint" dir="auto">
											' . ($__templater->method($__vars['ticketStatus'], 'isDefault', array()) ? 'Default' : '') . '
										</span>
									</div>
								</a>
							',
				),
				array(
					'class' => 'dataList-cell--min tsType',
					'_type' => 'cell',
					'html' => '
								' . $__compilerTemp2 . '
								' . $__compilerTemp3 . '
							',
				),
				array(
					'class' => 'dataList-cell--min',
					'_type' => 'cell',
					'html' => '
								<span class="tsColor" style="background: ' . $__templater->escape($__vars['ticketStatus']['status_color']) . ';"></span>
							',
				),
				array(
					'href' => $__templater->fn('link', array('mjst-support/statuses/delete', $__vars['ticketStatus'], ), false),
					'_type' => 'delete',
					'html' => '',
				))) . '
					';
			}
		}
		$__finalCompiled .= $__templater->form('
		<div class="block-outer">
			' . $__templater->callMacro('filter_macros', 'quick_filter', array(
			'key' => 'mjst-ticket-status',
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
			'action' => $__templater->fn('link', array('mjst-support/statuses/toggle', ), false),
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