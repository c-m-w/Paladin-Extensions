<?php
// FROM HASH: 4aae821bf4a1e931a78a01991a23b43a
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Member notes edit');
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formTextAreaRow(array(
		'name' => 'notes',
		'value' => $__vars['notes'],
		'rows' => '5',
		'autosize' => 'true',
	), array(
		'label' => 'Notes',
		'explain' => 'Only staff can view these notes.',
	)) . '
		</div>
	</div>

	' . $__templater->formSubmitRow(array(
		'submit' => 'Submit',
	), array(
	)) . '

', array(
		'action' => $__templater->fn('link', array('membernotes/save', '', array('user_id' => $__vars['userId'], ), ), false),
		'class' => 'block',
	));
	return $__finalCompiled;
});