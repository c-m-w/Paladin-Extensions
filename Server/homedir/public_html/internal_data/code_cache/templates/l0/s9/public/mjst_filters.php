<?php
// FROM HASH: 476e919335984f711d08622b266566c1
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__compilerTemp1 = '';
	if ((($__vars['xf']['visitor']['user_id'] AND $__vars['xf']['visitor']['mjst_department_ids']) OR $__templater->method($__vars['xf']['visitor'], 'hasPermission', array('mjstSupport', 'viewAnyTicket', )))) {
		$__compilerTemp1 .= '
		<div class="menu-row menu-row--separated">
			' . 'Owner name' . $__vars['xf']['language']['label_separator'] . '
			<div class="u-inputSpacer">
				' . $__templater->formTextBox(array(
			'name' => 'owner',
			'value' => ($__vars['ownerFilter'] ? $__vars['ownerFilter']['username'] : ''),
			'ac' => 'single',
		)) . '
			</div>
		</div>
		<div class="menu-row menu-row--separated">
			' . 'Assigned to' . $__vars['xf']['language']['label_separator'] . '
			<div class="u-inputSpacer">
				' . $__templater->formTextBox(array(
			'name' => 'assigned',
			'value' => ($__vars['assignedFilter'] ? $__vars['assignedFilter']['username'] : ''),
			'ac' => 'single',
		)) . '
			</div>
		</div>
	';
	} else {
		$__compilerTemp1 .= '
		' . $__templater->formHiddenVal('owner_id', $__vars['xf']['visitor']['user_id'], array(
		)) . '
	';
	}
	$__vars['ticketStatuses'] = $__templater->method($__templater->method($__vars['xf']['app']['em'], 'getRepository', array('MJ\\SupportTicket:TicketStatus', )), 'findTicketStatusList', array());
	$__compilerTemp2 = array(array(
		'value' => '',
		'label' => $__vars['xf']['language']['parenthesis_open'] . 'Any' . $__vars['xf']['language']['parenthesis_close'],
		'_type' => 'option',
	));
	if ($__templater->isTraversable($__vars['ticketStatuses'])) {
		foreach ($__vars['ticketStatuses'] AS $__vars['_ticketStatus']) {
			$__compilerTemp2[] = array(
				'value' => $__vars['_ticketStatus']['ticket_status_id'],
				'label' => $__templater->escape($__vars['_ticketStatus']['title']),
				'_type' => 'option',
			);
		}
	}
	$__finalCompiled .= $__templater->form('
	' . '
	' . $__compilerTemp1 . '

	<div class="menu-row menu-row--separated">
		' . 'Ticket ID' . $__vars['xf']['language']['label_separator'] . '
		<div class="u-inputSpacer">
			' . $__templater->formTextBox(array(
		'name' => 'ticket_id',
		'value' => $__vars['filters']['ticket_id'],
		'ac' => 'single',
	)) . '
		</div>
	</div>

	' . '
	<div class="menu-row menu-row--separated">
		' . 'Status' . $__vars['xf']['language']['label_separator'] . '
		<div class="u-inputSpacer">
			' . '' . '
			' . $__templater->formSelect(array(
		'name' => 'ticket_status_id',
		'value' => $__vars['filters']['ticket_status_id'],
	), $__compilerTemp2) . '
		</div>
	</div>

	' . '
	<div class="menu-row menu-row--separated">
		' . 'Priority' . $__vars['xf']['language']['label_separator'] . '
		<div class="u-inputSpacer">
			' . $__templater->formSelect(array(
		'name' => 'urgency',
		'value' => $__vars['filters']['urgency'],
	), array(array(
		'value' => '',
		'label' => $__vars['xf']['language']['parenthesis_open'] . 'Any' . $__vars['xf']['language']['parenthesis_close'],
		'_type' => 'option',
	),
	array(
		'value' => '1',
		'label' => '<span class="mjstPrioriy mjstPrioriy--1">' . 'High' . '</span>',
		'_type' => 'option',
	),
	array(
		'value' => '2',
		'label' => '<span class="mjstPrioriy mjstPrioriy--2">' . 'Medium' . '</span>',
		'_type' => 'option',
	),
	array(
		'value' => '3',
		'label' => '<span class="mjstPrioriy mjstPrioriy--3">' . 'Low' . '</span>',
		'_type' => 'option',
	))) . '
		</div>
	</div>

	' . '
	<div class="menu-row menu-row--separated">
		' . 'Sort by' . $__vars['xf']['language']['label_separator'] . '
		<div class="inputGroup u-inputSpacer">
			<span class="u-srOnly" id="ctrl_sort_by">' . 'Sort order' . '</span>
			' . $__templater->formSelect(array(
		'name' => 'order',
		'value' => ($__vars['filters']['order'] ?: $__vars['xf']['options']['mjstDefaultSortOrder']['order']),
		'aria-labelledby' => 'ctrl_sort_by',
	), array(array(
		'value' => 'last_update',
		'label' => 'Last update',
		'_type' => 'option',
	),
	array(
		'value' => 'open_date',
		'label' => 'First message',
		'_type' => 'option',
	),
	array(
		'value' => 'last_message_date',
		'label' => 'Last message',
		'_type' => 'option',
	),
	array(
		'value' => 'title',
		'label' => 'Title',
		'_type' => 'option',
	),
	array(
		'value' => 'reply_count',
		'label' => 'Replies',
		'_type' => 'option',
	))) . '
			<span class="inputGroup-splitter"></span>
			<span class="u-srOnly" id="ctrl_sort_direction">' . 'Sort direction' . '</span>
			' . $__templater->formSelect(array(
		'name' => 'direction',
		'value' => ($__vars['filters']['direction'] ?: $__vars['xf']['options']['mjstDefaultSortOrder']['direction']),
		'aria-labelledby' => 'ctrl_sort_direction',
	), array(array(
		'value' => 'desc',
		'label' => 'Descending',
		'_type' => 'option',
	),
	array(
		'value' => 'asc',
		'label' => 'Ascending',
		'_type' => 'option',
	))) . '
		</div>
	</div>

	' . '
	<div class="menu-footer">
		<span class="menu-footer-controls">
			' . $__templater->button('Filter', array(
		'type' => 'submit',
		'class' => 'button--primary',
	), '', array(
	)) . '
		</span>
	</div>
', array(
		'action' => $__templater->fn('link', array(($__vars['department'] ? 'support-tickets/departments' : 'support-tickets'), $__vars['department'], ), false),
		'method' => 'get',
	));
	return $__finalCompiled;
});