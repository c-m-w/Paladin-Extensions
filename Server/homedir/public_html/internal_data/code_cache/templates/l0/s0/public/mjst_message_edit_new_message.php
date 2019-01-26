<?php
// FROM HASH: d2b66de9d159005f5a76450fb9195ed8
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->fn('prefix', array('support_ticket', $__vars['ticket'], 'escaped', ), true) . $__templater->escape($__vars['ticket']['title']));
	$__finalCompiled .= '
';
	$__templater->pageParams['pageH1'] = $__templater->preEscaped($__templater->fn('prefix', array('support_ticket', $__vars['ticket'], ), true) . $__templater->escape($__vars['ticket']['title']));
	$__finalCompiled .= '

<div class="block-outer js-ticketStatusField">';
	$__compilerTemp1 = '';
	$__compilerTemp2 = '';
	$__compilerTemp2 .= '
				' . $__templater->callMacro('custom_fields_macros', 'custom_fields_view', array(
		'type' => 'tickets',
		'group' => 'ticket_status',
		'onlyInclude' => $__vars['ticket']['Department']['field_cache'],
		'set' => $__vars['ticket']['custom_fields'],
		'wrapperClass' => 'blockStatus-message',
	), $__vars) . '
			';
	if (strlen(trim($__compilerTemp2)) > 0) {
		$__compilerTemp1 .= '
		<div class="blockStatus blockStatus--info">
			' . $__compilerTemp2 . '
		</div>
	';
	}
	$__finalCompiled .= trim('
	' . $__compilerTemp1 . '
') . '</div>

' . $__templater->callMacro('mjst_message_macros', 'message', array(
		'message' => $__vars['message'],
		'ticket' => $__vars['ticket'],
	), $__vars);
	return $__finalCompiled;
});