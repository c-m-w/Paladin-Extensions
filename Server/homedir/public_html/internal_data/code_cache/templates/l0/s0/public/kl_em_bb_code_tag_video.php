<?php
// FROM HASH: 2e7dfd724b5d6c1a7905e0a355ac8c49
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
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
	$__templater->includeCss('kl_em_plyr.less');
	$__finalCompiled .= '

<div class="bbCodeVideo" style="' . $__templater->filter($__vars['size'], array(array('raw', array()),), true) . '">
	<video class="js-PlyrVideo" controls>
		';
	if ($__templater->isTraversable($__vars['sources'])) {
		foreach ($__vars['sources'] AS $__vars['source']) {
			$__finalCompiled .= '
			<source src="' . $__templater->escape($__vars['source']['url']) . '" type="video/' . $__templater->escape($__vars['source']['type']) . '">
		';
		}
	}
	$__finalCompiled .= '
		' . 'Your browser does not support the video tag.' . '
	</video>
</div>';
	return $__finalCompiled;
});