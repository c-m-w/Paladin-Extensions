<?php
// FROM HASH: 810d3c5757b83a15cbde82eb9ebe3959
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Gift ' . $__templater->escape($__vars['upgrade']['title']) . ' to a user');
	$__finalCompiled .= '

<div class="blocks">
	' . $__templater->form('
		<div class="block-container">
			<div class="block-body">
				' . $__templater->formRow($__templater->escape($__vars['upgrade']['title']) . ' (' . $__templater->escape($__templater->method($__vars['upgrade'], 'getCostPhrase', array())) . ')', array(
		'label' => 'Upgrade',
	)) . '

				' . $__templater->formTextBoxRow(array(
		'name' => 'username',
		'ac' => 'single',
		'autocomplete' => 'off',
		'required' => 'true',
		'maxlength' => $__templater->fn('max_length', array($__vars['xf']['visitor'], 'username', ), false),
		'placeholder' => 'Name' . $__vars['xf']['language']['ellipsis'],
		'autofocus' => 'on',
	), array(
		'label' => 'Gift to',
	)) . '

				' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'anonymous',
		'label' => 'Send gift anonymously',
		'_type' => 'option',
	)), array(
		'explain' => 'Checking this option will not reveal your identity to the user you are gifting.',
	)) . '

				' . $__templater->formSubmitRow(array(
		'submit' => 'Continue' . $__vars['xf']['language']['ellipsis'],
	), array(
	)) . '
			</div>
		</div>

		' . $__templater->formHiddenVal('payment_profile_id', $__vars['profileId'], array(
	)) . '
		' . $__templater->formHiddenVal('gift', '1', array(
	)) . '
		' . $__templater->formHiddenVal('confirmed', '1', array(
	)) . '
	', array(
		'action' => $__templater->fn('link', array('purchase', $__vars['upgrade'], array('user_upgrade_id' => $__vars['upgrade']['user_upgrade_id'], ), ), false),
		'class' => 'block',
		'ajax' => 'true',
	)) . '
</div>';
	return $__finalCompiled;
});