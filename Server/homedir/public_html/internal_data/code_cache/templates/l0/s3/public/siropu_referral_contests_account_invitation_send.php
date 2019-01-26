<?php
// FROM HASH: 5371a557629e34e2fe30556ecdbbb7ee
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
			' . $__templater->formRow('', array(
		'rowtype' => 'fullWidth noLabel noGutte',
		'html' => 'Use the form below to send email invitations to your friends and invite them join our community.',
	)) . '
			' . $__templater->callMacro('siropu_referral_contests_macros', 'invitation_form', array(), $__vars) . '
		</div>
	</div>
</div>';
	return $__finalCompiled;
});