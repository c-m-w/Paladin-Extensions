<?php
// FROM HASH: da2b77b71714df2862f94bcec8789403
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Post thread');
	$__finalCompiled .= '

';
	$__templater->breadcrumbs($__templater->method($__vars['forum'], 'getBreadcrumbs', array()));
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__vars['xf']['options']['similarThreadsShowPostThread']) {
		$__compilerTemp1 .= '
';
		$__templater->includeCss('andy_similarthreads.less');
		$__compilerTemp1 .= '
';
		$__templater->inlineJs('
!function($, window, document, _undefined)
{
	$(document).ready(function()
	{
		var pathname = $(location).attr(\'href\');
		var url = pathname.replace(\'post-thread\',\'similarthreads\');		

		$("#title").keyup(function() 
		{ 
			currentTitle = $(\'#title\').val();
			$.ajax(
			{
				type: "POST",
				url: url,
				data: { 
					\'title\': currentTitle,
					_xfToken: XF.config.csrf
				},
				dataType: "html",
				timeout: 500,
				success: function(data) 
				{
					$(data).find(\'.similarthreads-wrapper\').each(function()
					{
						$(\'#similarthreads-result\').empty();
						$(\'#similarthreads-result\').append($(this).html());
						$(\'#similarthreads-result\').slideDown("slow");
					});
				},
				error: function(request, status, err) 
				{
					if(status != "success") {
						$(\'#similarthreads-result\').slideUp("slow");
						$(\'#similarthreads-result\').empty();
					}
				}
			});	
		});
	});	
}
(jQuery, this, document);
');
		$__compilerTemp1 .= '

<div id="similarthreads-result"></div>
';
	}
	$__compilerTemp2 = '';
	if ($__vars['attachmentData']) {
		$__compilerTemp2 .= '
						' . $__templater->callMacro('helper_attach_upload', 'upload_block', array(
			'attachmentData' => $__vars['attachmentData'],
			'forceHash' => $__vars['forum']['draft_thread']['attachment_hash'],
		), $__vars) . '
					';
	}
	$__compilerTemp3 = '';
	if ($__vars['xf']['options']['multiQuote']) {
		$__compilerTemp3 .= '
						' . $__templater->callMacro('multi_quote_macros', 'button', array(
			'href' => $__templater->fn('link', array('threads/multi-quote', $__vars['thread'], ), false),
			'messageSelector' => '.js-post',
			'storageKey' => 'multiQuoteThread',
		), $__vars) . '
					';
	}
	$__compilerTemp4 = '';
	$__compilerTemp5 = '';
	$__compilerTemp5 .= '
						' . $__templater->callMacro('custom_fields_macros', 'custom_fields_edit', array(
		'type' => 'threads',
		'set' => $__vars['thread']['custom_fields'],
		'editMode' => $__templater->method($__vars['thread'], 'getFieldEditMode', array()),
		'onlyInclude' => $__vars['forum']['field_cache'],
		'requiredOnly' => ($__vars['inlineMode'] ? true : false),
	), $__vars) . '
					';
	if (strlen(trim($__compilerTemp5)) > 0) {
		$__compilerTemp4 .= '
					<hr class="formRowSep" />
					' . $__compilerTemp5 . '
				';
	}
	$__compilerTemp6 = '';
	if ($__templater->method($__vars['forum'], 'canEditTags', array())) {
		$__compilerTemp6 .= '
					<hr class="formRowSep" />
					';
		$__compilerTemp7 = '';
		if ($__vars['forum']['min_tags']) {
			$__compilerTemp7 .= '
								' . 'This content must have at least ' . $__templater->escape($__vars['forum']['min_tags']) . ' tag(s).' . '
							';
		}
		$__compilerTemp6 .= $__templater->formTokenInputRow(array(
			'name' => 'tags',
			'value' => ($__vars['thread']['tags'] ?: $__vars['forum']['draft_thread']['tags']),
			'href' => $__templater->fn('link', array('misc/tag-auto-complete', ), false),
			'min-length' => $__vars['xf']['options']['tagLength']['min'],
			'max-length' => $__vars['xf']['options']['tagLength']['max'],
			'max-tokens' => $__vars['xf']['options']['maxContentTags'],
		), array(
			'label' => 'Tags',
			'explain' => '
							' . 'Multiple tags may be separated by commas.' . '
							' . $__compilerTemp7 . '
						',
		)) . '
				';
	}
	$__compilerTemp8 = '';
	if (!$__vars['xf']['visitor']['user_id']) {
		$__compilerTemp8 .= '
					<hr class="formRowSep" />
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
		$__compilerTemp8 .= '
					<hr class="formRowSep" />
					' . $__templater->callMacro('helper_thread_options', 'watch_input', array(
			'thread' => $__vars['thread'],
		), $__vars) . '
					' . $__templater->callMacro('helper_thread_options', 'thread_status', array(
			'thread' => $__vars['thread'],
		), $__vars) . '
				';
	}
	$__compilerTemp9 = '';
	if ($__templater->method($__vars['forum'], 'canCreatePoll', array())) {
		$__compilerTemp9 .= '
			<h2 class="block-formSectionHeader">
				<span class="collapseTrigger collapseTrigger--block' . ($__vars['forum']['draft_thread']['poll'] ? ' is-active' : '') . '" data-xf-click="toggle" data-target="< :up :next">
					<span class="block-formSectionHeader-aligner">' . 'Post a poll' . '</span>
				</span>
			</h2>
			<div class="block-body block-body--collapsible' . ($__vars['forum']['draft_thread']['poll'] ? ' is-active' : '') . '">
				' . $__templater->callMacro('poll_macros', 'add_edit_inputs', array(
			'draft' => $__vars['forum']['draft_thread']['poll'],
		), $__vars) . '
			</div>
		';
	}
	$__finalCompiled .= $__templater->form('

	<div class="block-container">
		<div class="block-body">

			' . $__templater->formPrefixInputRow($__vars['prefixes'], array(
		'type' => 'thread',
		'prefix-value' => ($__vars['forum']['draft_thread']['prefix_id'] ?: ($__vars['thread']['prefix_id'] ?: $__vars['forum']['default_prefix_id'])),
		'textbox-value' => ($__vars['thread']['title'] ?: $__vars['forum']['draft_thread']['title']),
		'textbox-class' => 'input--title',
		'placeholder' => $__vars['forum']['thread_prompt'],
		'autofocus' => 'autofocus',
		'maxlength' => $__templater->fn('max_length', array('XF:Thread', 'title', ), false),
		'id' => 'title',
		'autocomplete' => 'off',
	), array(
		'label' => 'Title',
		'rowtype' => 'fullWidth noLabel',
	)) . '

			' . $__compilerTemp1 . '
<div class="js-inlineNewPostFields">
				' . $__templater->formEditorRow(array(
		'name' => 'message',
		'value' => ($__vars['post']['message'] ?: $__vars['forum']['draft_thread']['message']),
		'attachments' => ($__vars['attachmentData'] ? $__vars['attachmentData']['attachments'] : array()),
	), array(
		'rowtype' => 'fullWidth noLabel mergePrev',
		'label' => 'Message',
	)) . '

				' . $__templater->formRow('
					' . $__compilerTemp2 . '

					' . $__compilerTemp3 . '

					' . $__templater->button('', array(
		'class' => 'button--link u-jsOnly',
		'data-xf-click' => 'preview-click',
		'icon' => 'preview',
	), '', array(
	)) . '
				', array(
	)) . '

				' . $__compilerTemp4 . '

				' . $__compilerTemp6 . '

				' . $__compilerTemp8 . '
			</div>
		</div>

		' . $__compilerTemp9 . '

		' . $__templater->formSubmitRow(array(
		'submit' => 'Post thread',
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
		'action' => $__templater->fn('link', array('forums/post-thread', $__vars['forum'], ), false),
		'ajax' => 'true',
		'class' => 'block',
		'data-xf-init' => 'attachment-manager',
		'draft' => $__templater->fn('link', array('forums/draft', $__vars['forum'], ), false),
		'data-preview-url' => $__templater->fn('link', array('forums/thread-preview', $__vars['forum'], ), false),
	));
	return $__finalCompiled;
});