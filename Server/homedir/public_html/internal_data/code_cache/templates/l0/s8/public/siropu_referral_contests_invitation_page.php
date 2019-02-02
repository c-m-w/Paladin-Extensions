<?php
// FROM HASH: 2eb662582bb9043374bd1482cc1cc969
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Welcome!');
	$__finalCompiled .= '
';
	$__templater->pageParams['pageDescription'] = $__templater->preEscaped('You have been invited by our member ' . $__templater->escape($__vars['invitation']['User']['username']) . ' to join the community.');
	$__templater->pageParams['pageDescriptionMeta'] = true;
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		<div class="block-body">
			<div class="block-row">
				';
	if ($__vars['xf']['options']['siropuReferralContestsInvitationPageDescription']) {
		$__finalCompiled .= '
					' . $__templater->fn('bb_code', array($__vars['xf']['options']['siropuReferralContestsInvitationPageDescription'], 'siropu_referral_contests', null, ), true) . '
				';
	}
	$__finalCompiled .= '
			</div>
			<div class="block-row">
				' . $__templater->button('<i class="fa fa-key" style="padding-right:5px" aria-hidden="true"></i> ' . 'Click here to register', array(
		'href' => $__templater->fn('link', array('register', ), false),
		'class' => 'button--cta',
		'overlay' => 'true',
	), '', array(
	)) . '
			</div>
		</div>
	</div>
</div>';
	return $__finalCompiled;
});