<?php
// FROM HASH: a2bf5c973b000726d66611bebf8dbbbb
return array('macros' => array('kb_categories' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'kb' => '!',
		'kbCategories' => '!',
		'withRow' => '1',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__vars['withRow']) {
		$__finalCompiled .= '
		';
		$__compilerTemp1 = array(array(
			'value' => '',
			'label' => $__vars['xf']['language']['parenthesis_open'] . 'None' . $__vars['xf']['language']['parenthesis_close'],
			'_type' => 'option',
		));
		$__compilerTemp1 = $__templater->mergeChoiceOptions($__compilerTemp1, $__vars['kbCategories']);
		$__finalCompiled .= $__templater->formSelectRow(array(
			'name' => 'kb_category_id',
			'value' => $__vars['kb']['kb_category_id'],
		), $__compilerTemp1, array(
			'label' => 'Knowledge base category',
		)) . '
	';
	} else {
		$__finalCompiled .= '
		';
		$__compilerTemp2 = array(array(
			'value' => '',
			'label' => $__vars['xf']['language']['parenthesis_open'] . 'None' . $__vars['xf']['language']['parenthesis_close'],
			'_type' => 'option',
		));
		$__compilerTemp2 = $__templater->mergeChoiceOptions($__compilerTemp2, $__vars['kbCategories']);
		$__finalCompiled .= $__templater->formSelect(array(
			'name' => 'kb_category_id',
			'value' => $__vars['kb']['kb_category_id'],
		), $__compilerTemp2) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['kb'], 'isInsert', array())) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add knowledge base');
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit knowledge base' . $__vars['xf']['language']['label_separator']);
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['kb'], 'isUpdate', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('', array(
			'href' => $__templater->fn('link', array('support-tickets/knowledge-base/delete', $__vars['kb'], ), false),
			'icon' => 'delete',
			'overlay' => 'true',
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

' . '
';
	$__compilerTemp1 = '';
	if ($__vars['attachmentData']) {
		$__compilerTemp1 .= '
						' . $__templater->callMacro('public:helper_attach_upload', 'upload_block', array(
			'attachmentData' => $__vars['attachmentData'],
		), $__vars) . '
					';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formTextBoxRow(array(
		'name' => 'title',
		'value' => $__vars['kb']['title'],
	), array(
		'label' => 'Title',
	)) . '

			' . $__templater->callMacro(null, 'kb_categories', array(
		'kb' => $__vars['kb'],
		'kbCategories' => $__vars['kbCategories'],
	), $__vars) . '

			<hr class="formRowSep" />
			<div data-xf-init="attachment-manager">
				' . $__templater->formEditorRow(array(
		'name' => 'message',
		'value' => $__vars['kb']['message'],
		'attachments' => ((!$__templater->fn('empty', array($__vars['attachmentData']['attachments']))) ? $__vars['attachmentData']['attachments'] : array()),
		'data-min-height' => '200',
	), array(
		'label' => 'Message',
	)) . '
				' . $__templater->formRow('
					' . $__compilerTemp1 . '
				', array(
	)) . '
			</div>
			<hr class="formRowSep" />

			' . $__templater->formNumberBoxRow(array(
		'name' => 'display_order',
		'value' => $__vars['kb']['display_order'],
		'min' => '0',
		'step' => '1',
	), array(
		'label' => 'Display order',
	)) . '

			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'is_active',
		'label' => 'Active',
		'selected' => $__vars['kb']['is_active'],
		'_type' => 'option',
	)), array(
	)) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'sticky' => 'true',
		'icon' => 'save',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('support-tickets/knowledge-base/save', $__vars['kb'], ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});