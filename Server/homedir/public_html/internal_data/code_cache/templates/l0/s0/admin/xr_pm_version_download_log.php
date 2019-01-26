<?php
// FROM HASH: 228b9c6f305a4585ca263cf9285fc1f4
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Purchasers who downloaded ' . $__templater->escape($__vars['version']['Product']['product_title']) . ' ' . $__templater->escape($__vars['version']['version_string']) . '');
	$__finalCompiled .= '

<div class="block">
	<div class="block-container js-downloadLogList-' . $__templater->escape($__vars['version']['product_version_id']) . '">
		';
	$__compilerTemp1 = '';
	if ($__templater->isTraversable($__vars['downloads'])) {
		foreach ($__vars['downloads'] AS $__vars['download']) {
			$__compilerTemp1 .= '
				';
			$__compilerTemp2 = '';
			if ($__vars['download']['Purchase']['license_name']) {
				$__compilerTemp2 .= ' - ' . $__templater->escape($__vars['download']['Purchase']['license_name']);
			}
			$__compilerTemp1 .= $__templater->dataRow(array(
				'rowtype' => 'subsection',
				'rowclass' => 'dataList-row--noHover',
			), array(array(
				'href' => $__templater->fn('link', array('product-manager/purchases/edit', $__vars['download']['Purchase'], ), false),
				'_type' => 'cell',
				'html' => '
						' . $__templater->escape($__vars['download']['purchase_key']) . $__compilerTemp2 . '
					',
			))) . '
				' . $__templater->dataRow(array(
			), array(array(
				'_type' => 'cell',
				'html' => '
						' . $__templater->callMacro('public:member_list_macros', 'item', array(
				'user' => $__vars['download']['User'],
				'extraData' => $__templater->filter($__templater->fn('date_dynamic', array($__vars['download']['last_download_date'], ), false), array(array('preescaped', array()),), false),
			), $__vars) . '
					',
			))) . '
			';
		}
	}
	$__finalCompiled .= $__templater->dataList('
			<tbody class="dataList-rowGroup">
			' . $__compilerTemp1 . '
			</tbody>
		', array(
		'class' => 'block-body',
	)) . '
		';
	if ($__vars['hasNext']) {
		$__finalCompiled .= '
			<div class="block-footer">
				<span class="block-footer-controls">' . $__templater->button('
					' . 'Next' . $__vars['xf']['language']['ellipsis'] . '
				', array(
			'href' => $__templater->fn('link', array('product-manager/products/versions/download-log', $__vars['version'], array('page' => $__vars['page'] + 1, ), ), false),
			'data-xf-click' => 'inserter',
			'data-replace' => '.js-downloadLogList-' . $__vars['version']['product_version_id'],
			'data-scroll-target' => '< .overlay',
		), '', array(
		)) . '</span>
			</div>
		';
	}
	$__finalCompiled .= '
	</div>
</div>';
	return $__finalCompiled;
});