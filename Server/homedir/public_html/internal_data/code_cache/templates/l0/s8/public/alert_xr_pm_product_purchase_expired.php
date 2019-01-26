<?php
// FROM HASH: 02edbdfb58909ee2d9808ebadb823333
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= 'Your purchase ' . $__templater->escape($__vars['content']['purchase_key']) . ' for product ' . $__templater->escape($__vars['content']['Product']['product_title']) . ' has expired. <a href="' . $__templater->fn('link', array('canonical:products/purchase/renew', $__vars['content'], ), true) . '" class="fauxBlockLink-blockLink" data-xf-click="overlay">Renew now</a>.';
	return $__finalCompiled;
});