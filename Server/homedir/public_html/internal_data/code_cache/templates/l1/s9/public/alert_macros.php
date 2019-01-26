<?php
// FROM HASH: 794f2f56e943e6a7d75ad97b3f62df1d
return array('macros' => array('row' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'alert' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="contentRow">
		<div class="contentRow-figure">
			';
	if ($__vars['alert']['content_type'] === 'warning_alert') {
		$__finalCompiled .= '
	';
		if (!$__templater->method($__vars['alert']['Content'], 'canViewIssuer', array())) {
			$__finalCompiled .= '
		' . $__templater->fn('avatar', array($__templater->method($__vars['alert']['Content'], 'getAnonymizedIssuer', array()), 'xxs', false, array(
				'defaultname' => $__templater->arrayKey($__templater->method($__vars['alert']['Content'], 'getAnonymizedIssuer', array()), 'username'),
			))) . '
	';
		} else {
			$__finalCompiled .= '
		' . $__templater->fn('avatar', array($__vars['alert']['User'], 'xxs', false, array(
				'defaultname' => $__vars['alert']['username'],
			))) . '
	';
		}
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	' . $__templater->fn('avatar', array($__vars['alert']['User'], 'xxs', false, array(
			'defaultname' => $__vars['alert']['username'],
		))) . '
';
	}
	$__finalCompiled .= '
		</div>
		<div class="contentRow-main contentRow-main--close">
			' . $__templater->filter($__templater->method($__vars['alert'], 'render', array()), array(array('raw', array()),), true) . '
			<div class="contentRow-minor contentRow-minor--smaller">
				' . $__templater->fn('date_dynamic', array($__vars['alert']['event_date'], array(
	))) . '
			</div>
		</div>
	</div>
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';

	return $__finalCompiled;
});