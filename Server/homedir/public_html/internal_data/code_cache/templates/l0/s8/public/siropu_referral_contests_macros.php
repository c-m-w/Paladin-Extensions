<?php
// FROM HASH: 0953ffcf18a81b06d746fb8372789d4f
return array('macros' => array('invitation_form' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__compilerTemp1 = '';
	if (!$__vars['xf']['options']['siropuReferralContestsSenderName']) {
		$__compilerTemp1 .= '
			' . $__templater->formTextBoxRow(array(
			'name' => 'name',
			'value' => $__vars['xf']['visitor']['username'],
		), array(
			'label' => 'Your name',
		)) . '
		';
	}
	$__compilerTemp2 = '';
	if (!$__vars['xf']['options']['siropuReferralContestsSenderEmail']) {
		$__compilerTemp2 .= '
			' . $__templater->formRow('', array(
			'label' => 'Your email',
			'html' => $__templater->escape($__vars['xf']['visitor']['email']),
			'autocomplete' => 'off',
		)) . '
		';
	}
	$__finalCompiled .= $__templater->form('
		' . $__compilerTemp1 . '

		' . $__compilerTemp2 . '

		<hr class="formRowSep" />

		' . $__templater->formRow('
			<ul class="listPlain inputGroup-container">
				<li class="inputGroup" data-xf-init="field-adder" data-increment-format="email[]">
					' . $__templater->formTextBox(array(
		'name' => 'email[]',
		'type' => 'email',
		'placeholder' => 'Email',
		'autocomplete' => 'off',
	)) . '
				</li>
			</ul>
		', array(
		'label' => 'Recipient email address',
		'explain' => 'You can send invitations to multiple emails addresses by placing each email in a separate input field.',
	)) . '

		<hr class="formRowSep" />

		' . $__templater->formTextBoxRow(array(
		'name' => 'subject',
		'value' => $__vars['xf']['options']['siropuReferralContestsPredefinedEmailSubject'],
		'autocomplete' => 'off',
	), array(
		'label' => 'Subject',
	)) . '

		' . $__templater->formTextAreaRow(array(
		'name' => 'message',
		'value' => $__vars['xf']['options']['siropuReferralContestsPredefinedEmailMessage'],
		'rows' => '5',
	), array(
		'label' => 'Message',
		'explain' => ($__vars['xf']['options']['siropuReferralContestsInvitationOnly'] ? 'An invitation link with a unique code will be sent with the message.' : 'Your personal referral link will be sent with the message.'),
	)) . '

		' . $__templater->formSubmitRow(array(
		'icon' => 'email',
		'submit' => 'Send invitation',
	), array(
	)) . '
	', array(
		'action' => $__templater->fn('link', array('account/invitations/create', ), false),
		'ajax' => 'true',
		'data-force-flash-message' => 'true',
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
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('siropuReferralContests', 'sendInvitations', )) != 0) {
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
			<a href="' . $__templater->fn('link', array('account/invitations/list', ), true) . '" class="tabs-tab' . (($__vars['activeTab'] == 'list') ? ' is-active' : '') . '" role="tab" tabindex="0">' . ($__vars['xf']['options']['siropuReferralContestsCreateInvitations'] ? 'Your invitations' : 'Invitations sent') . '</a>
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