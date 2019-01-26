<?php
// FROM HASH: 997d55ac966a39358ab5f2cc9a930c5e
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '' . (((('<a href="' . $__templater->fn('link', array('products', $__vars['content']['Product'], ), true)) . '">') . $__templater->escape($__vars['content']['Product']['product_title'])) . '</a>') . ' has been updated to version ' . (((('<a href="' . $__templater->fn('link', array('products/version', $__vars['content'], ), true)) . '" class="fauxBlockLink-blockLink">') . $__templater->escape($__vars['content']['version_string'])) . '</a>') . '.';
	return $__finalCompiled;
});