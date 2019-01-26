<?php
// FROM HASH: f74570ba0f9985ce9aa0f489aa67cbe8
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__vars['issuer'] = $__vars['alert']['User'];
	$__finalCompiled .= '

';
	if (!$__templater->method($__vars['content'], 'canViewIssuer', array())) {
		$__finalCompiled .= '
	';
		$__vars['issuer'] = $__templater->method($__vars['content'], 'getAnonymizedIssuer', array());
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

' . '' . $__templater->fn('username_link', array($__vars['issuer'], false, array('defaultname' => $__vars['issuer']['username'], ), ), true) . ' issued you a warning for <a ' . ($__templater->method($__vars['content'], 'canView', array()) ? (('href="' . $__templater->fn('link', array('warnings', $__vars['content'], ), true)) . '" class="fauxBlockLink-blockLink"') : '') . '>' . $__templater->escape($__vars['content']['title']) . '</a> for ' . $__templater->escape($__vars['content']['points']) . ' points.';
	return $__finalCompiled;
});