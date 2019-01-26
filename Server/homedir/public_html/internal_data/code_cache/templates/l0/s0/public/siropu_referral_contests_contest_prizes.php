<?php
// FROM HASH: 12c467324af35e85a95cdfcaa4d8a93d
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Prizes' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['contest']['name']));
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		<div class="block-body">
			';
	$__compilerTemp1 = '';
	$__vars['i'] = 0;
	if ($__templater->isTraversable($__vars['prizes'])) {
		foreach ($__vars['prizes'] AS $__vars['prize']) {
			$__vars['i']++;
			$__compilerTemp1 .= '
					' . $__templater->dataRow(array(
			), array(array(
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['i']),
			),
			array(
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['prize']['type']['name']),
			),
			array(
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['prize']['amount']),
			))) . '
				';
		}
	}
	$__finalCompiled .= $__templater->dataList('
				<thead>
					' . $__templater->dataRow(array(
		'rowtype' => 'header',
	), array(array(
		'_type' => 'cell',
		'html' => 'Place',
	),
	array(
		'_type' => 'cell',
		'html' => 'Prize',
	),
	array(
		'_type' => 'cell',
		'html' => 'Amount',
	))) . '
				</thead>
				' . $__compilerTemp1 . '
			', array(
		'data-xf-init' => 'responsive-data-list',
	)) . '
		</div>
	</div>
</div>';
	return $__finalCompiled;
});