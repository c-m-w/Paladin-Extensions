<?php
// FROM HASH: 189c768270b10d9a42ee44bb97b84236
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['extra']['note']) {
		$__finalCompiled .= '
	' . 'Your request to change your user name to <b><i>' . $__templater->escape($__vars['extra']['name']) . '</i></b> has been rejected. Note: ' . $__templater->escape($__vars['extra']['note']) . '
' . '
';
	} else {
		$__finalCompiled .= '
	' . 'Your request to change your user name to <b><i>' . $__templater->escape($__vars['extra']['name']) . '</i></b> has been rejected.
' . '
';
	}
	return $__finalCompiled;
});