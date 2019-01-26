<?php
// FROM HASH: dee34124744e4591fc8b75423a29f2b0
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Conversation view');
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">
		<div class="block-body">
            ' . $__templater->formTextBoxRow(array(
		'name' => 'username',
		'placeholder' => 'Member',
		'ac' => 'single',
		'autocomplete' => 'off',
	), array(
		'label' => 'Conversations started by',
	)) . '
		</div>
	</div>

	' . $__templater->formSubmitRow(array(
		'submit' => 'Submit',
	), array(
	)) . '

', array(
		'action' => $__templater->fn('link', array('conversationview/', ), false),
		'class' => 'block',
	));
	return $__finalCompiled;
});