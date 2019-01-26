<?php
// FROM HASH: 7a03aebaf96edbcb4891b0b0b1265f83
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<xen:title>{xen:phrase nf_gift_upgrade_to_x, \'user=' . $__templater->escape($__vars['giftUser']['username']) . '\'}</xen:title>

<xen:navigation>
	<xen:breadcrumb source="$breadcrumbs" />
</xen:navigation>

<div class="xenForm formOverlay">
	<dl class="ctrlUnit">
		<dt>{xen:phrase upgrade}</dt>
		<dd>' . $__templater->escape($__vars['upgrade']['title']) . ' (' . $__templater->escape($__vars['upgrade']['costPhrase']) . ')</dd>
	</dl>

	<dl class="ctrlUnit">
		<dt>{xen:phrase nixfifty_giftupgrades_payment_processor}</dt>
		<dd>' . $__templater->escape($__vars['processor']) . '</dd>
	</dl>

	<dl class="ctrlUnit">
		<dt>{xen:phrase nixfifty_giftupgrades_send_gift_anonymously}:</dt>
		<dd>
			<xen:if is="' . $__templater->escape($__vars['anonymous']) . '">
				{xen:phrase yes}
			<xen:else />
				{xen:phrase no}
			</xen:if>
		</dd>
	</dl>

	<xen:if hascontent="true">
		<xen:contentcheck>
			<xen:foreach loop="$upgrade.paymentForms" key="$processorId" value="$form">
				<dl id="' . $__templater->escape($__vars['processorId']) . '" class="ctrlUnit submitUnit">
					<dt></dt>
					<dd>{xen:raw $form}</dd>
				</dl>
			</xen:foreach>
		</xen:contentcheck>
	</xen:if>
</div>';
	return $__finalCompiled;
});