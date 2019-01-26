<?php
// FROM HASH: a7c226a2ee80caeb4601eeb753089f5a
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<mail:subject>
	' . 'New ticket received - ' . ($__templater->fn('prefix', array('support_ticket', $__vars['ticket'], 'escaped', ), true) . $__templater->escape($__vars['ticket']['full_title'])) . '' . '
</mail:subject>

';
	if ($__vars['ticket']['creator_user_id'] != $__vars['ticket']['user_id']) {
		$__finalCompiled .= '
	' . '<p>' . $__templater->fn('username_link_email', array($__vars['message']['User'], $__vars['message']['username'], ), true) . ' opened a new ticket for you at ' . (((('<a href="' . $__templater->fn('link', array('canonical:index', ), true)) . '">') . $__templater->escape($__vars['xf']['options']['boardTitle'])) . '</a>') . '.</p>' . '
';
	} else {
		$__finalCompiled .= '
	' . '<p>Thank you for contacting our support team. A support ticket has now been opened for your request. You will be notified when a response is made by email. The details of your ticket are shown below.</p>' . '
';
	}
	$__finalCompiled .= '

<h2><a href="' . $__templater->fn('link', array('canonical:support-tickets/messages', $__vars['message'], ), true) . '">' . $__templater->fn('prefix', array('support_ticket', $__vars['ticket'], 'escaped', ), true) . $__templater->escape($__vars['ticket']['full_title']) . '</a></h2>

';
	if ((!$__vars['receiver']['user_id']) AND (!$__vars['ticket']['user_id'])) {
		$__finalCompiled .= '
	' . '<p><b>Ticket Password:</b> ' . $__templater->escape($__vars['ticket']['guest_password']) . '</p>' . '
';
	}
	$__finalCompiled .= '

' . '<p><b>Ticket ID:</b> ' . $__templater->escape($__vars['ticket']['ticket_id']) . '</p>
<p><b>Department:</b> ' . $__templater->escape($__vars['department']['title']) . '</p>
<p><b>Priority:</b> ' . $__templater->escape($__vars['ticket']['urgency_title']) . '</p>
<p><b>Status:</b> ' . $__templater->escape($__vars['ticket']['Status']['title']) . '</p>' . '

';
	if ($__vars['xf']['options']['mjstFirstMessageInEmail']) {
		$__finalCompiled .= '
	<div class="message">' . $__templater->fn('bb_code_type', array('emailHtml', $__vars['message']['message'], 'support_ticket_message', $__vars['message'], ), true) . '</div>
';
	}
	$__finalCompiled .= '

' . $__templater->callMacro('mjst_ticket_macros', 'go_ticket_bar', array(
		'ticket' => $__vars['ticket'],
		'watchType' => 'departments',
	), $__vars);
	return $__finalCompiled;
});