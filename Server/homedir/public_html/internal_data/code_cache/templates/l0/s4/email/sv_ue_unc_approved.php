<?php
// FROM HASH: 727320f2c8cda525b12a81c933cee1fa
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<mail:subject>
	' . 'User name changed on ' . $__templater->escape($__vars['xf']['options']['boardTitle']) . '' . '
</mail:subject>

' . '<p>Your user name on ' . (((('<a href="' . $__templater->fn('link', array('canonical:index', ), true)) . '">') . $__templater->escape($__vars['xf']['options']['boardTitle'])) . '</a>') . ' has been changed to {name}.</p>' . '

';
	if ($__vars['note']) {
		$__finalCompiled .= '
	<p>' . 'Note' . ' ' . $__templater->escape($__vars['note']) . '</p>
';
	}
	return $__finalCompiled;
});