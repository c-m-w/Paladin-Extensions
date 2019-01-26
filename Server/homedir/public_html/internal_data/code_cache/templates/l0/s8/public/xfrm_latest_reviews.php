<?php
// FROM HASH: 967c23bd8ffa234a755f23038543d2d2
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Latest reviews');
	$__templater->pageParams['pageNumber'] = $__vars['page'];
	$__finalCompiled .= '

<div class="block">
	<div class="block-outer">' . trim('

		' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => $__vars['total'],
		'link' => 'resources/latest-reviews',
		'wrapperclass' => 'block-outer-main',
		'perPage' => $__vars['perPage'],
	))) . '

	') . '</div>

	<div class="block-container">
		<div class="block-body">
			';
	if (!$__templater->test($__vars['reviews'], 'empty', array())) {
		$__finalCompiled .= '
				<div class="structItemContainer">
					';
		if ($__templater->isTraversable($__vars['reviews'])) {
			foreach ($__vars['reviews'] AS $__vars['review']) {
				$__finalCompiled .= '
						' . $__templater->callMacro('xfrm_resource_review_macros', 'review', array(
					'review' => $__vars['review'],
					'resource' => $__vars['review']['Resource'],
					'showResource' => true,
				), $__vars) . '
					';
			}
		}
		$__finalCompiled .= '
				</div>
			';
	} else {
		$__finalCompiled .= '
				<div class="block-row">' . 'No reviews have been left recently.' . '</div>
			';
	}
	$__finalCompiled .= '
		</div>
	</div>

	<div class="block-outer block-outer--after">
		' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => $__vars['total'],
		'link' => 'resources/latest-reviews',
		'wrapperclass' => 'block-outer-main',
		'perPage' => $__vars['perPage'],
	))) . '

		' . $__templater->fn('show_ignored', array(array(
		'wrapperclass' => 'block-outer-opposite',
	))) . '
	</div>
</div>';
	return $__finalCompiled;
});