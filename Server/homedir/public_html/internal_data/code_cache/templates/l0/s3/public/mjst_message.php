<?php
// FROM HASH: d5c6b9f009bdfdea7621987457a4f424
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['canInlineMod']) {
		$__finalCompiled .= '
	';
		$__templater->includeJs(array(
			'src' => 'xf/inline_mod.js',
			'min' => '1',
		));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

<div class="block" data-xf-init="' . ($__vars['canInlineMod'] ? 'inline-mod' : '') . '" data-type="support_ticket_message" data-href="' . $__templater->fn('link', array('inline-mod', ), true) . '">
	<div class="block-container">
		<div class="block-body">
			' . $__templater->callMacro('mjst_message_macros', 'message', array(
		'message' => $__vars['message'],
		'ticket' => $__vars['ticket'],
	), $__vars) . '
		</div>
	</div>
</div>';
	return $__finalCompiled;
});