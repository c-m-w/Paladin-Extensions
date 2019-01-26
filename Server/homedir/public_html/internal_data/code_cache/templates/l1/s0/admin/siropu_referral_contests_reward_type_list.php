<?php
// FROM HASH: b13e058def2321598dd0b5479960be17
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Reward types');
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	<div class="buttonGroup-buttonWrapper">
		' . $__templater->button('Add reward type', array(
		'class' => 'menuTrigger',
		'data-xf-click' => 'menu',
		'aria-expanded' => 'false',
		'aria-haspopup' => 'true',
		'icon' => 'add',
	), '', array(
	)) . '
		<div class="menu" data-menu="menu" aria-hidden="true">
			<div class="menu-content">
				<h4 class="menu-header">' . 'Type' . '</h4>
				<a href="' . $__templater->fn('link', array('referral-contests/reward-types/add', '', array('type' => 'trophy_points', ), ), true) . '" class="menu-linkRow">' . 'Trophy Points' . '</a>
				<a href="' . $__templater->fn('link', array('referral-contests/reward-types/add', '', array('type' => 'dbtech_credits', ), ), true) . '" class="menu-linkRow">' . '[DBTech] Credits' . '</a>
			</div>
		</div>
	</div>
');
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['rewardTypes'], 'empty', array())) {
		$__finalCompiled .= '
	';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['rewardTypes'])) {
			foreach ($__vars['rewardTypes'] AS $__vars['rewardType']) {
				$__compilerTemp1 .= '
						' . $__templater->dataRow(array(
					'label' => $__templater->escape($__vars['rewardType']['name']),
					'href' => $__templater->fn('link', array('referral-contests/reward-types/edit', $__vars['rewardType'], ), false),
					'hint' => $__templater->escape($__vars['rewardType']['type_phrase']),
					'delete' => $__templater->fn('link', array('referral-contests/reward-types/delete', $__vars['rewardType'], ), false),
					'dir' => 'auto',
				), array()) . '
					';
			}
		}
		$__finalCompiled .= $__templater->form('
		<div class="block-outer">
			' . $__templater->callMacro('filter_macros', 'quick_filter', array(
			'key' => 'rewardTypes',
			'class' => 'block-outer-opposite',
		), $__vars) . '
		</div>
		<div class="block-container">
			<div class="block-body">
				' . $__templater->dataList('
					' . $__compilerTemp1 . '
				', array(
		)) . '
				<div class="block-footer">
					<span class="block-footer-counter">' . $__templater->fn('display_totals', array($__vars['rewardTypes'], $__vars['total'], ), true) . '</span>
				</div>
			</div>
		</div>
	', array(
			'action' => $__templater->fn('link', array('referral-contests/reward-types/toggle', ), false),
			'class' => 'block',
			'ajax' => 'true',
		)) . '
';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'No items have been created yet.' . '</div>
';
	}
	return $__finalCompiled;
});