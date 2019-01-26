<?php
// FROM HASH: 78a25c4ae2d797da13476ae7c267e45e
return array('macros' => array('uix_search__component' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'content' => '!',
		'location' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if (($__templater->fn('property', array('uix_searchPosition', ), false) == $__vars['location']) OR ($__templater->fn('property', array('uix_logoBlockSearch', ), false) AND (($__vars['location'] == 'header') AND $__templater->fn('property', array('uix_enableLogoBlock', ), false)))) {
		$__finalCompiled .= '
		' . $__templater->escape($__vars['content']) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'uix_whatsNew__component' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'content' => '!',
		'location' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__templater->fn('property', array('uix_userTabsPosition', ), false) == $__vars['location']) {
		$__finalCompiled .= '
		' . $__templater->escape($__vars['content']) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'uix_loginTabs__component' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'content' => '!',
		'location' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__templater->fn('property', array('uix_loginTriggerPosition', ), false) == $__vars['location']) {
		$__finalCompiled .= '
		';
		if ($__vars['location'] == 'tablinks') {
			$__finalCompiled .= '
			';
			$__vars['uix_sectionLinksAlways'] = '1';
			$__finalCompiled .= '
		';
		}
		$__finalCompiled .= '
		' . $__templater->escape($__vars['content']) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'uix_userTabs__component' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'content' => '!',
		'location' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__templater->fn('property', array('uix_userTabsPosition', ), false) == $__vars['location']) {
		$__finalCompiled .= '
		';
		if ($__vars['location'] == 'tablinks') {
			$__finalCompiled .= '
			';
			$__vars['uix_sectionLinksAlways'] = '1';
			$__finalCompiled .= '
		';
		}
		$__finalCompiled .= '
		' . $__templater->escape($__vars['content']) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'uix_socialMedia__component' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'content' => '',
		'location' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if (($__templater->fn('property', array('uix_socialMediaPosition', ), false) == $__vars['location']) OR ($__templater->fn('property', array('uix_socialMediaLogoBlock', ), false) AND (($__vars['location'] == 'header') AND $__templater->fn('property', array('uix_enableLogoBlock', ), false)))) {
		$__finalCompiled .= '
		' . $__templater->escape($__vars['content']) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'uix_visitorTabs__component' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'socialMediaContent' => '',
		'searchContent' => '!',
		'location' => '!',
		'whatsNewContent' => '!',
		'visitorContent' => '!',
		'loginTabsContent' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__compilerTemp1 = '';
	$__compilerTemp1 .= '
			';
	$__compilerTemp2 = '';
	$__compilerTemp2 .= '
						';
	if ($__vars['xf']['visitor']['user_id']) {
		$__compilerTemp2 .= '
							' . $__templater->callMacro(null, 'uix_userTabs__component', array(
			'content' => $__vars['visitorContent'],
			'location' => $__vars['location'],
		), $__vars) . '
							';
	} else {
		$__compilerTemp2 .= '
							' . $__templater->callMacro(null, 'uix_loginTabs__component', array(
			'content' => $__vars['loginTabsContent'],
			'location' => $__vars['location'],
		), $__vars) . '
						';
	}
	$__compilerTemp2 .= '
					';
	if (strlen(trim($__compilerTemp2)) > 0) {
		$__compilerTemp1 .= '
				<div class="p-navgroup p-account ' . ($__vars['xf']['visitor']['user_id'] ? 'p-navgroup--member' : 'p-navgroup--guest') . '">
					' . $__compilerTemp2 . '
				</div>
			';
	}
	$__compilerTemp1 .= '
			';
	$__compilerTemp3 = '';
	$__compilerTemp3 .= '
						' . $__templater->callMacro(null, 'uix_whatsNew__component', array(
		'content' => $__vars['whatsNewContent'],
		'location' => $__vars['location'],
	), $__vars) . '
						' . $__templater->callMacro(null, 'uix_search__component', array(
		'content' => $__vars['searchContent'],
		'location' => $__vars['location'],
	), $__vars) . '
					';
	if (strlen(trim($__compilerTemp3)) > 0) {
		$__compilerTemp1 .= '
				<div class="p-navgroup p-discovery">
					' . $__compilerTemp3 . '
				</div>
			';
	}
	$__compilerTemp1 .= '
			' . $__templater->callMacro(null, 'uix_socialMedia__component', array(
		'content' => $__vars['socialMediaContent'],
		'location' => $__vars['location'],
	), $__vars) . '
		';
	if (strlen(trim($__compilerTemp1)) > 0) {
		$__finalCompiled .= '
		' . $__compilerTemp1 . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'uix_titlebar__component' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'location' => '!',
		'content' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__templater->fn('property', array('uix_titlebarLocation', ), false) === $__vars['location']) {
		$__finalCompiled .= '
		' . $__templater->escape($__vars['content']) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'uix_sidebar__component' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'location' => '!',
		'content' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__templater->fn('property', array('uix_sidebarLocation', ), false) === $__vars['location']) {
		$__finalCompiled .= '
		' . $__templater->escape($__vars['content']) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'uix_topBreadcrumb__component' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'location' => '',
		'content' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__templater->fn('property', array('uix_topBreadcrumbLocation', ), false) === $__vars['location']) {
		$__finalCompiled .= '
		' . $__templater->escape($__vars['content']) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'uix_bottomBreadcrumb__component' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'content' => '!',
		'location' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__templater->fn('property', array('uix_bottomBreadcrumbLocation', ), false) == $__vars['location']) {
		$__finalCompiled .= '
		' . $__templater->escape($__vars['content']) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'uix_logo__component' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'content' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	' . $__templater->escape($__vars['content']) . '
';
	return $__finalCompiled;
},
'uix_staffbar__component' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'content' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	' . $__templater->escape($__vars['content']) . '
';
	return $__finalCompiled;
},
'uix_sidebarNav__component' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'content' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	' . $__templater->escape($__vars['content']) . '
';
	return $__finalCompiled;
},
'uix_canvasTab' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'icon' => '!',
		'location' => '!',
		'canvas' => '!',
		'type' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__vars['location'] == $__vars['canvas']) {
		$__finalCompiled .= '
		<div class="uix_canvasTab uix_canvasTab__' . $__templater->escape($__vars['type']) . '" data-target="uix_canvasPanel__' . $__templater->escape($__vars['type']) . '">
			' . $__templater->callMacro('uix_icons.less', 'icon', array(
			'icon' => $__vars['icon'],
		), $__vars) . '
		</div>
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'uix_canvasTabs' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'location' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="uix_canvas__tabs">
		' . $__templater->callMacro(null, 'uix_canvasTab', array(
		'icon' => 'list',
		'type' => 'navigation',
		'location' => $__templater->fn('property', array('uix_canvas_location_navigation', ), false),
		'canvas' => $__vars['location'],
	), $__vars) . '
		' . $__templater->callMacro(null, 'uix_canvasTab', array(
		'icon' => 'grid',
		'type' => 'sidebar',
		'location' => $__templater->fn('property', array('uix_canvas_location_sidebar', ), false),
		'canvas' => $__vars['location'],
	), $__vars) . '
		' . $__templater->callMacro(null, 'uix_canvasTab', array(
		'icon' => 'user',
		'type' => 'account',
		'location' => $__templater->fn('property', array('uix_canvas_location_visitorTabs', ), false),
		'canvas' => $__vars['location'],
	), $__vars) . '
		' . $__templater->callMacro(null, 'uix_canvasTab', array(
		'icon' => 'email',
		'type' => 'conversations',
		'location' => $__templater->fn('property', array('uix_canvas_location_visitorTabs', ), false),
		'canvas' => $__vars['location'],
	), $__vars) . '
		' . $__templater->callMacro(null, 'uix_canvasTab', array(
		'icon' => 'alert',
		'type' => 'alerts',
		'location' => $__templater->fn('property', array('uix_canvas_location_visitorTabs', ), false),
		'canvas' => $__vars['location'],
	), $__vars) . '
		' . $__templater->callMacro(null, 'uix_canvasTab', array(
		'icon' => 'star',
		'type' => 'custom',
		'location' => $__templater->fn('property', array('uix_canvas_location_custom', ), false),
		'canvas' => $__vars['location'],
	), $__vars) . '
	</div>
';
	return $__finalCompiled;
},
'nav_entry' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'sidebarNav' => '',
		'navId' => '!',
		'nav' => '!',
		'selected' => false,
		'shortcut' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="p-navEl u-ripple ' . ($__vars['selected'] ? 'is-selected' : '') . '" ' . ($__vars['nav']['children'] ? 'data-has-children="true"' : '') . '>
		';
	if ($__vars['sidebarNav']) {
		$__finalCompiled .= '
		<div class="p-navEl__inner">
		';
	}
	$__finalCompiled .= '
			';
	if ($__vars['nav']['href']) {
		$__finalCompiled .= '
				' . $__templater->callMacro(null, 'nav_link', array(
			'navId' => $__vars['navId'],
			'nav' => $__vars['nav'],
			'class' => 'p-navEl-link ' . ($__vars['nav']['children'] ? 'p-navEl-link--splitMenu' : ''),
			'shortcut' => ($__vars['nav']['children'] ? false : $__vars['shortcut']),
		), $__vars) . '
				';
		if ($__vars['nav']['children']) {
			$__finalCompiled .= '
					<a data-xf-key="' . $__templater->escape($__vars['shortcut']) . '"
					   data-xf-click="menu"
					   data-menu-pos-ref="< .p-navEl"
					   data-arrow-pos-ref="< .p-navEl"
					   class="p-navEl-splitTrigger"
					   role="button"
					   tabindex="0"
					   aria-label="' . 'Toggle expanded' . '"
					   aria-expanded="false"
					   aria-haspopup="true">
					</a>
				';
		}
		$__finalCompiled .= '
			';
	} else if ($__vars['nav']['children']) {
		$__finalCompiled .= '
				<a data-xf-key="' . $__templater->escape($__vars['shortcut']) . '"
				   class="p-navEl-linkHolder"
				   data-menu-pos-ref="< .p-navEl"
				   data-arrow-pos-ref="< .p-navEl"
				   data-xf-click="menu"
				   role="button"
				   tabindex="0"
				   aria-expanded="false"
				   aria-haspopup="true">
					' . $__templater->callMacro(null, 'nav_link', array(
			'navId' => $__vars['navId'],
			'nav' => $__vars['nav'],
			'class' => 'p-navEl-link p-navEl-link--menuTrigger',
		), $__vars) . '
				</a>
			';
	} else {
		$__finalCompiled .= '
				' . $__templater->callMacro(null, 'nav_link', array(
			'navId' => $__vars['navId'],
			'nav' => $__vars['nav'],
			'class' => 'p-navEl-link',
			'shortcut' => $__vars['shortcut'],
		), $__vars) . '
			';
	}
	$__finalCompiled .= '
			';
	if ($__vars['nav']['children']) {
		$__finalCompiled .= '
				';
		if (!$__vars['sidebarNav']) {
			$__finalCompiled .= '
					<div class="menu menu--structural" data-menu="menu" aria-hidden="true">
						<div class="menu-content">
							<!--<h4 class="menu-header">' . $__templater->escape($__vars['nav']['title']) . '</h4>-->
							';
			if ($__templater->isTraversable($__vars['nav']['children'])) {
				foreach ($__vars['nav']['children'] AS $__vars['childNavId'] => $__vars['child']) {
					$__finalCompiled .= '
								' . $__templater->callMacro(null, 'nav_menu_entry', array(
						'navId' => $__vars['childNavId'],
						'nav' => $__vars['child'],
					), $__vars) . '
							';
				}
			}
			$__finalCompiled .= '
						</div>
					</div>
				';
		}
		$__finalCompiled .= '
			';
	}
	$__finalCompiled .= '
			';
	if ($__vars['sidebarNav'] AND ($__vars['nav']['children'] AND $__templater->fn('property', array('uix_tablinksInSideNav', ), false))) {
		$__finalCompiled .= '
				<a class="uix_sidebarNav--trigger">' . $__templater->callMacro('uix_icons.less', 'icon', array(
			'icon' => 'chevron-down',
		), $__vars) . '</a>
			';
	}
	$__finalCompiled .= '
		';
	if ($__vars['sidebarNav']) {
		$__finalCompiled .= '
		</div>
		';
	}
	$__finalCompiled .= '
		';
	if ($__templater->fn('property', array('uix_tablinksInSideNav', ), false)) {
		$__finalCompiled .= '
			';
		if ($__vars['sidebarNav']) {
			$__finalCompiled .= '
				<div ';
			if ($__vars['nav']['children']) {
				$__finalCompiled .= 'data-menu="false"';
			}
			$__finalCompiled .= ' class="uix_sidebarNav__subNav ';
			if ((!$__templater->fn('property', array('uix_sideNavCollapsed', ), false)) AND $__vars['selected']) {
				$__finalCompiled .= 'subNav--expand';
			}
			$__finalCompiled .= '">
					<div class="uix_sidebarNav__subNavInner">
						';
			if ($__templater->isTraversable($__vars['nav']['children'])) {
				foreach ($__vars['nav']['children'] AS $__vars['childNavId'] => $__vars['child']) {
					$__finalCompiled .= '
							' . $__templater->callMacro(null, 'nav_menu_entry', array(
						'navId' => $__vars['childNavId'],
						'nav' => $__vars['child'],
					), $__vars) . '
						';
				}
			}
			$__finalCompiled .= '
					</div>
				</div>
			';
		}
		$__finalCompiled .= '
		';
	}
	$__finalCompiled .= '
	</div>
';
	return $__finalCompiled;
},
'nav_link' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'navId' => '!',
		'nav' => '!',
		'class' => '',
		'titleHtml' => '',
		'shortcut' => false,
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__vars['tag'] = ($__vars['nav']['href'] ? 'a' : 'span');
	$__finalCompiled .= '
	<' . $__templater->escape($__vars['tag']) . ' ' . ($__vars['nav']['href'] ? (('href="' . $__templater->escape($__vars['nav']['href'])) . '"') : '') . '
		class="' . $__templater->escape($__vars['class']) . ' ' . $__templater->escape($__vars['nav']['attributes']['class']) . '"
		' . $__templater->fn('attributes', array($__vars['nav']['attributes'], array('class', ), ), true) . '
		' . (($__vars['shortcut'] !== false) ? (('data-xf-key="' . $__templater->escape($__vars['shortcut'])) . '"') : '') . '
		data-nav-id="' . $__templater->escape($__vars['navId']) . '">';
	if ($__vars['nav']['icon']) {
		$__finalCompiled .= '<i class="fa ' . $__templater->escape($__vars['nav']['icon']) . '" aria-hidden="true"></i> ';
	}
	$__finalCompiled .= ($__vars['titleHtml'] ? $__templater->filter($__vars['titleHtml'], array(array('raw', array()),), true) : $__templater->escape($__vars['nav']['title']));
	if ($__vars['nav']['counter']) {
		$__finalCompiled .= ' <span class="badge badge--highlighted">' . $__templater->filter($__vars['nav']['counter'], array(array('number', array()),), true) . '</span>';
	}
	$__finalCompiled .= '</' . $__templater->escape($__vars['tag']) . '>
';
	return $__finalCompiled;
},
'nav_menu_entry' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'navId' => '!',
		'nav' => '!',
		'depth' => '0',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	' . $__templater->callMacro(null, 'nav_link', array(
		'navId' => $__vars['navId'],
		'nav' => $__vars['nav'],
		'class' => 'menu-linkRow u-indentDepth' . $__vars['depth'] . ' js-offCanvasCopy',
	), $__vars) . '
	';
	if ($__vars['nav']['children']) {
		$__finalCompiled .= '
		';
		if ($__templater->isTraversable($__vars['nav']['children'])) {
			foreach ($__vars['nav']['children'] AS $__vars['childNavId'] => $__vars['child']) {
				$__finalCompiled .= '
			' . $__templater->callMacro(null, 'nav_menu_entry', array(
					'navId' => $__vars['childNavId'],
					'nav' => $__vars['child'],
					'depth' => ($__vars['depth'] + 1),
				), $__vars) . '
		';
			}
		}
		$__finalCompiled .= '
		';
		if ($__vars['depth'] == 0) {
			$__finalCompiled .= '
			<hr class="menu-separator" />
		';
		}
		$__finalCompiled .= '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'breadcrumbs' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'uix_hideBreadcrumb' => '!',
		'template' => '!',
		'pageAction' => '!',
		'breadcrumbs' => '!',
		'navTree' => '!',
		'selectedNavEntry' => null,
		'variant' => '',
		'sidebar' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__vars['breadcrumbCount'] = $__templater->preEscaped($__templater->filter($__templater->fn('count', array($__vars['breadcrumbs'], ), false), array(array('default', array(0, )),), true));
	$__finalCompiled .= '
    ';
	$__vars['navEntryCount'] = $__templater->preEscaped((($__vars['selectedNavEntry'] == null) ? 0 : 1));
	$__finalCompiled .= '

	';
	if ($__templater->fn('property', array('uix_collapsibleSidebar', ), false) AND ($__vars['sidebar'] AND ($__templater->fn('property', array('uix_sidebarTriggerPosition', ), false) == 'breadcrumb'))) {
		$__finalCompiled .= '
		';
		$__vars['breadcrumbHasAction'] = '1';
		$__finalCompiled .= '
	';
	} else if ($__vars['pageAction'] AND ($__templater->fn('property', array('uix_pageActionBreadcrumb', ), false) AND ((!$__templater->fn('property', array('uix_removePageAction', ), false)) OR ($__vars['template'] != 'forum_list')))) {
		$__finalCompiled .= '
		';
		$__vars['breadcrumbHasAction'] = '1';
		$__finalCompiled .= '
	';
	} else {
		$__finalCompiled .= '
		';
		$__vars['breadcrumbHasAction'] = '0';
		$__finalCompiled .= '
	';
	}
	$__finalCompiled .= '

	';
	if ($__vars['uix_hideBreadcrumb']) {
		$__finalCompiled .= '
		';
		$__vars['showBreadcrumb'] = '0';
		$__finalCompiled .= '
	';
	} else if ($__vars['breadcrumbHasAction']) {
		$__finalCompiled .= '
		';
		$__vars['showBreadcrumb'] = '1';
		$__finalCompiled .= '
	';
	} else if (((($__templater->filter($__vars['navEntryCount'], array(array('escape', array()),), false) + $__templater->filter($__vars['breadcrumbCount'], array(array('escape', array()),), false)) == 1)) AND $__templater->fn('property', array('uix_hideSingleCrumb', ), false)) {
		$__finalCompiled .= '
		';
		$__vars['showBreadcrumb'] = '0';
		$__finalCompiled .= '
	';
	} else {
		$__finalCompiled .= '
		';
		$__vars['showBreadcrumb'] = '1';
		$__finalCompiled .= '
	';
	}
	$__finalCompiled .= '

	';
	if ($__vars['showBreadcrumb']) {
		$__finalCompiled .= '
		<div class="breadcrumb ' . ($__vars['variant'] ? ('p-breadcrumb--' . $__templater->escape($__vars['variant'])) : '') . '">
			<div class="pageContent">
				';
		if ($__templater->fn('property', array('uix_collapsibleSidebar', ), false) AND (($__templater->fn('property', array('uix_sidebarLocation', ), false) == 'left') AND ($__vars['sidebar'] AND ($__templater->fn('property', array('uix_sidebarTriggerPosition', ), false) == 'breadcrumb')))) {
			$__finalCompiled .= '
					<a class="uix_sidebarTrigger button" id="uix_sidebarTrigger">
						<span>Sidebar</span>
						' . $__templater->callMacro('uix_icons.less', 'icon', array(
				'icon' => 'chevron-right',
			), $__vars) . '
					</a>
				';
		}
		$__finalCompiled .= '

				<ul class="p-breadcrumbs ' . ($__vars['variant'] ? ('p-breadcrumbs--' . $__templater->escape($__vars['variant'])) : '') . '"
					itemscope itemtype="https://schema.org/BreadcrumbList">

					';
		$__vars['rootBreadcrumb'] = $__vars['navTree'][$__vars['xf']['options']['rootBreadcrumb']];
		$__finalCompiled .= '
					';
		if ($__vars['rootBreadcrumb'] AND ($__vars['rootBreadcrumb']['href'] != $__vars['xf']['uri'])) {
			$__finalCompiled .= '
						' . $__templater->callMacro(null, 'crumb', array(
				'href' => $__vars['rootBreadcrumb']['href'],
				'value' => $__vars['rootBreadcrumb']['title'],
			), $__vars) . '
					';
		}
		$__finalCompiled .= '

					';
		if ($__vars['selectedNavEntry'] AND ($__vars['selectedNavEntry']['href'] AND (($__vars['selectedNavEntry']['href'] != $__vars['xf']['uri']) AND ($__vars['selectedNavEntry']['href'] != $__vars['rootBreadcrumb']['href'])))) {
			$__finalCompiled .= '
						' . $__templater->callMacro(null, 'crumb', array(
				'href' => $__vars['selectedNavEntry']['href'],
				'value' => $__vars['selectedNavEntry']['title'],
			), $__vars) . '
					';
		}
		$__finalCompiled .= '
					';
		if ($__templater->isTraversable($__vars['breadcrumbs'])) {
			foreach ($__vars['breadcrumbs'] AS $__vars['breadcrumb']) {
				if ($__vars['breadcrumb']['href'] != $__vars['xf']['uri']) {
					$__finalCompiled .= '
						' . $__templater->callMacro(null, 'crumb', array(
						'href' => $__vars['breadcrumb']['href'],
						'value' => $__vars['breadcrumb']['value'],
					), $__vars) . '
					';
				}
			}
		}
		$__finalCompiled .= '
				</ul>

				';
		if ($__templater->fn('property', array('uix_pageActionBreadcrumb', ), false)) {
			$__finalCompiled .= '
					';
			$__compilerTemp1 = '';
			$__compilerTemp1 .= (isset($__templater->pageParams['pageAction']) ? $__templater->pageParams['pageAction'] : '');
			if (strlen(trim($__compilerTemp1)) > 0) {
				$__finalCompiled .= '
						<div class="p-title-pageAction">' . $__compilerTemp1 . '</div>
					';
			}
			$__finalCompiled .= '
				';
		}
		$__finalCompiled .= '

				';
		if ($__templater->fn('property', array('uix_collapsibleSidebar', ), false) AND (($__templater->fn('property', array('uix_sidebarLocation', ), false) == 'right') AND ($__vars['sidebar'] AND ($__templater->fn('property', array('uix_sidebarTriggerPosition', ), false) == 'breadcrumb')))) {
			$__finalCompiled .= '
					<a class="uix_sidebarTrigger button" id="uix_sidebarTrigger">
						<span>Sidebar</span>
						' . $__templater->callMacro('uix_icons.less', 'icon', array(
				'icon' => 'chevron-right',
			), $__vars) . '
					</a>
				';
		}
		$__finalCompiled .= '
			</div>
		</div>
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'crumb' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'href' => '!',
		'value' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<li itemprop="itemListElement" itemscope itemtype="https://schema.org/ListItem">
		<a href="' . $__templater->escape($__vars['href']) . '" itemprop="item">
			';
	if (($__vars['href'] == $__vars['xf']['homePageUrl']) AND $__templater->fn('property', array('uix_homeCrumbIcon', ), false)) {
		$__finalCompiled .= '
				' . $__templater->callMacro('uix_icons.less', 'icon', array(
			'icon' => 'home',
		), $__vars) . '
			';
	} else {
		$__finalCompiled .= '
				<span itemprop="name">' . $__templater->escape($__vars['value']) . '</span>
			';
	}
	$__finalCompiled .= '
		</a>
	</li>
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<!DOCTYPE html>

';
	$__vars['siteName'] = $__vars['xf']['options']['boardTitle'];
	$__finalCompiled .= '
';
	$__vars['h1'] = $__templater->preEscaped($__templater->fn('page_h1', array($__vars['siteName'])));
	$__finalCompiled .= '
';
	$__vars['title'] = $__templater->preEscaped($__templater->fn('page_title', array('%s | %s', $__vars['xf']['options']['boardTitle'], null)));
	$__finalCompiled .= '
';
	$__vars['description'] = $__templater->preEscaped($__templater->fn('page_description'));
	$__finalCompiled .= '

';
	$__vars['uix_htmlClasses'] = $__templater->preEscaped('');
	$__finalCompiled .= '

';
	if ($__templater->fn('property', array('uix_pageWidthToggle', ), false) != 'disabled') {
		$__finalCompiled .= '
	' . '
	';
		$__vars['uix_htmlClasses'] = $__templater->preEscaped($__templater->escape($__vars['uix_htmlClasses']) . ' uix_page--' . $__templater->escape($__vars['uix_pageWidth']));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->fn('property', array('uix_navigationType', ), false) == 'sidebarNav') {
		$__finalCompiled .= '
	' . '
	';
		if (!$__vars['uix_sidebarNavCollapsed']) {
			$__finalCompiled .= '
		';
			$__vars['uix_htmlClasses'] = $__templater->preEscaped($__templater->escape($__vars['uix_htmlClasses']) . ' sidebarNav--active');
			$__finalCompiled .= '
	';
		}
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->fn('property', array('uix_collapsibleSidebar', ), false)) {
		$__finalCompiled .= '
	' . '
	';
		if ($__vars['uix_sidebarCollapsed']) {
			$__finalCompiled .= '
		';
			$__vars['uix_htmlClasses'] = $__templater->preEscaped($__templater->escape($__vars['uix_htmlClasses']) . ' uix_sidebarCollapsed');
			$__finalCompiled .= '
	';
		}
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if (((($__templater->fn('property', array('uix_loginTriggerPosition', ), false) == 'staffBar') OR ($__templater->fn('property', array('uix_userTabsPosition', ), false) == 'staffBar')) OR ((!$__templater->fn('property', array('uix_logoBlockSearch', ), false)) AND ($__templater->fn('property', array('uix_searchPosition', ), false) == 'staffBar'))) OR ((!$__templater->fn('property', array('uix_socialMediaLogoBlock', ), false)) AND ($__templater->fn('property', array('uix_socialMediaPosition', ), false) == 'staffBar'))) {
		$__finalCompiled .= '
	';
		$__vars['uix_responsiveStaffBar'] = 'always';
		$__finalCompiled .= '
';
	} else if ($__templater->fn('property', array('uix_enableLogoBlock', ), false)) {
		$__finalCompiled .= '
    ';
		if (($__templater->fn('property', array('uix_logoBlockSearch', ), false) AND ($__templater->fn('property', array('uix_searchPosition', ), false) == 'staffBar')) OR ($__templater->fn('property', array('uix_socialMediaLogoBlock', ), false) AND ($__templater->fn('property', array('uix_socialMediaPosition', ), false) == 'staffBar'))) {
			$__finalCompiled .= '
		';
			$__vars['uix_responsiveStaffBar'] = 'responsive';
			$__finalCompiled .= '
    ';
		}
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

' . '
';
	$__vars['uix_responsiveSectionLinks_min'] = '0';
	$__finalCompiled .= '
';
	$__vars['uix_responsiveSectionLinks_max'] = '99999';
	$__finalCompiled .= '
';
	$__vars['uix_sectionLinksAlways'] = '0';
	$__finalCompiled .= '

' . '

' . '

';
	if (!$__vars['uix_hideNavigation']) {
		$__finalCompiled .= '
';
		$__compilerTemp1 = '';
		if ($__templater->method($__vars['xf']['visitor'], 'canSearch', array())) {
			$__compilerTemp1 .= '
		<div class="uix_searchBar">
			<div class="uix_searchBarInner">
				<form action="' . $__templater->fn('link', array('search/search', ), true) . '" method="post" class="uix_searchForm" data-xf-init="quick-search">
					<a class="uix_search--close">
						' . $__templater->callMacro('uix_icons.less', 'icon', array(
				'icon' => 'close',
			), $__vars) . '
					</a>
					' . $__templater->formTextBox(array(
				'class' => 'js-uix_syncValue uix_searchInput uix_searchDropdown__trigger',
				'data-uixsync' => 'search',
				'name' => 'keywords',
				'placeholder' => 'Search' . $__vars['xf']['language']['ellipsis'],
				'aria-label' => 'Search',
				'data-menu-autofocus' => 'true',
			)) . '
					<a href="' . $__templater->fn('link', array('search', ), true) . '"
					   class="uix_search--settings u-ripple"
					   data-xf-key="' . '/' . '"
					   aria-label="' . 'Search' . '"
					   aria-expanded="false"
					   aria-haspopup="true"
					   title="' . $__templater->filter('Search', array(array('for_attr', array()),), true) . '">
						' . $__templater->callMacro('uix_icons.less', 'icon', array(
				'icon' => 'settings',
			), $__vars) . '
					</a>
					<span class="';
			if ($__templater->fn('property', array('uix_searchButton', ), false)) {
				$__compilerTemp1 .= 'uix_search--submit';
			}
			$__compilerTemp1 .= ' uix_searchIcon">
						' . $__templater->callMacro('uix_icons.less', 'icon', array(
				'icon' => 'search',
			), $__vars) . '
					</span>
					' . $__templater->fn('csrf_input') . '
				</form>
			</div>

			';
			if ($__templater->fn('property', array('uix_searchIconBehavior', ), false) != 'dropdown') {
				$__compilerTemp1 .= '
				<a class="uix_searchIconTrigger p-navgroup-link p-navgroup-link--iconic p-navgroup-link--search u-ripple"
				   aria-label="' . 'Search' . '"
				   aria-expanded="false"
				   aria-haspopup="true"
				   title="' . 'Search' . '">
					<i aria-hidden="true"></i>
				</a>
			';
			}
			$__compilerTemp1 .= '

			';
			if ($__templater->fn('property', array('uix_searchIconBehavior', ), false) != 'expand') {
				$__compilerTemp1 .= '
				<a href="' . $__templater->fn('link', array('search', ), true) . '"
				   class="p-navgroup-link p-navgroup-link--iconic p-navgroup-link--search u-ripple js-uix_minimalSearch__target"
				   data-xf-click="menu"
				   aria-label="' . 'Search' . '"
				   aria-expanded="false"
				   aria-haspopup="true"
				   title="' . 'Search' . '">
					<i aria-hidden="true"></i>
				</a>
			';
			}
			$__compilerTemp1 .= '

			<div class="menu menu--structural menu--wide" data-menu="menu" aria-hidden="true">
				<form action="' . $__templater->fn('link', array('search/search', ), true) . '" method="post"
					  class="menu-content"
					  data-xf-init="quick-search">
					<h3 class="menu-header">' . 'Search' . '</h3>
					' . '
					<div class="menu-row">
						';
			if ($__vars['searchConstraints']) {
				$__compilerTemp1 .= '
							<div class="inputGroup inputGroup--joined">
								' . $__templater->formTextBox(array(
					'name' => 'keywords',
					'class' => 'js-uix_syncValue',
					'data-uixsync' => 'search',
					'placeholder' => 'Search' . $__vars['xf']['language']['ellipsis'],
					'aria-label' => 'Search',
					'data-menu-autofocus' => 'true',
				)) . '
								';
				$__compilerTemp2 = array(array(
					'value' => '',
					'label' => 'Everywhere',
					'_type' => 'option',
				));
				if ($__templater->isTraversable($__vars['searchConstraints'])) {
					foreach ($__vars['searchConstraints'] AS $__vars['constraintName'] => $__vars['constraint']) {
						$__compilerTemp2[] = array(
							'value' => $__templater->filter($__vars['constraint'], array(array('json', array()),), false),
							'label' => $__templater->escape($__vars['constraintName']),
							'_type' => 'option',
						);
					}
				}
				$__compilerTemp1 .= $__templater->formSelect(array(
					'name' => 'constraints',
					'class' => 'js-quickSearch-constraint',
					'aria-label' => 'Search within',
				), $__compilerTemp2) . '
							</div>
							';
			} else {
				$__compilerTemp1 .= '
							' . $__templater->formTextBox(array(
					'name' => 'keywords',
					'class' => 'js-uix_syncValue',
					'data-uixsync' => 'search',
					'placeholder' => 'Search' . $__vars['xf']['language']['ellipsis'],
					'aria-label' => 'Search',
					'data-menu-autofocus' => 'true',
				)) . '
						';
			}
			$__compilerTemp1 .= '
					</div>

					' . '
					<div class="menu-row">
						' . $__templater->formCheckBox(array(
				'standalone' => 'true',
			), array(array(
				'name' => 'c[title_only]',
				'label' => 'Search titles only',
				'_type' => 'option',
			))) . '
					</div>
					' . '
					<div class="menu-row">
						<div class="inputGroup">
							<span class="inputGroup-text">' . 'By' . $__vars['xf']['language']['label_separator'] . '</span>
							<input class="input" name="c[users]" data-xf-init="auto-complete" placeholder="' . 'Member' . '" />
						</div>
					</div>
					<div class="menu-footer">
						<span class="menu-footer-controls">
							' . $__templater->button('', array(
				'type' => 'submit',
				'class' => 'button--primary',
				'icon' => 'search',
			), '', array(
			)) . '
							' . $__templater->button('Advanced search' . $__vars['xf']['language']['ellipsis'], array(
				'href' => $__templater->fn('link', array('search', ), false),
				'rel' => 'nofollow',
			), '', array(
			)) . '
						</span>
					</div>

					' . $__templater->fn('csrf_input') . '
				</form>
			</div>


			<div class="menu menu--structural menu--wide uix_searchDropdown__menu" aria-hidden="true">
				<form action="' . $__templater->fn('link', array('search/search', ), true) . '" method="post"
					  class="menu-content"
					  data-xf-init="quick-search">
					' . '
					';
			if ($__vars['searchConstraints']) {
				$__compilerTemp1 .= '
						<div class="menu-row">

							<div class="inputGroup inputGroup--joined">
								<input name="keywords"
											class="js-uix_syncValue"
											data-uixsync="search"
											placeholder="' . 'Search' . $__vars['xf']['language']['ellipsis'] . '"
											aria-label="' . 'Search' . '"
											type="hidden" />
								';
				$__compilerTemp3 = array(array(
					'value' => '',
					'label' => 'Everywhere',
					'_type' => 'option',
				));
				if ($__templater->isTraversable($__vars['searchConstraints'])) {
					foreach ($__vars['searchConstraints'] AS $__vars['constraintName'] => $__vars['constraint']) {
						$__compilerTemp3[] = array(
							'value' => $__templater->filter($__vars['constraint'], array(array('json', array()),), false),
							'label' => $__templater->escape($__vars['constraintName']),
							'_type' => 'option',
						);
					}
				}
				$__compilerTemp1 .= $__templater->formSelect(array(
					'name' => 'constraints',
					'class' => 'js-quickSearch-constraint',
					'aria-label' => 'Search within',
				), $__compilerTemp3) . '
							</div>
						</div>
					';
			} else {
				$__compilerTemp1 .= '
						<input name="keywords"
							class="js-uix_syncValue"
							data-uixsync="search"
							placeholder="' . 'Search' . $__vars['xf']['language']['ellipsis'] . '"
							aria-label="' . 'Search' . '"
							type="hidden" />
					';
			}
			$__compilerTemp1 .= '

					' . '
					<div class="menu-row">
						' . $__templater->formCheckBox(array(
				'standalone' => 'true',
			), array(array(
				'name' => 'c[title_only]',
				'label' => 'Search titles only',
				'_type' => 'option',
			))) . '
					</div>
					' . '
					<div class="menu-row">
						<div class="inputGroup">
							<span class="inputGroup-text">' . 'By' . $__vars['xf']['language']['label_separator'] . '</span>
							<input class="input" name="c[users]" data-xf-init="auto-complete" placeholder="' . 'Member' . '" />
						</div>
					</div>
					<div class="menu-footer">
						<span class="menu-footer-controls">
							' . $__templater->button('', array(
				'type' => 'submit',
				'class' => 'button--primary',
				'icon' => 'search',
			), '', array(
			)) . '
							' . $__templater->button('Advanced' . $__vars['xf']['language']['ellipsis'], array(
				'href' => $__templater->fn('link', array('search', ), false),
				'rel' => 'nofollow',
			), '', array(
			)) . '
						</span>
					</div>

					' . $__templater->fn('csrf_input') . '
				</form>
			</div>
		</div>
	';
		}
		$__vars['uix_search__component'] = $__templater->preEscaped('
	' . $__compilerTemp1 . '
');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

' . '

' . '

';
	$__vars['uix_whatsNew__component'] = $__templater->preEscaped('
	<a href="' . $__templater->fn('link', array('whats-new', ), true) . '"
	   class="p-navgroup-link p-navgroup-link--iconic p-navgroup-link--whatsnew"
	   title="' . $__templater->filter('What\'s new', array(array('for_attr', array()),), true) . '">
		<i aria-hidden="true"></i>
		<span class="p-navgroup-linkText">' . 'What\'s new' . '</span>
	</a>
');
	$__finalCompiled .= '

' . '

' . '

';
	$__compilerTemp4 = '';
	if ($__vars['template'] != 'login') {
		$__compilerTemp4 .= '
		';
		if ($__templater->fn('property', array('uix_loginStyle', ), false) == 'dropdown') {
			$__compilerTemp4 .= '
			<a href="' . $__templater->fn('link', array('login', ), true) . '" class="p-navgroup-link p-navgroup-link--textual p-navgroup-link--logIn" data-xf-click="menu">
				<i></i>
				<span class="p-navgroup-linkText">' . 'Log in' . '</span>
			</a>
			<div class="menu menu--structural menu--medium" data-menu="menu" aria-hidden="true" data-href="' . $__templater->fn('link', array('login', ), true) . '"></div>
		';
		} else if ($__templater->fn('property', array('uix_loginStyle', ), false) == 'modal') {
			$__compilerTemp4 .= '
			<a href="' . $__templater->fn('link', array('login', ), true) . '" class="p-navgroup-link u-ripple p-navgroup-link--textual p-navgroup-link--logIn" rel="nofollow" data-xf-click="overlay">
				<i></i>
				<span class="p-navgroup-linkText">' . 'Log in' . '</span>
			</a>
		';
		} else if ($__templater->fn('property', array('uix_loginStyle', ), false) == 'link') {
			$__compilerTemp4 .= '
			<a href="' . $__templater->fn('link', array('login', ), true) . '" class="p-navgroup-link u-ripple p-navgroup-link--textual p-navgroup-link--logIn" rel="nofollow">
				<i></i>
				<span class="p-navgroup-linkText">' . 'Log in' . '</span>
			</a>
		';
		} else if ($__templater->fn('property', array('uix_loginStyle', ), false) == 'slidingPanel') {
			$__compilerTemp4 .= '
			<a href="' . $__templater->fn('link', array('login', ), true) . '" id="uix_loginPanel--trigger" class="p-navgroup-link u-ripple p-navgroup-link--textual p-navgroup-link--logIn" rel="nofollow">
				<i></i>
				<span class="p-navgroup-linkText">' . 'Log in' . '</span>
			</a>
		';
		}
		$__compilerTemp4 .= '
	';
	}
	$__compilerTemp5 = '';
	if ($__vars['template'] != 'register_form') {
		$__compilerTemp5 .= '
		';
		if ($__templater->fn('property', array('uix_loginStyle', ), false) == 'modal') {
			$__compilerTemp5 .= '
			<a href="' . $__templater->fn('link', array('register', ), true) . '" class="p-navgroup-link u-ripple p-navgroup-link--textual p-navgroup-link--register" rel="nofollow" data-xf-click="overlay">
				<i></i>
				<span class="p-navgroup-linkText">' . 'Register' . '</span>
			</a>
		';
		} else {
			$__compilerTemp5 .= '
			<a href="' . $__templater->fn('link', array('register', ), true) . '" class="p-navgroup-link u-ripple p-navgroup-link--textual p-navgroup-link--register" rel="nofollow">
				<i></i>
				<span class="p-navgroup-linkText">' . 'Register' . '</span>
			</a>
		';
		}
		$__compilerTemp5 .= '
	';
	}
	$__vars['uix_loginTabs__component'] = $__templater->preEscaped('
	' . $__compilerTemp4 . '
	' . $__compilerTemp5 . '
');
	$__finalCompiled .= '

' . '

' . '

';
	if (!$__vars['uix_hideNavigation']) {
		$__finalCompiled .= '
';
		$__compilerTemp6 = '';
		if (($__vars['xf']['visitor']['user_state'] == 'rejected') OR ($__vars['xf']['visitor']['user_state'] == 'disabled')) {
			$__compilerTemp6 .= '
		<a href="' . $__templater->fn('link', array('account', ), true) . '"
		   class="p-navgroup-link u-ripple p-navgroup-link--iconic p-navgroup-link--user">
			' . $__templater->fn('avatar', array($__vars['xf']['visitor'], 'xxs', false, array(
				'href' => '',
			))) . '
			<span class="p-navgroup-linkText">' . $__templater->escape($__vars['xf']['visitor']['username']) . '</span>
		</a>

		<a href="' . $__templater->fn('link', array('logout', null, array('t' => $__templater->fn('csrf_token', array(), false), ), ), true) . '" class="p-navgroup-link">
			<span class="p-navgroup-linkText">' . 'Log out' . '</span>
		</a>
		';
		} else {
			$__compilerTemp6 .= '
		<a href="' . $__templater->fn('link', array('account', ), true) . '"
			class="p-navgroup-link u-ripple p-navgroup-link--iconic p-navgroup-link--user"
			data-xf-click="menu"
			data-xf-key="' . 'm' . '"
			data-menu-pos-ref="< .p-navgroup"
			aria-expanded="false"
			aria-haspopup="true">
			' . $__templater->fn('avatar', array($__vars['xf']['visitor'], 'xxs', false, array(
				'href' => '',
			))) . '
			<span class="p-navgroup-linkText">' . $__templater->escape($__vars['xf']['visitor']['username']) . '</span>
		</a>
		<div class="menu menu--structural menu--wide menu--account" data-menu="menu" aria-hidden="true"
			 data-href="' . $__templater->fn('link', array('account/visitor-menu', ), true) . '"
			 data-load-target=".js-visitorMenuBody">
			<div class="menu-content js-visitorMenuBody">
				<div class="menu-row">
					' . 'Loading' . $__vars['xf']['language']['ellipsis'] . '
				</div>
			</div>
		</div>

		<a href="' . $__templater->fn('link', array('conversations', ), true) . '"
		   class="p-navgroup-link u-ripple p-navgroup-link--iconic p-navgroup-link--conversations js-badge--conversations badgeContainer' . ($__vars['xf']['visitor']['conversations_unread'] ? ' badgeContainer--highlighted' : '') . '"
		   data-badge="' . $__templater->filter($__vars['xf']['visitor']['conversations_unread'], array(array('number', array()),), true) . '"
		   data-xf-click="menu"
		   data-xf-key="' . ',' . '"
		   data-menu-pos-ref="< .p-navgroup"
		   aria-expanded="false"
		   aria-haspopup="true">
			<i aria-hidden="true"></i>
			<span class="p-navgroup-linkText">' . 'Inbox' . '</span>
		</a>
		<div class="menu menu--structural menu--medium" data-menu="menu" aria-hidden="true"
			 data-href="' . $__templater->fn('link', array('conversations/popup', ), true) . '"
			 data-nocache="true"
			 data-load-target=".js-convMenuBody">
			<div class="menu-content">
				<h3 class="menu-header">' . 'Conversations' . '</h3>
				<div class="js-convMenuBody">
					<div class="menu-row">' . 'Loading' . $__vars['xf']['language']['ellipsis'] . '</div>
				</div>
				<div class="menu-footer menu-footer--split">
					<span class="menu-footer-main">
						<a href="' . $__templater->fn('link', array('conversations', ), true) . '">' . 'Show all' . $__vars['xf']['language']['ellipsis'] . '</a>
					</span>
					<span class="menu-footer-opposite">
						<a href="' . $__templater->fn('link', array('conversations/add', ), true) . '">' . 'Start a new conversation' . '</a>
					</span>
				</div>
			</div>
		</div>

		<a href="' . $__templater->fn('link', array('account/alerts', ), true) . '"
		   class="p-navgroup-link u-ripple p-navgroup-link--iconic p-navgroup-link--alerts js-badge--alerts badgeContainer' . ($__vars['xf']['visitor']['alerts_unread'] ? ' badgeContainer--highlighted' : '') . '"
		   data-badge="' . $__templater->filter($__vars['xf']['visitor']['alerts_unread'], array(array('number', array()),), true) . '"
		   data-xf-click="menu"
		   data-xf-key="' . '.' . '"
		   data-menu-pos-ref="< .p-navgroup"
		   aria-expanded="false"
		   aria-haspopup="true">
			<i aria-hidden="true"></i>
			<span class="p-navgroup-linkText">' . 'Alerts' . '</span>
		</a>
		<div class="menu menu--structural menu--medium" data-menu="menu" aria-hidden="true"
			 data-href="' . $__templater->fn('link', array('account/alerts-popup', ), true) . '"
			 data-nocache="true"
			 data-load-target=".js-alertsMenuBody">
			<div class="menu-content">
				<h3 class="menu-header">' . 'Alerts' . '</h3>
				<div class="js-alertsMenuBody">
					<div class="menu-row">' . 'Loading' . $__vars['xf']['language']['ellipsis'] . '</div>
				</div>
				<div class="menu-footer menu-footer--split">
					<span class="menu-footer-main">
						<a href="' . $__templater->fn('link', array('account/alerts', ), true) . '">' . 'Show all' . $__vars['xf']['language']['ellipsis'] . '</a>
					</span>
					<span class="menu-footer-opposite">
						<a href="' . $__templater->fn('link', array('account/preferences', ), true) . '">' . 'Preferences' . '</a>
					</span>
				</div>
			</div>
		</div>

' . $__templater->includeTemplate('th_page_container_visitorLink_bookmarks', $__vars) . '
	';
		}
		$__vars['uix_userTabs__component'] = $__templater->preEscaped('
	' . $__compilerTemp6 . '
');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

' . '

';
	$__vars['uix_socialMediaContent'] = $__templater->preEscaped('
	' . $__templater->includeTemplate('uix_socialMedia', $__vars) . '
');
	$__finalCompiled .= '

' . '

' . '

';
	if (!$__vars['uix_hideNavigation']) {
		$__finalCompiled .= '
' . '
';
	}
	$__finalCompiled .= '

' . '

';
	$__compilerTemp7 = '';
	if ((((!$__templater->fn('property', array('uix_removePageTitleForumList', ), false)) OR ((!$__templater->fn('in_array', array($__vars['template'], array('forum_list', 'forum_new_posts', ), ), false)))) AND (!$__vars['uix_hidePageTitle'])) OR ($__vars['pageAction'] AND ((!$__templater->fn('property', array('uix_pageActionBreadcrumb', ), false)) AND ((!$__templater->fn('property', array('uix_removePageAction', ), false)) OR ($__vars['template'] != 'forum_list'))))) {
		$__compilerTemp7 .= '
		';
		$__compilerTemp8 = '';
		$__compilerTemp8 .= '
						';
		$__compilerTemp9 = '';
		$__compilerTemp9 .= '
									';
		$__compilerTemp10 = '';
		$__compilerTemp10 .= '
												';
		if (!$__vars['noH1']) {
			$__compilerTemp10 .= '
													<h1 class="p-title-value">' . $__templater->escape($__vars['h1']) . '</h1>
												';
		}
		$__compilerTemp10 .= '
											';
		if (strlen(trim($__compilerTemp10)) > 0) {
			$__compilerTemp9 .= '
										<div class="p-title ' . ($__vars['noH1'] ? 'p-title--noH1' : '') . '">
											' . $__compilerTemp10 . '
										</div>
									';
		}
		$__compilerTemp9 .= '
									';
		if (!$__templater->test($__vars['description'], 'empty', array())) {
			$__compilerTemp9 .= '
										<div class="p-description">' . $__templater->escape($__vars['description']) . '</div>
									';
		}
		$__compilerTemp9 .= '
								';
		if (!$__templater->test($__vars['headerHtml'], 'empty', array())) {
			$__compilerTemp8 .= '
							<div class="p-body-header">
								' . $__templater->filter($__vars['headerHtml'], array(array('raw', array()),), true) . '
							</div>
						';
		} else if (strlen(trim($__compilerTemp9)) > 0) {
			$__compilerTemp8 .= '
							<div class="p-body-header">
								' . $__compilerTemp9 . '
							</div>
							';
			if ((!$__templater->fn('property', array('uix_pageActionBreadcrumb', ), false)) AND ((!$__templater->fn('property', array('uix_removePageAction', ), false)) OR ($__vars['template'] != 'forum_list'))) {
				$__compilerTemp8 .= '
								';
				$__compilerTemp11 = '';
				$__compilerTemp11 .= (isset($__templater->pageParams['pageAction']) ? $__templater->pageParams['pageAction'] : '');
				if (strlen(trim($__compilerTemp11)) > 0) {
					$__compilerTemp8 .= '
									<div class="p-title-pageAction">' . $__compilerTemp11 . '</div>
								';
				}
				$__compilerTemp8 .= '
							';
			}
			$__compilerTemp8 .= '
						';
		}
		$__compilerTemp8 .= '
					';
		if (strlen(trim($__compilerTemp8)) > 0) {
			$__compilerTemp7 .= '
			<div class="uix_titlebar">
				<div class="pageContent">
					' . $__compilerTemp8 . '
				</div>
			</div>
		';
		}
		$__compilerTemp7 .= '
	';
	}
	$__vars['uix_titlebar__component'] = $__templater->preEscaped('
	' . $__compilerTemp7 . '
');
	$__finalCompiled .= '

' . '

' . '

';
	$__compilerTemp12 = '';
	if ($__vars['sidebar']) {
		$__compilerTemp12 .= '
	<div class="p-body-sidebar">
		<div class="uix_sidebarInner' . ($__templater->fn('property', array('uix_stickySidebar', ), false) ? ' uix_stickyBodyElement' : '') . '">
			' . $__templater->callAdsMacro('container_sidebar_above', array(), $__vars) . '
			';
		if ($__templater->isTraversable($__vars['sidebar'])) {
			foreach ($__vars['sidebar'] AS $__vars['sidebarHtml']) {
				$__compilerTemp12 .= '
				' . $__templater->escape($__vars['sidebarHtml']) . '
			';
			}
		}
		$__compilerTemp12 .= '
			' . $__templater->callAdsMacro('container_sidebar_below', array(), $__vars) . '
		</div>
	</div>
';
	}
	$__vars['uix_sidebar__component'] = $__templater->preEscaped('
' . $__compilerTemp12 . '
');
	$__finalCompiled .= '

' . '


' . '

';
	$__vars['uix_topBreadcrumb__component'] = $__templater->preEscaped('
	' . $__templater->callAdsMacro('container_breadcrumb_top_above', array(), $__vars) . '
	' . $__templater->callMacro(null, 'breadcrumbs', array(
		'sidebar' => $__vars['sidebar'],
		'uix_hideBreadcrumb' => $__vars['uix_hideBreadcrumb'],
		'breadcrumbs' => $__vars['breadcrumbs'],
		'navTree' => $__vars['navTree'],
		'template' => $__vars['template'],
		'pageAction' => $__vars['pageAction'],
		'selectedNavEntry' => $__vars['selectedNavEntry'],
	), $__vars) . '
	' . $__templater->callAdsMacro('container_breadcrumb_top_below', array(), $__vars) . '
');
	$__finalCompiled .= '

' . '

' . '

';
	$__compilerTemp13 = '';
	if (!$__templater->fn('property', array('uix_removeBottomBreadcrumb', ), false)) {
		$__compilerTemp13 .= '
		' . $__templater->callAdsMacro('container_breadcrumb_bottom_above', array(), $__vars) . '
		' . $__templater->callMacro(null, 'breadcrumbs', array(
			'breadcrumbs' => $__vars['breadcrumbs'],
			'navTree' => $__vars['navTree'],
			'template' => $__vars['template'],
			'selectedNavEntry' => $__vars['selectedNavEntry'],
			'uix_hideBreadcrumb' => $__vars['uix_hideBreadcrumb'],
			'pageAction' => $__vars['pageAction'],
			'variant' => 'bottom',
		), $__vars) . '
		' . $__templater->callAdsMacro('container_breadcrumb_bottom_below', array(), $__vars) . '
	';
	}
	$__vars['uix_bottomBreadcrumb__component'] = $__templater->preEscaped('
	' . $__compilerTemp13 . '
');
	$__finalCompiled .= '

' . '

' . '

';
	$__compilerTemp14 = '';
	if ($__templater->fn('property', array('publicLogoUrl', ), false) OR $__templater->fn('property', array('publicLogoUrl2x', ), false)) {
		$__compilerTemp14 .= '
				<img src="' . $__templater->fn('base_url', array($__templater->fn('property', array('publicLogoUrl', ), false), ), true) . '"
					 alt="' . $__templater->escape($__vars['xf']['options']['boardTitle']) . '"
					 ' . ($__templater->fn('property', array('publicLogoUrl2x', ), false) ? (('srcset="' . $__templater->fn('base_url', array($__templater->fn('property', array('publicLogoUrl2x', ), false), ), true)) . ' 2x"') : '') . ' />
			';
	} else {
		$__compilerTemp14 .= '
				<h2 class="uix_logo--text"><i class="' . $__templater->fn('property', array('uix_logoIcon', ), true) . ' uix_logoIcon"></i>' . $__templater->fn('property', array('uix_logoText', ), true) . '</h2>
			';
	}
	$__compilerTemp15 = '';
	if ($__templater->fn('property', array('uix_logoSmall', ), false)) {
		$__compilerTemp15 .= '
			<a class="uix_logoSmall" href="' . (($__vars['xf']['options']['logoLink'] AND $__vars['xf']['homePageUrl']) ? $__templater->escape($__vars['xf']['homePageUrl']) : $__templater->fn('link', array('index', ), true)) . '">
				<img src="' . $__templater->fn('base_url', array($__templater->fn('property', array('uix_logoSmall', ), false), ), true) . '"
					 alt="' . $__templater->escape($__vars['xf']['options']['boardTitle']) . '"
				/>
			</a>
		';
	}
	$__vars['uix_logo__component'] = $__templater->preEscaped('
	<div class="p-header-logo p-header-logo--image">
		<a class="uix_logo" href="' . (($__vars['xf']['options']['logoLink'] AND $__vars['xf']['homePageUrl']) ? $__templater->escape($__vars['xf']['homePageUrl']) : $__templater->fn('link', array('index', ), true)) . '">
			' . $__compilerTemp14 . '
		</a>
		' . $__compilerTemp15 . '
	</div>
');
	$__finalCompiled .= '

' . '

' . '

';
	$__compilerTemp16 = '';
	$__compilerTemp17 = '';
	$__compilerTemp17 .= '
					';
	$__compilerTemp18 = '';
	$__compilerTemp18 .= '
									';
	if ($__vars['xf']['visitor']['is_moderator'] AND $__vars['xf']['session']['unapprovedCounts']['total']) {
		$__compilerTemp18 .= '
										<a href="' . $__templater->fn('link', array('approval-queue', ), true) . '" class="p-staffBar-link badgeContainer badgeContainer--highlighted" data-badge="' . $__templater->filter($__vars['xf']['session']['unapprovedCounts']['total'], array(array('number', array()),), true) . '">
											' . 'Approval queue' . '
										</a>
									';
	}
	$__compilerTemp18 .= '

									';
	if ($__vars['xf']['visitor']['is_moderator'] AND ((!$__vars['xf']['options']['reportIntoForumId']) AND $__vars['xf']['session']['reportCounts']['total'])) {
		$__compilerTemp18 .= '
										<a href="' . $__templater->fn('link', array('reports', ), true) . '"
											class="p-staffBar-link badgeContainer badgeContainer--visible ' . ((($__vars['xf']['session']['reportCounts']['total'] AND ($__vars['xf']['session']['reportCounts']['lastBuilt'] > $__vars['xf']['session']['reportLastRead'])) OR $__vars['xf']['session']['reportCounts']['assigned']) ? ' badgeContainer--highlighted' : '') . '"
											data-badge="' . ($__vars['xf']['session']['reportCounts']['assigned'] ? (($__templater->filter($__vars['xf']['session']['reportCounts']['assigned'], array(array('number', array()),), true) . ' / ') . $__templater->filter($__vars['xf']['session']['reportCounts']['total'], array(array('number', array()),), true)) : $__templater->filter($__vars['xf']['session']['reportCounts']['total'], array(array('number', array()),), true)) . '"
											title="' . ($__vars['xf']['session']['reportCounts']['lastBuilt'] ? (('Last report update' . $__vars['xf']['language']['label_separator'] . ' ') . $__templater->fn('date_time', array($__vars['xf']['session']['reportCounts']['lastBuilt'], ), true)) : '') . '">
											' . 'Reports' . '
										</a>
									';
	}
	$__compilerTemp18 .= '

									';
	$__compilerTemp19 = '';
	$__compilerTemp19 .= '
												' . '
												';
	if ($__vars['xf']['visitor']['is_moderator']) {
		$__compilerTemp19 .= '
													<a href="' . $__templater->fn('link', array('approval-queue', ), true) . '" class="menu-linkRow">' . 'Approval queue' . '</a>
												';
	}
	$__compilerTemp19 .= '
												';
	if ($__vars['xf']['visitor']['is_moderator'] AND (!$__vars['xf']['options']['reportIntoForumId'])) {
		$__compilerTemp19 .= '
													<a href="' . $__templater->fn('link', array('reports', ), true) . '" class="menu-linkRow" title="' . ($__vars['xf']['session']['reportCounts']['lastBuilt'] ? ('Last report update: ' . $__templater->fn('date_time', array($__vars['xf']['session']['reportCounts']['lastBuilt'], ), true)) : '') . '">' . 'Reports' . '</a>
												';
	}
	$__compilerTemp19 .= '
												' . '
												';
	if (strlen(trim($__compilerTemp19)) > 0) {
		$__compilerTemp18 .= '
										<a class="p-staffBar-link menuTrigger" data-xf-key="alt+m" data-xf-click="menu" role="button" tabindex="0" aria-expanded="false" aria-haspopup="true">' . 'Moderator' . '</a>
										<div class="menu" data-menu="menu" aria-hidden="true">
											<div class="menu-content">
												<h4 class="menu-header">' . 'Moderator tools' . '</h4>
												' . $__compilerTemp19 . '
											</div>
										</div>
									';
	}
	$__compilerTemp18 .= '

									';
	if ($__vars['xf']['visitor']['is_admin']) {
		$__compilerTemp18 .= '
										<a href="' . $__templater->fn('base_url', array('admin.php', ), true) . '" class="p-staffBar-link" target="_blank">' . 'Admin' . '</a>
									';
	}
	$__compilerTemp18 .= '

									';
	$__compilerTemp20 = '';
	$__compilerTemp20 .= '
													' . '
													';
	if ($__vars['xf']['visitor']['is_admin']) {
		$__compilerTemp20 .= '
														<a href="' . $__templater->fn('base_url', array('admin.php', ), true) . '" class="menu-linkRow">' . 'Admin' . '</a>
													';
	}
	$__compilerTemp20 .= '
													' . '
													';
	if ($__vars['xf']['visitor']['is_moderator']) {
		$__compilerTemp20 .= '
														<a href="' . $__templater->fn('link', array('approval-queue', ), true) . '" class="menu-linkRow">' . 'Approval queue' . '</a>
													';
	}
	$__compilerTemp20 .= '
													';
	if ($__vars['xf']['visitor']['is_moderator'] AND (!$__vars['xf']['options']['reportIntoForumId'])) {
		$__compilerTemp20 .= '
														<a href="' . $__templater->fn('link', array('reports', ), true) . '" class="menu-linkRow" title="' . ($__vars['xf']['session']['reportCounts']['lastBuilt'] ? ('Last report update: ' . $__templater->fn('date_time', array($__vars['xf']['session']['reportCounts']['lastBuilt'], ), true)) : '') . '">' . 'Reports' . '</a>
													';
	}
	$__compilerTemp20 .= '
													';
	if ($__vars['xf']['visitor']['is_moderator'] AND $__vars['xf']['session']['unapprovedCounts']['total']) {
		$__compilerTemp20 .= '
														<a href="' . $__templater->fn('link', array('approval-queue', ), true) . '" class="menu-linkRow badgeContainer badgeContainer--highlighted" data-badge="' . $__templater->filter($__vars['xf']['session']['unapprovedCounts']['total'], array(array('number', array()),), true) . '">
															' . 'Approval queue' . '
														</a>
													';
	}
	$__compilerTemp20 .= '

													';
	if ($__vars['xf']['visitor']['is_moderator'] AND ((!$__vars['xf']['options']['reportIntoForumId']) AND $__vars['xf']['session']['reportCounts']['total'])) {
		$__compilerTemp20 .= '
														<a href="' . $__templater->fn('link', array('reports', ), true) . '"
															class="menu-linkRow badgeContainer badgeContainer--visible ' . ((($__vars['xf']['session']['reportCounts']['total'] AND ($__vars['xf']['session']['reportCounts']['lastBuilt'] > $__vars['xf']['session']['reportLastRead'])) OR $__vars['xf']['session']['reportCounts']['assigned']) ? ' badgeContainer--highlighted' : '') . '"
															data-badge="' . ($__vars['xf']['session']['reportCounts']['assigned'] ? (($__templater->filter($__vars['xf']['session']['reportCounts']['assigned'], array(array('number', array()),), true) . ' / ') . $__templater->filter($__vars['xf']['session']['reportCounts']['total'], array(array('number', array()),), true)) : $__templater->filter($__vars['xf']['session']['reportCounts']['total'], array(array('number', array()),), true)) . '"
															title="' . ($__vars['xf']['session']['reportCounts']['lastBuilt'] ? ('Last report update' . $__templater->fn('date_time', array($__vars['xf']['session']['reportCounts']['lastBuilt'], ), true)) : '') . '">
															' . 'Reports' . '
														</a>
													';
	}
	$__compilerTemp20 .= '
												';
	if (strlen(trim($__compilerTemp20)) > 0) {
		$__compilerTemp18 .= '
										<a href="' . $__templater->fn('base_url', array('admin.php', ), true) . '" target="_blank" class="p-staffBar-link menuTrigger uix_adminTrigger" data-xf-click="menu" role="button" tabindex="0" aria-expanded="false" aria-haspopup="true">' . 'Admin' . '</a>
										<div class="menu" data-menu="menu" aria-hidden="true">
											<div class="menu-content">
												<h4 class="menu-header">' . 'Moderator tools' . '</h4>
												' . $__compilerTemp20 . '
											</div>
										</div>
									';
	}
	$__compilerTemp18 .= '
								';
	if (strlen(trim($__compilerTemp18)) > 0) {
		$__compilerTemp17 .= '
						';
		$__vars['uix_responsiveStaffBar'] = 'always';
		$__compilerTemp17 .= '
						<div class="p-staffBar-inner hScroller" data-xf-init="h-scroller">
							<div class="hScroller-scroll">
								' . $__compilerTemp18 . '
							</div>
						</div>
					';
	}
	$__compilerTemp17 .= '

					';
	$__compilerTemp21 = '';
	$__compilerTemp21 .= '
								' . $__templater->callMacro(null, 'uix_visitorTabs__component', array(
		'socialMediaContent' => $__vars['uix_socialMediaContent'],
		'whatsNewContent' => $__vars['uix_whatsNew__component'],
		'searchContent' => $__vars['uix_search__component'],
		'loginTabsContent' => $__vars['uix_loginTabs__component'],
		'visitorContent' => $__vars['uix_userTabs__component'],
		'location' => 'staffBar',
	), $__vars) . '
							';
	if (strlen(trim($__compilerTemp21)) > 0) {
		$__compilerTemp17 .= '
						<div class="p-nav-opposite">
							' . $__compilerTemp21 . '
						</div>
					';
	}
	$__compilerTemp17 .= '

				';
	if (strlen(trim($__compilerTemp17)) > 0) {
		$__compilerTemp16 .= '
		<div class="p-staffBar ';
		if ($__templater->fn('property', array('uix_stickyStaffBar', ), false)) {
			$__compilerTemp16 .= 'uix_stickyBar';
		}
		$__compilerTemp16 .= '">
			<div class="pageContent">
				' . $__compilerTemp17 . '
			</div>
		</div>
	';
	}
	$__vars['uix_staffbar__component'] = $__templater->preEscaped('
	' . $__compilerTemp16 . '
');
	$__finalCompiled .= '

';
	if ($__vars['uix_responsiveStaffBar'] == 'always') {
		$__finalCompiled .= '
	';
		$__vars['uix_htmlClasses'] = $__templater->preEscaped($__templater->escape($__vars['uix_htmlClasses']) . ' uix_alwaysStaffBar');
		$__finalCompiled .= '
';
	} else if ($__vars['uix_responsiveStaffBar'] == 'responsive') {
		$__finalCompiled .= '
	';
		$__vars['uix_htmlClasses'] = $__templater->preEscaped($__templater->escape($__vars['uix_htmlClasses']) . ' uix_responsiveStaffBar');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

' . '

' . '

';
	if ($__templater->fn('property', array('uix_collapsibleSidebar', ), false) AND ($__vars['sidebar'] AND ($__templater->fn('property', array('uix_sidebarTriggerPosition', ), false) == 'sectionLinks'))) {
		$__finalCompiled .= '
	';
		$__vars['uix_sectionLinksHasSidebarTrigger'] = '1';
		$__finalCompiled .= '
	';
		if ((0 + $__templater->fn('property', array('uix_sidebarBreakpoint', ), false)) < $__vars['uix_responsiveSectionLinks_max']) {
			$__finalCompiled .= '
		';
			$__vars['uix_responsiveSectionLinks_max'] = (0 + $__templater->fn('property', array('uix_sidebarBreakpoint', ), false));
			$__finalCompiled .= '
	';
		}
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '
';
	if (!$__vars['uix_hideNavigation']) {
		$__finalCompiled .= '
';
		$__compilerTemp22 = '';
		$__compilerTemp23 = '';
		$__compilerTemp23 .= '
					';
		$__compilerTemp24 = '';
		$__compilerTemp24 .= '
								';
		if ($__vars['uix_sectionLinksHasSidebarTrigger'] AND ($__templater->fn('property', array('uix_sidebarLocation', ), false) == 'left')) {
			$__compilerTemp24 .= '
									<a class="uix_sidebarTrigger button" id="uix_sidebarTrigger">
										<span>Sidebar</span>
										' . $__templater->callMacro('uix_icons.less', 'icon', array(
				'icon' => 'chevron-right',
			), $__vars) . '
									</a>
								';
		}
		$__compilerTemp24 .= '
								';
		if (!$__templater->test($__vars['selectedNavChildren'], 'empty', array()) AND (!$__templater->fn('property', array('uix_removeTablinks', ), false))) {
			$__compilerTemp24 .= '
									';
			if ((0 + $__templater->fn('property', array('publicNavCollapseWidth', ), false)) < $__vars['uix_responsiveSectionLinks_max']) {
				$__compilerTemp24 .= '
										';
				$__vars['uix_responsiveSectionLinks_max'] = (0 + $__templater->fn('property', array('publicNavCollapseWidth', ), false));
				$__compilerTemp24 .= '
									';
			}
			$__compilerTemp24 .= '
									<div class="p-sectionLinks-inner hScroller" data-xf-init="h-scroller">
										<div class="hScroller-scroll">
											<ul class="p-sectionLinks-list">
											';
			$__vars['i'] = 0;
			if ($__templater->isTraversable($__vars['selectedNavChildren'])) {
				foreach ($__vars['selectedNavChildren'] AS $__vars['navId'] => $__vars['navEntry']) {
					$__vars['i']++;
					$__compilerTemp24 .= '
												<li>
													' . $__templater->callMacro(null, 'nav_entry', array(
						'navId' => $__vars['navId'],
						'nav' => $__vars['navEntry'],
						'shortcut' => 'alt+' . $__vars['i'],
					), $__vars) . '
												</li>
											';
				}
			}
			$__compilerTemp24 .= '
											</ul>
										</div>
									</div>
								';
		}
		$__compilerTemp24 .= '
							';
		if (strlen(trim($__compilerTemp24)) > 0) {
			$__compilerTemp23 .= '
						<div class="p-sectionLinks--group">
							' . $__compilerTemp24 . '
						</div>
					';
		}
		$__compilerTemp23 .= '
					';
		$__compilerTemp25 = '';
		$__compilerTemp25 .= '
								' . $__templater->callMacro(null, 'uix_visitorTabs__component', array(
			'socialMediaContent' => $__vars['uix_socialMediaContent'],
			'whatsNewContent' => $__vars['uix_whatsNew__component'],
			'searchContent' => $__vars['uix_search__component'],
			'loginTabsContent' => $__vars['uix_loginTabs__component'],
			'visitorContent' => $__vars['uix_userTabs__component'],
			'location' => 'tablinks',
		), $__vars) . '
								';
		if ($__vars['uix_sectionLinksHasSidebarTrigger'] AND ($__templater->fn('property', array('uix_sidebarLocation', ), false) == 'right')) {
			$__compilerTemp25 .= '
									<a class="uix_sidebarTrigger button" id="uix_sidebarTrigger">
										<span>Sidebar</span>
										' . $__templater->callMacro('uix_icons.less', 'icon', array(
				'icon' => 'chevron-right',
			), $__vars) . '
									</a>
								';
		}
		$__compilerTemp25 .= '
							';
		if (strlen(trim($__compilerTemp25)) > 0) {
			$__compilerTemp23 .= '
						<div class="p-nav-opposite">
							' . $__compilerTemp25 . '
						</div>
					';
		}
		$__compilerTemp23 .= '
				';
		if (strlen(trim($__compilerTemp23)) > 0) {
			$__compilerTemp22 .= '
		<div class="p-sectionLinks">
			<div class="pageContent">
				' . $__compilerTemp23 . '
			</div>
		</div>
	';
		} else if ($__vars['selectedNavEntry']) {
			$__compilerTemp22 .= '
		<div class="p-sectionLinks p-sectionLinks--empty"></div>
	';
		}
		$__vars['subNavHtml'] = $__templater->preEscaped('
	' . $__compilerTemp22 . '
');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

' . '

';
	$__compilerTemp26 = '';
	if ($__templater->fn('property', array('uix_stickySidebar', ), false)) {
		$__compilerTemp26 .= ' uix_stickyBodyElement';
	}
	$__compilerTemp27 = '';
	$__vars['i'] = 0;
	if ($__templater->isTraversable($__vars['navTree'])) {
		foreach ($__vars['navTree'] AS $__vars['navSection'] => $__vars['navEntry']) {
			if (($__vars['navSection'] != $__vars['xf']['app']['defaultNavigationId'])) {
				$__vars['i']++;
				$__compilerTemp27 .= '
					<li class="uix_sidebarNavList__listItem">
						' . $__templater->callMacro(null, 'nav_entry', array(
					'sidebarNav' => '1',
					'navId' => $__vars['navSection'],
					'nav' => $__vars['navEntry'],
					'selected' => ($__vars['navSection'] == $__vars['pageSection']),
					'shortcut' => $__vars['i'],
				), $__vars) . '
					</li>
				';
			}
		}
	}
	$__compilerTemp28 = '';
	if ($__vars['xf']['visitor']['user_id']) {
		$__compilerTemp28 .= '
				<ul class="uix_sidebarNavList">
					<li><div class="p-navEl u-ripple"><a data-nav-id="profile" href="' . $__templater->fn('link', array('members', $__vars['xf']['visitor'], ), true) . '" class="p-navEl-link">Profile</a></div></li>
					<li><div class="p-navEl u-ripple"><a data-nav-id="alerts" href="' . $__templater->fn('link', array('account/alerts', ), true) . '" class="p-navEl-link">Alerts</a></div></li>
					<li><div class="p-navEl u-ripple"><a data-nav-id="settings" href="' . $__templater->fn('link', array('account/preferences', ), true) . '" class="p-navEl-link">Settings</a></div></li>
				</ul>
			';
	}
	$__compilerTemp29 = '';
	$__compilerTemp30 = '';
	$__compilerTemp30 .= '
						' . $__templater->filter($__vars['uix_sidebarNavWidgets'], array(array('raw', array()),), true) . '
					';
	if (strlen(trim($__compilerTemp30)) > 0) {
		$__compilerTemp29 .= '
				<div class="uix_sidebarNav__inner__widgets">
					' . $__compilerTemp30 . '
				</div>
			';
	}
	$__vars['uix_sidebarNav__component'] = $__templater->preEscaped('
	<div class="uix_sidebarNav">
		<div class="uix_sidebarNav__inner ' . $__compilerTemp26 . '">
			<ul class="uix_sidebarNavList js-offCanvasNavSource">
				' . $__compilerTemp27 . '
			</ul>
			' . $__compilerTemp28 . '
			' . $__compilerTemp29 . '
		</div>
	</div>
');
	$__finalCompiled .= '

' . '

';
	if ($__templater->fn('property', array('uix_enableLogoBlock', ), false)) {
		$__finalCompiled .= '
	';
		if ($__templater->fn('property', array('uix_socialMediaPosition', ), false) == 'tablinks') {
			$__finalCompiled .= '
		';
			if ($__templater->fn('property', array('uix_socialMediaLogoBlock', ), false)) {
				$__finalCompiled .= '
			';
				if ((0 + $__templater->fn('property', array('uix_viewportShowLogoBlock', ), false)) > $__vars['uix_responsiveSectionLinks_min']) {
					$__finalCompiled .= '
				';
					$__vars['uix_responsiveSectionLinks_min'] = (0 + $__templater->fn('property', array('uix_viewportShowLogoBlock', ), false));
					$__finalCompiled .= '
			';
				}
				$__finalCompiled .= '
		';
			} else {
				$__finalCompiled .= '
			';
				$__vars['uix_sectionLinksAlways'] = '1';
				$__finalCompiled .= '
		';
			}
			$__finalCompiled .= '
	';
		}
		$__finalCompiled .= '

	';
		if ($__templater->fn('property', array('uix_searchPosition', ), false) == 'tablinks') {
			$__finalCompiled .= '
		';
			if ($__templater->fn('property', array('uix_logoBlockSearch', ), false)) {
				$__finalCompiled .= '
			';
				if ((0 + $__templater->fn('property', array('uix_viewportShowLogoBlock', ), false)) > $__vars['uix_responsiveSectionLinks_min']) {
					$__finalCompiled .= '
				';
					$__vars['uix_responsiveSectionLinks_min'] = (0 + $__templater->fn('property', array('uix_viewportShowLogoBlock', ), false));
					$__finalCompiled .= '
			';
				}
				$__finalCompiled .= '
		';
			} else {
				$__finalCompiled .= '
			';
				$__vars['uix_sectionLinksAlways'] = '1';
				$__finalCompiled .= '
		';
			}
			$__finalCompiled .= '
	';
		}
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		if (($__templater->fn('property', array('uix_searchPosition', ), false) == 'tablinks') OR ($__templater->fn('property', array('uix_socialMediaPosition', ), false) == 'tablinks')) {
			$__finalCompiled .= '
		';
			$__vars['uix_sectionLinksAlways'] = '1';
			$__finalCompiled .= '
	';
		}
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	$__vars['uix_stickyTopLogoMin'] = '0';
	$__finalCompiled .= '
';
	$__vars['uix_stickyTopLogoMax'] = '0';
	$__finalCompiled .= '

';
	if ($__templater->fn('property', array('uix_stickyStaffBar', ), false)) {
		$__finalCompiled .= '
	';
		if ($__vars['uix_responsiveStaffBar'] == 'always') {
			$__finalCompiled .= '
		';
			$__vars['uix_stickyTopLogoMin'] = (0 + $__templater->fn('property', array('uix_stickyStaffBarHeight', ), false));
			$__finalCompiled .= '
		';
			$__vars['uix_stickyTopLogoMax'] = (0 + $__templater->fn('property', array('uix_stickyStaffBarHeight', ), false));
			$__finalCompiled .= '
	';
		} else if ($__vars['uix_responsiveStaffBar'] == 'responsive') {
			$__finalCompiled .= '
		';
			$__vars['uix_stickyTopLogoMin'] = (0 + $__templater->fn('property', array('uix_stickyStaffBarHeight', ), false));
			$__finalCompiled .= '
	';
		}
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

' . '

' . '

' . '

' . '


' . '

<html id="XF" lang="' . $__templater->escape($__vars['xf']['language']['language_code']) . '" dir="' . $__templater->escape($__vars['xf']['language']['text_direction']) . '"
	data-app="public"
	data-template="' . $__templater->escape($__vars['template']) . '"
	data-container-key="' . $__templater->escape($__vars['containerKey']) . '"
	data-content-key="' . $__templater->escape($__vars['contentKey']) . '"
	data-logged-in="' . ($__vars['xf']['visitor']['user_id'] ? 'true' : 'false') . '"
	data-cookie-prefix="' . $__templater->escape($__vars['xf']['cookie']['prefix']) . '"
	class="has-no-js' . ($__vars['template'] ? (' template-' . $__templater->escape($__vars['template'])) : '') . ' ' . $__templater->escape($__vars['uix_htmlClasses']) . ' ' . $__templater->escape($__vars['uix_additionalHtmlClasses']) . '"
	' . ($__vars['xf']['runJobs'] ? ' data-run-jobs=""' : '') . '>
<head>
	<meta charset="utf-8" />
	<meta http-equiv="X-UA-Compatible" content="IE=Edge" />
	<meta name="viewport" content="width=device-width, initial-scale=1">

	' . '

	<title>' . $__templater->escape($__vars['title']) . '</title>

	';
	if ($__templater->isTraversable($__vars['head'])) {
		foreach ($__vars['head'] AS $__vars['headTag']) {
			$__finalCompiled .= '
		' . $__templater->escape($__vars['headTag']) . '
	';
		}
	}
	$__finalCompiled .= '

	';
	if ((!$__vars['head']['meta_site_name']) AND !$__templater->test($__vars['siteName'], 'empty', array())) {
		$__finalCompiled .= '
		' . $__templater->callMacro('metadata_macros', 'site_name', array(
			'siteName' => $__vars['siteName'],
			'output' => true,
		), $__vars) . '
	';
	}
	$__finalCompiled .= '
	';
	if (!$__vars['head']['meta_title']) {
		$__finalCompiled .= '
		' . $__templater->callMacro('metadata_macros', 'title', array(
			'title' => ($__templater->fn('page_title', array(), false) ?: $__vars['siteName']),
			'output' => true,
		), $__vars) . '
	';
	}
	$__finalCompiled .= '
	';
	if ((!$__vars['head']['meta_description']) AND (!$__templater->test($__vars['description'], 'empty', array()) AND $__vars['pageDescriptionMeta'])) {
		$__finalCompiled .= '
		' . $__templater->callMacro('metadata_macros', 'description', array(
			'description' => $__vars['description'],
			'output' => true,
		), $__vars) . '
	';
	}
	$__finalCompiled .= '
	';
	if ((!$__vars['head']['meta_image_url']) AND $__templater->fn('property', array('publicMetadataLogoUrl', ), false)) {
		$__finalCompiled .= '
		' . $__templater->callMacro('metadata_macros', 'image_url', array(
			'imageUrl' => $__templater->fn('base_url', array($__templater->fn('property', array('publicMetadataLogoUrl', ), false), true, ), false),
			'output' => true,
		), $__vars) . '
	';
	}
	$__finalCompiled .= '

	';
	if ($__templater->fn('property', array('metaThemeColor', ), false)) {
		$__finalCompiled .= '
		<meta name="theme-color" content="' . $__templater->fn('property', array('metaThemeColor', ), true) . '" />
		<meta name="msapplication-TileColor" content="' . $__templater->fn('property', array('metaThemeColor', ), true) . '">
	';
	}
	$__finalCompiled .= '

	' . $__templater->includeTemplate('uix_config', $__vars) . '

	' . $__templater->callMacro('helper_js_global', 'head', array(
		'app' => 'public',
	), $__vars) . '

	';
	if ($__templater->fn('property', array('publicFaviconUrl', ), false)) {
		$__finalCompiled .= '
		<link rel="icon" type="image/png" href="' . $__templater->fn('base_url', array($__templater->fn('property', array('publicFaviconUrl', ), false), ), true) . '" sizes="32x32" />
	';
	}
	$__finalCompiled .= '
	';
	if ($__templater->fn('property', array('publicMetadataLogoUrl', ), false)) {
		$__finalCompiled .= '
		<link rel="apple-touch-icon" href="' . $__templater->fn('base_url', array($__templater->fn('property', array('publicMetadataLogoUrl', ), false), true, ), true) . '" />
	';
	}
	$__finalCompiled .= '
	' . $__templater->includeTemplate('google_analytics', $__vars) . '

	' . '

	<style>
		.uix_headerContainer .p-navSticky.is-sticky {
			top: ' . $__templater->escape($__vars['uix_stickyTopLogoMin']) . 'px !important;
		}
		@media (max-width: ' . $__templater->fn('property', array('uix_viewportShowLogoBlock', ), true) . ') {
			.uix_headerContainer .p-navSticky.is-sticky {
				top: ' . $__templater->escape($__vars['uix_stickyTopLogoMax']) . 'px !important;
			}
		}

		';
	$__vars['uix_stickyNavHeightTotal'] = '0';
	$__finalCompiled .= '
		';
	if (!$__vars['uix_hideNavigation']) {
		$__finalCompiled .= '
			';
		if ($__templater->fn('property', array('publicNavSticky', ), false) == 'primary') {
			$__finalCompiled .= '
				';
			$__vars['uix_stickyNavHeightTotal'] = $__templater->fn('property', array('uix_stickyNavHeight', ), false);
			$__finalCompiled .= '
			';
		} else if ($__templater->fn('property', array('publicNavSticky', ), false) == 'all') {
			$__finalCompiled .= '
				';
			$__vars['uix_stickyNavHeightTotal'] = ($__templater->fn('property', array('uix_stickyNavHeight', ), false) + $__templater->fn('property', array('uix_stickySectionLinkHeight', ), false));
			$__finalCompiled .= '
			';
		}
		$__finalCompiled .= '
		';
	}
	$__finalCompiled .= '

		';
	if ((!$__vars['uix_sectionLinksAlways']) AND ($__vars['uix_responsiveSectionLinks_min'] < $__vars['uix_responsiveSectionLinks_max'])) {
		$__finalCompiled .= '
			.uix_stickyBodyElement:not(.offCanvasMenu) {
				top: ' . (($__vars['uix_stickyTopLogoMin'] + $__vars['uix_stickyNavHeightTotal']) + $__templater->fn('property', array('elementSpacer', ), false)) . 'px !important;
			}

			@media (max-width: ' . $__templater->fn('property', array('uix_viewportShowLogoBlock', ), true) . ') {
				.uix_stickyBodyElement:not(.offCanvasMenu) {
					top: ' . (($__vars['uix_stickyTopLogoMax'] + $__vars['uix_stickyNavHeightTotal']) + $__templater->fn('property', array('elementSpacer', ), false)) . 'px !important;
				}
			}

			';
		$__vars['uix_stickyNavHeightTotal'] = '0';
		$__finalCompiled .= '
			';
		if (!$__vars['uix_hideNavigation']) {
			$__finalCompiled .= '
				';
			if ($__templater->fn('property', array('publicNavSticky', ), false) == 'primary') {
				$__finalCompiled .= '
					';
				$__vars['uix_stickyNavHeightTotal'] = $__templater->fn('property', array('uix_stickyNavHeight', ), false);
				$__finalCompiled .= '
				';
			} else if ($__templater->fn('property', array('publicNavSticky', ), false) == 'all') {
				$__finalCompiled .= '
					' . '
					';
				$__vars['uix_stickyNavHeightTotal'] = $__templater->fn('property', array('uix_stickyNavHeight', ), false);
				$__finalCompiled .= '
				';
			}
			$__finalCompiled .= '
			';
		}
		$__finalCompiled .= '

			@media(min-width: ' . $__templater->escape($__vars['uix_responsiveSectionLinks_min']) . 'px) and (max-width: ' . $__templater->escape($__vars['uix_responsiveSectionLinks_max']) . 'px) {
				' . '
				.p-sectionLinks {
					display: none;
				}

				.uix_stickyBodyElement:not(.offCanvasMenu) {
					top: ' . (($__vars['uix_stickyTopLogoMin'] + $__vars['uix_stickyNavHeightTotal']) + $__templater->fn('property', array('elementSpacer', ), false)) . 'px !important;
				}

				@media (max-width: ' . $__templater->fn('property', array('uix_viewportShowLogoBlock', ), true) . ') {
					.uix_stickyBodyElement:not(.offCanvasMenu) {
						top: ' . (($__vars['uix_stickyTopLogoMax'] + $__vars['uix_stickyNavHeightTotal']) + $__templater->fn('property', array('elementSpacer', ), false)) . 'px !important;
					}
				}
			}
		';
	} else {
		$__finalCompiled .= '
			.uix_stickyBodyElement:not(.offCanvasMenu) {
				top: ' . (($__vars['uix_stickyTopLogoMin'] + $__vars['uix_stickyNavHeightTotal']) + $__templater->fn('property', array('elementSpacer', ), false)) . 'px !important;
			}

			@media (max-width: ' . $__templater->fn('property', array('uix_viewportShowLogoBlock', ), true) . ') {
				.uix_stickyBodyElement:not(.offCanvasMenu) {
					top: ' . (($__vars['uix_stickyTopLogoMax'] + $__vars['uix_stickyNavHeightTotal']) + $__templater->fn('property', array('elementSpacer', ), false)) . 'px !important;
				}
			}
		';
	}
	$__finalCompiled .= '
	</style>

	' . '
</head>

<body data-template="' . $__templater->escape($__vars['template']) . '">
<div id="jumpToTop"></div>

' . '

<div class="uix_pageWrapper--fixed">
	<div class="p-pageWrapper" id="top">

		<div class="uix_headerContainer">
			<div class="uix_headerContainer--stickyFix"></div>
			' . $__templater->callMacro(null, 'uix_staffbar__component', array(
		'content' => $__vars['uix_staffbar__component'],
	), $__vars) . '

			';
	$__compilerTemp31 = '';
	$__compilerTemp32 = '';
	$__compilerTemp32 .= '
							';
	if ($__templater->fn('property', array('uix_enableLogoBlock', ), false)) {
		$__compilerTemp32 .= '
								' . $__templater->callMacro(null, 'uix_logo__component', array(
			'content' => $__vars['uix_logo__component'],
		), $__vars) . '
							';
	}
	$__compilerTemp32 .= '

							';
	$__compilerTemp33 = '';
	$__compilerTemp33 .= '
										' . $__templater->callMacro(null, 'uix_visitorTabs__component', array(
		'socialMediaContent' => $__vars['uix_socialMediaContent'],
		'whatsNewContent' => $__vars['uix_whatsNew__component'],
		'searchContent' => $__vars['uix_search__component'],
		'loginTabsContent' => $__vars['uix_loginTabs__component'],
		'visitorContent' => $__vars['uix_userTabs__component'],
		'location' => 'header',
	), $__vars) . '
									';
	if (strlen(trim($__compilerTemp33)) > 0) {
		$__compilerTemp32 .= '
								<div class="p-nav-opposite">
									' . $__compilerTemp33 . '
								</div>
							';
	}
	$__compilerTemp32 .= '
						';
	if (strlen(trim($__compilerTemp32)) > 0) {
		$__compilerTemp31 .= '
					<div class="p-header-content">
						' . $__compilerTemp32 . '
					</div>
				';
	}
	$__vars['uix_headerContent'] = $__templater->preEscaped('
				' . $__compilerTemp31 . '
			');
	$__finalCompiled .= '

			';
	$__compilerTemp34 = '';
	$__compilerTemp34 .= '
							' . $__templater->callAdsMacro('container_header', array(), $__vars) . '
						';
	if (strlen(trim($__compilerTemp34)) > 0) {
		$__finalCompiled .= '
				<header class="p-header p-header--hasExtraContent" id="header">
					<div class="p-header-inner">
						' . $__templater->escape($__vars['uix_headerContent']) . '
						' . $__compilerTemp34 . '

					</div>
				</header>
			';
	} else {
		$__finalCompiled .= '
				<header class="p-header" id="header">
					<div class="p-header-inner">
						' . $__templater->escape($__vars['uix_headerContent']) . '
					</div>
				</header>
			';
	}
	$__finalCompiled .= '

			';
	$__compilerTemp35 = '';
	if (!$__vars['uix_hideNavigation']) {
		$__compilerTemp35 .= '
							<a class="p-nav-menuTrigger" data-xf-click="off-canvas" data-menu=".js-headerOffCanvasMenu" role="button" tabindex="0">
								<i aria-hidden="true"></i>
								<span class="p-nav-menuText">' . 'Menu' . '</span>
							</a>
							';
		if (($__templater->fn('property', array('uix_navigationType', ), false) == 'sidebarNav') AND ($__templater->fn('property', array('uix_pageStyle', ), false) == 'covered')) {
			$__compilerTemp35 .= '
							<a class="p-nav-menuTrigger uix_sidebarNav--trigger" id="uix_sidebarNav--trigger">
								<i aria-hidden="true"></i>
								<span class="p-nav-menuText">' . 'Menu' . '</span>
							</a>
							';
		}
		$__compilerTemp35 .= '
						';
	}
	$__compilerTemp36 = '';
	if (!$__vars['uix_hideNavigation']) {
		$__compilerTemp36 .= '
							';
		if (($__templater->fn('property', array('uix_navigationType', ), false) != 'sidebarNav') OR ($__templater->fn('property', array('uix_pageStyle', ), false) != 'covered')) {
			$__compilerTemp36 .= '
							<div class="p-nav-scroller hScroller" data-xf-init="h-scroller">
								<div class="hScroller-scroll">
									<ul class="p-nav-list js-offCanvasNavSource">
									';
			$__vars['i'] = 0;
			if ($__templater->isTraversable($__vars['navTree'])) {
				foreach ($__vars['navTree'] AS $__vars['navSection'] => $__vars['navEntry']) {
					if (($__vars['navSection'] != $__vars['xf']['app']['defaultNavigationId'])) {
						$__vars['i']++;
						$__compilerTemp36 .= '
										<li>
											' . $__templater->callMacro(null, 'nav_entry', array(
							'navId' => $__vars['navSection'],
							'nav' => $__vars['navEntry'],
							'selected' => ($__vars['navSection'] == $__vars['pageSection']),
							'shortcut' => $__vars['i'],
						), $__vars) . '
										</li>
									';
					}
				}
			}
			$__compilerTemp36 .= '
									</ul>
								</div>
							</div>
							';
		}
		$__compilerTemp36 .= '

							';
		if ($__templater->fn('property', array('uix_activeNavTitle', ), false)) {
			$__compilerTemp36 .= '
								<div class="uix_activeNavTitle">
									<span>
										';
			if ($__vars['uix_mobileActiveNav']) {
				$__compilerTemp36 .= '
											' . $__templater->escape($__vars['uix_mobileActiveNav']) . '
										';
			} else if ($__vars['selectedNavEntry']['href']) {
				$__compilerTemp36 .= '
											' . $__templater->escape($__vars['selectedNavEntry']['title']) . '
										';
			} else {
				$__compilerTemp36 .= '
										';
			}
			$__compilerTemp36 .= '
									</span>
								</div>
							';
		}
		$__compilerTemp36 .= '
						';
	}
	$__compilerTemp37 = '';
	$__compilerTemp38 = '';
	$__compilerTemp38 .= '
										' . $__templater->callMacro(null, 'uix_visitorTabs__component', array(
		'socialMediaContent' => $__vars['uix_socialMediaContent'],
		'whatsNewContent' => $__vars['uix_whatsNew__component'],
		'searchContent' => $__vars['uix_search__component'],
		'loginTabsContent' => $__vars['uix_loginTabs__component'],
		'visitorContent' => $__vars['uix_userTabs__component'],
		'location' => 'navigation',
	), $__vars) . '
									';
	if (strlen(trim($__compilerTemp38)) > 0) {
		$__compilerTemp37 .= '
								<div class="p-nav-opposite">
									' . $__compilerTemp38 . '
								</div>
							';
	}
	$__vars['navHtml'] = $__templater->preEscaped('
				<nav class="p-nav">
					<div class="p-nav-inner">
						' . $__compilerTemp35 . '

						' . $__templater->callMacro(null, 'uix_logo__component', array(
		'content' => $__vars['uix_logo__component'],
	), $__vars) . '

						' . $__compilerTemp36 . '

							' . $__templater->callMacro(null, 'uix_search__component', array(
		'location' => 'navigationLeft',
		'content' => $__vars['uix_search__component'],
	), $__vars) . '

							' . $__compilerTemp37 . '
					</div>
				</nav>
			');
	$__finalCompiled .= '

			';
	if ($__templater->fn('property', array('publicNavSticky', ), false) == 'primary') {
		$__finalCompiled .= '
				<div class="p-navSticky p-navSticky--primary ';
		if ($__templater->fn('property', array('publicNavSticky', ), false) !== 'none') {
			$__finalCompiled .= 'uix_stickyBar';
		}
		$__finalCompiled .= '" data-top-offset-min="' . $__templater->escape($__vars['uix_stickyTopLogoMin']) . '" data-top-offset-max="' . $__templater->escape($__vars['uix_stickyTopLogoMax']) . '" data-top-offset-breakpoint="' . $__templater->fn('property', array('uix_viewportShowLogoBlock', ), true) . '">
					' . $__templater->filter($__vars['navHtml'], array(array('raw', array()),), true) . '
				</div>
				' . $__templater->filter($__vars['subNavHtml'], array(array('raw', array()),), true) . '
				';
	} else if ($__templater->fn('property', array('publicNavSticky', ), false) == 'all') {
		$__finalCompiled .= '
				<div class="p-navSticky p-navSticky--all ';
		if ($__templater->fn('property', array('publicNavSticky', ), false) !== 'none') {
			$__finalCompiled .= 'uix_stickyBar';
		}
		$__finalCompiled .= '" data-top-offset-min="' . $__templater->escape($__vars['uix_stickyTopLogoMin']) . '" data-top-offset-max="' . $__templater->escape($__vars['uix_stickyTopLogoMax']) . '" data-top-offset-breakpoint="' . $__templater->fn('property', array('uix_viewportShowLogoBlock', ), true) . '">
					' . $__templater->filter($__vars['navHtml'], array(array('raw', array()),), true) . '
					' . $__templater->filter($__vars['subNavHtml'], array(array('raw', array()),), true) . '
				</div>
				';
	} else {
		$__finalCompiled .= '
				' . $__templater->filter($__vars['navHtml'], array(array('raw', array()),), true) . '
				' . $__templater->filter($__vars['subNavHtml'], array(array('raw', array()),), true) . '
			';
	}
	$__finalCompiled .= '

			' . $__templater->callMacro('uix_welcomeSection', 'welcomeSection', array(
		'contentTemplate' => $__vars['template'],
		'location' => 'header',
		'showWelcomeSection' => $__vars['uix_showWelcomeSection'],
	), $__vars) . '
			' . $__templater->callMacro(null, 'uix_topBreadcrumb__component', array(
		'location' => 'header',
		'content' => $__vars['uix_topBreadcrumb__component'],
	), $__vars) . '
			' . $__templater->callMacro(null, 'uix_titlebar__component', array(
		'location' => 'header',
		'content' => $__vars['uix_titlebar__component'],
	), $__vars) . '

		</div>

		' . '

		<div class="offCanvasMenu offCanvasMenu--nav js-headerOffCanvasMenu" data-menu="menu" aria-hidden="true" data-ocm-builder="navigation">
			<div class="offCanvasMenu-backdrop" data-menu-close="true"></div>
			<div class="offCanvasMenu-content">
				<div class="offCanvasMenu-header">
					' . 'Menu' . '
					<a class="offCanvasMenu-closer" data-menu-close="true" role="button" tabindex="0" aria-label="' . 'Close' . '"></a>
				</div>
				';
	if ($__vars['xf']['visitor']['user_id']) {
		$__finalCompiled .= '
					<div class="p-offCanvasAccountLink">
						<a href="' . $__templater->fn('link', array('account', ), true) . '" class="offCanvasMenu-link">
							' . $__templater->fn('avatar', array($__vars['xf']['visitor'], 'xxs', false, array(
			'href' => '',
		))) . '
							' . $__templater->escape($__vars['xf']['visitor']['username']) . '
						</a>
						<hr class="offCanvasMenu-separator" />
					</div>
				';
	}
	$__finalCompiled .= '
				<div class="js-offCanvasNavTarget"></div>
			</div>
		</div>

		<div class="p-body">

			';
	if (($__templater->fn('property', array('uix_navigationType', ), false) == 'sidebarNav') AND ($__templater->fn('property', array('uix_pageStyle', ), false) == 'covered')) {
		$__finalCompiled .= '
				' . $__templater->callMacro(null, 'uix_sidebarNav__component', array(
			'content' => $__vars['uix_sidebarNav__component'],
		), $__vars) . '
			';
	}
	$__finalCompiled .= '

			<div class="p-body-inner">
				';
	if ((!$__templater->fn('is_addon_active', array('ThemeHouse/UIX', ), false)) AND $__vars['xf']['visitor']['is_admin']) {
		$__finalCompiled .= '
				<div class="blockMessage blockMessage--error blockMessage--errorUixAddon">
					<h2 style="margin: 0 0 .5em 0">UI.X Error</h2>
					<p>
						It appears that you do not have the UI.X Add-on installed. Please install this add-on to ensure your style works as expected. You can download the UI.X add-on <a href="https://www.themehouse.com/xenforo/2/addons/uix-addon">here</a>.
					</p>
					' . $__templater->button($__templater->callMacro('uix_icons.less', 'icon', array(
			'icon' => 'warning',
		), $__vars) . ' View Documention', array(
			'href' => 'https://www.themehouse.com/help/documentation/uix2',
			'class' => 'button--primary',
		), '', array(
		)) . '
				</div>
				';
	}
	$__finalCompiled .= '
				<!--XF:EXTRA_OUTPUT-->

				' . $__templater->callMacro(null, 'uix_titlebar__component', array(
		'location' => 'default',
		'content' => $__vars['uix_titlebar__component'],
	), $__vars) . '

				' . $__templater->callMacro('uix_welcomeSection', 'welcomeSection', array(
		'contentTemplate' => $__vars['template'],
		'location' => 'outsideWrapper',
		'showWelcomeSection' => $__vars['uix_showWelcomeSection'],
	), $__vars) . '

				' . '

				' . $__templater->callMacro(null, 'uix_topBreadcrumb__component', array(
		'location' => 'outsideWrapper',
		'content' => $__vars['uix_topBreadcrumb__component'],
	), $__vars) . '

				' . $__templater->callMacro('browser_warning_macros', 'javascript', array(), $__vars) . '
				' . $__templater->callMacro('browser_warning_macros', 'browser', array(), $__vars) . '

				<div class="uix_contentWrapper">

					';
	if (!$__vars['uix_hideNotices']) {
		$__finalCompiled .= '
						';
		if ($__vars['notices']['block']) {
			$__finalCompiled .= '
							' . $__templater->callMacro('notice_macros', 'notice_list', array(
				'type' => 'block',
				'notices' => $__vars['notices']['block'],
			), $__vars) . '
						';
		}
		$__finalCompiled .= '

						';
		if ($__vars['notices']['scrolling']) {
			$__finalCompiled .= '
							' . $__templater->callMacro('notice_macros', 'notice_list', array(
				'type' => 'scrolling',
				'notices' => $__vars['notices']['scrolling'],
			), $__vars) . '
						';
		}
		$__finalCompiled .= '
					';
	}
	$__finalCompiled .= '

					' . $__templater->callAdsMacro('container_content_above', array(), $__vars) . '
					' . $__templater->callMacro('uix_welcomeSection', 'welcomeSection', array(
		'contentTemplate' => $__vars['template'],
		'location' => 'insideWrapper',
		'showWelcomeSection' => $__vars['uix_showWelcomeSection'],
	), $__vars) . '
					' . $__templater->callMacro(null, 'uix_topBreadcrumb__component', array(
		'location' => 'insideWrapper',
		'content' => $__vars['uix_topBreadcrumb__component'],
	), $__vars) . '
					' . $__templater->callMacro(null, 'uix_titlebar__component', array(
		'location' => 'insideWrapper',
		'content' => $__vars['uix_titlebar__component'],
	), $__vars) . '

					<div class="p-body-main ' . ($__vars['sidebar'] ? 'p-body-main--withSidebar' : '') . ' ' . ($__vars['sideNav'] ? 'p-body-main--withSideNav' : '') . '">
						';
	if ($__vars['sideNav']) {
		$__finalCompiled .= '
							<div class="p-body-sideNav">
								<div class="p-body-sideNavTrigger">
									' . $__templater->button('
										' . ($__templater->escape($__vars['sideNavTitle']) ?: 'Navigation') . '
									', array(
			'class' => 'button--link',
			'data-xf-click' => 'off-canvas',
			'data-menu' => '#js-SideNavOcm',
		), '', array(
		)) . '
								</div>
								<div class="p-body-sideNavInner';
		if ($__templater->fn('property', array('uix_stickySidebar', ), false)) {
			$__finalCompiled .= ' uix_stickyBodyElement';
		}
		$__finalCompiled .= '" data-ocm-class="offCanvasMenu offCanvasMenu--blocks" id="js-SideNavOcm" data-ocm-builder="sideNav">
									<div data-ocm-class="offCanvasMenu-backdrop" data-menu-close="true"></div>
									<div data-ocm-class="offCanvasMenu-content">
										<div class="p-body-sideNavContent">
											' . $__templater->callAdsMacro('container_sidenav_above', array(), $__vars) . '
											';
		if ($__templater->isTraversable($__vars['sideNav'])) {
			foreach ($__vars['sideNav'] AS $__vars['sideNavHtml']) {
				$__finalCompiled .= '
												' . $__templater->escape($__vars['sideNavHtml']) . '
											';
			}
		}
		$__finalCompiled .= '
											' . $__templater->callAdsMacro('container_sidenav_below', array(), $__vars) . '
										</div>
									</div>
								</div>
							</div>
						';
	}
	$__finalCompiled .= '

						' . $__templater->callMacro(null, 'uix_sidebar__component', array(
		'content' => $__vars['uix_sidebar__component'],
		'location' => 'left',
	), $__vars) . '
						<div class="p-body-content">
							<div class="p-body-pageContent">
								' . $__templater->callMacro('uix_welcomeSection', 'welcomeSection', array(
		'contentTemplate' => $__vars['template'],
		'location' => 'insideBody',
		'showWelcomeSection' => $__vars['uix_showWelcomeSection'],
	), $__vars) . '
								' . $__templater->callMacro(null, 'uix_topBreadcrumb__component', array(
		'location' => 'insideBody',
		'content' => $__vars['uix_topBreadcrumb__component'],
	), $__vars) . '
								' . $__templater->callMacro(null, 'uix_titlebar__component', array(
		'location' => 'insideBody',
		'content' => $__vars['uix_titlebar__component'],
	), $__vars) . '
								';
	if (!$__templater->fn('in_array', array($__vars['template'], array('register_form', 'login', 'siropu_referral_contests_invitation_page', ), ), false)) {
		$__finalCompiled .= '
	' . $__templater->fn('siropu_invitation_message', array(), true) . '
';
	}
	$__finalCompiled .= '
' . $__templater->filter($__vars['content'], array(array('raw', array()),), true) . '
								' . $__templater->callMacro(null, 'uix_bottomBreadcrumb__component', array(
		'content' => $__vars['uix_bottomBreadcrumb__component'],
		'location' => 'insideContent',
	), $__vars) . '
							</div>
							' . $__templater->callAdsMacro('container_content_below', array(), $__vars) . '

							' . $__templater->callMacro(null, 'uix_bottomBreadcrumb__component', array(
		'content' => $__vars['uix_bottomBreadcrumb__component'],
		'location' => 'insideWrapper',
	), $__vars) . '
						</div>

						' . $__templater->callMacro(null, 'uix_sidebar__component', array(
		'content' => $__vars['uix_sidebar__component'],
		'location' => 'right',
	), $__vars) . '
					</div>

				</div>

				' . $__templater->callMacro(null, 'uix_bottomBreadcrumb__component', array(
		'content' => $__vars['uix_bottomBreadcrumb__component'],
		'location' => 'outsideWrapper',
	), $__vars) . '
			</div>
		</div>

		<footer class="p-footer" id="footer">

			';
	if ((!$__vars['uix_hideExtendedFooter']) AND $__templater->fn('property', array('uix_enableExtendedFooter', ), false)) {
		$__finalCompiled .= '
				' . $__templater->includeTemplate('uix_extendedFooter', $__vars) . '
			';
	}
	$__finalCompiled .= '

			<div class="p-footer-inner">
				<div class="pageContent">
					<div class="p-footer-row">
						';
	$__compilerTemp39 = '';
	$__compilerTemp39 .= '
									';
	if ($__templater->fn('property', array('uix_pageWidthToggle', ), false) != 'disabled') {
		$__compilerTemp39 .= '
										<li><a id="uix_widthToggle--trigger" data-xf-init="tooltip" title="' . 'Toggle width' . '" >' . $__templater->callMacro('uix_icons.less', 'icon', array(
			'icon' => 'collapse',
		), $__vars) . '</a></li>
									';
	}
	$__compilerTemp39 .= '
									';
	if ($__templater->method($__vars['xf']['visitor'], 'canChangeStyle', array())) {
		$__compilerTemp39 .= '
										<li><a href="' . $__templater->fn('link', array('misc/style', ), true) . '" data-xf-click="overlay" data-xf-init="tooltip" title="' . 'Style chooser' . '" rel="nofollow">' . $__templater->escape($__vars['xf']['style']['title']) . '</a></li>
									';
	}
	$__compilerTemp39 .= '
									';
	if ($__templater->method($__vars['xf']['visitor'], 'canChangeLanguage', array())) {
		$__compilerTemp39 .= '
										<li><a href="' . $__templater->fn('link', array('misc/language', ), true) . '" data-xf-click="overlay" data-xf-init="tooltip" title="' . 'Language chooser' . '" rel="nofollow"><i class="fa fa-globe" aria-hidden="true"></i> ' . $__templater->escape($__vars['xf']['language']['title']) . '</a></li>
									';
	}
	$__compilerTemp39 .= '
								';
	if (strlen(trim($__compilerTemp39)) > 0) {
		$__finalCompiled .= '
							<div class="p-footer-row-main">
								<ul class="p-footer-linkList p-footer-choosers">
								' . $__compilerTemp39 . '
								</ul>
							</div>
						';
	}
	$__finalCompiled .= '
					</div>
					<div class="p-footer-row-opposite">
						<ul class="p-footer-linkList">
							';
	if ($__templater->method($__vars['xf']['visitor'], 'canUseContactForm', array())) {
		$__finalCompiled .= '
								';
		if ($__vars['xf']['options']['contactUrl']['type'] == 'default') {
			$__finalCompiled .= '
									<li><a href="' . $__templater->fn('link', array('misc/contact', ), true) . '" data-xf-click="overlay">' . 'Contact us' . '</a></li>
								';
		} else if ($__vars['xf']['options']['contactUrl']['type'] == 'custom') {
			$__finalCompiled .= '
									<li><a href="' . $__templater->escape($__vars['xf']['options']['contactUrl']['custom']) . '" data-xf-click="' . ($__vars['xf']['options']['contactUrl']['overlay'] ? 'overlay' : '') . '">' . 'Contact us' . '</a></li>
								';
		}
		$__finalCompiled .= '
							';
	}
	$__finalCompiled .= '

							';
	if ($__vars['xf']['tosUrl']) {
		$__finalCompiled .= '
								<li><a href="' . $__templater->escape($__vars['xf']['tosUrl']) . '">' . 'Terms and rules' . '</a></li>
							';
	}
	$__finalCompiled .= '

							';
	if ($__vars['xf']['options']['privacyPolicyUrl']) {
		$__finalCompiled .= '
								<li><a href="' . $__templater->escape($__vars['xf']['options']['privacyPolicyUrl']) . '">' . 'Privacy' . '</a></li>
							';
	}
	$__finalCompiled .= '

							';
	if ($__vars['xf']['helpPageCount']) {
		$__finalCompiled .= '
								<li><a href="' . $__templater->fn('link', array('help', ), true) . '">' . 'Help' . '</a></li>
							';
	}
	$__finalCompiled .= '

							';
	if ($__vars['xf']['homePageUrl']) {
		$__finalCompiled .= '
								<li><a href="' . $__templater->escape($__vars['xf']['homePageUrl']) . '">' . 'Home' . '</a></li>
							';
	}
	$__finalCompiled .= '

							<li><a href="#top" title="' . 'Top' . '" data-xf-click="scroll-to"><i class="fa fa-arrow-up" aria-hidden="true"></i></a></li>

							<li><a href="' . $__templater->fn('link', array('forums/index.rss', '-', ), true) . '" target="_blank" class="p-footer-rssLink" title="' . 'RSS' . '"><span aria-hidden="true"><i class="fa fa-rss"></i></span></a></li>
						</ul>
					</div>
				</div>
			</div>

			<div class="p-footer-copyrightRow">
				<div class="pageContent">
					<div class="uix_copyrightBlock">
						';
	$__compilerTemp40 = '';
	$__compilerTemp40 .= '
									' . $__templater->fn('copyright') . '
									' . $__templater->callback('ThemeHouse\\Core\\Branding', 'renderStyleBranding', '', array());
	$__vars['thBrandingDisplayed'] = '1';
	$__compilerTemp40 .= '
									' . '' . '
								';
	if (strlen(trim($__compilerTemp40)) > 0) {
		$__finalCompiled .= '
							<div class="p-footer-copyright">
								' . $__compilerTemp40 . '
							</div>
						';
	}
	$__finalCompiled .= '

						';
	$__compilerTemp41 = '';
	$__compilerTemp41 .= '
								' . $__templater->callMacro('debug_macros', 'debug', array(
		'controller' => $__vars['controller'],
		'action' => $__vars['actionMethod'],
		'template' => $__vars['template'],
	), $__vars) . '
							';
	if (strlen(trim($__compilerTemp41)) > 0) {
		$__finalCompiled .= '
							<div class="p-footer-debug">
							' . $__compilerTemp41 . '
							</div>
						';
	}
	$__finalCompiled .= '
					</div>
					' . '
					' . $__templater->callMacro(null, 'uix_socialMedia__component', array(
		'content' => $__vars['uix_socialMediaContent'],
		'location' => 'copyright',
	), $__vars) . '
				</div>
			</div>
		</footer>
		';
	if ($__templater->fn('property', array('uix_fab', ), false) != 'never') {
		$__finalCompiled .= '
			';
		$__compilerTemp42 = '';
		$__compilerTemp42 .= (isset($__templater->pageParams['pageAction']) ? $__templater->pageParams['pageAction'] : '');
		if (strlen(trim($__compilerTemp42)) > 0) {
			$__finalCompiled .= '
				<div class="uix_fabBar uix_fabBar--active">
					<div class="p-title-pageAction">' . $__compilerTemp42 . '</div>
				</div>
			';
		}
		$__finalCompiled .= '
		';
	}
	$__finalCompiled .= '
	</div>
</div>

<div class="u-bottomFixer js-bottomFixTarget">
	';
	if ($__vars['notices']['floating']) {
		$__finalCompiled .= '
		' . $__templater->callMacro('notice_macros', 'notice_list', array(
			'type' => 'floating',
			'notices' => $__vars['notices']['floating'],
		), $__vars) . '
	';
	}
	$__finalCompiled .= '
</div>

';
	if ($__templater->fn('property', array('scrollJumpButtons', ), false)) {
		$__finalCompiled .= '
	<div class="u-scrollButtons js-scrollButtons" data-trigger-type="' . $__templater->fn('property', array('scrollJumpButtons', ), true) . '">
		' . $__templater->button('<i class="fa fa-arrow-up"></i>', array(
			'href' => '#top',
			'class' => 'button--scroll',
			'data-xf-click' => 'scroll-to',
		), '', array(
		)) . '
		';
		if ($__templater->fn('property', array('scrollJumpButtons', ), false) != 'up') {
			$__finalCompiled .= '
			' . $__templater->button('<i class="fa fa-arrow-down"></i>', array(
				'href' => '#footer',
				'class' => 'button--scroll',
				'data-xf-click' => 'scroll-to',
			), '', array(
			)) . '
		';
		}
		$__finalCompiled .= '
	</div>
';
	}
	$__finalCompiled .= '

' . $__templater->callMacro('helper_js_global', 'body', array(
		'app' => 'public',
		'jsState' => $__vars['jsState'],
	), $__vars) . '

';
	if ($__templater->fn('property', array('uix_loginStyle', ), false) == 'slidingPanel') {
		$__finalCompiled .= '
	<div class="uix__loginForm uix__loginForm--login">
		<div class="uix__loginForm--panel">
			' . $__templater->includeTemplate('login', $__vars) . '
		</div>
		<div class="uix__loginForm--mask"></div>
	</div>
';
	}
	$__finalCompiled .= '

' . $__templater->filter($__vars['ldJsonHtml'], array(array('raw', array()),), true) . '

</body>
</html>

' . '

' . '

' . '

' . '

';
	return $__finalCompiled;
});