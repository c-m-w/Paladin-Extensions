<?php
// FROM HASH: 860dd098b7bde58763fa9baf787fb477
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Delete message');
	$__finalCompiled .= '

';
	$__templater->breadcrumbs($__templater->method($__vars['ticket'], 'getBreadcrumbs', array()));
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__templater->method($__vars['message'], 'isFirstPost', array())) {
		$__compilerTemp1 .= '
				' . $__templater->formInfoRow('
					<div class="blockMessage blockMessage--important"><strong>' . 'Note' . $__vars['xf']['language']['label_separator'] . '</strong> ' . 'This is the first message in the ticket. Deleting it will delete the whole ticket.' . '</div>
				', array(
		)) . '
			';
	}
	$__compilerTemp2 = '';
	if ($__templater->method($__vars['message'], 'canSendModeratorActionAlert', array())) {
		$__compilerTemp2 .= '
				' . $__templater->callMacro('helper_action', 'author_alert', array(), $__vars) . '
			';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__compilerTemp1 . '
			' . $__templater->callMacro('helper_action', 'delete_type', array(
		'canHardDelete' => $__templater->method($__vars['message'], 'canDelete', array('hard', )),
	), $__vars) . '

			' . $__compilerTemp2 . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'delete',
		'sticky' => 'true',
	), array(
	)) . '
	</div>
	' . $__templater->fn('redirect_input', array(null, null, true)) . '
', array(
		'action' => $__templater->fn('link', array('support-tickets/messages/delete', $__vars['message'], ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});