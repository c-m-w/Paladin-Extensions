<?php
// FROM HASH: 9fdf7f58c12893a12fa93d9089a14d82
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['extra']['note']) {
		$__finalCompiled .= '
	' . '<b><i>' . $__templater->escape($__vars['extra']['old_name']) . '</i></b> changed their user name to <a href="' . ($__templater->fn('link', array('members', $__vars['content'], ), true) . '#previous-names') . '">' . $__templater->escape($__vars['extra']['name']) . '</a>. Note: ' . $__templater->escape($__vars['extra']['note']) . '
' . '
';
	} else {
		$__finalCompiled .= '
	' . '<b><i>' . $__templater->escape($__vars['extra']['old_name']) . '</i></b> changed their user name to <a href="' . ($__templater->fn('link', array('members', $__vars['content'], ), true) . '#previous-names') . '">' . $__templater->escape($__vars['extra']['name']) . '</a>.
' . '
';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
});