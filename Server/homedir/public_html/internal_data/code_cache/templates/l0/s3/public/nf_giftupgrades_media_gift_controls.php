<?php
// FROM HASH: 74e7e08044e8328833895dc269a635b5
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<xen:if is="' . $__templater->escape($__vars['media']['canGift']) . ' or ' . $__templater->escape($__vars['media']['nf_gifts']) . '">
	<span class="item">
		<xen:if is="' . $__templater->escape($__vars['media']['canGift']) . '">
			<a href="{xen:link xengallery/gift, $media}" class="OverlayTrigger control">{xen:phrase nixfifty_giftupgrades_gift}</a>

			<xen:if is="' . $__templater->escape($__vars['media']['nf_gifts']) . '">
				(<a href="{xen:link xengallery/gifts, $media}" class="OverlayTrigger">{xen:phrase nf_gifted_x_times, \'count=' . $__templater->escape($__vars['media']['nf_gifts']) . '\'}</a>)
			</xen:if>
		<xen:elseif is="' . $__templater->escape($__vars['media']['nf_gifts']) . '" />
			<a href="{xen:link xengallery/gifts, $media}" class="OverlayTrigger">{xen:phrase nf_gifted_x_times, \'count=' . $__templater->escape($__vars['media']['nf_gifts']) . '\'}</a>
		</xen:if>
	</span>
</xen:if>';
	return $__finalCompiled;
});