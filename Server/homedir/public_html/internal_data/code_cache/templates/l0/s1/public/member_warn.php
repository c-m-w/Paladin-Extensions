<?php
// FROM HASH: e17487ece59d861034565630df87e429
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Warn member' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['user']['username']));
	$__finalCompiled .= '

';
	if ($__vars['breadcrumbs']) {
		$__finalCompiled .= '
	';
		$__templater->breadcrumbs($__vars['breadcrumbs']);
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	$__templater->includeJs(array(
		'src' => 'xf/form_fill.js',
		'min' => '1',
	));
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__vars['contentUrl']) {
		$__compilerTemp1 .= '
					<a href="' . $__templater->escape($__vars['contentUrl']) . '">' . $__templater->escape($__vars['title']) . '</a>
				';
	} else {
		$__compilerTemp1 .= '
					' . $__templater->escape($__vars['title']) . '
				';
	}
	$__compilerTemp2 = '';
	if ($__vars['contentActions']['delete'] OR $__vars['contentActions']['public']) {
		$__compilerTemp2 .= '
			<h2 class="block-formSectionHeader"><span class="block-formSectionHeader-aligner">' . 'Content action' . '</span></h2>
			<div class="block-body">
				';
		$__compilerTemp3 = array(array(
			'value' => '',
			'label' => 'Do nothing',
			'_type' => 'option',
		));
		if ($__vars['contentActions']['delete']) {
			$__compilerTemp3[] = array(
				'value' => 'delete',
				'label' => 'Delete the content',
				'hint' => 'The item will remain viewable by moderators and may be restored at a later date.',
				'_dependent' => array($__templater->formTextBox(array(
				'name' => 'action_options[delete_reason]',
				'placeholder' => 'Reason for deletion' . $__vars['xf']['language']['ellipsis'],
				'maxlength' => $__templater->fn('max_length', array('XF:DeletionLog', 'delete_reason', ), false),
			))),
				'_type' => 'option',
			);
		}
		if ($__vars['contentActions']['public']) {
			$__compilerTemp3[] = array(
				'value' => 'public',
				'label' => 'Post a public warning',
				'hint' => 'This will be visible to anyone who can see the content for which this member is being warned.',
				'_dependent' => array($__templater->formTextBox(array(
				'name' => 'action_options[public_message]',
				'maxlength' => '255',
				'placeholder' => 'Public warning text' . $__vars['xf']['language']['ellipsis'],
			))),
				'_type' => 'option',
			);
		}
		$__compilerTemp2 .= $__templater->formRadioRow(array(
			'name' => 'content_action',
			'value' => $__templater->method($__vars['user'], 'getWarningDefaultContentAction', array()),
		), $__compilerTemp3, array(
			'label' => 'Content action',
		)) . '
			</div>
		';
	}
	$__compilerTemp4 = '';
	if ($__vars['xf']['options']['sv_warningimprovements_sticky_button']) {
		$__compilerTemp4 .= '
	' . $__templater->formCheckBoxRow(array(
		), array(array(
			'name' => 'send_warning_alert',
			'value' => '1',
			'checked' => ($__vars['xf']['options']['sv_warningimprovements_alert_send_default'] ? true : false),
			'label' => 'Send alert on warning',
			'_type' => 'option',
		)), array(
		)) . '

' . $__templater->formSubmitRow(array(
			'submit' => 'Warn',
			'sticky' => 'true',
		), array(
		)) . '
';
	} else {
		$__compilerTemp4 .= '
	' . $__templater->formSubmitRow(array(
			'submit' => 'Warn',
		), array(
		)) . '
';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formRow($__templater->fn('username_link', array($__vars['user'], false, array(
	))), array(
		'label' => 'Member',
	)) . '

			' . $__templater->formRow('
				' . $__compilerTemp1 . '
			', array(
		'label' => 'Content',
	)) . '

			' . $__templater->includeTemplate('sv_member_warn_chooser', $__vars) . '

			<div id="WarningEditableContainer">
				' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'points_enable',
		'value' => '1',
		'selected' => true,
		'label' => 'Apply warning points' . $__vars['xf']['language']['label_separator'],
		'_dependent' => array($__templater->formNumberBox(array(
		'name' => 'points',
		'value' => '1',
		'min' => '0',
	))),
		'_type' => 'option',
	)), array(
		'label' => 'Warning points',
	)) . '

				' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'expiry_enable',
		'value' => '1',
		'selected' => true,
		'label' => 'Points expire after' . $__vars['xf']['language']['label_separator'],
		'_dependent' => array('
							<div class="inputGroup">
								' . $__templater->formNumberBox(array(
		'name' => 'expiry_value',
		'value' => '1',
		'min' => '0',
	)) . '
								<span class="inputGroup-splitter"></span>
								' . $__templater->formSelect(array(
		'name' => 'expiry_unit',
		'value' => 'months',
		'class' => 'input--inline',
	), array(array(
		'value' => 'hours',
		'label' => 'Hours',
		'_type' => 'option',
	),
	array(
		'value' => 'days',
		'label' => 'Days',
		'_type' => 'option',
	),
	array(
		'value' => 'weeks',
		'label' => 'Weeks',
		'_type' => 'option',
	),
	array(
		'value' => 'months',
		'label' => 'Months',
		'_type' => 'option',
	),
	array(
		'value' => 'years',
		'label' => 'Years',
		'_type' => 'option',
	))) . '
							</div>
						'),
		'_type' => 'option',
	)), array(
		'label' => 'Points expiry',
	)) . '
			</div>

			' . $__templater->formTextAreaRow(array(
		'name' => 'notes',
		'autosize' => 'true',
	), array(
		'label' => 'Notes',
		'explain' => 'This will not be shown to the member receiving the warning.',
	)) . '
		</div>

		' . $__templater->includeTemplate('sv_warningimprovements_member_warn7', $__vars) . '
<h2 class="block-formSectionHeader"><span class="block-formSectionHeader-aligner">' . 'Member notification' . '</span></h2>
		<div class="block-body">
			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'start_conversation',
		'value' => '1',
		'data-xf-init' => 'disabler',
		'data-container' => '#WarningConversation',
		'data-hide' => 'true',
		'label' => 'Start a conversation with ' . $__templater->escape($__vars['user']['username']) . '',
		'_type' => 'option',
	)), array(
	)) . '

			<div id="WarningConversation">
				' . $__templater->formTextBoxRow(array(
		'name' => 'conversation_title',
		'maxlength' => $__templater->fn('max_length', array('XF:ConversationMaster', 'title', ), false),
	), array(
		'label' => 'Title',
	)) . '

				' . $__templater->formTextAreaRow(array(
		'name' => 'conversation_message',
		'rows' => '6',
		'autosize' => 'true',
		'maxlength' => $__vars['xf']['options']['messageMaxLength'],
	), array(
		'label' => 'Message',
	)) . '

				' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'open_invite',
		'value' => '1',
		'checked' => ($__vars['xf']['options']['sv_warningimprovements_conversation_invite'] ? true : false),
		'label' => '
						' . 'Allow ' . $__templater->escape($__vars['user']['username']) . ' to invite others to this conversation' . '
					',
		'_type' => 'option',
	),
	array(
		'name' => 'conversation_locked',
		'value' => '1',
		'checked' => ($__vars['xf']['options']['sv_warningimprovements_conversation_locked'] ? true : false),
		'label' => '
						' . 'Lock conversation (no responses will be allowed)' . '
					',
		'_type' => 'option',
	)), array(
	)) . '
			</div>
		</div>

		' . $__compilerTemp2 . '

		' . $__compilerTemp4 . '
	</div>

	' . $__templater->fn('redirect_input', array(null, null, true)) . '
	' . $__templater->formHiddenVal('filled_warning_definition_id', '0', array(
	)) . '
	<input type="checkbox" id="WarningEditableInput"
		data-xf-init="disabler" data-container="#WarningEditableContainer"
		checked="checked" style="display: none" />
', array(
		'action' => $__vars['warnUrl'],
		'ajax' => 'true',
		'class' => 'block',
		'data-xf-init' => 'form-fill',
	));
	return $__finalCompiled;
});