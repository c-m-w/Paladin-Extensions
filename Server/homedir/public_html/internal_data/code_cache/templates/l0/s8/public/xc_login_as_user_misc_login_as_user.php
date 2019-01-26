<?php
// FROM HASH: d29455bd2bf1444c169f1eeef3a91d76
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Login as user');
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">
		<div class="block-body">
			
			' . $__templater->formTokenInputRow(array(
		'name' => 'username',
		'value' => $__vars['username'],
		'href' => $__templater->fn('link', array('members/find', ), false),
		'max-tokens' => '3',
	), array(
		'label' => 'User',
	)) . '

			' . $__templater->formTextAreaRow(array(
		'name' => 'reason',
		'rows' => '3',
	), array(
		'label' => 'Reason',
	)) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'submit' => 'Login as user',
		'sticky' => 'true',
		'icon' => 'login',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('misc/login-as-user', ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});