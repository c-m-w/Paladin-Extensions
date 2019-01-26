<?php
// FROM HASH: 667f46c7acf9e77654e9c58ae84b40e6
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['xf']['session']['lau_id']) {
		$__finalCompiled .= '

    <a href="' . $__templater->fn('link', array('logout/lauout', ), true) . '" class="p-staffBar-link">
        ' . 'Logout from' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['xf']['visitor']['username']) . '
    </a>

    ';
	} else if ($__templater->method($__vars['xf']['visitor'], 'canUseLau', array()) AND $__vars['xf']['options']['lau_DisplayLoginStaffBar']) {
		$__finalCompiled .= '
    <a href="' . $__templater->fn('link', array('login/lauin', ), true) . '" class="p-staffBar-link" data-xf-click="overlay">
        ' . 'Login as User' . '
    </a>

';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
});