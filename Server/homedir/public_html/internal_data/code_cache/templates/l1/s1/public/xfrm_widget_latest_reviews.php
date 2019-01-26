<?php
// FROM HASH: a9880b24dbbc186d8e6e69f3bff9bdf7
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if (!$__templater->test($__vars['reviews'], 'empty', array())) {
		$__finalCompiled .= '
	<div class="block"' . $__templater->fn('widget_data', array($__vars['widget'], ), true) . '>
		<div class="block-container">
			<h3 class="block-minorHeader">
				<a href="' . $__templater->fn('link', array('resources/latest-reviews', ), true) . '" rel="nofollow">' . ($__templater->escape($__vars['title']) ?: 'Latest reviews') . '</a>
			</h3>
			<ul class="block-body">
				';
		if ($__templater->isTraversable($__vars['reviews'])) {
			foreach ($__vars['reviews'] AS $__vars['review']) {
				$__finalCompiled .= '
					<li class="block-row">
						' . $__templater->callMacro('xfrm_resource_review_macros', 'review_simple', array(
					'review' => $__vars['review'],
				), $__vars) . '
					</li>
				';
			}
		}
		$__finalCompiled .= '
			</ul>
		</div>
	</div>
';
	}
	return $__finalCompiled;
});