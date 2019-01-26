<?php
// FROM HASH: 8766111bb1d079ea5a40ec7b70879af3
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Discord');
	$__finalCompiled .= '

';
	$__templater->includeCss('EWRdiscord.less');
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		';
	if ($__vars['xf']['options']['EWRdiscord_widgetbot']['channel']) {
		$__finalCompiled .= '
			<embed width="100%" height="600px"
				src="https://widgetbot.io/embed/' . $__templater->escape($__vars['cache']['server']) . '/' . $__templater->escape($__vars['xf']['options']['EWRdiscord_widgetbot']['channel']) . '/00' . (($__templater->fn('property', array('styleType', ), false) == 'light') ? '1' : '0') . '2/" />
		';
	} else {
		$__finalCompiled .= '
			<div class="block-body discord-body">
				' . 'We have officially moved our chat room to our own public Discord server!' . '
				<div class="discord-join">
					' . '<a href="' . $__templater->escape($__vars['cache']['invite']) . '">CLICK HERE TO JOIN OUR DISCORD</a>' . '
				</div>
				' . 'We have officially moved our chat room to our own public Discord server!' . '
			</div>
		';
	}
	$__finalCompiled .= '
	</div>
</div>

';
	$__templater->modifySidebarHtml(null, '
	<iframe width="100%" height="600px" scrolling="no" frameborder="0"
		src="//discordapp.com/widget?id=' . $__templater->escape($__vars['cache']['server']) . '&theme=' . $__templater->fn('property', array('styleType', ), true) . '"></iframe>
', 'replace');
	return $__finalCompiled;
});