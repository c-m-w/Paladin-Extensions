<?php
// FROM HASH: ae1d54f9ad6b4e1135df0053ba717b16
return array('macros' => array('details' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'contest' => '!',
		'prizes' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<p>' . $__templater->filter($__templater->method($__vars['contest'], 'renderDescription', array()), array(array('raw', array()),), true) . '</p>
	';
	if ($__vars['contest']['end_date']) {
		$__finalCompiled .= '
		<p><b>' . 'Contest end date' . $__vars['xf']['language']['label_separator'] . '</b> <span style="color: ' . ($__templater->method($__vars['contest'], 'isValid', array()) ? 'green' : 'crimson') . '">' . $__templater->fn('date_dynamic', array($__vars['contest']['end_date'], array(
		))) . '</span></p>
	';
	}
	$__finalCompiled .= '
	';
	if (!$__templater->test($__vars['prizes'], 'empty', array())) {
		$__finalCompiled .= '
		<p>
			<b>' . 'Prizes' . $__vars['xf']['language']['label_separator'] . '</b>
			<ul class="listPlain">
				';
		$__vars['i'] = 0;
		if ($__templater->isTraversable($__vars['prizes'])) {
			foreach ($__vars['prizes'] AS $__vars['prize']) {
				$__vars['i']++;
				$__finalCompiled .= '
					<li><b>(' . $__templater->escape($__vars['i']) . ')</b> ' . $__templater->escape($__vars['prize']['amount']) . ' ' . $__templater->escape($__vars['prize']['type']['name']) . '</li>
				';
			}
		}
		$__finalCompiled .= '
			</ul>
		</p>
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'top_referrers' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'referrers' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__compilerTemp1 = '';
	$__vars['i'] = 0;
	if ($__templater->isTraversable($__vars['referrers'])) {
		foreach ($__vars['referrers'] AS $__vars['referrer']) {
			$__vars['i']++;
			$__compilerTemp1 .= '
			' . $__templater->dataRow(array(
			), array(array(
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['i']),
			),
			array(
				'_type' => 'cell',
				'html' => $__templater->fn('username_link', array($__vars['referrer'], true, array(
			))),
			),
			array(
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['referrer']['referral_count']),
			))) . '
		';
		}
	}
	$__finalCompiled .= $__templater->dataList('
		<thead>
			' . $__templater->dataRow(array(
		'rowtype' => 'header',
	), array(array(
		'_type' => 'cell',
		'html' => 'Place',
	),
	array(
		'_type' => 'cell',
		'html' => 'Referrer',
	),
	array(
		'_type' => 'cell',
		'html' => 'Referrals',
	))) . '
		</thead>
		' . $__compilerTemp1 . '
	', array(
		'data-xf-init' => 'responsive-data-list',
	)) . '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->escape($__vars['contest']['name']));
	$__finalCompiled .= '

' . $__templater->widgetPosition('siropu_referral_contests_view_above', array()) . '

<div class="block">
	<div class="block-container">
		<div class="block-body block-row">
			' . $__templater->callMacro(null, 'details', array(
		'contest' => $__vars['contest'],
		'prizes' => $__templater->method($__vars['contest'], 'getPrizes', array()),
	), $__vars) . '
		</div>
	</div>
</div>

';
	if (!$__templater->test($__vars['topReferrers'], 'empty', array())) {
		$__finalCompiled .= '
	<div class="block">
		<div class="block-container">
			<div class="block-body">
				' . $__templater->callMacro(null, 'top_referrers', array(
			'referrers' => $__vars['topReferrers'],
		), $__vars) . '
			</div>
		</div>
	</div>
';
	}
	$__finalCompiled .= '

' . '

' . '

' . $__templater->widgetPosition('siropu_referral_contests_view_below', array());
	return $__finalCompiled;
});