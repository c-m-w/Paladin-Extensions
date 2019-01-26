<?php
// FROM HASH: 6e2060d2c4d96284a215da68a3a714d8
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->escape($__vars['trending']['title']));
	$__finalCompiled .= '

';
	$__templater->wrapTemplate('forum_overview_wrapper', $__vars);
	$__finalCompiled .= '

';
	$__templater->setPageParam('uix_mainTabSets', 'forum');
	$__finalCompiled .= '
';
	$__templater->setPageParam('uix_mainTabActive', 'trending');
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__templater->method($__vars['xf']['visitor'], 'canCreateThread', array())) {
		$__compilerTemp1 .= '
		' . $__templater->button('
			' . 'Post thread' . $__vars['xf']['language']['ellipsis'] . '
		', array(
			'href' => $__templater->fn('link', array('forums/create-thread', ), false),
			'class' => 'button--cta',
			'icon' => 'write',
			'overlay' => 'true',
		), '', array(
		)) . '
	';
	}
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__compilerTemp1 . '
');
	$__finalCompiled .= '

';
	if ($__templater->fn('count', array($__vars['trendingConfigs'], ), false) > 1) {
		$__finalCompiled .= '
<div class="tabs tabs--standalone">
	<div class="hScroller" data-xf-init="h-scroller">
		<span class="hScroller--scroll">
			';
		if ($__templater->isTraversable($__vars['trendingConfigs'])) {
			foreach ($__vars['trendingConfigs'] AS $__vars['item']) {
				$__finalCompiled .= '
				<a href="' . $__templater->fn('link', array('trending', $__vars['item'], ), true) . '" class="tabs-tab ' . (($__vars['trending']['trending_id'] == $__vars['item']['trending_id']) ? 'is-active' : '') . '">' . $__templater->escape($__vars['item']['title']) . '</a>
			';
			}
		}
		$__finalCompiled .= '
		</span>
	</div>
</div>
';
	}
	$__finalCompiled .= '

' . $__templater->filter($__templater->method($__vars['trending'], 'renderTrendingContent', array()), array(array('raw', array()),), true) . '

';
	$__templater->modifySidebarHtml('_xfWidgetPositionSidebarThtrendingsidebar', $__templater->widgetPosition('thtrendingsidebar', array()), 'replace');
	$__finalCompiled .= '
';
	if ($__vars['xf']['options']['forumsDefaultPage'] === 'thtrending_trending_list') {
		$__finalCompiled .= '
	';
		$__templater->modifySidebarHtml('_xfWidgetPositionSidebarThuixIndexPage', $__templater->widgetPosition('thuix_index_page', array()), 'replace');
		$__finalCompiled .= '
';
	}
	return $__finalCompiled;
});