<?php
// FROM HASH: 3b1a0647cce82c0c30e1ff2d13dc27b5
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Referral contests');
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('Add contest', array(
		'href' => $__templater->fn('link', array('referral-contests/add', ), false),
		'icon' => 'add',
	), '', array(
	)) . '
');
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['contests'], 'empty', array())) {
		$__finalCompiled .= '
	';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['contests'])) {
			foreach ($__vars['contests'] AS $__vars['contest']) {
				$__compilerTemp1 .= '
						' . $__templater->dataRow(array(
					'label' => $__templater->escape($__vars['contest']['name']),
					'href' => $__templater->fn('link', array('referral-contests/edit', $__vars['contest'], ), false),
					'delete' => $__templater->fn('link', array('referral-contests/delete', $__vars['contest'], ), false),
				), array(array(
					'width' => '5%',
					'class' => 'dataList-cell--separated',
					'style' => 'text-align: center;',
					'_type' => 'cell',
					'html' => '
								' . $__templater->button('<i class="fa fa-bar-chart" aria-hidden="true"></i>', array(
					'href' => $__templater->fn('link', array('referral-contests/statistics', $__vars['contest'], ), false),
					'class' => 'button--link',
					'data-xf-init' => 'tooltip',
					'data-xf-click' => 'overlay',
					'title' => $__templater->filter('Contest statistics', array(array('for_attr', array()),), false),
				), '', array(
				)) . '
							',
				),
				array(
					'name' => 'enabled[' . $__vars['contest']['contest_id'] . ']',
					'selected' => $__vars['contest']['enabled'],
					'class' => 'dataList-cell--separated',
					'submit' => 'true',
					'tooltip' => 'Enable / disable \'' . $__vars['contest']['name'] . '\'',
					'_type' => 'toggle',
					'html' => '',
				))) . '
					';
			}
		}
		$__finalCompiled .= $__templater->form('
		<div class="block-outer">
			' . $__templater->callMacro('filter_macros', 'quick_filter', array(
			'key' => 'contests',
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
					<span class="block-footer-counter">' . $__templater->fn('display_totals', array($__vars['contests'], $__vars['total'], ), true) . '</span>
				</div>
			</div>
		</div>
	', array(
			'action' => $__templater->fn('link', array('referral-contests/toggle', ), false),
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