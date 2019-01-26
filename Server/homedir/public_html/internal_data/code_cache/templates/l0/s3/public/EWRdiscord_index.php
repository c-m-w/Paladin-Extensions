<?php
// FROM HASH: e2aff940896626d5a4dd52062dd5f27d
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Discord');
	$__finalCompiled .= '

';
	$__templater->includeCss('EWRdiscord.less');
	$__finalCompiled .= '

';
	if ($__vars['xf']['options']['EWRdiscord_widgetbot']) {
		$__finalCompiled .= '
	<div class="block">
		<div class="block-container discord-container">
			<widgetbot
				server="' . $__templater->escape($__vars['cache']['server']) . '"
				channel="' . $__templater->escape($__vars['xf']['options']['EWRdiscord_widgetbot']) . '"
				shard="https://' . $__templater->escape($__vars['xf']['options']['EWRdiscord_widgetbot_shard']) . 'widgetbot.io"
				height="600" width="100%"></widgetbot>
			<script src="https://cdn.jsdelivr.net/npm/@widgetbot/html-embed"></script>
		</div>
	</div>
';
	} else {
		$__finalCompiled .= '
	<div class="block">
		<div class="block-container discord-container">
			<div class="block-body discord-body">
				' . 'We have officially moved our chat room to our own public Discord server!' . '
				<div class="discord-join">
					' . '<a href="' . $__templater->escape($__vars['cache']['invite']) . '">CLICK HERE TO JOIN OUR DISCORD</a>' . '
				</div>
				' . 'We have officially moved our chat room to our own public Discord server!' . '
			</div>
		</div>
	</div>

	';
		$__templater->modifySidebarHtml(null, '
		<iframe width="100%" height="600px" scrolling="no" frameborder="0"
			src="//discordapp.com/widget?id=' . $__templater->escape($__vars['cache']['server']) . '&theme=' . $__templater->fn('property', array('styleType', ), true) . '"></iframe>
	', 'replace');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	$__templater->modifySidebarHtml('_xfWidgetPositionSidebarEwrDiscordIndexSidebar', $__templater->widgetPosition('ewr_discord_index_sidebar', array()), 'replace');
	return $__finalCompiled;
});