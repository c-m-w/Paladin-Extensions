<?php
// FROM HASH: a0b94da4296265580c3330260bca102b
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->fn('can_view_steam_profile', array($__vars['user'], ), false)) {
		$__finalCompiled .= '
	';
		$__templater->includeCss('public:message_macros_steam.less');
		$__finalCompiled .= '
	<dl class="steam steam--justified">
		<dt>' . 'Steam' . '</dt>
		<dd>
			<a href="https://steamcommunity.com/profiles/' . $__templater->escape($__vars['user']['Profile']['connected_accounts']['steam']) . '/" target="_blank">
				';
		if ($__vars['xf']['options']['blacktea_steamauth_message_macro_steamid']) {
			$__finalCompiled .= '
					' . $__templater->escape($__vars['user']['Profile']['connected_accounts']['steam']) . '
				';
		} else {
			$__finalCompiled .= '
					' . '<font size="4"><i class="fa fa-external-link-square"></i></font>' . '
				';
		}
		$__finalCompiled .= '
			</a>
		</dd>
	</dl>
';
	}
	return $__finalCompiled;
});