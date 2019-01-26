<?php
// FROM HASH: 4f662076ccb4ebe3fd70f933b2f0dd09
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<mail:subject>
	' . 'User name change rejected on ' . $__templater->escape($__vars['xf']['options']['boardTitle']) . '' . '
</mail:subject>

' . '<p>' . $__templater->escape($__vars['user']['username']) . ', your request to change your user name on ' . (((('<a href="' . $__templater->fn('link', array('canonical:index', ), true)) . '">') . $__templater->escape($__vars['xf']['options']['boardTitle'])) . '</a>') . ' to ' . $__templater->escape($__vars['name']) . ' has been rejected.</p>' . '

';
	if ($__vars['note']) {
		$__finalCompiled .= '
	<p>' . 'Note' . ' ' . $__templater->escape($__vars['note']) . '</p>
';
	}
	return $__finalCompiled;
});