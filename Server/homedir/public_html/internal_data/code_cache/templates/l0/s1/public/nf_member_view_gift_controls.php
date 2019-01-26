<?php
// FROM HASH: e116ddd2ee821845508f37f5a75e39fe
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<xen:if is="' . $__templater->escape($__vars['canGift']) . '">
	<li><a href="{xen:link members/gift, $user}" class="OverlayTrigger">{xen:phrase nixfifty_giftupgrades_gift}</a></li>
</xen:if>';
	return $__finalCompiled;
});