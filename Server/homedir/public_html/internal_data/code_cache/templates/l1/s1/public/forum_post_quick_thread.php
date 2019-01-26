<?php
// FROM HASH: df74ab9058d859e78c115a14173deea4
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__compilerTemp1 = '';
	if ($__templater->method($__vars['forum']['draft_thread'], 'exists', array())) {
		$__compilerTemp1 .= '
			' . $__templater->formRow('
				<div class="block-rowMessage block-rowMessage--important block-rowMessage--small">
					<a href="' . $__templater->fn('link', array('forums/post-thread', $__vars['forum'], ), true) . '">' . 'You have a saved draft. Click here to load it.' . '</a>
				</div>
			', array(
			'rowtype' => 'fullWidth noGutter noLabel mergeNext',
		)) . '
		';
	}
	$__compilerTemp2 = '';
	if ($__templater->method($__vars['forum'], 'canEditTags', array()) AND $__vars['forum']['min_tags']) {
		$__compilerTemp2 .= '
			<hr class="formRowSep" />
			';
		$__compilerTemp3 = '';
		if ($__vars['forum']['min_tags']) {
			$__compilerTemp3 .= '
						' . 'This content must have at least ' . $__templater->escape($__vars['forum']['min_tags']) . ' tag(s).' . '
					';
		}
		$__compilerTemp2 .= $__templater->formTokenInputRow(array(
			'name' => 'tags',
			'href' => $__templater->fn('link', array('misc/tag-auto-complete', ), false),
			'min-length' => $__vars['xf']['options']['tagLength']['min'],
			'max-length' => $__vars['xf']['options']['tagLength']['max'],
			'max-tokens' => $__vars['xf']['options']['maxContentTags'],
		), array(
			'rowtype' => 'fullWidth noGutter',
			'label' => 'Tags',
			'explain' => '
					' . 'Multiple tags may be separated by commas.' . '
					' . $__compilerTemp3 . '
				',
		)) . '
		';
	}
	$__compilerTemp4 = '';
	if (!$__vars['xf']['visitor']['user_id']) {
		$__compilerTemp4 .= '
			' . $__templater->formTextBoxRow(array(
			'name' => '_xfUsername',
			'data-xf-init' => 'guest-username',
			'maxlength' => $__templater->fn('max_length', array($__vars['xf']['visitor'], 'username', ), false),
		), array(
			'rowtype' => 'fullWidth noGutter',
			'label' => 'Name',
		)) . '

			' . $__templater->formRowIfContent($__templater->fn('captcha', array(false)), array(
			'label' => 'Verification',
			'rowtype' => 'fullWidth noGutter noLabel',
		)) . '
		';
	} else {
		$__compilerTemp4 .= '
			' . $__templater->callMacro('helper_thread_options', 'watch_input', array(
			'thread' => $__vars['thread'],
			'rowType' => 'fullWidth noGutter noLabel',
			'visible' => false,
		), $__vars) . '
		';
	}
	$__compilerTemp5 = '';
	$__compilerTemp6 = '';
	$__compilerTemp6 .= '
						';
	if ($__vars['attachmentData'] OR $__vars['xf']['options']['multiQuote']) {
		$__compilerTemp6 .= '
							';
		if ($__vars['attachmentData']) {
			$__compilerTemp6 .= '
								' . $__templater->callMacro('helper_attach_upload', 'upload_block', array(
				'attachmentData' => $__vars['attachmentData'],
				'rowType' => 'fullWidth',
			), $__vars) . '
							';
		}
		$__compilerTemp6 .= '

							';
		if ($__vars['xf']['options']['multiQuote']) {
			$__compilerTemp6 .= '
								' . $__templater->callMacro('multi_quote_macros', 'button', array(
				'href' => $__templater->fn('link', array('threads/multi-quote', $__vars['thread'], ), false),
				'messageSelector' => '.js-post',
				'storageKey' => 'multiQuoteThread',
			), $__vars) . '
							';
		}
		$__compilerTemp6 .= '
						';
	}
	$__compilerTemp6 .= '
					';
	if (strlen(trim($__compilerTemp6)) > 0) {
		$__compilerTemp5 .= '
				<div class="formButtonGroup-extra">
					' . $__compilerTemp6 . '
				</div>
			';
	}
	$__finalCompiled .= $__templater->form('

	<div class="js-quickThreadFields" data-xf-init="attachment-manager">

		' . $__compilerTemp1 . '

		' . $__templater->formEditorRow(array(
		'name' => 'message',
		'value' => $__vars['post']['message'],
		'rows' => '3',
		'data-min-height' => '100',
		'data-max-height' => '300',
		'placeholder' => 'Message' . $__vars['xf']['language']['ellipsis'],
	), array(
		'rowtype' => 'fullWidth noGutter noLabel mergeNext',
		'label' => 'Message',
	)) . '

		' . $__templater->callMacro('custom_fields_macros', 'custom_fields_edit', array(
		'type' => 'threads',
		'set' => $__vars['thread']['custom_fields'],
		'editMode' => $__templater->method($__vars['thread'], 'getFieldEditMode', array()),
		'onlyInclude' => $__vars['forum']['field_cache'],
		'rowType' => 'fullWidth noGutter',
		'requiredOnly' => ($__vars['inlineMode'] ? true : false),
	), $__vars) . '

		' . $__compilerTemp2 . '

		' . $__compilerTemp4 . '

		<div class="formButtonGroup">
			<div class="formButtonGroup-primary">
				' . $__templater->button('
					' . 'Post' . '
				', array(
		'type' => 'submit',
		'class' => 'button--primary',
		'icon' => 'write',
	), '', array(
	)) . '

				' . $__templater->button('More options' . $__vars['xf']['language']['ellipsis'], array(
		'type' => 'submit',
		'formnovalidate' => 'formnovalidate',
		'name' => 'more-options',
		'value' => '1',
		'title' => $__templater->filter('Show the full post new thread editor, with options for attaching files, creating polls and more', array(array('for_attr', array()),), false),
		'data-prevent-ajax' => 'true',
		'data-xf-init' => 'tooltip',
	), '', array(
	)) . '

				' . $__templater->button('', array(
		'type' => 'reset',
		'class' => 'button--icon button--icon--cancel button--iconOnly',
		'title' => $__templater->filter('Cancel', array(array('for_attr', array()),), false),
		'data-xf-init' => 'tooltip',
	), '', array(
	)) . '
			</div>
			' . $__compilerTemp5 . '
		</div>
	</div>
', array(
		'action' => $__templater->fn('link', array('forums/post-thread', $__vars['forum'], ), false),
		'draft' => $__templater->fn('link', array('forums/draft', $__vars['forum'], ), false),
	));
	return $__finalCompiled;
});