<?php
// FROM HASH: 67656ff347455c4afb2c819cd52f344f
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<ul class="reactions-right__list">
	';
	if ($__vars['modifyReactLink']) {
		$__finalCompiled .= '
		<li class="modify_reacts">
			<a href="' . $__templater->escape($__vars['modifyReactLink']) . '"
			   data-xf-click="menu"
			   data-menu-pos-ref="< .modify_reacts"
			   aria-expanded="true"
			   aria-haspopup="true">
				<span>' . 'Undo Reactions' . '</span>
			</a>
			<div class="menu menu--modify-reacts" data-menu="menu" aria-hidden="true"
				 data-href="' . $__templater->escape($__vars['modifyReactLink']) . '"
				 data-load-target=".js-modifyReactsMenuBody"
				 data-nocache="true">
				<div class="menu-content js-modifyReactsMenuBody">
					<div class="menu-row">
						' . 'Loading' . $__vars['xf']['language']['ellipsis'] . '
					</div>
				</div>
			</div>
		</li>
	';
	}
	$__finalCompiled .= '

	';
	if ($__templater->isTraversable($__vars['reactions'])) {
		foreach ($__vars['reactions'] AS $__vars['reaction']) {
			if ($__vars['reactions']) {
				$__finalCompiled .= '
		<li>
			<a href="' . $__templater->escape($__vars['reaction']['url']) . '" data-xf-click="react" data-reaction-bar="< .message | .reactions-bar">
				' . $__templater->escape($__vars['reaction']['rendered']) . '
			</a>
		</li>
	';
			}
		}
	}
	$__finalCompiled .= '
</ul>


';
	if ($__vars['unreactLink']) {
		$__finalCompiled .= '
	<div>
		<a class="unreact-link" href="' . $__templater->escape($__vars['unreactLink']) . '" title="' . 'Undo Reactions' . '" data-xf-click="react" data-reaction-bar="< .message | .reactions-bar">' . 'Undo Reactions' . '</a>
	</div>
';
	} else {
		$__finalCompiled .= '
	';
		if ($__vars['reactions'] AND ($__templater->fn('property', array('thReactionsAnimation', ), false) !== 'none')) {
			$__finalCompiled .= '
		<div class="th_reactions__trigger">
			' . $__templater->fn('reaction_trigger_icon', array(), true) . '
		</div>
	';
		}
		$__finalCompiled .= '
';
	}
	return $__finalCompiled;
});