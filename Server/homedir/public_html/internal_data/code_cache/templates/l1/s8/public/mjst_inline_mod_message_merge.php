<?php
// FROM HASH: 20a1d857a02233ef24fab5efcd7ee184
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Inline moderation - Merge messages');
	$__finalCompiled .= '

';
	$__compilerTemp1 = array();
	if ($__templater->isTraversable($__vars['messages'])) {
		foreach ($__vars['messages'] AS $__vars['messageId'] => $__vars['message']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['messageId'],
				'label' => ($__templater->escape($__vars['message']['User']['username']) ?: $__templater->escape($__vars['message']['username'])) . ' &middot; ' . $__templater->fn('date_time', array($__vars['message']['message_date'], ), true),
				'_type' => 'option',
			);
		}
	}
	$__compilerTemp2 = '';
	if ($__templater->isTraversable($__vars['messages'])) {
		foreach ($__vars['messages'] AS $__vars['message']) {
			$__compilerTemp2 .= '
		' . $__templater->formHiddenVal('ids[]', $__vars['message']['message_id'], array(
			)) . '
	';
		}
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formInfoRow('Are you sure you want to merge ' . $__templater->escape($__vars['total']) . ' messages together?', array(
		'rowtype' => 'confirm',
	)) . '

			' . $__templater->formSelectRow(array(
		'name' => 'target_message_id',
		'value' => $__vars['first']['message_id'],
	), $__compilerTemp1, array(
		'label' => 'Merge into message',
	)) . '

			' . $__templater->formTextAreaRow(array(
		'name' => 'message',
		'value' => $__vars['messageText'],
		'rows' => '5',
		'autosize' => 'true',
		'maxlength' => $__vars['xf']['options']['messageMaxLength'],
	), array(
		'label' => 'Preview',
	)) . '

			' . $__templater->callMacro('helper_action', 'author_alert', array(
		'selected' => ($__vars['total'] == 1),
	), $__vars) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'merge',
	), array(
	)) . '
	</div>

	' . $__compilerTemp2 . '

	' . $__templater->formHiddenVal('type', 'support_ticket_message', array(
	)) . '
	' . $__templater->formHiddenVal('action', 'merge', array(
	)) . '
	' . $__templater->formHiddenVal('confirmed', '1', array(
	)) . '

	' . $__templater->fn('redirect_input', array($__vars['redirect'], null, true)) . '
', array(
		'action' => $__templater->fn('link', array('inline-mod', ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});