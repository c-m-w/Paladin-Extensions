<?php
// FROM HASH: be7deb6f0f1d1637011cd53b5e14f3f1
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Inline moderation - Merge tickets');
	$__finalCompiled .= '

';
	$__compilerTemp1 = array();
	if ($__templater->isTraversable($__vars['tickets'])) {
		foreach ($__vars['tickets'] AS $__vars['ticket']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['ticket']['support_ticket_id'],
				'label' => $__templater->fn('prefix', array('support_ticket', $__vars['ticket'], 'escaped', ), true) . $__templater->escape($__vars['ticket']['title']),
				'_type' => 'option',
			);
		}
	}
	$__compilerTemp2 = '';
	if ($__templater->isTraversable($__vars['tickets'])) {
		foreach ($__vars['tickets'] AS $__vars['ticket']) {
			$__compilerTemp2 .= '
		' . $__templater->formHiddenVal('ids[]', $__vars['ticket']['support_ticket_id'], array(
			)) . '
	';
		}
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formInfoRow('Are you sure you want to delete ' . $__templater->escape($__vars['total']) . ' ticket(s)?', array(
		'rowtype' => 'confirm',
	)) . '

			' . $__templater->formSelectRow(array(
		'name' => 'target_ticket_id',
		'value' => $__vars['first']['support_ticket_id'],
	), $__compilerTemp1, array(
		'label' => 'Destination ticket',
		'explain' => 'All messages from the other tickets will be merged into this ticket.',
	)) . '

			' . $__templater->callMacro('mjst_helper_action', 'ticket_alert', array(
		'selected' => ($__vars['total'] == 1),
	), $__vars) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'merge',
	), array(
	)) . '
	</div>

	' . $__compilerTemp2 . '

	' . $__templater->formHiddenVal('type', 'support_ticket', array(
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