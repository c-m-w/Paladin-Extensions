<?php
// FROM HASH: a591b756740617a2bfe9d18f0f7defc7
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Confirm action');
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formInfoRow('
				' . 'Please confirm that you want to delete the following' . $__vars['xf']['language']['label_separator'] . '
				<strong><a href="' . $__templater->fn('link', array('mjst-support/predefined-replies/group/edit', $__vars['replyGroup'], ), true) . '" data-xf-click="overlay">' . $__templater->escape($__vars['replyGroup']['title']) . '</a></strong>
				' . 'Predefined replies belonging to this group will be disassociated, rather than deleted.' . '
			', array(
		'rowtype' => 'confirm',
	)) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'delete',
	), array(
		'rowtype' => 'simple',
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('mjst-support/predefined-replies/group/delete', $__vars['replyGroup'], ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});