<?php
// FROM HASH: 070dc57e8ab2b0219138ddc450f0f743
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Assign ticket');
	$__finalCompiled .= '

';
	$__templater->breadcrumbs($__templater->method($__vars['ticket'], 'getBreadcrumbs', array()));
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__vars['ticket']['AssignedUser']) {
		$__compilerTemp1 .= '
				' . $__templater->formRow('
					' . $__templater->escape($__vars['ticket']['AssignedUser']['username']) . '
					' . $__templater->button('Unassign', array(
			'href' => $__templater->fn('link', array('support-tickets/unassign', $__vars['ticket'], ), false),
		), '', array(
		)) . '
				', array(
			'label' => 'Current assigned to',
		)) . '
			';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__compilerTemp1 . '
			' . $__templater->formTextBoxRow(array(
		'name' => 'username',
		'value' => $__vars['ticket']['AssignedUser']['username'],
		'ac' => 'single',
		'autocomplete' => 'off',
		'maxlength' => $__templater->fn('max_length', array($__vars['xf']['visitor'], 'username', ), false),
	), array(
		'label' => 'Assign to',
	)) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'assign',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('support-tickets/assign', $__vars['ticket'], ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});