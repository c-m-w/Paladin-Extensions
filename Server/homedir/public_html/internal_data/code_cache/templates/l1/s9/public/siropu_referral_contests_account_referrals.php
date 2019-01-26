<?php
// FROM HASH: 476ee390db1003eff032b9e8ee462d19
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Your referrals');
	$__finalCompiled .= '

';
	$__templater->wrapTemplate('account_wrapper', $__vars);
	$__finalCompiled .= '

';
	if (!$__vars['xf']['options']['siropuReferralContestsInvitationOnly']) {
		$__finalCompiled .= '
	<div class="block">
		<div class="block-container">
			<div class="block-body block-row">
				<b>' . 'Your referral link' . '</b>: ' . $__templater->fn('siropu_referral_link', array('user', ), true) . '
				' . $__templater->callMacro('siropu_referral_contests_referral_link_widget', 'copy_to_clipboard', array(
			'type' => 'user',
		), $__vars) . '
			</div>
			' . $__templater->callMacro('siropu_referral_contests_macros', 'referral_tools_block_footer', array(
			'invitationsSent' => true,
		), $__vars) . '
		</div>
	</div>
';
	}
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['referrals'], 'empty', array())) {
		$__finalCompiled .= '
	<div class="block">
		<div class="block-container">
			<ol class="block-body">
				';
		if ($__templater->isTraversable($__vars['referrals'])) {
			foreach ($__vars['referrals'] AS $__vars['referral']) {
				$__finalCompiled .= '
					<li class="block-row block-row--separated">
						' . $__templater->callMacro('member_list_macros', 'item', array(
					'user' => $__vars['referral'],
					'extraData' => $__templater->fn('date_time', array($__vars['referral']['register_date'], ), false),
				), $__vars) . '
					</li>
				';
			}
		}
		$__finalCompiled .= '
			</ol>
		</div>

		' . $__templater->fn('page_nav', array(array(
			'link' => 'account/referrals',
			'page' => $__vars['page'],
			'total' => $__vars['total'],
			'wrapperclass' => 'block-outer block-outer--after',
			'perPage' => $__vars['perPage'],
		))) . '
	</div>
';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'You do not have any referrals at the moment.' . '</div>
';
	}
	return $__finalCompiled;
});