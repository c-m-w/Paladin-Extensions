<?php
// FROM HASH: 7fed196df8b0db16869e4c1961d3e816
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__compilerTemp1 = '';
	if ($__vars['xf']['visitor']['pending_username_change']) {
		$__compilerTemp1 .= '
		' . $__vars['xf']['language']['parenthesis_open'] . 'Pending change to ' . $__templater->escape($__vars['xf']['visitor']['pending_username_change']['to_username']) . '' . $__vars['xf']['language']['parenthesis_close'] . '
	';
	} else if ($__templater->method($__vars['xf']['visitor'], 'canChangeUsername', array())) {
		$__compilerTemp1 .= '
		' . $__templater->button('Change', array(
			'href' => $__templater->fn('link', array('account/username-change', ), false),
			'class' => 'button--link',
			'overlay' => 'true',
		), '', array(
		)) . '
	';
	}
	$__finalCompiled .= $__templater->formRow('

	' . $__templater->escape($__vars['xf']['visitor']['username']) . '

	' . $__compilerTemp1 . '
', array(
		'rowtype' => 'button',
		'label' => 'User name',
	));
	return $__finalCompiled;
});