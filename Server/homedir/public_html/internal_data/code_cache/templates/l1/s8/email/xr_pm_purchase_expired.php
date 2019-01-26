<?php
// FROM HASH: 0f200586b72855f4c0a4c26f54907a39
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<mail:subject>
	' . 'Your purchase for ' . $__templater->escape($__vars['product']['product_title']) . ' has expired.' . '
</mail:subject>

' . '' . $__templater->escape($__vars['receiver']['username']) . ',<br />
<br />
Your purchase ' . $__templater->escape($__vars['purchase']['purchase_key']) . ' for product ' . $__templater->escape($__vars['product']['product_title']) . ' has expired.<br />
<br />
You will be unable to download updates or receive support for the product until the purchase is renewed.' . '

<p><a href="' . $__templater->fn('link', array('canonical:products/purchase', $__vars['purchase'], ), true) . '" class="button">' . 'View this purchase' . '</a></p>
<p><a href="' . $__templater->fn('link', array('canonical:products/purchase/renew', $__vars['purchase'], ), true) . '" class="button">' . 'Renew this purchase' . '</a></p>';
	return $__finalCompiled;
});