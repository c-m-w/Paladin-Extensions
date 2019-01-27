<?php
// FROM HASH: 0000e42f8f9b0679f3dac45a769f7071
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('trader_submit_feedback_for' . ' ' . $__templater->escape($__vars['username']));
	$__finalCompiled .= '

';
	$__templater->includeCss('andy_trader.less');
	$__finalCompiled .= '

<a href="' . $__templater->fn('link', array('trader/history', '', array('user_id' => $__vars['userId'], ), ), true) . '" rel="nofollow">' . 'Return to trader history menu' . '</a>
<br />
<br />

' . $__templater->form('
	<div class="block-container">
		<div class="block-body">
			
			' . $__templater->formTextBoxRow(array(
		'name' => 'username',
		'readonly' => 'readonly',
		'value' => $__vars['username'],
		'class' => 'trader-muted',
	), array(
		'label' => 'Username',
	)) . '
			
			' . $__templater->formRadioRow(array(
		'name' => 'rating',
	), array(array(
		'value' => '0',
		'selected' => 1,
		'label' => 'Positive',
		'_type' => 'option',
	),
	array(
		'value' => '1',
		'label' => 'Neutral',
		'_type' => 'option',
	),
	array(
		'value' => '2',
		'label' => 'Negative',
		'_type' => 'option',
	)), array(
		'label' => 'Rating',
	)) . '

			' . $__templater->formTextAreaRow(array(
		'name' => 'buyer_comment',
		'rows' => '5',
		'autosize' => 'true',
	), array(
		'label' => 'Buyer comment',
		'explain' => 'As a buyer please describe your experience with this seller. (200 character limit)',
	)) . '
		</div>
	</div>

	' . $__templater->formSubmitRow(array(
		'submit' => 'Submit',
	), array(
	)) . '

', array(
		'action' => $__templater->fn('link', array('trader/saveseller', '', array('user_id' => $__vars['userId'], ), ), false),
		'class' => 'block',
	));
	return $__finalCompiled;
});