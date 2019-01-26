<?php
// FROM HASH: 7f63f59c5964b7d5c1f7c278b546cfec
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<xen:if is="' . $__templater->escape($__vars['post']['canGift']) . ' or ' . $__templater->escape($__vars['post']['nf_gifts']) . '">
	<span class="item">
		<xen:if is="' . $__templater->escape($__vars['post']['canGift']) . '">
			<a href="{xen:link posts/gift, $post}" class="OverlayTrigger control">{xen:phrase nixfifty_giftupgrades_gift}</a>

			<xen:if is="' . $__templater->escape($__vars['post']['nf_gifts']) . '">
				(<a href="{xen:link posts/gifts, $post}" class="OverlayTrigger">{xen:phrase nf_gifted_x_times, \'count=' . $__templater->escape($__vars['post']['nf_gifts']) . '\'}</a>)
			</xen:if>
		<xen:elseif is="' . $__templater->escape($__vars['post']['nf_gifts']) . '" />
			<a href="{xen:link posts/gifts, $post}" class="OverlayTrigger">{xen:phrase nf_gifted_x_times, \'count=' . $__templater->escape($__vars['post']['nf_gifts']) . '\'}</a>
		</xen:if>
	</span>
</xen:if>';
	return $__finalCompiled;
});