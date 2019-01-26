<?php
// FROM HASH: f3b28dbe3366ac0998f281115948f850
return array('macros' => array('go_ticket_bar' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'ticket' => '!',
		'watchType' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<table cellpadding="10" cellspacing="0" border="0" width="100%" class="linkBar">
	<tr>
		<td>
			<a href="' . $__templater->fn('link', array('canonical:support-tickets', $__vars['ticket'], ), true) . '" class="button">' . 'View this ticket' . '</a>
		</td>
		<td align="' . ($__vars['xf']['isRtl'] ? 'left' : 'right') . '">
			';
	if ($__vars['watchType'] == 'ticket') {
		$__finalCompiled .= '
				<a href="' . $__templater->fn('link', array('canonical:watched/tickets', ), true) . '" class="buttonFake">' . 'Watched tickets' . '</a>
			';
	} else if ($__vars['watchType'] == 'department') {
		$__finalCompiled .= '
				<a href="' . $__templater->fn('link', array('canonical:watched/ticket-departments', ), true) . '" class="buttonFake">' . 'Watched departments' . '</a>
			';
	}
	$__finalCompiled .= '
		</td>
	</tr>
	</table>
';
	return $__finalCompiled;
},
'watched_department_footer' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'ticket' => '!',
		'department' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	' . '<p class="minorText">Please do not reply to this message. You must visit the ticket to reply.</p>

<p class="minorText">This message was sent to you because you opted to watch the department "' . $__templater->escape($__vars['department']['title']) . '" at ' . $__templater->escape($__vars['xf']['options']['boardTitle']) . ' with email notification of new tickets or messages. You will not receive any further emails about this thread until you have read the new messages.</p>

<p class="minorText">If you no longer wish to receive these emails, you may <a href="' . $__templater->fn('link', array('canonical:email-stop/content', $__vars['xf']['toUser'], array('t' => 'support_department', 'id' => $__vars['department']['department_id'], ), ), true) . '">disable emails from this department</a> or <a href="' . $__templater->fn('link', array('canonical:email-stop/all', $__vars['xf']['toUser'], ), true) . '">disable all emails</a>.</p>' . '
';
	return $__finalCompiled;
},
'watched_ticket_footer' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'ticket' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	' . '<p class="minorText">Please do not reply to this message. You must visit the ticket to reply.</p>

<p class="minorText">This message was sent to you because you opted to watch the ticket ' . $__templater->escape($__vars['ticket']['title']) . ' at ' . $__templater->escape($__vars['xf']['options']['boardTitle']) . ' with email notification of new replies. You will not receive any further emails about this ticket until you have read the new messages.</p>' . '
	';
	if ($__vars['ticket']['user_id']) {
		$__finalCompiled .= '
	' . '<p class="minorText">If you no longer wish to receive these emails, you may <a href="' . $__templater->fn('link', array('canonical:email-stop/content', $__vars['xf']['toUser'], array('t' => 'support_ticket', 'id' => $__vars['ticket']['support_ticket_id'], ), ), true) . '">disable emails from this ticket</a> or <a href="' . $__templater->fn('link', array('canonical:email-stop/all', $__vars['xf']['toUser'], ), true) . '">disable all emails</a>.</p>' . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '

' . '

' . '

';
	return $__finalCompiled;
});