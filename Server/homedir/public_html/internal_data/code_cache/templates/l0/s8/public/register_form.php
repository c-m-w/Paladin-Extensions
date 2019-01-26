<?php
// FROM HASH: b9ea70d9523e03fa32d8f4f4c0da0c9c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeJs(array(
		'src' => 'xf/login_signup.js',
		'min' => '1',
	));
	$__finalCompiled .= '
';
	if ($__vars['xf']['options']['siropuReferralContestsInvitationOnly'] OR $__vars['xf']['options']['siropuReferralContestsReferrerUserField']) {
		$__finalCompiled .= '
	';
		$__templater->includeJs(array(
			'src' => 'siropu/rc/invitation.js',
			'min' => '1',
		));
		$__templater->inlineJs('
		XF.siropuInvitationCode = \'' . $__templater->fn('siropu_invitation_code', array(), false) . '\';
		XF.siropuReferrerUsername = \'' . $__templater->fn('siropu_referrer_username', array(), false) . '\';
		XF.siropuReferrerAutocomplete = ' . ($__vars['xf']['options']['siropuReferralContestsReferrerAutocomplete'] ? 'true' : 'false') . ';
		XF.siropuReferralEmail = \'' . $__templater->fn('siropu_referral_invitation_email', array(), false) . '\';
	');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '
';
	$__templater->setPageParam('uix_hideExtendedFooter', '1');
	$__finalCompiled .= '
';
	$__templater->setPageParam('uix_hideNotices', '1');
	$__finalCompiled .= '
';
	$__templater->setPageParam('uix_hideBreadcrumb', '1');
	$__finalCompiled .= '
' . '

';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Register');
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if (!$__templater->test($__vars['providers'], 'empty', array())) {
		$__compilerTemp1 .= '
					';
		$__compilerTemp2 = '';
		if ($__templater->isTraversable($__vars['providers'])) {
			foreach ($__vars['providers'] AS $__vars['provider']) {
				$__compilerTemp2 .= '
							<li>
								' . $__templater->button('
									' . $__templater->escape($__vars['provider']['title']) . '
								', array(
					'href' => $__templater->fn('link', array('register/connected-accounts', $__vars['provider'], array('setup' => true, ), ), false),
					'class' => 'button--provider button--provider--' . $__vars['provider']['provider_id'],
				), '', array(
				)) . '
							</li>
						';
			}
		}
		$__compilerTemp1 .= $__templater->formRow('

					<ul class="listHeap">
						' . $__compilerTemp2 . '
					</ul>
				', array(
			'rowtype' => 'button',
			'label' => 'Register faster using',
		)) . '
			';
	}
	$__compilerTemp3 = '';
	if (($__templater->fn('rand', array(0, 2, ), false) == 1)) {
		$__compilerTemp3 .= '
				' . $__templater->formTextBoxRow(array(
			'name' => $__templater->method($__vars['regForm'], 'getFieldName', array('email_hp', )),
			'value' => '',
			'type' => 'email',
			'autocomplete' => 'off',
			'maxlength' => $__templater->fn('max_length', array($__vars['xf']['visitor'], 'email', ), false),
		), array(
			'rowclass' => 'formRow--limited',
			'label' => 'Email',
			'explain' => 'Please leave this field blank.',
		)) . '
			';
	}
	$__compilerTemp4 = '';
	if (($__templater->fn('rand', array(0, 2, ), false) == 1)) {
		$__compilerTemp4 .= '
				' . $__templater->formTextBoxRow(array(
			'name' => 'email',
			'value' => '',
			'type' => 'email',
			'autocomplete' => 'off',
			'maxlength' => $__templater->fn('max_length', array($__vars['xf']['visitor'], 'email', ), false),
		), array(
			'rowclass' => 'formRow--limited',
			'label' => 'Email',
			'explain' => 'Please leave this field blank.',
		)) . '
			';
	}
	$__compilerTemp5 = '';
	if (($__templater->fn('rand', array(0, 2, ), false) == 1)) {
		$__compilerTemp5 .= '
				' . $__templater->formTextBoxRow(array(
			'name' => 'password',
			'type' => 'password',
			'autocomplete' => 'off',
		), array(
			'rowclass' => 'formRow--limited',
			'label' => 'Password',
			'explain' => 'Please leave this field blank.',
		)) . '
			';
	}
	$__finalCompiled .= $__templater->form('
	
	<div class="block-container">
		<div class="block-body">
			' . $__compilerTemp1 . '
			
			' . '

			' . $__templater->callMacro('register_macros', 'username_row', array(
		'fieldName' => $__templater->method($__vars['regForm'], 'getFieldName', array('username', )),
		'value' => $__vars['fields']['username'],
	), $__vars) . '
			
			' . $__templater->formTextBoxRow(array(
		'name' => 'username',
		'value' => '',
		'autocomplete' => 'off',
		'maxlength' => $__templater->fn('max_length', array($__vars['xf']['visitor'], 'username', ), false),
	), array(
		'rowclass' => 'formRow--limited',
		'label' => 'User name',
		'explain' => 'Please leave this field blank.',
	)) . '

			' . '
			' . $__compilerTemp3 . '

			' . $__templater->callMacro('register_macros', 'email_row', array(
		'fieldName' => $__templater->method($__vars['regForm'], 'getFieldName', array('email', )),
		'value' => $__vars['fields']['email'],
	), $__vars) . '

			' . '
			' . $__compilerTemp4 . '

			' . '
			' . $__compilerTemp5 . '

			' . $__templater->formTextBoxRow(array(
		'name' => $__templater->method($__vars['regForm'], 'getFieldName', array('password', )),
		'type' => 'password',
		'autocomplete' => 'off',
		'required' => 'required',
	), array(
		'label' => 'Password',
		'hint' => 'Required',
	)) . '

			' . $__templater->callMacro('register_macros', 'dob_row', array(), $__vars) . '

			' . $__templater->callMacro('register_macros', 'location_row', array(
		'value' => $__vars['fields']['location'],
	), $__vars) . '

			' . $__templater->callMacro('register_macros', 'custom_fields', array(), $__vars) . '

			' . $__templater->formRowIfContent($__templater->fn('captcha', array(false)), array(
		'label' => 'Verification',
		'hint' => 'Required',
	)) . '

			' . '

			' . $__templater->callMacro('register_macros', 'tos_row', array(), $__vars) . '
		</div>
		' . $__templater->callMacro('register_macros', 'submit_row', array(), $__vars) . '
	</div>

	' . $__templater->formHiddenVal('reg_key', $__templater->method($__vars['regForm'], 'getUniqueKey', array()), array(
	)) . '
	' . $__templater->formHiddenVal($__templater->method($__vars['regForm'], 'getFieldName', array('timezone', )), '', array(
		'data-xf-init' => 'auto-timezone',
	)) . '
', array(
		'action' => $__templater->fn('link', array('register/register', ), false),
		'ajax' => 'true',
		'class' => 'block',
		'data-xf-init' => 'reg-form',
		'data-timer' => $__vars['xf']['options']['registrationTimer'],
	));
	return $__finalCompiled;
});