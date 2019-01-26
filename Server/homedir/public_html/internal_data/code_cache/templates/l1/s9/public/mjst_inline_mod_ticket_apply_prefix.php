<?php
// FROM HASH: d4a28c86694ba24c1fd57f9a9477356a
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Inline moderation - Apply ticket prefix');
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
			' . $__templater->formInfoRow('Are you sure you want to apply the prefix specified below to the ' . $__templater->escape($__vars['total']) . ' selected tickets?', array(
		'rowtype' => 'confirm',
	)) . '

			' . $__templater->callMacro('prefix_macros', 'row', array(
		'type' => 'support_ticket',
		'prefixes' => $__vars['prefixes'],
		'selected' => $__vars['selectedPrefix'],
		'explain' => (($__vars['departmentCount'] > 1) ? 'The tickets you have selected are located in more than one department. Tickets will only be updated if the chosen prefix is valid in its department.' : ''),
	), $__vars) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'confirm',
	), array(
	)) . '
	</div>

	' . $__compilerTemp1 . '

	' . $__templater->formHiddenVal('type', 'support_ticket', array(
	)) . '
	' . $__templater->formHiddenVal('action', 'apply_prefix', array(
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