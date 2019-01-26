<?php
// FROM HASH: 244f51a887b6faca4d41575508961d88
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->formRow('
	' . 'Resource version in \'' . (((('<a href="' . $__templater->fn('link', array('resources/history', $__vars['content'], ), true)) . '">') . $__templater->escape($__vars['content']['Resource']['title'])) . '</a>') . '\'' . '
', array(
		'label' => 'Resource version',
	)) . '

' . $__templater->formRow('
	' . $__templater->fn('username_link', array($__vars['content']['Resource']['User'], true, array(
		'defaultname' => $__vars['content']['Resource']['username'],
	))) . '
', array(
		'label' => 'Author',
	)) . '

' . $__templater->formRow('
	' . $__templater->fn('date_dynamic', array($__vars['content']['release_date'], array(
	))) . '
', array(
		'label' => 'Release date',
	)) . '

' . $__templater->formRow('
	' . $__templater->button('Download', array(
		'class' => 'button--link',
		'href' => $__templater->fn('link', array('resources/version/download', $__vars['version'], ), false),
	), '', array(
	)) . '
', array(
		'label' => 'Download',
	)) . '

' . $__templater->callMacro('approval_queue_macros', 'action_row', array(
		'unapprovedItem' => $__vars['unapprovedItem'],
		'handler' => $__vars['handler'],
	), $__vars);
	return $__finalCompiled;
});