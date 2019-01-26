<?php
// FROM HASH: dfd1f9b9dccb4c6691ad1f5d2be86fd7
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<ul>
	';
	if ($__templater->isTraversable($__vars['reacts'])) {
		foreach ($__vars['reacts'] AS $__vars['react']) {
			if ($__vars['reacts']) {
				$__finalCompiled .= '
		<li class="th_reactions__listItem">
			';
				if ($__vars['react']['canReact']) {
					$__finalCompiled .= '
				<a href="' . $__templater->escape($__vars['react']['url']) . '" data-xf-click="react" data-reaction-bar="< .message | .reactions-bar">' . $__templater->escape($__vars['react']['rendered']) . '</a>
				';
				} else {
					$__finalCompiled .= '
				' . $__templater->escape($__vars['react']['rendered']) . '
			';
				}
				$__finalCompiled .= '

			';
				if ($__templater->fn('property', array('th_reactions__showTitles', ), false)) {
					$__finalCompiled .= '
				';
					if ($__vars['react']['title']) {
						$__finalCompiled .= '
					<span class="reaction-title">' . $__templater->escape($__vars['react']['title']) . '</span>
				';
					}
					$__finalCompiled .= '
			';
				}
				$__finalCompiled .= '
			';
				if (($__templater->fn('property', array('thReactionsDivider', ), false) != '')) {
					$__finalCompiled .= '
				<span class="reaction-divider"> ' . $__templater->fn('property', array('thReactionsDivider', ), true) . ' </span>
			';
				}
				$__finalCompiled .= '
			<span class="reaction-count">' . $__templater->escape($__vars['react']['count']) . '</span>
		</li>
	';
			}
		}
	}
	$__finalCompiled .= '

	';
	if ($__vars['reactionListUrl']) {
		$__finalCompiled .= '
		<li>
			<a class="list-reacts" href="' . $__templater->escape($__vars['reactionListUrl']) . '" data-xf-click="overlay" data-nocache="true">' . 'Show all' . '</a>
		</li>
	';
	}
	$__finalCompiled .= '
</ul>';
	return $__finalCompiled;
});