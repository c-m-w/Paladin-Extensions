<?php
// FROM HASH: b569dd34d1f1b154792fe89b76eb164b
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if (!$__vars['user']['user_id']) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add member');
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit member' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['user']['username']));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['user']['user_id']) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('', array(
			'href' => $__templater->fn('link', array('mjst-support/departments/members/remove', $__vars['department'], array('user_id' => $__vars['user']['user_id'], ), ), false),
			'icon' => 'delete',
			'overlay' => 'true',
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__vars['user']['user_id']) {
		$__compilerTemp1 .= '
				' . $__templater->formRow('
					' . $__templater->escape($__vars['user']['username']) . '
				', array(
			'label' => 'Member',
		)) . '
			';
	} else {
		$__compilerTemp1 .= '
				' . $__templater->formTextBoxRow(array(
			'name' => 'username',
			'ac' => 'single',
			'value' => $__vars['user']['username'],
		), array(
			'label' => 'User',
		)) . '
			';
	}
	$__templater->includeJs(array(
		'src' => 'xf/permission.js',
		'min' => '1',
	));
	$__templater->includeCss('permission.less');
	$__finalCompiled .= $__templater->form('

	<div class="block-container">
		<div class="block-body">
			' . $__compilerTemp1 . '
		</div>

		' . '' . '
		' . '' . '

		' . $__templater->callMacro('permission_macros', 'content_edit_groups', array(
		'interfaceGroups' => $__vars['permissionData']['interfaceGroups'],
		'permissionsGrouped' => $__vars['permissionData']['permissionsGrouped'],
		'values' => $__vars['permissionData']['values'],
	), $__vars) . '

		' . $__templater->formHiddenVal('user_id', $__vars['user']['user_id'], array(
	)) . '
		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
		'sticky' => 'true',
	), array(
	)) . '
	</div>

', array(
		'action' => $__templater->fn('link', array('mjst-support/departments/members/save', $__vars['department'], ), false),
		'ajax' => 'true',
		'class' => 'block',
		'data-xf-init' => 'permission-form',
		'data-permission-type' => 'global',
	));
	return $__finalCompiled;
});