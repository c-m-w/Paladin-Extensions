<?php
// FROM HASH: 77479db9a44c5db7f535a1b985ce04ca
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Password for ticket' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['ticket']['full_title']));
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
	$__templater->inlineCss('
	.blockMessage{
		text-align: center;
		font-size: 18px;
	}
	.bigText{
		font-size: 22px;
	}
	.codeText{
		font-family: @xf-fontFamilyCode;
		direction: ltr;
		//white-space: nowrap;
		word-wrap: normal;
	}
');
	$__finalCompiled .= '

';
	if (!$__templater->method($__vars['ticket'], 'canViewGuestTicket', array())) {
		$__finalCompiled .= '
' . $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formTextBoxRow(array(
			'name' => 'password',
			'type' => 'password',
		), array(
			'label' => 'Password',
		)) . '
		</div>
		' . $__templater->formSubmitRow(array(
			'submit' => 'Enter ticket',
			'icon' => 'write',
			'sticky' => 'true',
		), array(
		)) . '
	</div>
', array(
			'action' => $__templater->fn('link', array('support-tickets/password', $__vars['ticket'], ), false),
			'ajax' => 'true',
			'class' => 'block',
		)) . '
';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage blockMessage--important bigText">
		';
		if (!$__vars['ticket']['user_id']) {
			$__finalCompiled .= '
			' . 'Password' . $__vars['xf']['language']['label_separator'] . ' <span class="codeText">' . $__templater->escape($__vars['ticket']['guest_password']) . '</span>
		';
		}
		$__finalCompiled .= '
	</div>
';
	}
	return $__finalCompiled;
});