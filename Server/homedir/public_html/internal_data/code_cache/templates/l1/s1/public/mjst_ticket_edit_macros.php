<?php
// FROM HASH: 180313eb00e785950bc94fec343b9939
return array('macros' => array('department' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'ticket' => '!',
		'departments' => '!',
		'rowtype' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__vars['departments']['count'] == 1) {
		$__finalCompiled .= '
		';
		$__vars['department'] = $__templater->method($__vars['departments'], 'first', array());
		$__finalCompiled .= '
		' . $__templater->formRow('
			' . $__templater->escape($__vars['department']['title']) . '
			' . $__templater->formHiddenVal('department_id', $__vars['department']['department_id'], array(
		)) . '
		', array(
			'label' => 'Department',
			'rowtype' => $__vars['rowtype'],
		)) . '
	';
	} else {
		$__finalCompiled .= '
		';
		$__compilerTemp1 = array();
		if ($__templater->isTraversable($__vars['departments'])) {
			foreach ($__vars['departments'] AS $__vars['department']) {
				$__compilerTemp1[] = array(
					'value' => $__vars['department']['department_id'],
					'label' => $__templater->escape($__vars['department']['title']),
					'_type' => 'option',
				);
			}
		}
		$__finalCompiled .= $__templater->formSelectRow(array(
			'name' => 'department_id',
			'value' => $__vars['ticket']['department_id'],
			'class' => 'js-departmentList',
		), $__compilerTemp1, array(
			'rowtype' => $__vars['rowtype'],
			'label' => 'Department',
		)) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'urgency' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'ticket' => '!',
		'rowtype' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	' . $__templater->formRadioRow(array(
		'name' => 'urgency',
		'value' => $__vars['ticket']['urgency'],
		'listclass' => 'listInline',
	), array(array(
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
	)), array(
		'rowtype' => $__vars['rowtype'],
		'label' => 'Priority',
	)) . '
';
	return $__finalCompiled;
},
'status' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'ticket' => '!',
		'ticketStatuses' => '!',
		'rowtype' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__compilerTemp1 = array();
	if ($__templater->isTraversable($__vars['ticketStatuses'])) {
		foreach ($__vars['ticketStatuses'] AS $__vars['_ticketStatus']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['_ticketStatus']['ticket_status_id'],
				'label' => $__templater->escape($__vars['_ticketStatus']['title']),
				'_type' => 'option',
			);
		}
	}
	$__finalCompiled .= $__templater->formSelectRow(array(
		'name' => 'ticket_status_id',
		'value' => $__vars['ticket']['ticket_status_id'],
	), $__compilerTemp1, array(
		'rowtype' => $__vars['rowtype'],
		'label' => 'Status',
	)) . '
';
	return $__finalCompiled;
},
'title' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'ticket' => '!',
		'prefixes' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	' . $__templater->formPrefixInputRow($__vars['prefixes'], array(
		'type' => 'support_ticket',
		'prefix-value' => $__vars['ticket']['prefix_id'],
		'textbox-value' => $__vars['ticket']['title_'],
		'textbox-class' => 'input--title',
		'href' => $__templater->fn('link', array('support-tickets/departments/prefixes', ), false),
		'listen-to' => '< .js-prefixListenContainer | .js-departmentList',
		'autofocus' => 'autofocus',
		'maxlength' => $__templater->fn('max_length', array($__vars['ticket'], 'title', ), false),
		'placeholder' => 'Title' . $__vars['xf']['language']['ellipsis'],
	), array(
		'label' => 'Title',
		'rowtype' => 'fullWidth noLabel',
	)) . '
';
	return $__finalCompiled;
},
'message' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'message' => '',
		'attachmentData' => array(),
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div data-xf-init="attachment-manager">
		' . $__templater->formEditorRow(array(
		'name' => 'message',
		'value' => $__vars['message'],
		'data-min-height' => '200',
		'attachments' => $__vars['attachmentData']['attachments'],
	), array(
		'rowtype' => 'fullWidth noLabel',
		'label' => 'Message',
	)) . '

		';
	$__compilerTemp1 = '';
	if ($__vars['attachmentData']) {
		$__compilerTemp1 .= '
				' . $__templater->callMacro('helper_attach_upload', 'upload_block', array(
			'attachmentData' => $__vars['attachmentData'],
		), $__vars) . '
			';
	}
	$__finalCompiled .= $__templater->formRow('
			' . $__compilerTemp1 . '
		', array(
	)) . '
	</div>
';
	return $__finalCompiled;
},
'custom_fields' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'ticket' => '!',
		'department' => '!',
		'rowtype' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__templater->includeJs(array(
		'src' => 'mj/mjst/custom-field.js',
	));
	$__finalCompiled .= '
	<div class="customFields" data-xf-init="mjst-custom-field"
		data-listen-to="< .js-prefixListenContainer | .js-departmentList"
		data-tid="' . $__templater->escape($__vars['ticket']['support_ticket_id']) . '"
		data-row-type="' . $__templater->escape($__vars['rowtype']) . '"
		data-emode="' . $__templater->escape($__templater->method($__vars['ticket'], 'getFieldEditMode', array())) . '"
		data-href="' . $__templater->fn('link', array('support-tickets/departments/custom-fields', ), true) . '">
		';
	$__compilerTemp1 = '';
	$__compilerTemp1 .= '
				' . $__templater->callMacro('custom_fields_macros', 'custom_fields_edit', array(
		'type' => 'tickets',
		'set' => $__vars['ticket']['custom_fields'],
		'editMode' => $__templater->method($__vars['ticket'], 'getFieldEditMode', array()),
		'rowType' => $__vars['rowtype'],
		'onlyInclude' => $__vars['department']['field_cache'],
	), $__vars) . '
			';
	if (strlen(trim($__compilerTemp1)) > 0) {
		$__finalCompiled .= '
			<hr class="formRowSep" />
			' . $__compilerTemp1 . '
		';
	}
	$__finalCompiled .= '
	</div>
';
	return $__finalCompiled;
},
'watch_input' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'ticket' => '!',
		'rowType' => '',
		'visible' => true,
	), $__arguments, $__vars);
	$__finalCompiled .= '

	';
	$__vars['ticketWatch'] = $__vars['ticket']['Watch'][$__vars['xf']['visitor']['user_id']];
	$__finalCompiled .= '
	';
	$__vars['defaultTicketWatch'] = ($__templater->method($__vars['ticket'], 'isInsert', array()) ? $__vars['xf']['visitor']['Option']['creation_watch_state'] : $__vars['xf']['visitor']['Option']['interaction_watch_state']);
	$__finalCompiled .= '
	';
	$__vars['watchChecked'] = (($__vars['ticket']['support_ticket_id'] AND !$__templater->test($__vars['ticketWatch'], 'empty', array())) ?: ($__vars['defaultTicketWatch'] != ''));
	$__finalCompiled .= '
	';
	$__vars['watchEmailChecked'] = (($__vars['ticket']['support_ticket_id'] AND $__vars['ticketWatch']['email_subscribe']) ?: ($__vars['defaultTicketWatch'] == 'watch_email'));
	$__finalCompiled .= '

	';
	if ($__vars['visible']) {
		$__finalCompiled .= '
		' . $__templater->formCheckBoxRow(array(
		), array(array(
			'name' => 'watch_ticket',
			'value' => '1',
			'selected' => $__vars['watchChecked'],
			'label' => 'Watch this ticket' . $__vars['xf']['language']['ellipsis'],
			'_dependent' => array($__templater->formCheckBox(array(
		), array(array(
			'name' => 'watch_ticket_email',
			'value' => '1',
			'selected' => $__vars['watchEmailChecked'],
			'label' => 'and receive email notifications',
			'_type' => 'option',
		)))),
			'_type' => 'option',
		)), array(
			'label' => 'Options',
			'rowtype' => $__vars['rowType'],
		)) . '
	';
	} else {
		$__finalCompiled .= '
		' . $__templater->formHiddenVal('watch_ticket', $__vars['watchChecked'], array(
		)) . '
		' . $__templater->formHiddenVal('watch_ticket_email', $__vars['watchEmailChecked'], array(
		)) . '
	';
	}
	$__finalCompiled .= '
	' . $__templater->formHiddenVal('_xfSet[watch_ticket]', '1', array(
	)) . '
';
	return $__finalCompiled;
},
'owner_type' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'ticket' => '!',
		'draft' => array(),
		'rowType' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__vars['targetType'] = ($__vars['ticket']['support_ticket_id'] ? ($__vars['ticket']['user_id'] ? 'member' : 'guest') : ($__vars['draft']['target_type'] ? $__vars['draft']['target_type'] : 'member'));
	$__finalCompiled .= '
	' . $__templater->formRadio(array(
		'name' => 'target_type',
		'value' => $__vars['targetType'],
	), array(array(
		'value' => 'member',
		'data-hide' => 'true',
		'label' => 'Member',
		'_dependent' => array('
				<div>' . 'Receiver' . $__vars['xf']['language']['label_separator'] . '</div>
				' . $__templater->formTextBox(array(
		'name' => 'target_member',
		'value' => ($__vars['ticket']['username'] ? $__vars['ticket']['username'] : $__vars['draft']['target_member']),
		'ac' => 'single',
		'autocomplete' => 'off',
		'maxlength' => $__templater->fn('max_length', array($__vars['xf']['visitor'], 'username', ), false),
		'placeholder' => 'Name' . $__vars['xf']['language']['ellipsis'],
	)) . '
			'),
		'_type' => 'option',
	),
	array(
		'value' => 'guest',
		'data-hide' => 'true',
		'label' => 'Guest',
		'_dependent' => array('
				<div>' . 'Name' . $__vars['xf']['language']['label_separator'] . '</div>
				' . $__templater->formTextBox(array(
		'name' => 'guest_username',
		'value' => ($__vars['ticket']['username'] ? $__vars['ticket']['username'] : $__vars['draft']['guest_username']),
		'maxlength' => $__templater->fn('max_length', array($__vars['xf']['visitor'], 'username', ), false),
		'placeholder' => 'Name' . $__vars['xf']['language']['ellipsis'],
	)) . '
			', '
				<div>' . 'Email' . $__vars['xf']['language']['label_separator'] . '</div>
				' . $__templater->formTextBox(array(
		'name' => 'guest_email',
		'value' => ($__vars['ticket']['user_email'] ? $__vars['ticket']['user_email'] : $__vars['draft']['guest_email']),
		'maxlength' => $__templater->fn('max_length', array($__vars['xf']['visitor'], 'email', ), false),
		'placeholder' => 'Email' . $__vars['xf']['language']['ellipsis'],
	)) . '
			'),
		'_type' => 'option',
	))) . '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '

' . '

' . '

' . '

' . '

' . '

' . '

';
	return $__finalCompiled;
});