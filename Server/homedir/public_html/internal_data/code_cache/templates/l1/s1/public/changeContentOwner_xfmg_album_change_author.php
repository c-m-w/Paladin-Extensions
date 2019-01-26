<?php
// FROM HASH: 574b760bf50e8ef19acb352878a7bba2
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Change album owner');
	$__finalCompiled .= '

';
	$__templater->breadcrumbs($__templater->method($__vars['album'], 'getBreadcrumbs', array()));
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formTextBoxRow(array(
		'name' => 'new_author_username',
		'value' => '',
		'ac' => 'true',
		'data-single' => 'true',
	), array(
		'label' => 'New author name',
		'explain' => 'Enter the name of the new thread author.',
	)) . '
		</div>

		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
		'sticky' => 'true',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('media/albums/change-owner', $__vars['album'], ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});