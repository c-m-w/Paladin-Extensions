<?php
// FROM HASH: 8766aac55d3f714f253d8d5d8d4c9558
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('GoogleSearch_results.less');
	$__finalCompiled .= '

';
	$__templater->includeJs(array(
		'prod' => 'GoogleSearch/search_results_tabs.min.js',
		'dev' => 'GoogleSearch/search_results_tabs.js',
		'addon' => 'GoogleSearch',
	));
	$__finalCompiled .= '

<h2 class="block-tabHeader block-tabHeader--searchResultsTabs tabs hScroller" data-xf-init="h-scroller results-tabs">
	<span class="hScroller-scroll">
		<span class="tabs-tab is-active" id="forum-search-results">
			' . 'Forum search' . '
		</span>

		<span class="tabs-tab" id="google-search-results">
			' . 'Google search' . '
		</span>
	</span>
</h2>

<div class="block-body google-search-results" style="display: none;">
	';
	$__templater->inlineJs('
		(function() {
		var cx = "' . $__vars['xf']['options']['GoogleSearch_id'] . '";
		var gcse = document.createElement(\'script\');
		gcse.type = \'text/javascript\';
		gcse.async = true;
		gcse.src = \'https://cse.google.com/cse.js?cx=\' + cx;
		var s = document.getElementsByTagName(\'script\')[0];
		s.parentNode.insertBefore(gcse, s);
		})();
	');
	$__finalCompiled .= '
	<gcse:search></gcse:search>
	<gcse:searchresults></gcse:searchresults>
</div>';
	return $__finalCompiled;
});