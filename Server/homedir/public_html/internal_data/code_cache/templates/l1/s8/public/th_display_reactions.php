<?php
// FROM HASH: 1d77d09e3cdc20aaf9738f61cc99f26b
return array('macros' => array('reactions_bar' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'type' => '!',
		'id' => '!',
		'content' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__templater->fn('react_handler_status', array($__vars['type'], ), false)) {
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

		';
		$__compilerTemp1 = '';
		$__compilerTemp1 .= '
					';
		$__compilerTemp2 = $__vars;
		$__compilerTemp2['reactionContentList'] = $__templater->fn('reaction_content_list', array($__vars['content'], $__templater->method($__vars['content'], 'getReactUsers', array()), array($__vars['type'], $__vars['content'][$__vars['id']], $__vars['content']['user_id'], ), true, $__templater->fn('property', array('thMaxReactionsMin', ), false), 0, ), false);
		$__compilerTemp2['reactionList'] = $__templater->fn('reaction_list', array($__vars['content'], $__templater->method($__vars['content'], 'getReactUsers', array()), array($__vars['type'], $__vars['content'][$__vars['id']], $__vars['content']['user_id'], ), ), false);
		$__compilerTemp1 .= $__templater->includeTemplate('th_display_bar_internal_reactions', $__compilerTemp2) . '
				';
		if (strlen(trim($__compilerTemp1)) > 0) {
			$__finalCompiled .= '
			<div class="reactions-bar reactions-bar--' . $__templater->fn('property', array('thReactionsAnimation', ), true) . ' content"
				 id="reactions-bar-' . $__templater->escape($__vars['content'][$__vars['id']]) . '">
				' . $__compilerTemp1 . '
			</div>
		';
		}
		$__finalCompiled .= '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'reactions_bit_list' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'type' => '!',
		'id' => '!',
		'content' => '!',
		'reactUsers' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__templater->fn('property', array('th_reactions_showOnThreadList', ), false)) {
		$__finalCompiled .= '
		';
		$__templater->includeCss('th_reactions.less');
		$__finalCompiled .= '

		';
		$__compilerTemp1 = '';
		$__compilerTemp1 .= '
					';
		$__compilerTemp2 = $__vars;
		$__compilerTemp2['reactionContentList'] = $__templater->fn('reaction_content_list', array($__vars['content'], $__vars['reactUsers'], array($__vars['type'], $__vars['content'][$__vars['id']], $__vars['content']['user_id'], ), false, 3, $__vars['xf']['options']['th_reactionsLimit'], '', true, ), false);
		$__compilerTemp1 .= $__templater->includeTemplate('th_display_bar_internal_reactions', $__compilerTemp2) . '
				';
		if (strlen(trim($__compilerTemp1)) > 0) {
			$__finalCompiled .= '
			<div class="reactions-bar bit-list" id="reactions-bar-' . $__templater->escape($__vars['content'][$__vars['id']]) . '">
				' . $__compilerTemp1 . '
			</div>
		';
		}
		$__finalCompiled .= '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'react_postbit' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'reacts' => '!',
		'reactsCount' => '!',
		'displayType' => '!',
		'displayLocation' => 'other',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__vars['displayType'] === 'bar') {
		$__finalCompiled .= '
		' . $__templater->callMacro(null, 'react_total_bar', array(
			'reacts' => $__vars['reacts'],
			'reactsCount' => $__vars['reactsCount'],
			'displayLocation' => $__vars['displayLocation'],
		), $__vars) . '
	';
	}
	$__finalCompiled .= '

	';
	if ($__vars['displayType'] === 'text') {
		$__finalCompiled .= '
		' . $__templater->callMacro(null, 'react_total_text', array(
			'reacts' => $__vars['reacts'],
			'reactsCount' => $__vars['reactsCount'],
			'displayLocation' => $__vars['displayLocation'],
		), $__vars) . '
	';
	}
	$__finalCompiled .= '

	';
	if ($__vars['displayType'] === 'percentage') {
		$__finalCompiled .= '
		' . $__templater->callMacro(null, 'react_total_percentage', array(
			'reacts' => $__vars['reacts'],
			'reactsCount' => $__vars['reactsCount'],
			'displayLocation' => $__vars['displayLocation'],
		), $__vars) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'react_total_percentage' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'reacts' => '!',
		'reactsCount' => '!',
		'displayLocation' => 'other',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__compilerTemp1 = '';
	$__compilerTemp1 .= '
						';
	if ($__templater->isTraversable($__vars['xf']['reactionTypes'])) {
		foreach ($__vars['xf']['reactionTypes'] AS $__vars['reactionTypeId'] => $__vars['reactionType']) {
			$__compilerTemp1 .= '
							';
			$__vars['rtTotal'] = ($__templater->fn('is_array', array($__vars['reacts'][$__vars['reactionTypeId']], ), false) ? $__templater->fn('count', array($__vars['reacts'][$__vars['reactionTypeId']], ), false) : $__vars['reacts'][$__vars['reactionTypeId']]);
			$__compilerTemp1 .= '
							';
			$__vars['segmentPerc'] = ((($__templater->fn('is_array', array($__vars['reacts'][$__vars['reactionTypeId']], ), false) ? $__templater->fn('count', array($__vars['reacts'][$__vars['reactionTypeId']], ), false) : $__vars['reacts'][$__vars['reactionTypeId']]) / ($__vars['reactsCount'] ? $__vars['reactsCount'] : 1)) * 100) . '%';
			$__compilerTemp1 .= '
							<span data-xf-init="tooltip"
								  title="' . $__templater->escape($__vars['reactionType']['title']) . '"
								  class="reacts_total_perc__reactionType reacts_total_perc__reactionType--' . $__templater->escape($__vars['reactionTypeId']) . '"
								  style="color: ' . $__templater->escape($__vars['reactionType']['color']) . '">
								' . $__templater->filter($__vars['segmentPerc'], array(array('number', array()),), true) . '%
							</span>
						';
		}
	}
	$__compilerTemp1 .= '
					';
	if (strlen(trim($__compilerTemp1)) > 0) {
		$__finalCompiled .= '
		<div class="reacts_total_perc reacts_total_perc--' . $__templater->escape($__vars['displayLocation']) . '">
			<div class="pairs pairs--justified">
				<dt>' . 'Reactions' . '</dt>
				<dd>
					' . $__compilerTemp1 . '
				</dd>
			</div>
		</div>
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'react_total_text' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'reacts' => '!',
		'reactsCount' => '!',
		'displayLocation' => 'other',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__compilerTemp1 = '';
	$__compilerTemp1 .= '        
						';
	if ($__templater->isTraversable($__vars['xf']['reactionTypes'])) {
		foreach ($__vars['xf']['reactionTypes'] AS $__vars['reactionTypeId'] => $__vars['reactionType']) {
			$__compilerTemp1 .= '
							';
			$__vars['rtTotal'] = ($__templater->fn('is_array', array($__vars['reacts'][$__vars['reactionTypeId']], ), false) ? $__templater->fn('count', array($__vars['reacts'][$__vars['reactionTypeId']], ), false) : $__vars['reacts'][$__vars['reactionTypeId']]);
			$__compilerTemp1 .= '
							<span data-xf-init="tooltip"
								  title="' . $__templater->escape($__vars['reactionType']['title']) . '"
								  class="reacts_total_text__reactionType reacts_total_text__reactionType--' . $__templater->escape($__vars['reactionTypeId']) . '" style="color: ' . $__templater->escape($__vars['reactionType']['color']) . '">' . $__templater->filter($__vars['rtTotal'], array(array('number', array()),), true) . '</span>
						';
		}
	}
	$__compilerTemp1 .= '
					';
	if (strlen(trim($__compilerTemp1)) > 0) {
		$__finalCompiled .= '
		';
		$__templater->includeCss('th_reactions.less');
		$__finalCompiled .= '
		<div class="reacts_total_text reacts_total_text--' . $__templater->escape($__vars['displayLocation']) . '">
			<div class="pairs pairs--justified">
				<dt>' . 'Reactions' . '</dt>
				<dd>
					' . $__compilerTemp1 . '
				</dd>
			</div>
		</div>
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'react_total_bar' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'reacts' => '!',
		'reactsCount' => '!',
		'class' => '',
		'width' => '100%',
		'displayLocation' => 'other',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__vars['reactsCount']) {
		$__finalCompiled .= '
		';
		$__compilerTemp1 = '';
		$__compilerTemp1 .= '
					' . '
					';
		if ($__templater->isTraversable($__vars['xf']['reactionTypes'])) {
			foreach ($__vars['xf']['reactionTypes'] AS $__vars['reactionTypeId'] => $__vars['reactionType']) {
				$__compilerTemp1 .= '
						';
				$__vars['rtTotal'] = $__templater->preEscaped(($__templater->fn('is_array', array($__vars['reacts'][$__vars['reactionTypeId']], ), false) ? $__templater->fn('count', array($__vars['reacts'][$__vars['reactionTypeId']], ), true) : $__templater->escape($__vars['reacts'][$__vars['reactionTypeId']])));
				$__compilerTemp1 .= '
						';
				$__vars['segmentWidth'] = ((($__templater->fn('is_array', array($__vars['reacts'][$__vars['reactionTypeId']], ), false) ? $__templater->fn('count', array($__vars['reacts'][$__vars['reactionTypeId']], ), false) : $__vars['reacts'][$__vars['reactionTypeId']]) / $__vars['reactsCount']) * 100) . '%';
				$__compilerTemp1 .= '
						<div class="react_bar_segment react_bar_' . $__templater->escape($__vars['reactionTypeId']) . ' Tooltip" title="' . '' . $__templater->escape($__vars['reactionType']['title']) . ' reactions: ' . ($__templater->fn('empty', array($__vars['rtTotal'])) ? '0' : $__templater->escape($__vars['rtTotal'])) . '' . '" style="background-color: ' . $__templater->escape($__vars['reactionType']['color']) . '; width: ' . $__templater->escape($__vars['segmentWidth']) . '" data-xf-init="tooltip"></div>
					';
			}
		}
		$__compilerTemp1 .= '
				';
		if (strlen(trim($__compilerTemp1)) > 0) {
			$__finalCompiled .= '
			<div class="react_total_bar react_total_bar--' . $__templater->escape($__vars['displayLocation']) . ' ' . $__templater->escape($__vars['class']) . '">
				' . $__compilerTemp1 . '
			</div>
		';
		}
		$__finalCompiled .= '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '

' . '

' . '

' . '

' . '

';
	return $__finalCompiled;
});