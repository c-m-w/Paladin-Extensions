<?php
// FROM HASH: 9611ba93b72db4992bc6fa54f8a395d2
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Trader history for' . ' ' . $__templater->escape($__vars['username']));
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
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'view', ))) {
		$__finalCompiled .= '
	<a href="' . $__templater->fn('link', array('trader/ratingseller', '', array('user_id' => $__vars['userId'], ), ), true) . '" rel="nofollow">' . 'Selling history' . ' (' . $__templater->escape($__vars['sellerCount']) . ')</a>
';
	}
	$__finalCompiled .= '

<br />
<br />

';
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'view', )) AND $__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'rate', ))) {
		$__finalCompiled .= '
	<a href="' . $__templater->fn('link', array('trader/rateseller', '', array('user_id' => $__vars['userId'], ), ), true) . '" rel="nofollow">' . 'Submit feedback' . '</a>
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
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'view', ))) {
		$__finalCompiled .= '
	<a href="' . $__templater->fn('link', array('trader/ratingbuyer', '', array('user_id' => $__vars['userId'], ), ), true) . '" rel="nofollow">' . 'Buying history' . ' (' . $__templater->escape($__vars['buyerCount']) . ')</a>
';
	}
	$__finalCompiled .= '

<br />
<br />

';
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'view', )) AND $__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'rate', ))) {
		$__finalCompiled .= '
	<a href="' . $__templater->fn('link', array('trader/ratebuyer', '', array('user_id' => $__vars['userId'], ), ), true) . '" rel="nofollow">' . 'Submit feedback' . '</a>
';
	}
	$__finalCompiled .= '

</div>

<br />';
	return $__finalCompiled;
});