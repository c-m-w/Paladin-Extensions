<?php
// FROM HASH: b82b193bb8b12b95f095bf52d59aabf9
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= 'You have been granted <a href="' . $__templater->fn('link', array('account/invitations/list', ), true) . '">' . $__templater->escape($__vars['extra']['count']) . ' invitation(s)</a>!';
	return $__finalCompiled;
});