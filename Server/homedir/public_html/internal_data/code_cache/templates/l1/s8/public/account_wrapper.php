<?php
// FROM HASH: 28618570ae0c438a583fb9993224109c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__compilerTemp1 = '';
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('siropuReferralContests', 'refer', ))) {
		$__compilerTemp1 .= '
	';
		if ($__vars['xf']['options']['siropuReferralContestsInvitationOnly']) {
			$__compilerTemp1 .= '
		<a class="blockLink ' . (($__vars['pageSelected'] == 'invitations') ? 'is-selected' : '') . '" href="' . (($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('siropuReferralContests', 'sendInvitations', )) != 0) ? $__templater->fn('link', array('account/invitations/create', ), true) : $__templater->fn('link', array('account/invitations/list', ), true)) . '">
			' . 'Your invitations' . '
		</a>
	';
		} else {
			$__compilerTemp1 .= '
		<a class="blockLink ' . (($__vars['pageSelected'] == 'referrals') ? 'is-selected' : '') . '" href="' . $__templater->fn('link', array('account/referrals', ), true) . '">
			' . 'Your referrals' . '
		</a>
	';
		}
		$__compilerTemp1 .= '
';
	}
	$__compilerTemp2 = '';
	if ($__templater->method($__vars['xf']['visitor'], 'canEditSignature', array())) {
		$__compilerTemp2 .= '
					<a class="blockLink ' . (($__vars['pageSelected'] == 'signature') ? 'is-selected' : '') . '" href="' . $__templater->fn('link', array('account/signature', ), true) . '">
						' . 'Signature' . '
					</a>
				';
	}
	$__compilerTemp3 = '';
	if ($__vars['xf']['app']['userUpgradeCount']) {
		$__compilerTemp3 .= '
					<a class="blockLink ' . (($__vars['pageSelected'] == 'upgrades') ? 'is-selected' : '') . '" href="' . $__templater->fn('link', array('account/upgrades', ), true) . '">
						' . 'Account upgrades' . '
					</a>
				';
	}
	$__compilerTemp4 = '';
	if ($__vars['xf']['app']['connectedAccountCount']) {
		$__compilerTemp4 .= '
					<a class="blockLink ' . (($__vars['pageSelected'] == 'connected_account') ? 'is-selected' : '') . '" href="' . $__templater->fn('link', array('account/connected-accounts', ), true) . '">
						' . 'Connected accounts' . '
					</a>
				';
	}
	$__templater->modifySideNavHtml(null, '
	<div class="block">
		<div class="block-container">
			<h3 class="block-header">' . 'Your account' . '</h3>
			<div class="block-body">
				' . '
				<a class="blockLink" href="' . $__templater->fn('link', array('members', $__vars['xf']['visitor'], ), true) . '">' . 'Your profile' . '</a>
				<a class="blockLink ' . (($__vars['pageSelected'] == 'alerts') ? 'is-selected' : '') . '" href="' . $__templater->fn('link', array('account/alerts', ), true) . '">
					' . 'Alerts' . '
				</a>
' . $__templater->includeTemplate('sv_ue_account_wrapper_likes_given', $__vars) . '
				<a class="blockLink ' . (($__vars['pageSelected'] == 'likes') ? 'is-selected' : '') . '" href="' . $__templater->fn('link', array('account/likes', ), true) . '">
					' . 'Likes received' . '
				</a>
				' . $__templater->includeTemplate('sv_ue_account_wrapper_watched', $__vars) . '
' . '
' . $__compilerTemp1 . '
			</div>

			' . $__templater->includeTemplate('sv_ue_account_wrapper_conversations', $__vars) . '
<h3 class="block-minorHeader">' . 'Settings' . '</h3>
			<div class="block-body">
				' . '
				<a class="blockLink ' . (($__vars['pageSelected'] == 'account_details') ? 'is-selected' : '') . '" href="' . $__templater->fn('link', array('account/account-details', ), true) . '">
					' . 'Account details' . '
				</a>
				<a class="blockLink ' . (($__vars['pageSelected'] == 'security') ? 'is-selected' : '') . '" href="' . $__templater->fn('link', array('account/security', ), true) . '">
					' . 'Password and security' . '
				</a>
				<a class="blockLink ' . (($__vars['pageSelected'] == 'privacy') ? 'is-selected' : '') . '" href="' . $__templater->fn('link', array('account/privacy', ), true) . '">
					' . 'Privacy' . '
				</a>
				<a class="blockLink ' . (($__vars['pageSelected'] == 'preferences') ? 'is-selected' : '') . '" href="' . $__templater->fn('link', array('account/preferences', ), true) . '">
					' . 'Preferences' . '
				</a>
				' . $__compilerTemp2 . '
				' . $__compilerTemp3 . '
				' . $__compilerTemp4 . '
				<a class="blockLink ' . (($__vars['pageSelected'] == 'following') ? 'is-selected' : '') . '" href="' . $__templater->fn('link', array('account/following', ), true) . '">
					' . 'Following' . '
				</a>
				<a class="blockLink ' . (($__vars['pageSelected'] == 'ignored') ? 'is-selected' : '') . '" href="' . $__templater->fn('link', array('account/ignored', ), true) . '">
					' . 'Ignoring' . '
				</a>
				<a href="' . $__templater->fn('link', array('logout', null, array('t' => $__templater->fn('csrf_token', array(), false), ), ), true) . '" class="blockLink">' . '<b>Log out</b>' . '</a>
				' . '
			</div>
		</div>
	</div>
', 'replace');
	$__finalCompiled .= '
';
	$__templater->setPageParam('sideNavTitle', 'Your account');
	$__finalCompiled .= '

';
	$__templater->breadcrumb($__templater->preEscaped('Your account'), $__templater->fn('link', array('account', ), false), array(
	));
	$__finalCompiled .= '

' . $__templater->filter($__vars['innerContent'], array(array('raw', array()),), true);
	return $__finalCompiled;
});