<?php
// FROM HASH: e8c4b8c5a45f18a15a973543bb4691fd
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<xen:if is="' . $__templater->escape($__vars['event']['canGift']) . ' or ' . $__templater->escape($__vars['event']['nf_gifts']) . '">
	<span class="item">
		<xen:if is="' . $__templater->escape($__vars['event']['canGift']) . '">
			<a href="{xen:link calendar/gift, $event}" class="OverlayTrigger control">{xen:phrase nixfifty_giftupgrades_gift}</a>

			<xen:if is="' . $__templater->escape($__vars['event']['nf_gifts']) . '">
				(<a href="{xen:link calendar/gifts, $event}" class="OverlayTrigger">{xen:phrase nf_gifted_x_times, \'count=' . $__templater->escape($__vars['event']['nf_gifts']) . '\'}</a>)
			</xen:if>
		<xen:elseif is="' . $__templater->escape($__vars['event']['nf_gifts']) . '" />
			<a href="{xen:link calendar/gifts, $event}" class="OverlayTrigger">{xen:phrase nf_gifted_x_times, \'count=' . $__templater->escape($__vars['event']['nf_gifts']) . '\'}</a>
		</xen:if>
	</span>
</xen:if>';
	return $__finalCompiled;
});