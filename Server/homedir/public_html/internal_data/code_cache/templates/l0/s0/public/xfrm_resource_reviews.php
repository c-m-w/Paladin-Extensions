<?php
// FROM HASH: 48a0f7832d80aba2a59ef873b14fc8a0
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->fn('prefix', array('resource', $__vars['resource'], 'escaped', ), true) . $__templater->escape($__vars['resource']['title']) . ' - ' . 'Reviews');
	$__templater->pageParams['pageNumber'] = $__vars['page'];
	$__finalCompiled .= '

';
	$__compilerTemp1 = $__vars;
	$__compilerTemp1['pageSelected'] = 'reviews';
	$__templater->wrapTemplate('xfrm_resource_wrapper', $__compilerTemp1);
	$__finalCompiled .= '

<div class="block">
	';
	$__compilerTemp2 = '';
	$__compilerTemp2 .= '
				' . $__templater->callMacro('xfrm_resource_wrapper_macros', 'action_buttons', array(
		'resource' => $__vars['resource'],
	), $__vars) . '
			';
	if (strlen(trim($__compilerTemp2)) > 0) {
		$__finalCompiled .= '
		<div class="block-outer">
			<div class="block-outer-opposite">
			' . $__compilerTemp2 . '
			</div>
		</div>
	';
	}
	$__finalCompiled .= '

	<div class="block-container">
		<div class="block-body">
		';
	if ($__templater->isTraversable($__vars['reviews'])) {
		foreach ($__vars['reviews'] AS $__vars['review']) {
			$__finalCompiled .= '
			' . $__templater->callMacro('xfrm_resource_review_macros', 'review', array(
				'review' => $__vars['review'],
				'resource' => $__vars['resource'],
			), $__vars) . '
		';
		}
	}
	$__finalCompiled .= '
		</div>
	</div>
	';
	$__compilerTemp3 = '';
	$__compilerTemp3 .= '
				' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => $__vars['total'],
		'link' => 'resources/reviews',
		'data' => $__vars['resource'],
		'wrapperclass' => 'block-outer-main',
		'perPage' => $__vars['perPage'],
	))) . '
			';
	if (strlen(trim($__compilerTemp3)) > 0) {
		$__finalCompiled .= '
		<div class="block-outer block-outer--after">
			' . $__compilerTemp3 . '
		</div>
	';
	}
	$__finalCompiled .= '
</div>';
	return $__finalCompiled;
});