<?php
// FROM HASH: 76fc976ebc4d3723140132538fdbe293
return array('macros' => array('item' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'user' => '!',
		'extraData' => '',
		'extraDataBig' => false,
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="contentRow">
		<div class="contentRow-figure">
			' . $__templater->fn('avatar', array($__vars['user'], 's', false, array(
		'notooltip' => 'true',
	))) . '
		</div>
		<div class="contentRow-main">
			';
	if ($__vars['extraData']) {
		$__finalCompiled .= '
				<div class="contentRow-extra ' . ($__vars['extraDataBig'] ? 'contentRow-extra--largest' : '') . '">' . $__templater->escape($__vars['extraData']) . '</div>
			';
	}
	$__finalCompiled .= '
			<h3 class="contentRow-header">' . $__templater->fn('username_link', array($__vars['user'], true, array(
		'notooltip' => 'true',
	))) . '</h3>

			' . $__templater->fn('user_blurb', array($__vars['user'], array(
		'class' => 'contentRow-lesser',
	))) . '

			<div class="contentRow-minor">
				<ul class="listInline listInline--bullet">
					' . '
					<li><dl class="pairs pairs--inline">
						<dt>' . 'Messages' . '</dt>
						<dd>' . $__templater->filter($__vars['user']['message_count'], array(array('number', array()),), true) . '</dd>
					</dl></li>
					' . '
';
	if ($__templater->method($__vars['xf']['visitor'], 'canViewResources', array()) AND $__vars['user']['xfrm_resource_count']) {
		$__finalCompiled .= '
	<li><dl class="pairs pairs--inline">
		<dt>' . 'Resources' . '</dt>
		<dd>' . $__templater->filter($__vars['user']['xfrm_resource_count'], array(array('number', array()),), true) . '</dd>
	</dl></li>
';
	}
	$__finalCompiled .= '
					<li><dl class="pairs pairs--inline">
						<dt>' . 'Likes' . '</dt>
						<dd>' . $__templater->filter($__vars['user']['like_count'], array(array('number', array()),), true) . '</dd>
					</dl></li>
					' . '
					';
	if ($__vars['xf']['options']['enableTrophies']) {
		$__finalCompiled .= '
						<li><dl class="pairs pairs--inline">
							<dt>' . 'Points' . '</dt>
							<dd>' . $__templater->filter($__vars['user']['trophy_points'], array(array('number', array()),), true) . '</dd>
						</dl></li>
					';
	}
	$__finalCompiled .= '
					' . '
';
	if ($__vars['xf']['options']['siropuReferralContestsDisplayReferralCount']) {
		$__finalCompiled .= '
	<li><dl class="pairs pairs--inline">
			<dt>' . 'Referrals' . '</dt>
		<dd>
			';
		if ($__vars['user']['siropu_referral_count']) {
			$__finalCompiled .= '
				<a href="' . $__templater->fn('link', array('referrals/users', $__vars['user'], ), true) . '" class="fauxBlockLink-linkRow u-concealed" data-xf-click="overlay">' . $__templater->filter($__vars['user']['siropu_referral_count'], array(array('number', array()),), true) . '</a>
			';
		} else {
			$__finalCompiled .= '
				' . $__templater->filter($__vars['user']['siropu_referral_count'], array(array('number', array()),), true) . '
			';
		}
		$__finalCompiled .= '
		</dd>
		</dl></li>
';
	}
	$__finalCompiled .= '
				</ul>
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