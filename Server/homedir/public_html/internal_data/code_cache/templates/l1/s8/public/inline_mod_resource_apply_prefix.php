<?php
// FROM HASH: 180006e6fdb3e102c05030f93176b506
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Apply prefix');
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__templater->isTraversable($__vars['resources'])) {
		foreach ($__vars['resources'] AS $__vars['resource']) {
			$__compilerTemp1 .= '
		' . $__templater->formHiddenVal('ids[]', $__vars['resource']['resource_id'], array(
			)) . '
	';
		}
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formInfoRow('Are you sure you want to apply a prefix to ' . $__templater->escape($__vars['total']) . ' extension(s)?', array(
		'rowtype' => 'confirm',
	)) . '

			' . $__templater->callMacro('prefix_macros', 'row', array(
		'type' => 'resource',
		'prefixes' => $__vars['prefixes'],
		'selected' => $__vars['selectedPrefix'],
		'explain' => (($__vars['categoryCount'] > 1) ? 'The extensions you have selected are located in more than one category. Each extension will only be updated if the chosen prefix is valid in its category.' : ''),
	), $__vars) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'confirm',
	), array(
	)) . '
	</div>

	' . $__compilerTemp1 . '

	' . $__templater->formHiddenVal('type', 'resource', array(
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