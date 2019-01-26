<?php
// FROM HASH: 9dd40197eae498c5b3675f5deedbdb85
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('List Steam Connected Accounts');
	$__finalCompiled .= '
';
	$__templater->inlineCss('
	.dataList-cell.dataList-cell--image img {
		margin-right: 8px;
	}
');
	$__finalCompiled .= '
';
	if ((!$__vars['items']) OR $__templater->test($__vars['items'], 'empty', array())) {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'No items have been created yet.' . '</div>
';
	} else {
		$__finalCompiled .= '
	';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['items'])) {
			foreach ($__vars['items'] AS $__vars['item']) {
				$__compilerTemp1 .= '
						' . $__templater->dataRow(array(
				), array(array(
					'class' => 'dataList-cell--min dataList-cell--image dataList-cell--imageSmall',
					'href' => $__templater->fn('link', array('users/edit', $__vars['item'], ), false),
					'_type' => 'cell',
					'html' => '
								' . $__templater->fn('avatar', array($__vars['item'], 's', false, array(
					'href' => '',
				))) . '
							',
				),
				array(
					'href' => $__templater->fn('link', array('users/edit', $__vars['item'], ), false),
					'label' => $__templater->escape($__vars['item']['username']),
					'hint' => $__templater->escape($__vars['item']['email']),
					'_type' => 'main',
					'html' => '',
				),
				array(
					'href' => 'https://steamcommunity.com/profiles/' . $__vars['connectedAccounts'][$__vars['item']['user_id']]['provider_key'] . '/',
					'_type' => 'cell',
					'html' => '
								' . $__templater->escape($__vars['connectedAccounts'][$__vars['item']['user_id']]['provider_key']) . '
							',
				))) . '
					';
			}
		}
		$__finalCompiled .= $__templater->form('
		<div class="block-outer">
			' . $__templater->callMacro('filter_macros', 'quick_filter', array(
			'key' => 'items',
			'ajax' => $__templater->fn('link', array('steam/list', null, array('criteria' => $__vars['criteria'], ), ), false),
			'class' => 'block-outer-opposite',
		), $__vars) . '
		</div>
		<div class="block-container">
			<div class="block-body">
				' . $__templater->dataList('
					' . $__compilerTemp1 . '
				', array(
		)) . '
			</div>
			<div class="block-footer block-footer--split">
				<span class="block-footer-counter">' . $__templater->fn('display_totals', array($__vars['items'], $__vars['total'], ), true) . '</span>
			</div>
		</div>
		' . $__templater->fn('page_nav', array(array(
			'page' => $__vars['page'],
			'total' => $__vars['total'],
			'link' => 'steam/list',
			'wrapperclass' => 'js-filterHide block-outer block-outer--after',
			'perPage' => $__vars['perPage'],
		))) . '
	', array(
			'action' => '',
			'class' => 'block',
		)) . '
';
	}
	return $__finalCompiled;
});