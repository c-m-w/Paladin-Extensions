<?php
// FROM HASH: 5649ab29fc209a34e4012cc87c869db6
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['_upgrade']['PurchaseRequest']['extra_data']['is_gift']) {
		$__finalCompiled .= '
	(' . 'from' . $__vars['xf']['language']['label_separator'] . '
	' . $__templater->fn('username_link', array($__vars['_upgrade']['PurchaseRequest']['extra_data']['payUser'], false, array(
			'defaultname' => 'Guest',
			'href' => $__templater->fn('link', array('users/edit', $__vars['_upgrade']['PurchaseRequest']['extra_data']['payUser'], ), false),
		))) . ($__vars['_upgrade']['PurchaseRequest']['extra_data']['is_anonymous'] ? '*' : '') . ')
';
	}
	return $__finalCompiled;
});