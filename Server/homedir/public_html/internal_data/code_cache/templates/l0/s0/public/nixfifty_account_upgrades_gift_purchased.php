<?php
// FROM HASH: d36ab186b191666e522db4b15dfe79d6
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<xen:foreach loop="$purchased" value="$upgrade">
	<li class="primaryContent upgrade">
		<div action="' . $__templater->escape($__vars['payPalUrl']) . '" method="post" class="upgradeForm">
			<div class="cost">' . $__templater->escape($__vars['upgrade']['costPhrase']) . '</div>
			<a href="{xen:link full:account/upgrades/gift, \'\', \'upgrade_id=' . $__templater->escape($__vars['upgrade']['user_upgrade_id']) . '\'}" class="button OverlayTrigger">{xen:phrase nixfifty_giftupgrades_gift}</a>
		</div>

		<div class="upgradeMain">
			<h4 class="title">' . $__templater->escape($__vars['upgrade']['title']) . '</h4>
			<xen:if is="' . $__templater->escape($__vars['upgrade']['description']) . '">
				<div class="description">{xen:raw $upgrade.description}</div>
			</xen:if>
		</div>
	</li>
</xen:foreach>';
	return $__finalCompiled;
});