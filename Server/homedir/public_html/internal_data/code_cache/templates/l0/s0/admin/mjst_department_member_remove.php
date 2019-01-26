<?php
// FROM HASH: 60539b9bc3826d2300ff42b33a38c801
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Remove member' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['user']['username']));
	$__finalCompiled .= '

';
	$__templater->includeJs(array(
		'src' => 'xf/permission.js',
		'min' => '1',
	));
	$__templater->includeCss('permission.less');
	$__finalCompiled .= $__templater->form('

	<div class="block-container">
		<div class="block-body">
			' . $__templater->formInfoRow('
				' . 'Please confirm that you want to remove the following member' . $__vars['xf']['language']['label_separator'] . '
				<strong><a href="' . $__templater->fn('link', array('mjst-support/departments/edit', $__vars['department'], ), true) . '">' . $__templater->escape($__vars['user']['username']) . '</a></strong>
			', array(
		'rowtype' => 'confirm',
	)) . '
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
		'icon' => 'delete',
		'sticky' => 'true',
	), array(
	)) . '
	</div>

', array(
		'action' => $__templater->fn('link', array('mjst-support/departments/members/remove', $__vars['department'], ), false),
		'ajax' => 'true',
		'class' => 'block',
		'data-xf-init' => 'permission-form',
		'data-permission-type' => 'global',
	));
	return $__finalCompiled;
});