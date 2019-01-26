<?php
// FROM HASH: 5371a557629e34e2fe30556ecdbbb7ee
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Email invitations');
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
		'html' => 'Fill out the form below to send email invitations to your friends so they may register. Please note that codes expire after 3 days if no one has registered with the code.',
	)) . '
			' . $__templater->callMacro('siropu_referral_contests_macros', 'invitation_form', array(), $__vars) . '
		</div>
	</div>
</div>';
	return $__finalCompiled;
});