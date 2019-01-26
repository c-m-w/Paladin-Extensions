<?php
// FROM HASH: 21bcef63cb0acb2af3757f3ab3dc4617
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
						<div class="reactionCount-row-cell">' . 'Reaction' . '</div>
						<div class="reactionCount-row-cell">' . 'Given' . '</div>
						<div class="reactionCount-row-cell">' . 'Received' . '</div>
					</div>
					';
	if ($__templater->isTraversable($__vars['reactionCounts'])) {
		foreach ($__vars['reactionCounts'] AS $__vars['reactionCount']) {
			$__finalCompiled .= '
						<div class="reactionCount-row">
							<div class="reactionCount-row-cell">' . $__templater->fn('reaction', array($__vars['reactionCount']['reaction'], ), true) . '</div>
							<div class="reactionCount-row-cell"><a href="' . $__templater->fn('link', array('members/reactions', $__vars['user'], array('type' => 'given', 'reaction_id' => $__vars['reactionCount']['reaction']['reaction_id'], ), ), true) . '">' . $__templater->filter($__vars['reactionCount']['count_given'], array(array('number_short', array()),), true) . '</a></div>
							<div class="reactionCount-row-cell"><a href="' . $__templater->fn('link', array('members/reactions', $__vars['user'], array('type' => 'received', 'reaction_id' => $__vars['reactionCount']['reaction']['reaction_id'], ), ), true) . '">' . $__templater->filter($__vars['reactionCount']['count_received'], array(array('number_short', array()),), true) . '</a></div>
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