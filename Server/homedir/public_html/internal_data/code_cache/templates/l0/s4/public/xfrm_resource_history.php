<?php
// FROM HASH: 4c9b6cd92ebf018b3922fcaf0e5f63f6
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->fn('prefix', array('resource', $__vars['resource'], 'escaped', ), true) . $__templater->escape($__vars['resource']['title']) . ' - ' . 'History');
	$__finalCompiled .= '

';
	$__compilerTemp1 = $__vars;
	$__compilerTemp1['pageSelected'] = 'history';
	$__templater->wrapTemplate('xfrm_resource_wrapper', $__compilerTemp1);
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		<div class="block-body">
			';
	$__compilerTemp2 = array(array(
		'_type' => 'cell',
		'html' => 'Version',
	)
,array(
		'_type' => 'cell',
		'html' => 'Release date',
	));
	if ($__vars['hasDownload']) {
		$__compilerTemp2[] = array(
			'_type' => 'cell',
			'html' => 'Downloads',
		);
	}
	$__compilerTemp2[] = array(
		'_type' => 'cell',
		'html' => 'Rating',
	);
	if ($__vars['hasDownload'] AND $__templater->method($__vars['resource'], 'canDownload', array())) {
		$__compilerTemp2[] = array(
			'_type' => 'cell',
			'html' => '',
		);
	}
	if ($__vars['hasDelete']) {
		$__compilerTemp2[] = array(
			'_type' => 'cell',
			'html' => '',
		);
	}
	$__compilerTemp3 = '';
	if ($__templater->isTraversable($__vars['versions'])) {
		foreach ($__vars['versions'] AS $__vars['version']) {
			$__compilerTemp3 .= '
					';
			$__compilerTemp4 = array(array(
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['version']['version_string']),
			)
,array(
				'_type' => 'cell',
				'html' => $__templater->fn('date_dynamic', array($__vars['version']['release_date'], array(
			))),
			));
			if ($__vars['hasDownload']) {
				$__compilerTemp4[] = array(
					'_type' => 'cell',
					'html' => '
								' . ($__templater->method($__vars['version'], 'isDownloadable', array()) ? $__templater->filter($__vars['version']['download_count'], array(array('number', array()),), true) : 'N/A') . '
							',
				);
			}
			$__compilerTemp4[] = array(
				'_type' => 'cell',
				'html' => '
							' . $__templater->callMacro('rating_macros', 'stars_text', array(
				'rating' => $__vars['version']['rating_avg'],
				'count' => $__vars['version']['rating_count'],
			), $__vars) . '
						',
			);
			if ($__vars['hasDownload'] AND $__templater->method($__vars['resource'], 'canDownload', array())) {
				if ($__templater->method($__vars['version'], 'isDownloadable', array())) {
					$__compilerTemp4[] = array(
						'href' => $__templater->fn('link', array('resources/version/download', $__vars['version'], ), false),
						'overlay' => ($__vars['version']['file_count'] > 1),
						'_type' => 'action',
						'html' => 'Download',
					);
				} else {
					$__compilerTemp4[] = array(
						'class' => 'dataList-cell--alt',
						'_type' => 'cell',
						'html' => '',
					);
				}
			}
			if ($__vars['hasDelete']) {
				if ($__templater->method($__vars['version'], 'canDelete', array())) {
					$__compilerTemp4[] = array(
						'href' => $__templater->fn('link', array('resources/version/delete', $__vars['version'], ), false),
						'_type' => 'delete',
						'html' => '',
					);
				} else {
					$__compilerTemp4[] = array(
						'class' => 'dataList-cell--alt',
						'_type' => 'cell',
						'html' => '',
					);
				}
			}
			$__compilerTemp3 .= $__templater->dataRow(array(
				'rowclass' => (($__vars['version']['version_state'] == 'deleted') ? 'dataList-row--deleted' : ''),
			), $__compilerTemp4) . '
				';
		}
	}
	$__finalCompiled .= $__templater->dataList('
				' . $__templater->dataRow(array(
		'rowtype' => 'header',
	), $__compilerTemp2) . '
				' . $__compilerTemp3 . '
			', array(
		'data-xf-init' => 'responsive-data-list',
	)) . '
		</div>
	</div>
</div>';
	return $__finalCompiled;
});