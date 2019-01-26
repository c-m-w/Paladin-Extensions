<?php
// FROM HASH: 65dac1ff32d7e24a84543241eb30dd00
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['xf']['visitor']['user_id'] AND ($__templater->fn('property', array('uix_visitorTabsMobile', ), false) == 'canvas')) {
		$__finalCompiled .= '
	<ul class="sidePanel__tabs">
		<li>
			<a data-attr="navigation" class="sidePanel__tab sidePanel__tab--active js-visitorTab">' . $__templater->callMacro('uix_icons.less', 'icon', array(
			'icon' => 'menu',
		), $__vars) . '</a>
		</li>

		';
		if ($__vars['xf']['visitor']['user_id'] AND ($__templater->fn('property', array('uix_visitorTabsMobile', ), false) == 'canvas')) {
			$__finalCompiled .= '

		<li>
			<a data-attr="account" data-xf-click="toggle" data-target=".js-visitorTabPanel .uix_canvasPanelBody" class="sidePanel__tab js-visitorTab">' . $__templater->callMacro('uix_icons.less', 'icon', array(
				'icon' => 'user',
			), $__vars) . '</a>
		</li>

		<li>
			<a data-attr="inbox" data-xf-click="toggle" data-target=".js-convoTabPanel .uix_canvasPanelBody" data-badge="' . $__templater->filter($__vars['xf']['visitor']['conversations_unread'], array(array('number', array()),), true) . '" class="sidePanel__tab js-convoTab js-badge--conversations badgeContainer' . ($__vars['xf']['visitor']['conversations_unread'] ? ' badgeContainer--highlighted' : '') . '">
				' . $__templater->callMacro('uix_icons.less', 'icon', array(
				'icon' => 'inbox',
			), $__vars) . '
			</a>
		</li>

		<li>
			<a data-attr="alerts" data-xf-click="toggle" data-target=".js-alertTabPanel .uix_canvasPanelBody" data-badge="' . $__templater->filter($__vars['xf']['visitor']['alerts_unread'], array(array('number', array()),), true) . '" class="sidePanel__tab js-alertTab js-badge--alerts badgeContainer' . ($__vars['xf']['visitor']['alerts_unread'] ? ' badgeContainer--highlighted' : '') . '">
				' . $__templater->callMacro('uix_icons.less', 'icon', array(
				'icon' => 'alert',
			), $__vars) . '
			</a>
		</li>
		';
		}
		$__finalCompiled .= '
	</ul>
';
	}
	return $__finalCompiled;
});