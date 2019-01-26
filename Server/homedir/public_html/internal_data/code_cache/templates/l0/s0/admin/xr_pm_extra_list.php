<?php
// FROM HASH: b9ca6637a494bfdb911bec6dea5dce7c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Product extras');
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('
		' . 'Add extra' . '
	', array(
		'icon' => 'add',
		'href' => $__templater->fn('link', array('product-manager/products/extras/add', ), false),
	), '', array(
	)) . '
');
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['extras'], 'empty', array())) {
		$__finalCompiled .= '
	<div class="block">
		<div class="block-container">
			<div class="block-body">
				';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['extras'])) {
			foreach ($__vars['extras'] AS $__vars['extra']) {
				$__compilerTemp1 .= '
						' . $__templater->dataRow(array(
					'label' => $__templater->escape($__vars['extra']['extra_title']),
					'href' => $__templater->fn('link', array('product-manager/products/extras/edit', $__vars['extra'], ), false),
					'delete' => $__templater->fn('link', array('product-manager/products/extras/delete', $__vars['extra'], ), false),
					'explain' => $__templater->escape($__vars['extra']['extra_description']),
				), array()) . '
					';
			}
		}
		$__finalCompiled .= $__templater->dataList('
					<tbody class="dataList-rowGroup">
					' . $__compilerTemp1 . '
					</tbody>
				', array(
		)) . '
			</div>
		</div>
	</div>
';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'No items have been created yet.' . '</div>
';
	}
	return $__finalCompiled;
});