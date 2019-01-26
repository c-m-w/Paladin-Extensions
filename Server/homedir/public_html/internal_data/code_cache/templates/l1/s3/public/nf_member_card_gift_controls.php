<?php
// FROM HASH: 82dbcd4bd3eb7b0a7c719ad66060f8f0
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<xen:if is="' . $__templater->escape($__vars['canGift']) . '">
	<a href="{xen:link members/gift, $user}" class="OverlayTrigger">{xen:phrase nixfifty_giftupgrades_gift}</a>
</xen:if>';
	return $__finalCompiled;
});