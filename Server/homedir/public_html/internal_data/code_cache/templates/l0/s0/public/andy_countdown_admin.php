<?php
// FROM HASH: a23e85414ec2287e56fa65f2e4b741d6
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Countdown');
	$__finalCompiled .= '

' . 'Enter UTC time.' . '
<br />
<br />

' . $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formTextBoxRow(array(
		'name' => 'title',
		'value' => $__vars['title'],
	), array(
		'label' => 'Title',
	)) . '
			' . $__templater->formTextBoxRow(array(
		'name' => 'link',
		'value' => $__vars['link'],
	), array(
		'label' => 'Link',
	)) . '
			' . $__templater->formTextBoxRow(array(
		'name' => 'year',
		'value' => $__vars['year'],
	), array(
		'label' => 'Year',
	)) . '
			' . $__templater->formTextBoxRow(array(
		'name' => 'month',
		'value' => $__vars['month'],
	), array(
		'label' => 'Month',
	)) . '
			' . $__templater->formTextBoxRow(array(
		'name' => 'day',
		'value' => $__vars['day'],
	), array(
		'label' => 'Day',
	)) . '
			' . $__templater->formTextBoxRow(array(
		'name' => 'hour',
		'value' => $__vars['hour'],
	), array(
		'label' => 'Hour',
	)) . '
			' . $__templater->formTextBoxRow(array(
		'name' => 'minute',
		'value' => $__vars['minute'],
	), array(
		'label' => 'Minute',
	)) . '
			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'active',
		'value' => '1',
		'checked' => $__vars['activeChecked'],
		'label' => 'Active',
		'hint' => 'Show countdown',
		'_type' => 'option',
	)), array(
	)) . '
		
		</div>
	</div>

	' . $__templater->formSubmitRow(array(
		'submit' => 'Submit',
	), array(
	)) . '

', array(
		'action' => $__templater->fn('link', array('countdown/save', ), false),
		'ajax' => 'true',
		'class' => 'block',
		'data-force-flash-message' => 'true',
	));
	return $__finalCompiled;
});