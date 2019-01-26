<?php
// FROM HASH: cbace2ec8de6d0bd33a59b230ae7c2ce
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->formRow('
	<a href="' . $__templater->fn('link', array('resources', $__vars['content'], ), true) . '">' . $__templater->escape($__vars['content']['title']) . '</a>
', array(
		'label' => 'Extension',
	)) . '

' . $__templater->formRow('
	<a href="' . $__templater->fn('link', array('resources/categories', $__vars['content']['Category'], ), true) . '">' . $__templater->escape($__vars['content']['Category']['title']) . '</a>
', array(
		'label' => 'Category',
	)) . '

' . $__templater->formRow('
	' . $__templater->fn('username_link', array($__vars['content']['User'], true, array(
		'defaultname' => $__vars['content']['username'],
	))) . '
', array(
		'label' => 'Author',
	)) . '

' . $__templater->formRow('
	' . $__templater->fn('date_dynamic', array($__vars['content']['resource_date'], array(
	))) . '
', array(
		'label' => 'Post date',
	)) . '

' . $__templater->callMacro('approval_queue_macros', 'spam_log', array(
		'spamDetails' => $__vars['spamDetails'],
	), $__vars) . '

' . $__templater->formRow('
	' . $__templater->fn('bb_code', array($__vars['content']['Description']['message'], 'resource_update', $__vars['content']['Description'], ), true) . '
', array(
		'label' => 'Content',
	)) . '

' . $__templater->callMacro('approval_queue_macros', 'action_row', array(
		'unapprovedItem' => $__vars['unapprovedItem'],
		'handler' => $__vars['handler'],
	), $__vars);
	return $__finalCompiled;
});