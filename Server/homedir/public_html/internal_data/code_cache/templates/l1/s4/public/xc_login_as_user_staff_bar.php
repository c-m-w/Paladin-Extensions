<?php
// FROM HASH: 201156876c8c8915022ea78004277394
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['xf']['session']['login_as_user']) {
		$__finalCompiled .= '
	';
		$__vars['userRepo'] = $__templater->method($__vars['xf']['app']['em'], 'getRepository', array('XF:User', ));
		$__finalCompiled .= '
	';
		$__vars['userRever'] = $__templater->method($__vars['userRepo'], 'getVisitor', array($__vars['xf']['session']['login_as_user'], ));
		$__finalCompiled .= '
        <a href="' . $__templater->fn('link', array('misc/logout-as-user', ), true) . '"
           class="p-staffBar-link">
            ' . 'Revert user (' . $__templater->escape($__vars['userRever']['username']) . ')' . '
        </a>
    ';
	} else {
		$__finalCompiled .= '

    ';
		if ($__templater->method($__vars['xf']['visitor'], 'canLoginAsUser', array())) {
			$__finalCompiled .= '
        <a href="' . $__templater->fn('link', array('misc/login-as-user', ), true) . '"
           class="p-staffBar-link"
           data-xf-click="overlay">
            ' . 'Login as user' . '
        </a>
    ';
		}
		$__finalCompiled .= '
';
	}
	return $__finalCompiled;
});