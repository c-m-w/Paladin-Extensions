<?php
// FROM HASH: 232e423ff58d5a828cc36ae7ea86eee8
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Referral contests');
	$__finalCompiled .= '

' . $__templater->widgetPosition('siropu_referral_contests_list_above', array()) . '

';
	$__compilerTemp1 = true;
	if ($__templater->isTraversable($__vars['contests'])) {
		foreach ($__vars['contests'] AS $__vars['contest']) {
			$__compilerTemp1 = false;
			$__finalCompiled .= '
	<div class="block">
		<div class="block-container">
			<div class="block-header">
				<a href="' . $__templater->fn('link', array('referral-contests', $__vars['contest'], ), true) . '">' . $__templater->escape($__vars['contest']['name']) . '</a>
			</div>
			<div class="block-body block-row">
				' . $__templater->callMacro('siropu_referral_contests_contest_view', 'details', array(
				'contest' => $__vars['contest'],
			), $__vars) . '

				';
			if (!$__templater->test($__vars['contest']['prizes'], 'empty', array())) {
				$__finalCompiled .= '
					' . $__templater->button('<i class="fa fa-trophy" aria-hidden="true"></i> ' . 'View prizes', array(
					'href' => $__templater->fn('link', array('referral-contests/prizes', $__vars['contest'], ), false),
					'class' => 'button--link',
					'data-xf-click' => 'overlay',
				), '', array(
				)) . '
				';
			}
			$__finalCompiled .= '

				' . $__templater->button('<i class="fa fa-users" aria-hidden="true"></i> ' . 'View top referrers', array(
				'href' => $__templater->fn('link', array('referral-contests/top-referrers', $__vars['contest'], ), false),
				'class' => 'button--link',
				'data-xf-click' => 'overlay',
			), '', array(
			)) . '
			</div>
		</div>
	</div>
	';
		}
	}
	if ($__compilerTemp1) {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'No contests have been found.' . '</div>
';
	}
	$__finalCompiled .= '

' . $__templater->widgetPosition('siropu_referral_contests_list_below', array());
	return $__finalCompiled;
});