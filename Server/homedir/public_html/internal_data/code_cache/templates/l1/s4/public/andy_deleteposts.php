<?php
// FROM HASH: bc71de08c860af4b87ea5ae350771d45
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Delete posts');
	$__finalCompiled .= '

(' . 'Search' . ')

<br /><br />

' . $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formTextBoxRow(array(
		'name' => 'posted_by',
		'placeholder' => 'Member',
		'ac' => 'single',
		'autocomplete' => 'off',
	), array(
		'label' => 'Posted by',
	)) . '
		</div>
	</div>

	' . $__templater->formSubmitRow(array(
		'submit' => 'Search',
	), array(
	)) . '

', array(
		'action' => $__templater->fn('link', array('deleteposts/confirm', ), false),
		'class' => 'block',
	));
	return $__finalCompiled;
});