<?php
// FROM HASH: 699c20dadd194a58d5d3cc7392d5f3ca
return array('macros' => array('pre_reply_groups' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'reply' => '!',
		'replyGroups' => '!',
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
		$__compilerTemp1 = $__templater->mergeChoiceOptions($__compilerTemp1, $__vars['replyGroups']);
		$__finalCompiled .= $__templater->formSelectRow(array(
			'name' => 'reply_group_id',
			'value' => $__vars['reply']['reply_group_id'],
		), $__compilerTemp1, array(
			'label' => 'Predefined reply group',
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
		$__compilerTemp2 = $__templater->mergeChoiceOptions($__compilerTemp2, $__vars['replyGroups']);
		$__finalCompiled .= $__templater->formSelect(array(
			'name' => 'reply_group_id',
			'value' => $__vars['reply']['reply_group_id'],
		), $__compilerTemp2) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['reply'], 'isInsert', array())) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add predefined reply');
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit predefined reply' . $__vars['xf']['language']['label_separator']);
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['reply'], 'isUpdate', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('', array(
			'href' => $__templater->fn('link', array('mjst-support/predefined-replies/delete', $__vars['reply'], ), false),
			'icon' => 'delete',
			'overlay' => 'true',
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

' . '
' . $__templater->form('
	<div class="block-container">
		<div class="block-body">

			' . $__templater->formTextBoxRow(array(
		'name' => 'title',
		'value' => $__vars['reply']['title'],
	), array(
		'label' => 'Title',
	)) . '

			' . $__templater->callMacro(null, 'pre_reply_groups', array(
		'reply' => $__vars['reply'],
		'replyGroups' => $__vars['replyGroups'],
	), $__vars) . '

			<hr class="formRowSep" />
			' . $__templater->formEditorRow(array(
		'name' => 'message',
		'value' => $__vars['reply']['message'],
		'data-min-height' => '200',
	), array(
		'label' => 'Message',
		'explain' => 'You may use these placeholders: <br />
[TICKET_USER] - the ticket submitter\'s name.<br />
[BOARD_TITLE] - the board title.<br />
[SUPPORT_USER] - the supporter name who is replying.<br />',
	)) . '

			<hr class="formRowSep" />

			' . $__templater->callMacro('display_order_macros', 'row', array(
		'value' => $__vars['reply']['display_order'],
	), $__vars) . '

			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'is_active',
		'label' => 'Active',
		'selected' => $__vars['reply']['is_active'],
		'_type' => 'option',
	)), array(
	)) . '

			' . $__templater->callMacro('helper_user_group_edit', 'checkboxes', array(
		'selectedUserGroups' => ($__vars['reply']['reply_id'] ? $__vars['reply']['allowed_user_group_ids'] : array(-1, )),
	), $__vars) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'sticky' => 'true',
		'icon' => 'save',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('mjst-support/predefined-replies/save', $__vars['reply'], ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});