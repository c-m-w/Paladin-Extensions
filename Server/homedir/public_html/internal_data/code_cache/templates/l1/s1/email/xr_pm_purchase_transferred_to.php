<?php
// FROM HASH: 97c5bd3a829639f4b5e6c71002fa3482
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<mail:subject>
	' . 'A purchase for ' . $__templater->escape($__vars['product']['product_title']) . ' has been transferred to you.' . '
</mail:subject>


' . '' . $__templater->escape($__vars['receiver']['username']) . ',<br />
<br />
A purchase ' . $__templater->escape($__vars['purchase']['purchase_key']) . ' for ' . $__templater->escape($__vars['product']['product_title']) . ' has now been transferred to you.<br />
<br />
You should now be able to download updates, receive support and view the purchase details.' . '

<p><a href="' . $__templater->fn('link', array('canonical:products/purchase', $__vars['purchase'], ), true) . '" class="button">' . 'View this purchase' . '</a></p>';
	return $__finalCompiled;
});