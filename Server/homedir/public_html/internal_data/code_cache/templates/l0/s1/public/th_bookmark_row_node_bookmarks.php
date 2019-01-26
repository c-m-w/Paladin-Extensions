<?php
// FROM HASH: 1d5409a62d2187a965077450a284e5d0
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<a href="' . $__templater->escape($__templater->method($__vars['bookmark'], 'getContentUrl', array())) . '" class="fauxBlockLink-blockLink">' . $__templater->escape($__vars['node']['title']) . '</a>';
	return $__finalCompiled;
});