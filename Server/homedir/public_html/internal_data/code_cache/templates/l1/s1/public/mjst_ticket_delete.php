<?php
// FROM HASH: edb4914f5b1f8904802b5a7f78bb0dd3
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Delete ticket');
	$__finalCompiled .= '

';
	$__templater->breadcrumbs($__templater->method($__vars['ticket'], 'getBreadcrumbs', array()));
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__templater->method($__vars['ticket'], 'canSendModeratorActionAlert', array())) {
		$__compilerTemp1 .= '
				' . $__templater->callMacro('mjst_helper_action', 'ticket_alert', array(), $__vars) . '
			';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formInfoRow('
				' . 'Please confirm that you want to delete the following' . $__vars['xf']['language']['label_separator'] . '
				<strong><a href="' . $__templater->fn('link', array('support-tickets', $__vars['ticket'], ), true) . '">' . $__templater->escape($__vars['ticket']['title']) . '</a></strong>
			', array(
		'rowtype' => 'confirm',
	)) . '

			' . $__compilerTemp1 . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'delete',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('support-tickets/delete', $__vars['ticket'], ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});