<?php
// FROM HASH: 0e34e78c7423738fc4a42897c47be06f
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Open ticket');
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['ticket'], 'getBreadcrumbs', array())) {
		$__finalCompiled .= '
	';
		$__templater->breadcrumbs($__templater->method($__vars['ticket'], 'getBreadcrumbs', array()));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	$__templater->includeCss('mjst_ticket_open.less');
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if (!$__vars['xf']['visitor']['user_id']) {
		$__compilerTemp1 .= '
				<hr class="formRowSep" />
				' . $__templater->formTextBoxRow(array(
			'name' => '_xfUsername',
			'data-xf-init' => 'guest-username',
			'maxlength' => $__templater->fn('max_length', array($__vars['xf']['visitor'], 'username', ), false),
			'value' => $__vars['draf']['guest_username'],
		), array(
			'label' => 'Name',
		)) . '

				' . $__templater->formTextBoxRow(array(
			'name' => 'guest_email',
			'maxlength' => $__templater->fn('max_length', array($__vars['xf']['visitor'], 'email', ), false),
			'value' => $__vars['draf']['guest_email'],
		), array(
			'label' => 'Email',
		)) . '
			';
	} else if ($__templater->method($__vars['xf']['visitor'], 'canOpenTicketForMember', array())) {
		$__compilerTemp1 .= '
				' . $__templater->formCheckBoxRow(array(
		), array(array(
			'name' => 'is_open',
			'value' => '1',
			'data-hide' => 'true',
			'checked' => $__vars['draft']['is_open'],
			'label' => 'Open ticket for' . $__vars['xf']['language']['ellipsis'],
			'_dependent' => array('
							' . $__templater->callMacro('mjst_ticket_edit_macros', 'owner_type', array(
			'draft' => $__vars['draft'],
			'ticket' => $__vars['ticket'],
		), $__vars) . '
						'),
			'_type' => 'option',
		)), array(
		)) . '
			';
	}
	$__compilerTemp2 = '';
	if ($__vars['xf']['options']['mjstRequireCaptcha']) {
		$__compilerTemp2 .= '
				' . $__templater->formRowIfContent($__templater->fn('captcha', array(false)), array(
			'label' => 'Verification',
		)) . '
			';
	}
	$__compilerTemp3 = '';
	if ($__vars['xf']['options']['mjstNumberSuggestKb'] AND $__templater->method($__vars['xf']['visitor'], 'canViewKb', array())) {
		$__compilerTemp3 .= '
				';
		$__templater->includeJs(array(
			'src' => 'mj/mjst/kb.js',
			'min' => '1',
		));
		$__compilerTemp3 .= '
				<div class="formRow formRow--input formRow--fullWidth formRow--noLabel kbSuggest">
					<div class="mjstKbSuggest" data-xf-init="mjst-kb-suggest"></div>
				</div>
			';
	}
	$__compilerTemp4 = '';
	if ($__vars['xf']['visitor']['user_id']) {
		$__compilerTemp4 .= '
				<hr class="formRowSep" />
				' . $__templater->callMacro('mjst_ticket_edit_macros', 'watch_input', array(
			'ticket' => $__vars['ticket'],
		), $__vars) . '
			';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body js-prefixListenContainer">
			' . $__templater->callMacro('mjst_ticket_edit_macros', 'department', array(
		'ticket' => $__vars['ticket'],
		'departments' => $__vars['departments'],
	), $__vars) . '

			' . $__compilerTemp1 . '

			' . $__compilerTemp2 . '

			' . $__templater->callMacro('mjst_ticket_edit_macros', 'urgency', array(
		'ticket' => $__vars['ticket'],
	), $__vars) . '

			' . $__templater->callMacro('mjst_ticket_edit_macros', 'title', array(
		'ticket' => $__vars['ticket'],
		'prefixes' => $__vars['prefixes'],
	), $__vars) . '

			' . $__compilerTemp3 . '

			' . $__templater->callMacro('mjst_ticket_edit_macros', 'message', array(
		'message' => $__vars['draft']['message'],
		'attachmentData' => $__vars['attachmentData'],
	), $__vars) . '

			<hr class="formRowSep" />
			' . $__templater->callMacro('mjst_ticket_edit_macros', 'custom_fields', array(
		'ticket' => $__vars['ticket'],
		'department' => $__vars['department'],
	), $__vars) . '

			<hr class="formRowSep" />

			' . $__compilerTemp4 . '
		</div>

		' . $__templater->formSubmitRow(array(
		'submit' => 'Open ticket',
		'icon' => 'write',
		'sticky' => 'true',
	), array(
		'html' => '
				' . $__templater->button('', array(
		'class' => 'u-jsOnly',
		'data-xf-click' => 'preview-click',
		'icon' => 'preview',
	), '', array(
	)) . '
			',
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('support-tickets/open', $__vars['ticket'], ), false),
		'upload' => 'true',
		'ajax' => 'true',
		'class' => 'block',
		'draft' => $__templater->fn('link', array('support-tickets/draft', $__vars['ticket'], ), false),
		'data-preview-url' => $__templater->fn('link', array('support-tickets/ticket-preview', ), false),
	));
	return $__finalCompiled;
});