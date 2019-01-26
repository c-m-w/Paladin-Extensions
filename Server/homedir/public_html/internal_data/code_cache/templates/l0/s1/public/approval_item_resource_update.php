<?php
// FROM HASH: 644e8e54d4191f50e7e028d7c74e9f15
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->formRow('
	' . 'Update \'' . (((('<a href="' . $__templater->fn('link', array('resources/update', $__vars['content'], ), true)) . '">') . $__templater->escape($__vars['content']['title'])) . '</a>') . '\' in resource \'' . (((('<a href="' . $__templater->fn('link', array('resources', $__vars['content']['Resource'], ), true)) . '">') . $__templater->escape($__vars['content']['Resource']['title'])) . '</a>') . '\'' . '
', array(
		'label' => 'Resource update',
	)) . '

' . $__templater->formRow('
	' . $__templater->fn('username_link', array($__vars['content']['Resource']['User'], true, array(
		'defaultname' => $__vars['content']['Resource']['username'],
	))) . '
', array(
		'label' => 'Author',
	)) . '

' . $__templater->formRow('
	' . $__templater->fn('date_dynamic', array($__vars['content']['post_date'], array(
	))) . '
', array(
		'label' => 'Post date',
	)) . '

' . $__templater->callMacro('approval_queue_macros', 'spam_log', array(
		'spamDetails' => $__vars['spamDetails'],
	), $__vars) . '

' . $__templater->formRow('
	' . $__templater->fn('bb_code', array($__vars['content']['message'], 'resource_update', $__vars['content'], ), true) . '
', array(
		'label' => 'Content',
	)) . '

' . $__templater->callMacro('approval_queue_macros', 'action_row', array(
		'unapprovedItem' => $__vars['unapprovedItem'],
		'handler' => $__vars['handler'],
	), $__vars);
	return $__finalCompiled;
});