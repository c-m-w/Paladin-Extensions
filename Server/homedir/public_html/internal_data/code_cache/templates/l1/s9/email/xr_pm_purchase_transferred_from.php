<?php
// FROM HASH: dd98cf3c44b8fb6ce835e61e10fdd247
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<mail:subject>
	' . 'Your purchase for ' . $__templater->escape($__vars['product']['product_title']) . ' has been transferred.' . '
</mail:subject>

' . '' . $__templater->escape($__vars['receiver']['username']) . ',<br />
<br />
Your purchase ' . $__templater->escape($__vars['purchase']['purchase_key']) . ' for product ' . $__templater->escape($__vars['product']['product_title']) . ' has now been transferred.<br />
<br />
You will no longer be able to access the purchase history, receive support, or download updates.';
	return $__finalCompiled;
});