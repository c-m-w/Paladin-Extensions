<?php
// FROM HASH: 72034544b92504df05bef3d8423df4e1
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Reply to ticket');
	$__finalCompiled .= '

';
	$__templater->setPageParam('head.' . 'metaNoindex', $__templater->preEscaped('<meta name="robots" content="noindex" />'));
	$__finalCompiled .= '

';
	$__templater->breadcrumbs($__templater->method($__vars['ticket'], 'getBreadcrumbs', array()));
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__vars['attachmentData']) {
		$__compilerTemp1 .= '
					' . $__templater->callMacro('helper_attach_upload', 'upload_block', array(
			'attachmentData' => $__vars['attachmentData'],
			'forceHash' => $__vars['ticket']['draft_reply']['attachment_hash'],
		), $__vars) . '
				';
	}
	$__compilerTemp2 = '';
	if ($__vars['xf']['options']['multiQuote']) {
		$__compilerTemp2 .= '
					' . $__templater->callMacro('multi_quote_macros', 'button', array(
			'href' => $__templater->fn('link', array('support-tickets/multi-quote', $__vars['ticket'], ), false),
			'messageSelector' => '.js-post',
			'storageKey' => 'multiQuoteTicket',
		), $__vars) . '
				';
	}
	$__compilerTemp3 = '';
	if (!$__vars['xf']['visitor']['user_id']) {
		$__compilerTemp3 .= '
				' . $__templater->formTextBoxRow(array(
			'name' => '_xfUsername',
			'data-xf-init' => 'guest-username',
			'maxlength' => $__templater->fn('max_length', array($__vars['xf']['visitor'], 'username', ), false),
		), array(
			'label' => 'Name',
		)) . '

				' . $__templater->formRowIfContent($__templater->fn('captcha', array(false)), array(
			'label' => 'Verification',
		)) . '
			';
	} else {
		$__compilerTemp3 .= '
				' . $__templater->callMacro('mjst_ticket_edit_macros', 'watch_input', array(
			'ticket' => $__vars['ticket'],
		), $__vars) . '
			';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formEditorRow(array(
		'name' => 'message',
		'value' => $__vars['defaultMessage'],
		'attachments' => ($__vars['attachmentData'] ? $__vars['attachmentData']['attachments'] : array()),
		'placeholder' => 'Write your reply...',
	), array(
		'rowtype' => 'fullWidth noLabel',
		'label' => 'Message',
	)) . '

			' . $__templater->formRow('
				' . $__compilerTemp1 . '

				' . $__compilerTemp2 . '
				' . $__templater->button('', array(
		'class' => 'button--link u-jsOnly',
		'data-xf-click' => 'preview-click',
		'icon' => 'preview',
	), '', array(
	)) . '
			', array(
	)) . '

			' . $__compilerTemp3 . '
		</div>
		' . $__templater->formSubmitRow(array(
		'submit' => 'Post reply',
		'icon' => 'reply',
		'sticky' => 'true',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('support-tickets/add-reply', $__vars['ticket'], ), false),
		'class' => 'block',
		'ajax' => 'true',
		'draft' => $__templater->fn('link', array('support-tickets/draft', $__vars['ticket'], ), false),
		'data-xf-init' => 'attachment-manager',
		'data-preview-url' => $__templater->fn('link', array('tickets/reply-preview', $__vars['ticket'], ), false),
	));
	return $__finalCompiled;
});