<?php
// FROM HASH: ae29e46965d92c0b7a863681ecbd1281
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['xf']['visitor'], 'canLoginAsUser', array())) {
		$__finalCompiled .= '
    <a href="' . $__templater->fn('link', array('misc/login-as-user', '', array('user_id' => $__vars['user']['user_id'], ), ), true) . '"
       data-xf-click="overlay"
       class="button button--link">

        ' . 'Login as user' . '

    </a>
';
	}
	return $__finalCompiled;
});