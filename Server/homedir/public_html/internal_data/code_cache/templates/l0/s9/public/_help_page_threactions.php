<?php
// FROM HASH: def0e83c3f2eec43d50b6f699248ad0e
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if (!$__templater->test($__vars['reactions'], 'empty', array())) {
		$__finalCompiled .= '
	';
		if ($__templater->isTraversable($__vars['reaction_types'])) {
			foreach ($__vars['reaction_types'] AS $__vars['reaction_type']) {
				$__finalCompiled .= '
		<div class="block">
			<div class="block-container">
				';
				$__compilerTemp1 = '';
				if ($__templater->isTraversable($__vars['reactions'][$__vars['reaction_type']['reaction_type_id']])) {
					foreach ($__vars['reactions'][$__vars['reaction_type']['reaction_type_id']] AS $__vars['reaction']) {
						$__compilerTemp1 .= '
						' . $__templater->dataRow(array(
							'rowclass' => 'dataList-row--noHover',
						), array(array(
							'class' => 'dataList-cell--min dataList-cell--imageSmall dataList-cell--alt',
							'_type' => 'cell',
							'html' => '
								<img src="/' . $__templater->escape($__vars['reaction']['image_url']) . '" />
							',
						),
						array(
							'label' => $__templater->escape($__vars['reaction']['title']),
							'_type' => 'main',
							'html' => '',
						))) . '
					';
					}
				}
				$__finalCompiled .= $__templater->dataList('
					' . $__templater->dataRow(array(
					'rowtype' => 'header',
				), array(array(
					'class' => 'dataList-cell--min',
					'style' => 'background-color: ' . $__vars['reaction_type']['color'] . ';',
					'_type' => 'cell',
					'html' => '
							<img src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==">
						',
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->escape($__vars['reaction_type']['title']),
				))) . '
					' . $__compilerTemp1 . '
				', array(
					'data-xf-init' => 'responsive-data-list',
				)) . '
			</div>
		</div>
	';
			}
		}
		$__finalCompiled .= '
	';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'No items have been created yet.' . '</div>
';
	}
	return $__finalCompiled;
});