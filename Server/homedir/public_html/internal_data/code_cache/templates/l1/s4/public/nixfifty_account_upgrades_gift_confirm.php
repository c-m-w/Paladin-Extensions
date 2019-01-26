<?php
// FROM HASH: 07dfd244ffd86bbf82d4eb1ebd2c09d4
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<xen:title>{xen:phrase nixfifty_giftupgrades_gift_x_to_a_user, \'upgrade=' . $__templater->escape($__vars['upgrade']['title']) . '\'}</xen:title>
<xen:h1>{xen:phrase nixfifty_giftupgrades_gift_x_to_a_user, \'upgrade=' . $__templater->escape($__vars['upgrade']['title']) . '\'}</xen:h1>

<div class="xenForm">

	<dl class="ctrlUnit">
		<dt>{xen:phrase upgrade}:</dt>
		<dd>' . $__templater->escape($__vars['upgrade']['title']) . '</dd>
	</dl>

	<dl class="ctrlUnit">
		<dt>{xen:phrase cost}:</dt>
		<dd>' . $__templater->escape($__vars['upgrade']['costPhrase']) . '</dd>
	</dl>

	<dl class="ctrlUnit">
		<dt>{xen:phrase nixfifty_giftupgrades_payment_processor}:</dt>
		<dd>' . $__templater->escape($__vars['selectedProcessor']) . '</dd>
	</dl>

	<dl class="ctrlUnit findMember">
		<dt><label for="ctrl_title_gift_to">{xen:phrase nixfifty_giftupgrades_gift_to}:</label></dt>
		<dd>' . $__templater->escape($__vars['giftUser']['username']) . '</dd>
	</dl>

	<dl class="ctrlUnit">
		<dt>{xen:phrase nixfifty_giftupgrades_send_gift_anonymously}:</dt>
		<dd>{xen:if \'' . $__templater->escape($__vars['anonymous']) . '\', \'Yes\', \'No\'}</dd>
	</dl>

</div>
<xen:if hascontent="true">
	<xen:contentcheck>
		<xen:foreach loop="$upgrade.paymentForm" key="$processorId" value="$form">
			<div id="' . $__templater->escape($__vars['processorId']) . '" class="submitUnit" style="text-align: center; padding-right: 250px;">{xen:raw $form}</div>
		</xen:foreach>
	</xen:contentcheck>
</xen:if>';
	return $__finalCompiled;
});