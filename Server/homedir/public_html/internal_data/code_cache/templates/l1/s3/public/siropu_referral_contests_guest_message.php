<?php
// FROM HASH: 9ab753fa817daf0b6891aa4d46d0220b
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<div class="blockMessage blockMessage--success">
	<i class="fa fa-info-circle" aria-hidden="true"></i>
	' . 'Welcome! You have been invited by <b>' . $__templater->escape($__vars['user']['username']) . '</b> to join our community. Please click <a href="' . $__templater->fn('link', array('register', ), true) . '" data-xf-click="overlay">here</a> to register.' . '
</div>';
	return $__finalCompiled;
});