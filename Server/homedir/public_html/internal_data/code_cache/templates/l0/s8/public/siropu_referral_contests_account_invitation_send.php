<?php
// FROM HASH: a1804d94fd623a5f4ae5c81ef726398e
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Send invitations');
	$__finalCompiled .= '

';
	$__templater->wrapTemplate('account_wrapper', $__vars);
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		' . $__templater->callMacro('siropu_referral_contests_macros', 'invitation_tabs', array(), $__vars) . '

		<div class="block-body">
			' . $__templater->callMacro('siropu_referral_contests_macros', 'invitation_form', array(), $__vars) . '
		</div>
	</div>
</div>';
	return $__finalCompiled;
});