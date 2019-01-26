<?php
// FROM HASH: 266a3db2d126bbe6668fb906057d085f
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<li><label>
	<input type="checkbox" name="user_criteria[giftupgrades_gift_received_count][rule]" value="giftupgrades_gift_received_count" class="Disabler" id="ucrit_giftupgrades_gift_received_count" {xen:checked $userCriteria.giftupgrades_gift_received_count} />
	{xen:phrase nixfifty_giftupgrades_user_has_received_at_least_x_gifts}:</label>
	<div class="criteriaQualifier" id="ucrit_giftupgrades_gift_received_count_Disabler">
		<xen:spinbox name="user_criteria[giftupgrades_gift_received_count][data][items]" value="' . $__templater->escape($__vars['userCriteria']['giftupgrades_gift_received_count']['items']) . '" size="5" min="0" step="1" />
	</div>
</li>

<li><label>
	<input type="checkbox" name="user_criteria[giftupgrades_gift_given_count][rule]" value="giftupgrades_gift_given_count" class="Disabler" id="ucrit_giftupgrades_gift_given_count" {xen:checked $userCriteria.giftupgrades_gift_given_count} />
	{xen:phrase nixfifty_giftupgrades_user_has_given_at_least_x_gifts}:</label>
	<div class="criteriaQualifier" id="ucrit_giftupgrades_gift_given_count_Disabler">
		<xen:spinbox name="user_criteria[giftupgrades_gift_given_count][data][items]" value="' . $__templater->escape($__vars['userCriteria']['giftupgrades_gift_given_count']['items']) . '" size="5" min="0" step="1" />
	</div>
</li>';
	return $__finalCompiled;
});