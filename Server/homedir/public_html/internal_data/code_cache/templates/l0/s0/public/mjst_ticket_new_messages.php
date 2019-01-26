<?php
// FROM HASH: a6271921dd0edf9fbc3c259d1e8ec452
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['firstUnshownMessage']) {
		$__finalCompiled .= '
	<div class="message">
		<div class="message-inner">
			<div class="message-cell message-cell--alert">
				' . 'There are more messages to display.' . ' <a href="' . $__templater->fn('link', array('support-tickets/messages', $__vars['firstUnshownMessage'], ), true) . '">' . 'View them?' . '</a>
			</div>
		</div>
	</div>
';
	}
	$__finalCompiled .= '

';
	if ($__templater->isTraversable($__vars['messages'])) {
		foreach ($__vars['messages'] AS $__vars['message']) {
			$__finalCompiled .= '
	' . $__templater->callMacro('mjst_message_macros', 'message', array(
				'message' => $__vars['message'],
				'ticket' => $__vars['ticket'],
			), $__vars) . '
';
		}
	}
	return $__finalCompiled;
});