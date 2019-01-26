<?php
// FROM HASH: 8e668da59a05173def28f6608074e0a0
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->filter($__templater->method($__vars['userGroup'], 'getIconHtml', array()), array(array('raw', array()),), true) . ' <a class="ug" href="' . $__templater->fn('link', array('members/usergroup', $__vars['userGroup'], ), true) . '">' . $__templater->escape($__vars['userGroup']['title']) . '</a>
';
	return $__finalCompiled;
});