<?php
// FROM HASH: e3da20911e2268653e7d60924d8dc0a6
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['xf']['options']['EWRdiscord_widgetbot'] AND ((!$__vars['xf']['visitor']['Option']['discord_options']['crate']) AND ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('EWRdiscord', 'viewCrate', )) AND ($__vars['xf']['uri'] != $__templater->fn('link', array('ewr-discord', ), false))))) {
		$__finalCompiled .= '
	
	<script src="https://cdn.jsdelivr.net/npm/@widgetbot/crate@3" async>
		const crate = new Crate({
			server: \'' . $__templater->escape($__vars['xf']['options']['EWRdiscord_server']) . '\',
			channel: \'' . $__templater->escape($__vars['xf']['options']['EWRdiscord_widgetbot']) . '\',
			shard: \'https://' . $__templater->escape($__vars['xf']['options']['EWRdiscord_widgetbot_shard']) . 'widgetbot.io\',
			
			notifications: ' . ((!$__vars['xf']['visitor']['Option']['discord_options']['toast']) ? 'true' : 'false') . ',
			indicator: ' . ((!$__vars['xf']['visitor']['Option']['discord_options']['count']) ? 'true' : 'false') . ',
		});

		';
		if ($__vars['xf']['visitor']['user_id'] AND (!$__vars['xf']['visitor']['Option']['discord_options']['toast'])) {
			$__finalCompiled .= '
			crate.notify({
				content: \'' . 'Discord integration can be disabled in [account preferences](' . $__templater->fn('link', array('canonical:account/preferences', ), true) . ')' . '\',
				timeout: 10000
			});
		';
		}
		$__finalCompiled .= '
	</script>
';
	}
	return $__finalCompiled;
});