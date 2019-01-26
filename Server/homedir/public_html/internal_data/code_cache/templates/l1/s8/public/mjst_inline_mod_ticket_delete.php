<?php
// FROM HASH: 4e05b3f896339744044b238ac12d2bc0
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Inline moderation - Delete tickets');
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__templater->isTraversable($__vars['tickets'])) {
		foreach ($__vars['tickets'] AS $__vars['ticket']) {
			$__compilerTemp1 .= '
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

			' . $__templater->callMacro('mjst_helper_action', 'ticket_alert', array(), $__vars) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'delete',
	), array(
	)) . '
	</div>

	' . $__compilerTemp1 . '

	' . $__templater->formHiddenVal('type', 'support_ticket', array(
	)) . '
	' . $__templater->formHiddenVal('action', 'delete', array(
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