<?php
// FROM HASH: 08413b1ac9850e73d0fe9c14ec05ba37
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Buying history for' . ' ' . $__templater->escape($__vars['buyer_name']));
	$__finalCompiled .= '

<a href="' . $__templater->fn('link', array('trader/history', '', array('user_id' => $__vars['userId'], ), ), true) . '" rel="nofollow">' . 'Return to marketplace history menu' . '</a>
<br />
<br />

<div class="block-container">
	<div class="block-body">
		';
	$__compilerTemp1 = '';
	if ($__templater->isTraversable($__vars['results'])) {
		foreach ($__vars['results'] AS $__vars['result']) {
			$__compilerTemp1 .= '
				';
			$__compilerTemp2 = array(array(
				'_type' => 'cell',
				'html' => $__templater->fn('date_dynamic', array($__vars['result']['timestamp'], array(
			))),
			));
			if ($__vars['result']['rating'] == 0) {
				$__compilerTemp2[] = array(
					'_type' => 'cell',
					'html' => 'Positive',
				);
			}
			if ($__vars['result']['rating'] == 1) {
				$__compilerTemp2[] = array(
					'_type' => 'cell',
					'html' => 'Neutral',
				);
			}
			if ($__vars['result']['rating'] == 2) {
				$__compilerTemp2[] = array(
					'_type' => 'cell',
					'html' => 'Negative',
				);
			}
			$__compilerTemp2[] = array(
				'_type' => 'cell',
				'html' => '<a href="' . $__templater->escape($__vars['xf']['options']['traderMembersLink']) . $__templater->escape($__vars['result']['seller_id']) . '/">' . $__templater->escape($__vars['result']['seller_name']) . '</a>',
			);
			$__compilerTemp2[] = array(
				'_type' => 'cell',
				'html' => '<a href="' . $__templater->escape($__vars['xf']['options']['traderMembersLink']) . $__templater->escape($__vars['result']['buyer_id']) . '/">' . $__templater->escape($__vars['result']['buyer_name']) . '</a>',
			);
			$__compilerTemp2[] = array(
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['result']['seller_comment']),
			);
			if (($__vars['visitor']['user_id'] == $__vars['result']['buyer_id']) AND (($__vars['editLimit'] < $__vars['result']['timestamp']) AND (!$__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'admin', ))))) {
				$__compilerTemp2[] = array(
					'_type' => 'cell',
					'html' => '<a href="' . $__templater->fn('link', array('trader/editbuyer', '', array('trader_id' => $__vars['result']['trader_id'], ), ), true) . '">' . 'Edit' . '</a>',
				);
			}
			if (($__vars['visitor']['user_id'] == $__vars['result']['buyer_id']) AND (($__vars['editLimit'] >= $__vars['result']['timestamp']) AND (!$__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'admin', ))))) {
				$__compilerTemp2[] = array(
					'_type' => 'cell',
					'html' => '&nbsp',
				);
			}
			if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'admin', ))) {
				$__compilerTemp2[] = array(
					'_type' => 'cell',
					'html' => '<a href="' . $__templater->fn('link', array('trader/editbuyer', '', array('trader_id' => $__vars['result']['trader_id'], ), ), true) . '">' . 'Edit' . '</a>',
				);
			}
			if (($__vars['visitor']['user_id'] != $__vars['result']['buyer_id']) AND (!$__templater->method($__vars['xf']['visitor'], 'hasPermission', array('trader', 'admin', )))) {
				$__compilerTemp2[] = array(
					'_type' => 'cell',
					'html' => '&nbsp',
				);
			}
			$__compilerTemp1 .= $__templater->dataRow(array(
				'rowclass' => 'dataList-row--noHover',
			), $__compilerTemp2) . '
			';
		}
	}
	$__finalCompiled .= $__templater->dataList('
			' . $__templater->dataRow(array(
		'rowtype' => 'header',
	), array(array(
		'_type' => 'cell',
		'html' => 'Date',
	),
	array(
		'_type' => 'cell',
		'html' => 'Rating',
	),
	array(
		'_type' => 'cell',
		'html' => 'Buyer',
	),
	array(
		'_type' => 'cell',
		'html' => 'Seller',
	),
	array(
		'_type' => 'cell',
		'html' => 'Seller comment',
	),
	array(
		'_type' => 'cell',
		'html' => 'Action',
	))) . '
			' . $__compilerTemp1 . '
		', array(
		'data-xf-init' => 'responsive-data-list',
	)) . '
	</div>
</div>

<br />';
	return $__finalCompiled;
});