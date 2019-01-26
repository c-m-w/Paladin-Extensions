<?php
// FROM HASH: 4b128469c061be3db96611934aae56c0
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Create invitation links');
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formNumberBoxRow(array(
		'name' => 'invitation_count',
		'min' => '1',
		'value' => '1',
	), array(
		'label' => 'Number of invitations',
	)) . '
			' . $__templater->formDateInputRow(array(
		'name' => 'expiration_date',
	), array(
		'label' => 'Expiration date',
		'hint' => 'Optional',
	)) . '

			' . $__templater->formTextBoxRow(array(
		'name' => 'referrer',
		'data-xf-init' => 'auto-complete',
		'data-single' => 'true',
	), array(
		'label' => 'Referrer',
		'hint' => 'Optional',
	)) . '

			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'generate_link',
		'value' => '1',
		'label' => 'Generate invitation link',
		'_type' => 'option',
	)), array(
	)) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'add',
		'submit' => 'Create invitation links',
		'class' => 'js-overlayClose',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('referral-contests/invitations/save', ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});