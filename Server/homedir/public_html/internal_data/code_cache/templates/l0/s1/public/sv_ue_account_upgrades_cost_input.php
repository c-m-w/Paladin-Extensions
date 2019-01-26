<?php
// FROM HASH: 94541974e422addb0be573b74584471a
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['upgrade']['cost_amount'] == '0.00') {
		$__finalCompiled .= '
	<!-- this maximum is not arbitrary, some payment providers error on values over 999.99 -->
	' . $__templater->formNumberBox(array(
			'name' => 'cost_amount',
			'placeholder' => $__vars['upgrade']['cost_currency'],
			'class' => 'input--inline input--number js-numberBoxTextInput',
			'size' => '4',
			'value' => '',
			'min' => '0',
			'max' => '999.99',
			'step' => '0.01',
		)) . '

	<span class="inputGroup-splitter"></span>
';
	}
	return $__finalCompiled;
});