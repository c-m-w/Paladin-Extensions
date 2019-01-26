<?php
// FROM HASH: 10e278a41508c310d9935bd1363f0a61
return array('macros' => array('react_block' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'reactionId' => '!',
		'reacts' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__compilerTemp1 = '';
	$__compilerTemp1 .= '
					';
	if ($__templater->isTraversable($__vars['reacts'])) {
		foreach ($__vars['reacts'] AS $__vars['reactId'] => $__vars['react']) {
			$__compilerTemp1 .= '
						<li>
							<div class="contentRow contentRow--alignMiddle">
								<div class="contentRow-figure">
									' . $__templater->fn('avatar', array($__vars['react']['Reactor'], 'xs', false, array(
			))) . '
								</div>
								<div class="contentRow-main">
									';
			if ($__templater->method($__vars['react'], 'canUnreact', array())) {
				$__compilerTemp1 .= '
										<div class="contentRow-extra contentRow-extra--large">
											<a href="' . $__templater->escape($__templater->method($__templater->method($__vars['react'], 'getHandler', array()), 'getUnreactSingleLink', array($__vars['react']['react_id'], ))) . '" data-xf-click="overlay">
												<i class="fa fa-times" aria-hidden="true"></i>
											</a>
										</div>
									';
			}
			$__compilerTemp1 .= '

									<h3 class="contentRow-title">' . $__templater->fn('username_link', array($__vars['react']['Reactor'], true, array(
				'class' => 'reactOverviewBlock-header',
			))) . '</h3>

									<div class="contentRow-lesser">
										' . $__templater->fn('date_dynamic', array($__vars['react']['react_date'], array(
			))) . '
									</div>
								</div>
							</div>
						</li>
					';
		}
	}
	$__compilerTemp1 .= '
				';
	if (strlen(trim($__compilerTemp1)) > 0) {
		$__finalCompiled .= '
		<li class="reactOverviewBlock">
			<h3 class="reaction-item block-textHeader">
				' . $__templater->fn('reaction', array($__vars['reactionId'], 'list', ), true) . '
				<span class="reaction-title">' . $__templater->escape($__vars['xf']['reactions'][$__vars['reactionId']]['title']) . '</span>
			</h3>
			<ol class="reactOverviewBlock-list">
				' . $__compilerTemp1 . '
			</ol>
		</li>
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['title']) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->escape($__vars['title']));
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('th_members_who_reacted_this_reactions');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['breadcrumbs']) {
		$__finalCompiled .= '
	';
		$__templater->breadcrumbs($__vars['breadcrumbs']);
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	$__templater->includeCss('th_reactions.less');
	$__finalCompiled .= '
' . $__templater->includeTemplate('th_xfrm_jsOptions', $__vars) . '
';
	$__templater->includeJs(array(
		'src' => 'themehouse/reactions/react.js',
		'addon' => 'ThemeHouse/Reactions',
	));
	$__finalCompiled .= '

<div class="block js-reactList js-reactList-' . $__templater->escape($__vars['type']) . $__templater->escape($__vars['id']) . '">
	<div class="block-container">
		' . $__templater->callMacro('th_display_reactions', 'react_total_bar', array(
		'reacts' => $__vars['reactsByType'],
		'reactsCount' => $__vars['reactsCount'],
	), $__vars) . '
		<div class="block-body">
			<h2 class="block-tabHeader block-tabHeader--reactionsList tabs"
				data-xf-init="tabs"
				data-panes=".js-reactionTabPanes-' . $__templater->escape($__vars['type']) . $__templater->escape($__vars['id']) . '"
				data-state="replace"
				role="tablist">
				<span class="hScroller-scroll">
					<span class="tabs-tab"
						  id="all"
						  role="tab">' . 'All' . ' (' . $__templater->escape($__vars['reactsCount']) . ')</span>

					';
	if ($__templater->isTraversable($__vars['xf']['reactionTypes'])) {
		foreach ($__vars['xf']['reactionTypes'] AS $__vars['reactionTypeId'] => $__vars['reactionType']) {
			$__finalCompiled .= '
						';
			if ($__templater->fn('count', array($__vars['reactsByReactionType'][$__vars['reactionTypeId']], ), false)) {
				$__finalCompiled .= '
							<span class="tabs-tab"
								  id="' . $__templater->escape($__vars['reactionTypeId']) . '"
								  role="tab">' . $__templater->escape($__vars['reactionType']['title']) . ' (' . $__templater->fn('count', array($__vars['reactsByType'][$__vars['reactionTypeId']], ), true) . ')</span>
						';
			}
			$__finalCompiled .= '
					';
		}
	}
	$__finalCompiled .= '
				</span>
			</h2>
		</div>
	</div>

	<div class="block-container">
		<ul class="tabPanes js-reactionTabPanes-' . $__templater->escape($__vars['type']) . $__templater->escape($__vars['id']) . '">
			';
	if ($__templater->isTraversable($__vars['reactsByReactionType'])) {
		foreach ($__vars['reactsByReactionType'] AS $__vars['reactionTypeId'] => $__vars['reactions']) {
			$__finalCompiled .= '
				<li class="is-active" role="tabpanel" id="' . $__templater->escape($__vars['reactionTypeId']) . '">
					<div class="block-body">
						<ol class="reactOverviewBlocks">
							';
			if ($__templater->isTraversable($__vars['reactions'])) {
				foreach ($__vars['reactions'] AS $__vars['reactionId'] => $__vars['reacts']) {
					$__finalCompiled .= '
								' . $__templater->callMacro(null, 'react_block', array(
						'reactionId' => $__vars['reactionId'],
						'reacts' => $__vars['reacts'],
					), $__vars) . '
							';
				}
			}
			$__finalCompiled .= '
						</ol>
					</div>
				</li>
			';
		}
	}
	$__finalCompiled .= '
		</ul>
	</div>
</div>

';
	return $__finalCompiled;
});