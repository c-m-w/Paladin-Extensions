<?php
// FROM HASH: 46d18d91979c1b25d7c863b83ea46062
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<div class="block" data-widget-section="memberReactions"' . $__templater->fn('widget_data', array($__vars['widget'], ), true) . '>
	<div class="block-container">
		<div class="block-minorHeader">' . $__templater->escape($__vars['title']) . '</div>
		<div class="block-body">
			<div class="block-row">
				<div class="reactionCount">
					<div class="reactionCount-row reactionCount-row--heading">
						<div class="reactionCount-row-cell reactionCount-row-cell--primary">' . 'Reaction' . '</div>
						<div class="reactionCount-row-cell reactionCount-row-cell--secondary">' . 'Given' . '</div>
						<div class="reactionCount-row-cell reactionCount-row-cell--secondary">' . 'Received' . '</div>
					</div>
					';
	if ($__templater->isTraversable($__vars['reactionCounts'])) {
		foreach ($__vars['reactionCounts'] AS $__vars['reactionCount']) {
			$__finalCompiled .= '
						<div class="reactionCount-row">
							<div class="reactionCount-row-cell reactionCount-row-cell--primary">' . $__templater->fn('reaction', array($__vars['reactionCount']['reaction'], ), true) . '</div>
							<div class="reactionCount-row-cell reactionCount-row-cell--secondary">' . $__templater->filter($__vars['reactionCount']['count_given'], array(array('number', array()),), true) . '</div>
							<div class="reactionCount-row-cell reactionCount-row-cell--secondary">' . $__templater->filter($__vars['reactionCount']['count_received'], array(array('number', array()),), true) . '</div>
						</div>
					';
		}
	}
	$__finalCompiled .= '
				</div>
			</div>
		</div>
	</div>
</div>

';
	$__templater->includeCss('th_reactions.less');
	return $__finalCompiled;
});