<?php
// FROM HASH: 0b002ba4755daef51f30819e47df5801
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Google search');
	$__finalCompiled .= '

' . $__templater->formTextBoxRow(array(
		'name' => 'search_query',
	), array(
		'label' => 'Search query',
		'explain' => 'Type search query and Google will find everything related on forum: threads, users, profile posts and so on...',
	));
	return $__finalCompiled;
});