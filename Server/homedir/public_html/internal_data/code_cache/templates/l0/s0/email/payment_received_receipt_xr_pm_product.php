<?php
// FROM HASH: c657cac870a51608469756c8d3ff3a42
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<mail:subject>
	';
	if ($__vars['purchasable']['purchasable']['purchase_type'] == 'product') {
		$__finalCompiled .= '
		' . 'Receipt for your product purchase at ' . $__templater->escape($__vars['xf']['options']['boardTitle']) . '' . '
	';
	} else if ($__vars['purchasable']['purchasable']['purchase_type'] == 'renewal') {
		$__finalCompiled .= '
		' . 'Receipt for your renewal at ' . $__templater->escape($__vars['xf']['options']['boardTitle']) . '' . '
	';
	} else {
		$__finalCompiled .= '
		' . 'Receipt for your purchase of optional extras at ' . $__templater->escape($__vars['xf']['options']['boardTitle']) . '' . '
	';
	}
	$__finalCompiled .= '
</mail:subject>

<p>' . 'Thank you for making a purchase at <a href="' . $__templater->fn('link', array('canonical:index', ), true) . '">' . $__templater->escape($__vars['xf']['options']['boardTitle']) . '</a>.' . '</p>

<table border="0" width="100%" cellpadding="0" cellspacing="0">
	<tr>
		<td><b>' . 'Purchased item' . '</b></td>
		<td align="right"><b>' . 'Price' . '</b></td>
	</tr>
	<tr>
		<td><a href="' . $__templater->fn('link', array('canonical:products/purchase', $__vars['purchasable']['purchasable'], ), true) . '">' . $__templater->escape($__vars['purchasable']['title']) . '</a></td>
		<td align="right">' . $__templater->filter($__vars['purchasable']['purchasable']['total_price'], array(array('currency', array($__vars['purchasable']['purchasble']['purchase_currency'], )),), true) . '</td>
	</tr>
</table>

<p><a href="' . $__templater->fn('link', array('canonical:products/purchases', ), true) . '" class="button">' . 'View all of your purchases' . '</a></p>

';
	if ($__templater->method($__vars['xf']['toUser'], 'canUseContactForm', array())) {
		$__finalCompiled .= '
	<p>' . 'Thank you for your purchase. If you have any questions, please <a href="' . $__templater->fn('link', array('canonical:misc/contact', ), true) . '">contact us</a>.' . '</p>
';
	} else {
		$__finalCompiled .= '
	<p>' . 'Thank you for your purchase.' . '</p>
';
	}
	return $__finalCompiled;
});