<?php
// FROM HASH: 68c4423da90f8cb74db35d3a27668327
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['shoutbox']['showTitle']) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Shoutbox');
		$__finalCompiled .= '
	';
		$__templater->pageParams['noH1'] = true;
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['shoutbox']['isFullPage']) {
		$__finalCompiled .= '
	';
		$__templater->setPageParam('template', 'SIROPU_SHOUTBOX_CONTAINER');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	$__templater->includeCss('siropu_shoutbox.less');
	$__finalCompiled .= '

';
	$__templater->includeJs(array(
		'src' => 'siropu/shoutbox/core.js',
		'min' => '1',
	));
	$__templater->inlineJs('
	jQuery.extend(XF.phrases, {
		siropu_shoutbox_loading_more_shouts: "' . $__templater->filter('Loading more shouts...', array(array('escape', array('js', )),), false) . '",
		siropu_shoutbox_shout_delete_confirm: "' . $__templater->filter('Are you sure you want to delete this shout?', array(array('escape', array('js', )),), false) . '",
		siropu_shoutbox_placeholder: "' . $__templater->filter('What\'s on your mind?', array(array('escape', array('js', )),), false) . '",
		siropu_shoutbox_please_wait: "' . $__templater->filter('Please wait...', array(array('escape', array('js', )),), false) . '",
		siropu_shoutbox_please_wait_x_seconds: "' . $__templater->filter('Please wait ' . $__vars['xf']['options']['siropuShoutboxFloodCheckLength'] . ' seconds...', array(array('escape', array('js', )),), false) . '"
	});
');
	$__finalCompiled .= '

<div class="siropuShoutbox block" data-refresh-interval="' . ($__vars['xf']['options']['siropuShoutboxRefreshInterval'] * 1000) . '" data-last-id="' . $__templater->escape($__vars['shoutbox']['lastId']) . '" data-load-more="' . (($__templater->method($__vars['xf']['visitor'], 'canUseSiropuShoutbox', array()) AND ($__templater->fn('count', array($__vars['shoutbox']['shouts'], ), false) == $__vars['xf']['options']['siropuShoutboxDisplayLimit'])) ? 1 : 0) . '" data-last-active="' . $__templater->escape($__vars['xf']['time']) . '" data-sound="' . ($__vars['shoutbox']['sound'] ? 'on' : 'off') . '" data-reverse="' . ($__vars['shoutbox']['reverse'] ? 'true' : 'false') . '" data-collapsed="' . ($__vars['shoutbox']['collapsed'] ? 'true' : 'false') . '" data-timeout="' . ($__templater->method($__vars['xf']['visitor'], 'canBypassFloodCheckSiropuShoutbox', array()) ? 0 : ($__vars['xf']['options']['siropuShoutboxFloodCheckLength'] * 1000)) . '" data-xf-init="siropu-shoutbox">
	<div class="block-container">
		<div class="' . ($__vars['options']['sidebarStyle'] ? 'block-minorHeader' : 'block-header') . '">
			<i class="fa fa-comments" aria-hidden="true"></i> ' . $__templater->escape($__vars['title']) . '
			<span>
				';
	if ($__vars['xf']['options']['siropuShoutboxPopup'] AND (!$__vars['shoutbox']['isFullPage'])) {
		$__finalCompiled .= '
					<a href="' . $__templater->fn('link', array('shoutbox/fullpage', ), true) . '" title="' . 'Open in popup' . '" data-xf-click="siropu-shoutbox-popup" data-xf-init="tooltip"><i class="fa fa-external-link" aria-hidden="true"></i></a>
				';
	}
	$__finalCompiled .= '
				';
	if ($__vars['xf']['options']['siropuShoutboxSound']) {
		$__finalCompiled .= '
					<a role="button" title="' . 'Toggle sound' . '" data-xf-click="siropu-shoutbox-toggle-sound" data-xf-init="tooltip"><i class="fa fa-volume-' . ($__vars['shoutbox']['sound'] ? 'up' : 'off') . '" aria-hidden="true"></i></a>
				';
	}
	$__finalCompiled .= '
				<a role="button" title="' . 'Toggle direction' . '" data-xf-click="siropu-shoutbox-toggle-direction" data-xf-init="tooltip"><i class="fa fa-arrow-' . ($__vars['shoutbox']['reverse'] ? 'up' : 'down') . '" aria-hidden="true"></i></a>
				<a role="button" title="' . 'Toggle visibility' . '" data-xf-click="siropu-shoutbox-toggle-visibility" data-xf-init="tooltip"><i class="fa fa-' . ($__vars['shoutbox']['collapsed'] ? 'plus' : 'minus') . '" aria-hidden="true"></i></a>
			</span>
		</div>
		<div class="block-body"' . ($__vars['shoutbox']['collapsed'] ? ' style="display: none;"' : '') . '>
			';
	if ($__vars['xf']['options']['siropuShoutboxHeader']) {
		$__finalCompiled .= '
				<div class="siropuShoutboxHeader">
					' . $__templater->filter($__vars['xf']['options']['siropuShoutboxHeader'], array(array('raw', array()),), true) . '
				</div>
			';
	}
	$__finalCompiled .= '
			';
	if ($__vars['shoutbox']['reverse'] == false) {
		$__finalCompiled .= '
				' . $__templater->callMacro('siropu_shoutbox_form', 'submit', array(), $__vars) . '
			';
	}
	$__finalCompiled .= '
			<ol class="siropuShoutboxShouts"';
	if ($__vars['shoutbox']['height']) {
		$__finalCompiled .= ' style="height: ' . $__templater->escape($__vars['shoutbox']['height']) . 'px;"';
	}
	$__finalCompiled .= '>
				';
	if (!$__templater->test($__vars['shoutbox']['shouts'], 'empty', array())) {
		$__finalCompiled .= '
					' . $__templater->includeTemplate('siropu_shoutbox_shout_list', $__vars) . '
				';
	} else {
		$__finalCompiled .= '
					<li>' . 'No shouts have been posted yet.' . '</li>
				';
	}
	$__finalCompiled .= '
			</ol>
			';
	if ($__vars['shoutbox']['reverse'] == true) {
		$__finalCompiled .= '
				' . $__templater->callMacro('siropu_shoutbox_form', 'submit', array(
			'class' => 'siropuShoutboxReverse',
		), $__vars) . '
			';
	}
	$__finalCompiled .= '
			';
	if ($__vars['xf']['options']['siropuShoutboxFooter']) {
		$__finalCompiled .= '
				<div class="siropuShoutboxFooter">
					' . $__templater->filter($__vars['xf']['options']['siropuShoutboxFooter'], array(array('raw', array()),), true) . '
				</div>
			';
	}
	$__finalCompiled .= '
		</div>
	</div>
</div>';
	return $__finalCompiled;
});