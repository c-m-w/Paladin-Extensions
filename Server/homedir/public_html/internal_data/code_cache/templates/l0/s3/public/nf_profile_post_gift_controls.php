<?php
// FROM HASH: 9de5f425f1bec314e3520968f305b2fa
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<xen:if is="' . $__templater->escape($__vars['profilePost']['canGift']) . ' or ' . $__templater->escape($__vars['profilePost']['nf_gifts']) . '">
	<span class="item">
		<xen:if is="' . $__templater->escape($__vars['profilePost']['canGift']) . '">
			<a href="{xen:link profile-posts/gift, $profilePost}" class="OverlayTrigger control">{xen:phrase nixfifty_giftupgrades_gift}</a>

			<xen:if is="' . $__templater->escape($__vars['profilePost']['nf_gifts']) . '">
				(<a href="{xen:link profile-posts/gifts, $profilePost}" class="OverlayTrigger">{xen:phrase nf_gifted_x_times, \'count=' . $__templater->escape($__vars['profilePost']['nf_gifts']) . '\'}</a>)
			</xen:if>
		<xen:elseif is="' . $__templater->escape($__vars['profilePost']['nf_gifts']) . '" />
			<a href="{xen:link profile-posts/gifts, $profilePost}" class="OverlayTrigger">{xen:phrase nf_gifted_x_times, \'count=' . $__templater->escape($__vars['profilePost']['nf_gifts']) . '\'}</a>
		</xen:if>
	</span>
</xen:if>';
	return $__finalCompiled;
});