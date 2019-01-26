<?php
// FROM HASH: d40b84d3b4168d327f063ec2fa26db8d
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<mail:subject>
	' . '' . ($__templater->fn('prefix', array('support_ticket', $__vars['ticket'], 'escaped', ), true) . $__templater->escape($__vars['ticket']['title'])) . ' - New message in watched department' . '
</mail:subject>

' . '<p>' . $__templater->fn('username_link_email', array($__vars['message']['User'], $__vars['message']['username'], ), true) . ' posted a new message to a department you are watching at ' . (((('<a href="' . $__templater->fn('link', array('canonical:index', ), true)) . '">') . $__templater->escape($__vars['xf']['options']['boardTitle'])) . '</a>') . '.</p>' . '

<h2><a href="' . $__templater->fn('link', array('canonical:support-tickets/messages', $__vars['message'], ), true) . '">' . $__templater->fn('prefix', array('support_ticket', $__vars['ticket'], 'escaped', ), true) . $__templater->escape($__vars['ticket']['full_title']) . '</a></h2>

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
	), $__vars) . '

' . $__templater->callMacro('mjst_ticket_macros', 'watched_department_footer', array(
		'ticket' => $__vars['ticket'],
		'department' => $__vars['department'],
	), $__vars);
	return $__finalCompiled;
});