<?php
// FROM HASH: c2164e61bbe814fafae8b7bb56f461e4
return array('macros' => array('featured_carousel' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'featuredResources' => '!',
		'viewAllLink' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if (!$__templater->test($__vars['featuredResources'], 'empty', array())) {
		$__finalCompiled .= '
		';
		$__templater->includeCss('carousel.less');
		$__finalCompiled .= '
		';
		$__templater->includeCss('lightslider.less');
		$__finalCompiled .= '

		';
		$__templater->includeJs(array(
			'prod' => 'xf/carousel-compiled.js',
			'dev' => 'vendor/lightslider/lightslider.min.js, xf/carousel.js',
		));
		$__finalCompiled .= '

		<div class="carousel carousel--withFooter">
			<ul class="carousel-body carousel-body--show2" data-xf-init="carousel">
				';
		if ($__templater->isTraversable($__vars['featuredResources'])) {
			foreach ($__vars['featuredResources'] AS $__vars['resource']) {
				$__finalCompiled .= '
					<li>
						<div class="carousel-item">
							<div class="contentRow">
								<div class="contentRow-figure">
									';
				if ($__vars['xf']['options']['xfrmAllowIcons']) {
					$__finalCompiled .= '
										' . $__templater->fn('resource_icon', array($__vars['resource'], 'm', $__templater->fn('link', array('resources', $__vars['resource'], ), false), ), true) . '
									';
				} else {
					$__finalCompiled .= '
										' . $__templater->fn('avatar', array($__vars['resource']['User'], 'm', false, array(
						'notooltip' => 'true',
					))) . '
									';
				}
				$__finalCompiled .= '
								</div>
								<div class="contentRow-main">
									<h4 class="contentRow-title"><a href="' . $__templater->fn('link', array('resources', $__vars['resource'], ), true) . '">' . $__templater->fn('prefix', array('resource', $__vars['resource'], ), true) . $__templater->escape($__vars['resource']['title']) . '</a></h4>
									<div class="contentRow-lesser">' . $__templater->escape($__vars['resource']['tag_line']) . '</div>
									<div class="contentRow-minor contentRow-minor--smaller">
										<ul class="listInline listInline--bullet">
											<li>' . ($__templater->escape($__vars['resource']['User']['username']) ?: $__templater->escape($__vars['resource']['username'])) . '</li>
											' . '
											<li>' . 'Updated' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->fn('date_dynamic', array($__vars['resource']['last_update'], array(
				))) . '</li>
										</ul>
									</div>
								</div>
							</div>
						</div>
					</li>
				';
			}
		}
		$__finalCompiled .= '
			</ul>
			<div class="carousel-footer">
				<a href="' . $__templater->escape($__vars['viewAllLink']) . '">' . 'View all featured resources' . '</a>
			</div>
		</div>
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'list_filter_bar' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'filters' => '!',
		'baseLinkPath' => '!',
		'category' => null,
		'creatorFilter' => null,
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__vars['sortOrders'] = array('last_update' => 'Last update', 'resource_date' => 'Submission date', 'rating_weighted' => 'Rating', 'download_count' => 'Downloads', 'title' => 'Title', );
	$__finalCompiled .= '

	<div class="block-filterBar">
		<div class="filterBar">
			';
	$__compilerTemp1 = '';
	$__compilerTemp1 .= '
						';
	if ($__vars['filters']['type']) {
		$__compilerTemp1 .= '
							<li><a href="' . $__templater->fn('link', array($__vars['baseLinkPath'], $__vars['category'], $__templater->filter($__vars['filters'], array(array('replace', array('type', null, )),), false), ), true) . '"
								class="filterBar-filterToggle" data-xf-init="tooltip" title="' . $__templater->filter('Remove this filter', array(array('for_attr', array()),), true) . '">
								<span class="filterBar-filterToggle-label">' . 'Price' . $__vars['xf']['language']['label_separator'] . '</span>
								';
		if ($__vars['filters']['type'] == 'free') {
			$__compilerTemp1 .= 'Free';
		} else {
			$__compilerTemp1 .= 'Paid';
		}
		$__compilerTemp1 .= '</a></li>
						';
	}
	$__compilerTemp1 .= '
						';
	if ($__vars['filters']['prefix_id']) {
		$__compilerTemp1 .= '
							<li><a href="' . $__templater->fn('link', array($__vars['baseLinkPath'], $__vars['category'], $__templater->filter($__vars['filters'], array(array('replace', array('prefix_id', null, )),), false), ), true) . '"
								class="filterBar-filterToggle" data-xf-init="tooltip" title="' . $__templater->filter('Remove this filter', array(array('for_attr', array()),), true) . '">
								<span class="filterBar-filterToggle-label">' . 'Prefix' . $__vars['xf']['language']['label_separator'] . '</span>
								' . $__templater->fn('prefix_title', array('resource', $__vars['filters']['prefix_id'], ), true) . '</a></li>
						';
	}
	$__compilerTemp1 .= '
						';
	if ($__vars['filters']['creator_id'] AND $__vars['creatorFilter']) {
		$__compilerTemp1 .= '
							<li><a href="' . $__templater->fn('link', array($__vars['baseLinkPath'], $__vars['category'], $__templater->filter($__vars['filters'], array(array('replace', array('creator_id', null, )),), false), ), true) . '"
								class="filterBar-filterToggle" data-xf-init="tooltip" title="' . $__templater->filter('Remove this filter', array(array('for_attr', array()),), true) . '">
								<span class="filterBar-filterToggle-label">' . 'Creator' . $__vars['xf']['language']['label_separator'] . '</span>
								' . $__templater->escape($__vars['creatorFilter']['username']) . '</a></li>
						';
	}
	$__compilerTemp1 .= '
						';
	if ($__vars['filters']['order'] AND $__vars['sortOrders'][$__vars['filters']['order']]) {
		$__compilerTemp1 .= '
							<li><a href="' . $__templater->fn('link', array($__vars['baseLinkPath'], $__vars['category'], $__templater->filter($__vars['filters'], array(array('replace', array(array('order' => null, 'direction' => null, ), )),), false), ), true) . '"
								class="filterBar-filterToggle" data-xf-init="tooltip" title="' . $__templater->filter('Return to the default order', array(array('for_attr', array()),), true) . '">
								<span class="filterBar-filterToggle-label">' . 'Sort by' . $__vars['xf']['language']['label_separator'] . '</span>
								' . $__templater->escape($__vars['sortOrders'][$__vars['filters']['order']]) . '
								<i class="fa ' . (($__vars['filters']['direction'] == 'asc') ? 'fa-angle-up' : 'fa-angle-down') . '" aria-hidden="true"></i>
								<span class="u-srOnly">';
		if ($__vars['filters']['direction'] == 'asc') {
			$__compilerTemp1 .= 'Ascending';
		} else {
			$__compilerTemp1 .= 'Descending';
		}
		$__compilerTemp1 .= '</span>
							</a></li>
						';
	}
	$__compilerTemp1 .= '
					';
	if (strlen(trim($__compilerTemp1)) > 0) {
		$__finalCompiled .= '
				<ul class="filterBar-filters">
					' . $__compilerTemp1 . '
				</ul>
			';
	}
	$__finalCompiled .= '

			<a class="filterBar-menuTrigger" data-xf-click="menu" role="button" tabindex="0" aria-expanded="false" aria-haspopup="true">' . 'Filters' . '</a>
			<div class="menu menu--wide" data-menu="menu" aria-hidden="true"
				data-href="' . $__templater->fn('link', array($__vars['baseLinkPath'] . '/filters', $__vars['category'], $__vars['filters'], ), true) . '"
				data-load-target=".js-filterMenuBody">
				<div class="menu-content">
					<h4 class="menu-header">' . 'Show only' . $__vars['xf']['language']['label_separator'] . '</h4>
					<div class="js-filterMenuBody">
						<div class="menu-row">' . 'Loading' . $__vars['xf']['language']['ellipsis'] . '</div>
					</div>
				</div>
			</div>
		</div>
	</div>
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '

';
	return $__finalCompiled;
});