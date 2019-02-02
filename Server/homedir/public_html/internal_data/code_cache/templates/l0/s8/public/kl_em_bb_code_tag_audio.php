<?php
// FROM HASH: 2a9d51d95a02ce9fe796ea1b720340ab
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

<div class="bbCodeAudio">
	<audio class="js-PlyrAudio" controls>
		';
	if ($__templater->isTraversable($__vars['sources'])) {
		foreach ($__vars['sources'] AS $__vars['source']) {
			$__finalCompiled .= '
			<source src="' . $__templater->escape($__vars['source']['url']) . '" type="audio/' . $__templater->escape($__vars['source']['type']) . '">
		';
		}
	}
	$__finalCompiled .= '
		' . 'Your browser does not support the audio element.' . '
	</audio>
</div>';
	return $__finalCompiled;
});