<?php
// FROM HASH: e83b93273a80f4d628ea15918427d9bc
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Login as User');
	$__finalCompiled .= '

' . $__templater->form('
    <div class="block-container">
        <div class="block-body">
            ' . $__templater->formTextBoxRow(array(
		'name' => 'username',
		'autofocus' => ((!$__vars['username']) ? 'autofocus' : false),
		'maxlength' => '50',
		'ac' => 'single',
		'autocomplete' => 'off',
		'value' => $__vars['username'],
		'required' => 'required',
		'readonly' => $__vars['username'],
	), array(
		'label' => 'User name',
	)) . '

            ' . $__templater->formTextBoxRow(array(
		'name' => 'reason',
		'maxlength' => '255',
		'autocomplete' => 'off',
		'required' => ($__vars['xf']['options']['lau_ReasonRequired'] ? 'required' : false),
		'autofocus' => ($__vars['username'] ? 'autofocus' : false),
	), array(
		'label' => 'Reason',
		'hint' => ($__vars['xf']['options']['lau_ReasonRequired'] ? 'Required' : 'Optional'),
	)) . '
        </div>
        ' . $__templater->formSubmitRow(array(
		'submit' => 'Log in',
		'icon' => 'login',
	), array(
	)) . '
    </div>
', array(
		'action' => $__templater->fn('link', array('login/lauin', ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});