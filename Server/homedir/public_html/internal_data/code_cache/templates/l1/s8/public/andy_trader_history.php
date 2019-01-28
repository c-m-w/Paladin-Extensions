<?php
// FROM HASH: d5ef9c9a8aefeb9b6a4cbe1919acdc21
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Marketplace history for' . ' ' . $__templater->escape($__vars['username']));
	$__finalCompiled .= '

';
	$__templater->includeCss('andy_trader.less');
	$__finalCompiled .= '

<br />

<div class="wrapper">
	
';
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'view', )) AND (!$__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'rate', )))) {
		$__finalCompiled .= '
	' . 'View selling history for' . ' ' . $__templater->escape($__vars['username']) . '.
';
	}
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'view', )) AND $__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'rate', ))) {
		$__finalCompiled .= '
	' . 'View selling history or provide feedback for' . ' ' . $__templater->escape($__vars['username']) . '.
';
	}
	$__finalCompiled .= '

<br />
<br />

';
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'view', )) AND $__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'rate', ))) {
		$__finalCompiled .= '
	' . $__templater->button('Submit feedback', array(
			'class' => 'button--link button rippleButton',
			'href' => $__templater->fn('link', array('trader/rateseller', '', array('user_id' => $__vars['userId'], ), ), false),
			'rel' => 'nofollow',
		), '', array(
		)) . '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'view', ))) {
		$__finalCompiled .= '
	' . $__templater->button('Selling history' . ' (' . $__templater->escape($__vars['sellerCount']) . ')', array(
			'class' => 'button--link button rippleButton',
			'href' => $__templater->fn('link', array('trader/ratingseller', '', array('user_id' => $__vars['userId'], ), ), false),
			'rel' => 'nofollow',
		), '', array(
		)) . '
';
	}
	$__finalCompiled .= '

</div>

<br />

<div class="wrapper">

';
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'view', )) AND (!$__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'rate', )))) {
		$__finalCompiled .= '
	' . 'View buying history for' . ' ' . $__templater->escape($__vars['username']) . '.
';
	}
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'view', )) AND $__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'rate', ))) {
		$__finalCompiled .= '
	' . 'View buying history or provide feedback for' . ' ' . $__templater->escape($__vars['username']) . '.
';
	}
	$__finalCompiled .= '

<br />
<br />

';
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'view', )) AND $__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'rate', ))) {
		$__finalCompiled .= '
	' . $__templater->button('Submit feedback', array(
			'class' => 'button--link button rippleButton',
			'href' => $__templater->fn('link', array('trader/ratebuyer', '', array('user_id' => $__vars['userId'], ), ), false),
			'rel' => 'nofollow',
		), '', array(
		)) . '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'view', ))) {
		$__finalCompiled .= '
	' . $__templater->button('Buying history' . ' (' . $__templater->escape($__vars['buyerCount']) . ')', array(
			'class' => 'button--link button rippleButton',
			'href' => $__templater->fn('link', array('trader/ratingbuyer', '', array('user_id' => $__vars['userId'], ), ), false),
			'rel' => 'nofollow',
		), '', array(
		)) . '
';
	}
	$__finalCompiled .= '

</div>

<br />';
	return $__finalCompiled;
});