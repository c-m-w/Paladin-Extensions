<?php
// FROM HASH: 06b8a96c594d1fab5bb81cc7aa2b350d
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('widget_ah_discord.less');
	$__finalCompiled .= '
<script> ' . $__templater->includeTemplate('widget_ah_discord_js', $__vars) . ' </script>

';
	if ($__vars['xf']['visitor']['user_id']) {
		$__finalCompiled .= '
';
		if ($__templater->method($__vars['xf']['visitor'], 'isMemberOf', array(11, ))) {
			$__finalCompiled .= '
';
		} else {
			$__finalCompiled .= '
<div class="block"' . $__templater->fn('widget_data', array($__vars['widget'], ), true) . '>	
	<div class="block-container">
		<h3 class="block-minorHeader">' . $__templater->escape($__vars['title']) . '</h3>
		<div class="block-body block-row">
			<div class="discord-widget"></div>
		</div>
	</div>
</div>
';
		}
		$__finalCompiled .= '
';
	}
	return $__finalCompiled;
});