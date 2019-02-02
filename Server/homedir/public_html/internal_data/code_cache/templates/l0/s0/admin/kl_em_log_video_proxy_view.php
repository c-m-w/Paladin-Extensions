<?php
// FROM HASH: 7632d40550b35397e52c6ac38b5bf9de
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Video proxy details');
	$__finalCompiled .= '

';
	$__templater->includeJs(array(
		'src' => 'https://cdn.polyfill.io/v2/polyfill.min.js',
	));
	$__finalCompiled .= '
';
	$__templater->includeJs(array(
		'src' => 'editor-manager/vendor/plyr.min.js',
		'addon' => 'KL/EditorManager',
	));
	$__finalCompiled .= '
';
	$__templater->includeJs(array(
		'src' => 'editor-manager/vendor/rangetouch.js',
		'addon' => 'KL/EditorManager',
	));
	$__finalCompiled .= '
';
	$__templater->includeJs(array(
		'src' => 'editor-manager/video-audio.js',
		'addon' => 'KL/EditorManager',
	));
	$__finalCompiled .= '
';
	$__templater->includeCss('public:kl_em_plyr.less');
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formRow('
				<div>
					<video class="js-PlyrVideo" controls>
						<source src="' . $__templater->fn('link', array('logs/video-proxy/video', $__vars['video'], ), true) . '" type="' . $__templater->escape($__vars['video']['mime_type']) . '">
						' . 'Your browser does not support the video tag.' . '
					</video>
				</div>
				<a href="' . $__templater->escape($__vars['audio']['url']) . '" target="_blank">' . $__templater->escape($__vars['audio']['url']) . '</a>
			', array(
		'label' => 'Video',
	)) . '
			' . $__templater->formRow($__templater->filter($__vars['video']['views'], array(array('number', array()),), true), array(
		'label' => 'Hits',
	)) . '
			' . $__templater->formRow($__templater->fn('date_dynamic', array($__vars['video']['first_request_date'], array(
	))), array(
		'label' => 'First requested',
	)) . '
			' . $__templater->formRow($__templater->fn('date_dynamic', array($__vars['video']['last_request_date'], array(
	))), array(
		'label' => 'Last requested',
	)) . '

			';
	if ($__vars['xf']['options']['KLEMVideoLinkProxyReferrer']['enabled'] AND !$__templater->test($__vars['video']['Referrers'], 'empty', array())) {
		$__finalCompiled .= '
				';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['video']['Referrers'])) {
			foreach ($__vars['video']['Referrers'] AS $__vars['referrer']) {
				$__compilerTemp1 .= '
						' . $__templater->dataRow(array(
					'rowclass' => 'dataList-row--noHover',
				), array(array(
					'dir' => 'auto',
					'_type' => 'cell',
					'html' => '<a href="' . $__templater->escape($__vars['referrer']['referrer_url']) . '" target="_blank">' . $__templater->escape($__vars['referrer']['referrer_url']) . '</a>',
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->filter($__vars['referrer']['hits'], array(array('number', array()),), true),
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->fn('date_dynamic', array($__vars['referrer']['first_date'], array(
				))),
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->fn('date_dynamic', array($__vars['referrer']['last_date'], array(
				))),
				))) . '
					';
			}
		}
		$__finalCompiled .= $__templater->dataList('
					' . $__templater->dataRow(array(
			'rowtype' => 'header',
		), array(array(
			'_type' => 'cell',
			'html' => 'Referrer',
		),
		array(
			'_type' => 'cell',
			'html' => 'Hits',
		),
		array(
			'_type' => 'cell',
			'html' => 'First seen',
		),
		array(
			'_type' => 'cell',
			'html' => 'Last seen',
		))) . '
					' . $__compilerTemp1 . '
				', array(
			'class' => 'dataList--separatedTop',
			'data-xf-init' => 'responsive-data-list',
		)) . '
			';
	}
	$__finalCompiled .= '
		</div>
	</div>
</div>';
	return $__finalCompiled;
});