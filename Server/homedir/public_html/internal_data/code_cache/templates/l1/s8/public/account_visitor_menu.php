<?php
// FROM HASH: 4f1825098b829aec5e1396b3e26a54e9
return array('macros' => array('visitor_panel_row' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="contentRow">
		<div class="contentRow-figure">
			' . $__templater->fn('avatar', array($__vars['xf']['visitor'], 's', false, array(
		'href' => '',
		'notooltip' => 'true',
		'update' => $__templater->fn('link', array('account/avatar', $__vars['xf']['visitor'], ), false),
	))) . '
		</div>
		<div class="contentRow-main">
			<h3 class="contentRow-header">' . $__templater->fn('username_link', array($__vars['xf']['visitor'], true, array(
		'notooltip' => 'true',
	))) . '</h3>
			<div class="contentRow-lesser">
				' . $__templater->fn('user_title', array($__vars['xf']['visitor'], false, array(
	))) . '
			</div>

			<div class="contentRow-minor">
				' . '
				<dl class="pairs pairs--justified fauxBlockLink">
					<dt>' . 'Messages' . '</dt>
					<dd>
						<a href="' . $__templater->fn('link', array('search/member', null, array('user_id' => $__vars['xf']['visitor']['user_id'], ), ), true) . '" class="fauxBlockLink-linkRow u-concealed">
							' . $__templater->filter($__vars['xf']['visitor']['message_count'], array(array('number', array()),), true) . '
						</a>
					</dd>
				</dl>
				<!--\\[XF:stats_pairs:above_likes]-->
' . $__templater->callMacro('th_display_reactions', 'react_total_text', array(
		'reacts' => $__vars['xf']['visitor']['react_count'],
		'reactsCount' => $__templater->method($__vars['xf']['visitor'], 'getReactTotalCount', array()),
	), $__vars) . '
				' . '
';
	if ($__vars['xf']['options']['siropuReferralContestsDisplayReferralCount']) {
		$__finalCompiled .= '
	<dl class="pairs pairs--justified fauxBlockLink">
		<dt>' . 'Referrals' . '</dt>
		<dd>
			<a href="' . $__templater->fn('link', array('referrals/users', $__vars['xf']['visitor'], ), true) . '" class="fauxBlockLink-linkRow u-concealed" data-xf-click="overlay">' . $__templater->filter($__vars['xf']['visitor']['siropu_referral_count'], array(array('number', array()),), true) . '</a>
		</dd>
	</dl>
';
	}
	$__finalCompiled .= '
				';
	if ($__vars['xf']['options']['enableTrophies']) {
		$__finalCompiled .= '
					<dl class="pairs pairs--justified fauxBlockLink">
						<dt>' . 'Trophy points' . '</dt>
						<dd>
							<a href="' . $__templater->fn('link', array('members/trophies', $__vars['xf']['visitor'], ), true) . '" data-xf-click="overlay" class="fauxBlockLink-linkRow u-concealed">
								' . $__templater->filter($__vars['xf']['visitor']['trophy_points'], array(array('number', array()),), true) . '
							</a>
						</dd>
					</dl>
				';
	}
	$__finalCompiled .= '
			</div>
		</div>
	</div>
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<div class="menu-row menu-row--highlighted">
	' . $__templater->callMacro(null, 'visitor_panel_row', array(), $__vars) . '
</div>

' . '

' . '
<hr class="menu-separator menu-separator--hard" />

<ul class="listPlain listColumns listColumns--narrow listColumns--together">
	' . '
	';
	if ($__vars['xf']['options']['enableNewsFeed']) {
		$__finalCompiled .= '
		<li><a href="' . $__templater->fn('link', array('whats-new/news-feed', ), true) . '" class="menu-linkRow">' . 'News feed' . '</a></li>
	';
	}
	$__finalCompiled .= '
	<li><a href="' . $__templater->fn('link', array('search/member', null, array('user_id' => $__vars['xf']['visitor']['user_id'], ), ), true) . '" class="menu-linkRow">' . 'Your content' . '</a></li>
' . $__templater->includeTemplate('sv_ue_account_visitor_menu_likes_given', $__vars) . '
	<li><a href="' . $__templater->fn('link', array('account/likes', ), true) . '" class="menu-linkRow">' . 'Likes received' . '</a></li>
	' . '
';
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('siropuReferralContests', 'refer', ))) {
		$__finalCompiled .= '
	';
		if ($__vars['xf']['options']['siropuReferralContestsInvitationOnly']) {
			$__finalCompiled .= '
		<li><a href="' . (($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('siropuReferralContests', 'sendInvitations', )) != 0) ? $__templater->fn('link', array('account/invitations/create', ), true) : $__templater->fn('link', array('account/invitations/list', ), true)) . '" class="menu-linkRow">' . 'Your invitations' . '</a></li>
	';
		} else {
			$__finalCompiled .= '
		<li><a href="' . $__templater->fn('link', array('account/referrals', ), true) . '" class="menu-linkRow">' . 'Your referrals' . '</a></li>
	';
		}
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '
</ul>

' . '
<hr class="menu-separator" />

<ul class="listPlain listColumns listColumns--narrow listColumns--together">
	' . '
	<li><a href="' . $__templater->fn('link', array('account/account-details', ), true) . '" class="menu-linkRow">' . 'Account details' . '</a></li>
	<li><a href="' . $__templater->fn('link', array('account/security', ), true) . '" class="menu-linkRow">' . 'Password and security' . '</a></li>
	<li><a href="' . $__templater->fn('link', array('account/privacy', ), true) . '" class="menu-linkRow">' . 'Privacy' . '</a></li>
	<li><a href="' . $__templater->fn('link', array('account/preferences', ), true) . '" class="menu-linkRow">' . 'Preferences' . '</a></li>
	';
	if ($__templater->method($__vars['xf']['visitor'], 'canEditSignature', array())) {
		$__finalCompiled .= '
		<li><a href="' . $__templater->fn('link', array('account/signature', ), true) . '" class="menu-linkRow">' . 'Signature' . '</a></li>
	';
	}
	$__finalCompiled .= '
	';
	if ($__vars['xf']['app']['userUpgradeCount']) {
		$__finalCompiled .= '
		<li><a href="' . $__templater->fn('link', array('account/upgrades', ), true) . '" class="menu-linkRow">' . 'Account upgrades' . '</a></li>
	';
	}
	$__finalCompiled .= '
	';
	if ($__vars['xf']['app']['connectedAccountCount']) {
		$__finalCompiled .= '
		<li><a href="' . $__templater->fn('link', array('account/connected-accounts', ), true) . '" class="menu-linkRow">' . 'Connected accounts' . '</a></li>
	';
	}
	$__finalCompiled .= '
	<li><a href="' . $__templater->fn('link', array('account/following', ), true) . '" class="menu-linkRow">' . 'Following' . '</a></li>
	<li><a href="' . $__templater->fn('link', array('account/ignored', ), true) . '" class="menu-linkRow">' . 'Ignoring' . '</a></li>
	';
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('countdown', 'admin', ))) {
		$__finalCompiled .= '
<li><a href="' . $__templater->fn('link', array('countdown/admin/', ), true) . '" class="menu-linkRow" >' . 'Countdown admin' . '</a></li>
';
	}
	$__finalCompiled .= '
' . $__templater->includeTemplate('th_account_visitor_menu_bookmarkLink_bookmarks', $__vars) . '
';
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('conversationView', 'view', ))) {
		$__finalCompiled .= '
<li><a href="' . $__templater->fn('link', array('conversationview', ), true) . '" class="menu-linkRow" >' . 'Conversation view' . '</a></li>
';
	}
	$__finalCompiled .= '
';
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('emailLog', 'view', ))) {
		$__finalCompiled .= '
<li><a href="' . $__templater->fn('link', array('emaillog/', ), true) . '" class="menu-linkRow" >' . 'Email log' . '</a></li>
';
	}
	$__finalCompiled .= '
' . '
</ul>

' . '
<hr class="menu-separator" />

<a href="' . $__templater->fn('link', array('logout', null, array('t' => $__templater->fn('csrf_token', array(), false), ), ), true) . '" class="menu-linkRow">' . '<b>Log out</b>' . '</a>

';
	return $__finalCompiled;
});