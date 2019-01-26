<?php
// FROM HASH: 19f1d1b098a1dab7e05ad3851a3530aa
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->isTraversable($__vars['mjstStatusStyles'])) {
		foreach ($__vars['mjstStatusStyles'] AS $__vars['id'] => $__vars['color']) {
			if ($__vars['color']) {
				$__finalCompiled .= '
	.mjstStatus.mjstStatus--style' . $__templater->escape($__vars['id']) . '
	{
		color: ' . $__templater->filter($__vars['color'], array(array('raw', array()),), true) . ';
		border-color: ' . $__templater->filter($__vars['color'], array(array('raw', array()),), true) . ';
	}
';
			}
		}
	}
	return $__finalCompiled;
});