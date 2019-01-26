<?php
// FROM HASH: 060018a20feb5994fb12e50372fa3b2d
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit ticket');
	$__finalCompiled .= '

';
	$__templater->includeJs(array(
		'src' => 'mj/mjst/ticket.js',
		'min' => '1',
	));
	$__finalCompiled .= '

';
	$__templater->breadcrumbs($__templater->method($__vars['ticket'], 'getBreadcrumbs', array()));
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__templater->method($__vars['ticket'], 'canEditTicketDepartment', array()) AND $__vars['departments']) {
		$__compilerTemp1 .= '
				' . $__templater->callMacro('mjst_ticket_edit_macros', 'department', array(
			'departments' => $__vars['departments'],
			'ticket' => $__vars['ticket'],
		), $__vars) . '
			';
	}
	$__compilerTemp2 = '';
	if ($__templater->method($__vars['ticket'], 'canEditTicketStatus', array()) AND $__vars['ticketStatuses']) {
		$__compilerTemp2 .= '
				' . $__templater->callMacro('mjst_ticket_edit_macros', 'status', array(
			'ticketStatuses' => $__vars['ticketStatuses'],
			'ticket' => $__vars['ticket'],
		), $__vars) . '
			';
	}
	$__compilerTemp3 = '';
	if ($__templater->method($__vars['ticket'], 'canChangeOwner', array())) {
		$__compilerTemp3 .= '
				' . $__templater->formCheckBoxRow(array(
		), array(array(
			'name' => 'change_owner',
			'value' => '1',
			'data-hide' => 'true',
			'label' => 'Change ticket owner to' . $__vars['xf']['language']['ellipsis'],
			'_dependent' => array('
							' . $__templater->callMacro('mjst_ticket_edit_macros', 'owner_type', array(
			'ticket' => $__vars['ticket'],
		), $__vars) . '
						'),
			'_type' => 'option',
		)), array(
		)) . '
			';
	}
	$__compilerTemp4 = '';
	if ($__templater->method($__vars['ticket'], 'canDelete', array())) {
		$__compilerTemp4 .= '
					' . $__templater->button('Delete' . $__vars['xf']['language']['ellipsis'], array(
			'href' => $__templater->fn('link', array('tickets/delete', $__vars['ticket'], ), false),
			'icon' => 'delete',
			'overlay' => 'true',
		), '', array(
		)) . '
				';
	}
	$__compilerTemp5 = '';
	if ($__vars['noInlineMod']) {
		$__compilerTemp5 .= '
		' . $__templater->formHiddenVal('_xfNoInlineMod', '1', array(
		)) . '
	';
	}
	$__compilerTemp6 = '';
	if ($__vars['departmentName']) {
		$__compilerTemp6 .= '
		' . $__templater->formHiddenVal('_xfDepartmentName', '1', array(
		)) . '
	';
	}
	$__finalCompiled .= $__templater->form('

	<div class="block-container">
		<div class="block-body">
			' . $__compilerTemp1 . '

			' . $__compilerTemp2 . '

			' . $__templater->callMacro('mjst_ticket_edit_macros', 'title', array(
		'ticket' => $__vars['ticket'],
		'prefixes' => $__vars['prefixes'],
	), $__vars) . '

			' . $__templater->callMacro('mjst_ticket_edit_macros', 'urgency', array(
		'ticket' => $__vars['ticket'],
	), $__vars) . '

			' . $__templater->callMacro('mjst_ticket_edit_macros', 'custom_fields', array(
		'ticket' => $__vars['ticket'],
		'department' => $__vars['department'],
	), $__vars) . '

			' . $__compilerTemp3 . '
		</div>

		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
		'sticky' => 'true',
	), array(
		'html' => '
				' . $__compilerTemp4 . '
			',
	)) . '
	</div>

	' . $__compilerTemp5 . '
	' . $__compilerTemp6 . '
', array(
		'action' => $__templater->fn('link', array('support-tickets/edit', $__vars['ticket'], ), false),
		'class' => 'block',
		'ajax' => 'true',
		'data-xf-init' => 'ticket-edit-form',
		'data-item-selector' => '.js-ticketListItem-' . $__vars['ticket']['support_ticket_id'],
	));
	return $__finalCompiled;
});