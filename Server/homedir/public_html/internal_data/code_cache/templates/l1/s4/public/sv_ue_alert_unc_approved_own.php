<?php
// FROM HASH: 245136f05291abc9cb33ad8341fd0ba1
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['extra']['note']) {
		$__finalCompiled .= '
	' . 'Your user name has been changed to <b><i>' . $__templater->escape($__vars['extra']['name']) . '</i></b>. Note: ' . $__templater->escape($__vars['extra']['note']) . '
' . '
';
	} else {
		$__finalCompiled .= '
	' . 'Your user name has been changed to <b><i>' . $__templater->escape($__vars['extra']['name']) . '</i></b>.
' . '
';
	}
	return $__finalCompiled;
});