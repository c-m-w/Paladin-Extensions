<?php
// FROM HASH: bdec4e9250c100b02da9e7c3b20f1ab4
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<div class="block">
	<div class="block-container">
		<h3 class="block-header">
			<a href="' . $__templater->fn('link', array('referral-contests', ), true) . '">' . 'Referral contests' . '</a>
		</h3>
		<div class="block-body">
			';
	if (!$__templater->test($__vars['contests'], 'empty', array())) {
		$__finalCompiled .= '
				<ul class="listPlain">
					';
		if ($__templater->isTraversable($__vars['contests'])) {
			foreach ($__vars['contests'] AS $__vars['contest']) {
				$__finalCompiled .= '
						<li class="block-row block-row--separated">
							<h3 class="block-textHeader">
								<a href="' . $__templater->fn('link', array('referral-contests', $__vars['contest'], ), true) . '">' . $__templater->filter($__vars['contest']['name'], array(array('raw', array()),), true) . '</a>
							</h3>

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
				if (!$__templater->test($__vars['contest']['prizes'], 'empty', array())) {
					$__finalCompiled .= '
								' . $__templater->button('<i class="fa fa-trophy" aria-hidden="true"></i>', array(
						'href' => $__templater->fn('link', array('referral-contests/prizes', $__vars['contest'], ), false),
						'class' => 'button--link',
						'title' => $__templater->filter('View prizes', array(array('for_attr', array()),), false),
						'data-xf-init' => 'tooltip',
						'data-xf-click' => 'overlay',
					), '', array(
					)) . '
							';
				}
				$__finalCompiled .= '

							' . $__templater->button('<i class="fa fa-users" aria-hidden="true"></i>', array(
					'href' => $__templater->fn('link', array('referral-contests/top-referrers', $__vars['contest'], ), false),
					'class' => 'button--link',
					'title' => $__templater->filter('View top referrers', array(array('for_attr', array()),), false),
					'data-xf-init' => 'tooltip',
					'data-xf-click' => 'overlay',
				), '', array(
				)) . '
						</li>
					';
			}
		}
		$__finalCompiled .= '
				</ul>
			';
	} else {
		$__finalCompiled .= '
				<div class="block-row">' . 'No contests have been found.' . '</div>
			';
	}
	$__finalCompiled .= '
		</div>
		';
	if (!$__templater->test($__vars['contests'], 'empty', array()) AND $__vars['options']['tools']) {
		$__finalCompiled .= '
			' . $__templater->callMacro('siropu_referral_contests_macros', 'referral_tools_block_footer', array(
			'faq' => false,
		), $__vars) . '
		';
	}
	$__finalCompiled .= '
	</div>
</div>';
	return $__finalCompiled;
});