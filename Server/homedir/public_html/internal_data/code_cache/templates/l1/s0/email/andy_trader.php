<?php
// FROM HASH: a4ffe3ed935aef08de8b34400a8aa7c4
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<mail:subject>
	' . 'Trader feedback' . ' (' . 'from' . ' ' . $__templater->escape($__vars['xf']['options']['boardTitle']) . ')
</mail:subject>

<h2>' . 'Trader feedback' . '</h2>

' . $__templater->filter($__vars['message'], array(array('raw', array()),), true);
	return $__finalCompiled;
});