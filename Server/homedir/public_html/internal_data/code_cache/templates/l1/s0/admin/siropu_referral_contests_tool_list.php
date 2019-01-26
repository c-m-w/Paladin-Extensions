<?php
// FROM HASH: fd27b3cbd50ece1afe60986dfe08cad0
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Referral tools');
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	<div class="buttonGroup-buttonWrapper">
		' . $__templater->button('Add tool', array(
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
				<a href="' . $__templater->fn('link', array('referral-contests/tools/add', '', array('type' => 'banner', ), ), true) . '" class="menu-linkRow">' . 'Banner' . '</a>
				<a href="' . $__templater->fn('link', array('referral-contests/tools/add', '', array('type' => 'text', ), ), true) . '" class="menu-linkRow">' . 'Text link' . '</a>
			</div>
		</div>
	</div>
');
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['tools'], 'empty', array())) {
		$__finalCompiled .= '
	';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['tools'])) {
			foreach ($__vars['tools'] AS $__vars['tool']) {
				$__compilerTemp1 .= '
						' . $__templater->dataRow(array(
					'label' => $__templater->escape($__vars['tool']['name']),
					'href' => $__templater->fn('link', array('referral-contests/tools/edit', $__vars['tool'], ), false),
					'hint' => $__templater->escape($__vars['tool']['type_phrase']),
					'explain' => $__templater->escape($__vars['tool']['click_count']) . ' ' . 'Clicks',
					'delete' => $__templater->fn('link', array('referral-contests/tools/delete', $__vars['tool'], ), false),
					'dir' => 'auto',
				), array(array(
					'name' => 'enabled[' . $__vars['tool']['tool_id'] . ']',
					'selected' => $__vars['tool']['enabled'],
					'class' => 'dataList-cell--separated',
					'submit' => 'true',
					'tooltip' => 'Enable / disable \'' . $__vars['tool']['name'] . '\'',
					'_type' => 'toggle',
					'html' => '',
				))) . '
					';
			}
		}
		$__finalCompiled .= $__templater->form('
		<div class="block-outer">
			' . $__templater->callMacro('filter_macros', 'quick_filter', array(
			'key' => 'tools',
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
					<span class="block-footer-counter">' . $__templater->fn('display_totals', array($__vars['tools'], $__vars['total'], ), true) . '</span>
				</div>
			</div>
		</div>
	', array(
			'action' => $__templater->fn('link', array('referral-contests/tools/toggle', ), false),
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