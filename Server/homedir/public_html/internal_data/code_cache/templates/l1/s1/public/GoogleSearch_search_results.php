<?php
// FROM HASH: d83fd6a82d7167109434803f8dacafad
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Google search');
	$__finalCompiled .= '

';
	$__templater->includeCss('GoogleSearch_results.less');
	$__finalCompiled .= '

';
	$__templater->breadcrumb($__templater->preEscaped('Search'), $__templater->fn('link', array('google-search', ), false), array(
	));
	$__finalCompiled .= '

';
	$__templater->setPageParam('head.' . 'robots', $__templater->preEscaped('<meta name="robots" content="noindex" />'));
	$__finalCompiled .= '

';
	if ($__vars['failedType']) {
		$__finalCompiled .= '
	';
		if (($__vars['failedType'] == 'no_results')) {
			$__finalCompiled .= '
		<div class="blockMessage blockMessage--iconic blockMessage--GoogleSearchFrown">
			<b>' . 'No results found!' . '</b><br>
			' . 'We have also tried Google search. You can see the results below this block.' . '
		</div>
	';
		} else {
			$__finalCompiled .= '
		<div class="blockMessage blockMessage--iconic blockMessage--GoogleSearchFrown">
			<b>' . '<b>Our forum failed to perform a search!</b>' . '</b><br>
			' . $__templater->escape($__vars['explain']) . '
		</div>
	';
		}
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

<div class="block">
	<div class="block-container google-search-block">
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
	</div>
</div>';
	return $__finalCompiled;
});