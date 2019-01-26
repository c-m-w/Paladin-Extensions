<?php
// FROM HASH: 0969d22d02768d7d6499e06ad65ec4ef
return array('macros' => array('copy_to_clipboard' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'type' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__vars['xf']['options']['siropuReferralContestsCopyToClipboard']) {
		$__finalCompiled .= '
		<button class="siropuCopyReferralLink button button--link" data-clipboard-text="' . $__templater->fn('siropu_referral_link', array($__vars['type'], ), true) . '" style="font-size: 10px; padding: 2px 5px;">' . 'Copy' . '</button>
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<div class="block">
	<div class="block-container">
		<div class="block-body">
			<h3 class="block-header">
				' . 'Referral link' . '
			</h3>
			<div class="block-row">
				<p>
					<b>' . 'Your referral link' . '</b>: ' . $__templater->fn('siropu_referral_link', array('user', ), true) . '
					' . $__templater->callMacro(null, 'copy_to_clipboard', array(
		'type' => 'user',
	), $__vars) . '
				</p>
				';
	$__compilerTemp1 = '';
	$__compilerTemp1 .= '
							' . $__templater->fn('siropu_referral_link', array('page', null, $__vars['options']['currentPageLink'], ), true) . '
						';
	if (strlen(trim($__compilerTemp1)) > 0) {
		$__finalCompiled .= '
					<p>
						<b>' . 'Current page referral link' . '</b>: 
						' . $__compilerTemp1 . '
						' . $__templater->callMacro(null, 'copy_to_clipboard', array(
			'type' => 'page',
		), $__vars) . '
					</p>
				';
	}
	$__finalCompiled .= '
			</div>
		</div>
		' . $__templater->callMacro('siropu_referral_contests_macros', 'referral_tools_block_footer', array(
		'invitationsSent' => $__vars['options']['invitationsSent'],
	), $__vars) . '
	</div>
</div>

';
	return $__finalCompiled;
});