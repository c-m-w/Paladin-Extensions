<?php
// FROM HASH: f6fd143d46c59b033b9dd84a3202957a
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Top referrers' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['contest']['name']));
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		<div class="block-body">
			';
	if (!$__templater->test($__vars['topReferrers'], 'empty', array())) {
		$__finalCompiled .= '
				' . $__templater->callMacro('siropu_referral_contests_contest_view', 'top_referrers', array(
			'referrers' => $__vars['topReferrers'],
		), $__vars) . '
			';
	} else {
		$__finalCompiled .= '
				<div class="block-row">' . 'No referrers have been found.' . '</div>
			';
	}
	$__finalCompiled .= '
		</div>
	</div>
</div>';
	return $__finalCompiled;
});