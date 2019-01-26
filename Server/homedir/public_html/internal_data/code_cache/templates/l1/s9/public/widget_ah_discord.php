<?php
// FROM HASH: f8753f37529da67bb22631385f3ea593
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->inlineJs($__templater->includeTemplate('widget_ah_discord_js', $__vars));
	$__finalCompiled .= '
';
	$__templater->includeCss('widget_ah_discord.less');
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('ahDW_perms', 'ahDW_perm', ))) {
		$__finalCompiled .= '
	<div class="block"' . $__templater->fn('widget_data', array($__vars['widget'], ), true) . '>	
		<div class="block-container">
			<h3 class="block-minorHeader">
				' . $__templater->escape($__vars['title']) . '
				';
		if ($__vars['xf']['options']['ahDW_showJoin']) {
			$__finalCompiled .= '
					';
			if ($__vars['xf']['options']['ahDW_joinDisplay'] == 'title') {
				$__finalCompiled .= '
						<a href="' . $__templater->escape($__vars['xf']['options']['ahDW_inviteLink']) . '" target="_blank" class="button button--primary joinButton" style="margin-left: auto;">' . $__templater->escape($__vars['xf']['options']['ahDW_joinText']) . '</a>
					';
			}
			$__finalCompiled .= '
				';
		}
		$__finalCompiled .= '
			</h3>
			<div class="block-body block-row">
				<div class="discord-widget"></div>
			</div>
		</div>
	</div>
';
	}
	return $__finalCompiled;
});