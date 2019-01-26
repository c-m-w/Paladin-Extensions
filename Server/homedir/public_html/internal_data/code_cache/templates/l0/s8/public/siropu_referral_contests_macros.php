<?php
// FROM HASH: 0f81168911dddd80d5bb76b19be26e4e
return array('macros' => array('invitation_form' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(), $__arguments, $__vars);
	$__finalCompiled .= '
	' . $__templater->form('
		' . $__templater->formInfoRow('This option allows you to create invitations that you can send out using a method other than email.', array(
	)) . '
		' . $__templater->formNumberBoxRow(array(
		'name' => 'count',
		'value' => '1',
		'min' => '1',
		'max' => '10',
	), array(
		'label' => 'Number of invitations',
	)) . '
		' . $__templater->formSubmitRow(array(
		'icon' => 'add',
		'submit' => 'Create invitations',
	), array(
	)) . '
	', array(
		'action' => $__templater->fn('link', array('account/invitations/create', ), false),
		'ajax' => 'true',
	)) . '
';
	return $__finalCompiled;
},
'referral_tools_block_footer' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'faq' => true,
		'invitationsSent' => false,
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="block-footer block-footer-split">
		<span class="block-footer-counter">
			<a href="' . $__templater->fn('link', array('account/referral-tools', ), true) . '" data-xf-click="overlay"><i class="fa fa-cog" aria-hidden="true"></i> ' . 'Tools' . '</a>
			';
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('siropuReferralContests', 'createInvitations', ))) {
		$__finalCompiled .= '
				&nbsp; <a href="' . $__templater->fn('link', array('account/invitations/create', ), true) . '" data-xf-click="overlay"><i class="fa fa-users" aria-hidden="true"></i> ' . 'Invite friends' . '</a>
				';
		if ($__vars['invitationsSent']) {
			$__finalCompiled .= '
					&nbsp; <a href="' . $__templater->fn('link', array('account/invitations/list', ), true) . '" data-xf-click="overlay"><i class="fa fa-paper-plane" aria-hidden="true"></i> ' . ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('siropuReferralContests', 'createInvitations', )) ? 'Your invitations' : 'Invitations sent') . '</a>
				';
		}
		$__finalCompiled .= '
			';
	}
	$__finalCompiled .= '
		</span>
		';
	if ($__vars['faq']) {
		$__finalCompiled .= '
			<span class="block-footer-controls">
				<a href="' . $__templater->fn('link', array('account/referral-faq', ), true) . '" data-xf-click="overlay"><i class="fa fa-question-circle" aria-hidden="true"></i> ' . 'What\'s this?' . '</a>
			</span>
		';
	}
	$__finalCompiled .= '
	</div>
';
	return $__finalCompiled;
},
'invitation_tabs' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'activeTab' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<h2 class="block-tabHeader tabs hScroller" data-xf-init="h-scroller" role="tablist">
		<span class="hScroller-scroll">
			' . '
			';
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('siropuReferralContests', 'createInvitations', ))) {
		$__finalCompiled .= '
				<a href="' . $__templater->fn('link', array('account/invitations/create', ), true) . '" class="tabs-tab' . (($__vars['activeTab'] == 'create') ? ' is-active' : '') . '" role="tab" tabindex="0">' . 'Create invitations' . '</a>
			';
	}
	$__finalCompiled .= '
			<a href="' . $__templater->fn('link', array('account/invitations/list', ), true) . '" class="tabs-tab' . (($__vars['activeTab'] != 'create') ? ' is-active' : '') . '" role="tab" tabindex="0">' . ($__vars['xf']['options']['siropuReferralContestsCreateInvitations'] ? 'Your invitations' : 'Invitations sent') . '</a>
		</span>
	</h2>
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '

' . '

';
	return $__finalCompiled;
});