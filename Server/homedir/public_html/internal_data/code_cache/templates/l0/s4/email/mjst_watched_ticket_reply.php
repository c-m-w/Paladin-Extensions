<?php
// FROM HASH: 9f69a5cc96c702d6000f84ef8d46ad6e
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<mail:subject>
	' . '' . ($__templater->fn('prefix', array('support_ticket', $__vars['ticket'], 'escaped', ), true) . $__templater->escape($__vars['ticket']['full_title'])) . ' - New reply to watched ticket' . '
</mail:subject>

' . '<p>' . $__templater->fn('username_link_email', array($__vars['message']['User'], $__vars['message']['username'], ), true) . ' replied to a ticket you are watching at ' . (((('<a href="' . $__templater->fn('link', array('canonical:index', ), true)) . '">') . $__templater->escape($__vars['xf']['options']['boardTitle'])) . '</a>') . '.</p>' . '

<h2><a href="' . $__templater->fn('link', array('canonical:support-tickets/messages', $__vars['message'], ), true) . '">' . $__templater->fn('prefix', array('support_ticket', $__vars['ticket'], 'escaped', ), true) . $__templater->escape($__vars['ticket']['full_title']) . '</a></h2>

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
		'watchType' => 'tickets',
	), $__vars) . '
' . $__templater->callMacro('mjst_ticket_macros', 'watched_ticket_footer', array(
		'ticket' => $__vars['ticket'],
	), $__vars);
	return $__finalCompiled;
});