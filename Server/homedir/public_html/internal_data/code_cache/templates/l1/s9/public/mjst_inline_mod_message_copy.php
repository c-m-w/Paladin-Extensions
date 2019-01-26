<?php
// FROM HASH: 768a8eb63d9b7219e9b7bcda89430c15
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Inline moderation - Copy messages');
	$__finalCompiled .= '

';
	$__compilerTemp1 = array();
	if ($__templater->isTraversable($__vars['departments'])) {
		foreach ($__vars['departments'] AS $__vars['department']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['department']['department_id'],
				'label' => $__templater->escape($__vars['department']['title']),
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
		<div class="block-body js-prefixListenContainer">
			' . $__templater->formInfoRow('Are you sure you want to copy ' . $__templater->escape($__vars['total']) . ' message(s) to a new ticket?', array(
		'rowtype' => 'confirm',
	)) . '

			' . $__templater->formRadioRow(array(
		'name' => 'ticket_type',
		'value' => $__vars['type'],
	), array(array(
		'value' => 'new',
		'checked' => 'checked',
		'labelclass' => 'u-featuredText',
		'label' => 'New ticket',
		'_dependent' => array('
						<label>' . 'Destination department' . $__vars['xf']['language']['label_separator'] . '</label>
						' . $__templater->formSelect(array(
		'name' => 'department_id',
		'value' => $__vars['first']['Ticket']['department_id'],
		'class' => 'js-departmentList',
	), $__compilerTemp1) . '
					', '
						<label>' . 'New ticket title' . $__vars['xf']['language']['label_separator'] . '</label>
						' . $__templater->formPrefixInput($__vars['prefixes'], array(
		'type' => 'support_ticket',
		'prefix-value' => $__vars['first']['Ticket']['prefix_id'],
		'textbox-value' => $__vars['first']['Ticket']['title'],
		'autofocus' => 'autofocus',
		'href' => $__templater->fn('link', array('departments/prefixes', ), false),
		'listen-to' => '< .js-prefixListenContainer | .js-departmentList',
		'maxlength' => $__templater->fn('max_length', array($__vars['first']['Ticket'], 'title', ), false),
	)) . '
					'),
		'_type' => 'option',
	),
	array(
		'value' => 'existing',
		'labelclass' => 'u-featuredText',
		'label' => 'Existing ticket',
		'_dependent' => array('
						<label>' . 'Ticket url' . $__vars['xf']['language']['label_separator'] . '</label>
						' . $__templater->formTextBox(array(
		'name' => 'existing_url',
		'type' => 'url',
	)) . '
					'),
		'_type' => 'option',
	)), array(
	)) . '

			' . $__templater->callMacro('helper_action', 'author_alert', array(
		'selected' => ($__vars['total'] == 1),
	), $__vars) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'copy',
	), array(
	)) . '
	</div>

	' . $__compilerTemp2 . '

	' . $__templater->formHiddenVal('type', 'support_ticket_message', array(
	)) . '
	' . $__templater->formHiddenVal('action', 'copy', array(
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