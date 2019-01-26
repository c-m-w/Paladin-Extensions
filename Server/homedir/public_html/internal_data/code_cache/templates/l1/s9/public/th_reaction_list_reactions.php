<?php
// FROM HASH: d4fbb927ca8df2b227152c524d6671d0
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<div class="th_reactions__scrollContainer">
	<div class="th_reactions__scroll th_reactions__leftScrollLeft">
		<div class="th_reactions__scroll__iconWrap th_reactions__leftScrollLeft__iconWrap">
			<i class="fa fa-chevron-left"></i>
		</div>
	</div>

	<ul class="reactions-right__list">
		' . '

		' . '
		';
	if ($__templater->isTraversable($__vars['reactions'])) {
		foreach ($__vars['reactions'] AS $__vars['reaction']) {
			if ($__vars['reactions']) {
				$__finalCompiled .= '
			';
				if ($__vars['reaction']['is_default']) {
					$__finalCompiled .= '
				<li class="th_reactions__reaction">
					<a href="' . $__templater->escape($__vars['reaction']['url']) . '" data-xf-click="react" data-reaction-bar="< .message | .reactions-bar">
						' . $__templater->escape($__vars['reaction']['rendered']) . '
					</a>
				</li>
			';
				}
				$__finalCompiled .= '
		';
			}
		}
	}
	$__finalCompiled .= '

		';
	if ($__templater->isTraversable($__vars['reactions'])) {
		foreach ($__vars['reactions'] AS $__vars['reaction']) {
			if ($__vars['reactions']) {
				$__finalCompiled .= '
			';
				if (!$__vars['reaction']['is_default']) {
					$__finalCompiled .= '
				<li class="th_reactions__reaction">
					<a href="' . $__templater->escape($__vars['reaction']['url']) . '" data-xf-click="react" data-reaction-bar="< .message | .reactions-bar">
						' . $__templater->escape($__vars['reaction']['rendered']) . '
					</a>
				</li>
			';
				}
				$__finalCompiled .= '
		';
			}
		}
	}
	$__finalCompiled .= '
	</ul>

	<div class="th_reactions__scroll th_reactions__rightScrollRight">
		<div class="th_reactions__scroll__iconWrap th_reactions__rightScrollRight__iconWrap">
			<i class="fa fa-chevron-right"></i>
		</div>
	</div>
</div>

';
	if ($__vars['unreactLink'] OR $__vars['modifyReactLink']) {
		$__finalCompiled .= '
	<div class="modify_reacts">
		<a data-xf-click="menu"
			data-menu-pos-ref="< .modify_reacts"
			aria-expanded="true"
			aria-haspopup="true">
			<span>' . 'Undo Reactions' . '</span>
		</a>
		<div class="menu menu--modify-reacts" data-menu="menu" aria-hidden="true"
				data-href="' . ($__templater->escape($__vars['unreactLink']) ?: $__templater->escape($__vars['modifyReactLink'])) . '"
				data-load-target=".js-modifyReactsMenuBody"
				data-nocache="true">
			<div class="menu-content js-modifyReactsMenuBody">
				<div class="menu-row">
					' . 'Loading' . $__vars['xf']['language']['ellipsis'] . '
				</div>
			</div>
		</div>
	</div>
';
	}
	$__finalCompiled .= '

';
	if ((!$__vars['unreactLink']) AND ($__vars['reactions'] AND ($__templater->fn('property', array('thReactionsAnimation', ), false) !== 'none'))) {
		$__finalCompiled .= '
	';
		$__vars['th_reactions_defaultTrigger'] = '0';
		$__finalCompiled .= '
	';
		if ($__templater->isTraversable($__vars['reactions'])) {
			foreach ($__vars['reactions'] AS $__vars['reaction']) {
				if ($__vars['reactions']) {
					$__finalCompiled .= '
		';
					if ($__vars['reaction']['is_default']) {
						$__finalCompiled .= '
			';
						$__vars['th_reactions_defaultTrigger'] = '1';
						$__finalCompiled .= '
			<div class="th_reactions__trigger th_reactions__triggerPrimary">
				<span href="' . $__templater->escape($__vars['reaction']['url']) . '" data-xf-click="react" data-reaction-bar="< .message | .reactions-bar">
					' . $__templater->escape($__vars['reaction']['rendered']) . '
				</span>
			</div>
		';
					}
					$__finalCompiled .= '
	';
				}
			}
		}
		$__finalCompiled .= '

	';
		if ((!$__vars['th_reactions_defaultTrigger']) OR $__templater->fn('property', array('th_reactions_secondaryTrigger', ), false)) {
			$__finalCompiled .= '
		<div class="th_reactions__trigger th_reactions__triggerSecondary">
			' . $__templater->fn('reaction_trigger_icon', array(), true) . '
		</div>
	';
		}
		$__finalCompiled .= '
';
	}
	return $__finalCompiled;
});