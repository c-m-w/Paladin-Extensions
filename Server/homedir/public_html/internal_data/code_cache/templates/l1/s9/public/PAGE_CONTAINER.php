<?php
// FROM HASH: c920e20ff2a10785aec458980dd21d58
return array('macros' => array('uix_mainTabComponent' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'content' => '!',
		'location' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if (($__templater->fn('property', array('uix_tabBarLocation', ), false) === $__vars['location']) AND $__templater->fn('property', array('uix_enableMainTabs', ), false)) {
		$__finalCompiled .= '
		' . $__templater->escape($__vars['content']) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'uix_sidebarTrigger__component' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'location' => '',
		'content' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if (($__vars['location'] == $__templater->fn('property', array('uix_sidebarTriggerPosition', ), false)) OR ($__vars['location'] == 'navigation')) {
		$__finalCompiled .= '
		' . $__templater->escape($__vars['content']) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'uix_search__component' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'content' => '!',
		'location' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if (($__templater->fn('property', array('uix_searchPosition', ), false) == $__vars['location']) OR ($__vars['location'] == 'navigation')) {
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
	if (($__vars['xf']['visitor']['user_id'] AND ($__templater->fn('property', array('uix_userTabsPosition', ), false) == $__vars['location'])) OR ($__vars['location'] == 'navigation')) {
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
	if (($__templater->fn('property', array('uix_loginTriggerPosition', ), false) == $__vars['location']) OR ($__vars['location'] == 'navigation')) {
		$__finalCompiled .= '
		';
		if ($__vars['location'] == 'tablinks') {
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
	if (($__templater->fn('property', array('uix_userTabsPosition', ), false) == $__vars['location']) OR ($__vars['location'] == 'navigation')) {
		$__finalCompiled .= '
		';
		if ($__vars['location'] == 'tablinks') {
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
	if (($__templater->fn('property', array('uix_socialMediaPosition', ), false) == $__vars['location']) OR ($__vars['location'] == 'copyright')) {
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
				<div class="p-navgroup p-discovery' . ((!$__templater->method($__vars['xf']['visitor'], 'canSearch', array())) ? ' p-discovery--noSearch' : '') . '">
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
'breadcrumbs' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'breadcrumbHasCrumbs' => '!',
		'crumbContent' => '!',
		'variant' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__compilerTemp1 = '';
	$__compilerTemp1 .= '
					';
	if ($__vars['breadcrumbHasCrumbs']) {
		$__compilerTemp1 .= '
						';
		$__compilerTemp2 = '';
		$__compilerTemp2 .= '
									' . $__templater->escape($__vars['crumbContent']) . '
								';
		if (strlen(trim($__compilerTemp2)) > 0) {
			$__compilerTemp1 .= '
							<ul class="p-breadcrumbs ' . ($__vars['variant'] ? ('p-breadcrumbs--' . $__templater->escape($__vars['variant'])) : '') . '"
								itemscope itemtype="https://schema.org/BreadcrumbList">
								' . $__compilerTemp2 . '
							</ul>
						';
		}
		$__compilerTemp1 .= '
					';
	}
	$__compilerTemp1 .= '
				';
	if (strlen(trim($__compilerTemp1)) > 0) {
		$__finalCompiled .= '
		<div class="breadcrumb block ' . ($__vars['variant'] ? ('p-breadcrumb--' . $__templater->escape($__vars['variant'])) : '') . '">
			<div class="pageContent">
				' . $__compilerTemp1 . '
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
		'position' => 0,
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
		';
	if ($__vars['position']) {
		$__finalCompiled .= '<meta itemprop="position" content="' . $__templater->escape($__vars['position']) . '" />';
	}
	$__finalCompiled .= '
	</li>
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
'uix_notices' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'location' => '!',
		'content' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__vars['location'] == $__templater->fn('property', array('uix_noticeLocation', ), false)) {
		$__finalCompiled .= '
		' . $__templater->escape($__vars['content']) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'uix_footer' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'insideContent' => '!',
		'location' => '!',
		'content' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if (($__vars['insideContent'] AND ($__vars['location'] == 'insideContent')) OR (($__vars['location'] == 'bottom') AND (!$__vars['insideContent']))) {
		$__finalCompiled .= '
		' . $__templater->escape($__vars['content']) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'uix_logoBlock' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'content' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
				';
	$__compilerTemp1 = '';
	$__compilerTemp1 .= '
								' . $__templater->callAdsMacro('container_header', array(), $__vars) . '
							';
	if (strlen(trim($__compilerTemp1)) > 0) {
		$__finalCompiled .= '
					<header class="p-header p-header--hasExtraContent" id="header">
						<div class="p-header-inner">
							' . $__templater->escape($__vars['content']) . '
							' . $__compilerTemp1 . '

						</div>
					</header>
				';
	} else {
		$__finalCompiled .= '
					<header class="p-header" id="header">
						<div class="p-header-inner">
							' . $__templater->escape($__vars['content']) . '
						</div>
					</header>
				';
	}
	$__finalCompiled .= '
			';
	return $__finalCompiled;
},
'canvasNavPanel' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'widgets' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
					<div class="offCanvasMenu-header">
						' . 'Menu' . '
						<a class="offCanvasMenu-closer" data-menu-close="true" role="button" tabindex="0" aria-label="' . $__templater->filter('Close', array(array('for_attr', array()),), true) . '"></a>
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
					';
	if ($__vars['xf']['visitor']['user_id']) {
		$__finalCompiled .= '
						<div class="offCanvasMenu-linkHolder u-ripple ' . (($__vars['uix_myAccountLinks'] == 'profile') ? 'is-selected' : '') . '"><div class="p-navEl__inner"><a data-nav-id="profile" href="' . $__templater->fn('link', array('members', $__vars['xf']['visitor'], ), true) . '" class="offCanvasMenu-link">' . 'Profile' . '</a></div></div>
						<div class="offCanvasMenu-linkHolder u-ripple ' . (($__vars['uix_myAccountLinks'] == 'alerts') ? 'is-selected' : '') . '"><div class="p-navEl__inner"><a data-nav-id="alerts" href="' . $__templater->fn('link', array('account/alerts', ), true) . '" class="offCanvasMenu-link">' . 'Alerts' . '</a></div></div>
						<div class="offCanvasMenu-linkHolder u-ripple ' . (($__vars['uix_myAccountLinks'] == 'settings') ? 'is-selected' : '') . '"><div class="p-navEl__inner"><a data-nav-id="settings" href="' . $__templater->fn('link', array('account/preferences', ), true) . '" class="offCanvasMenu-link">' . 'Settings' . '</a></div></div>
					';
	}
	$__finalCompiled .= '
					';
	$__compilerTemp1 = '';
	$__compilerTemp1 .= '
								' . $__templater->filter($__vars['widgets'], array(array('raw', array()),), true) . '
							';
	if (strlen(trim($__compilerTemp1)) > 0) {
		$__finalCompiled .= '
						<div class="uix_sidebarNav__inner__widgets">
							' . $__compilerTemp1 . '
						</div>
					';
	}
	$__finalCompiled .= '
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
					   aria-label="' . $__templater->filter('Toggle expanded', array(array('for_attr', array()),), true) . '"
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
	$__finalCompiled .= '<span>' . ($__vars['titleHtml'] ? $__templater->filter($__vars['titleHtml'], array(array('raw', array()),), true) : $__templater->escape($__vars['nav']['title'])) . '</span>';
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
	if ($__vars['uix_showWelcomeSection']) {
		$__finalCompiled .= '
	';
		$__vars['uix_htmlClasses'] = $__templater->preEscaped($__templater->escape($__vars['uix_htmlClasses']) . ' uix_hasWelcomeSection');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

' . '
';
	$__vars['uix_subNavContentStatic'] = '0';
	$__finalCompiled .= '

' . '

' . '

';
	$__compilerTemp1 = '';
	$__compilerTemp2 = '';
	$__compilerTemp2 .= '
					';
	if ($__vars['uix_mainTabSets']) {
		$__compilerTemp2 .= '
						' . $__templater->callMacro('uix_mainTabSets', $__vars['uix_mainTabSets'], array(
			'activeTab' => $__vars['uix_mainTabActive'],
		), $__vars) . '
					';
	}
	$__compilerTemp2 .= '
				';
	if (strlen(trim($__compilerTemp2)) > 0) {
		$__compilerTemp1 .= '
	<div class="block uix_mainTabBar">
		<div class="block-tabHeader tabs hScroller" data-xf-init="h-scroller">
			<span class="hScroller-scroll">
				' . $__compilerTemp2 . '
			</span>
		</div>
	</div>
';
	}
	$__vars['uix_mainTabComponent'] = $__templater->preEscaped('
' . $__compilerTemp1 . '
');
	$__finalCompiled .= '

' . '

' . '

';
	$__compilerTemp3 = '';
	if ($__vars['sidebar']) {
		$__compilerTemp3 .= '
		';
		if ($__templater->fn('property', array('uix_collapsibleSidebar', ), false) AND $__vars['uix_canCollapseSidebar']) {
			$__compilerTemp3 .= '
			<a class="uix_sidebarTrigger__component uix_sidebarTrigger ' . (($__templater->fn('property', array('uix_sidebarTriggerPosition', ), false) == 'sectionLinks') ? 'p-navgroup-link' : 'button') . '" data-xf-init="tooltip" title="' . 'Sidebar' . '">
				<i class="mdi mdi-dots-vertical"></i>
				<span class="uix_sidebarTrigger--phrase">' . 'Sidebar' . '</span>
			</a>
		';
		}
		$__compilerTemp3 .= '
		';
		if ($__templater->fn('property', array('uix_sidebarMobileCanvas', ), false)) {
			$__compilerTemp3 .= '
			<a class="uix_sidebarCanvasTrigger uix_sidebarTrigger__component ' . (($__templater->fn('property', array('uix_sidebarTriggerPosition', ), false) == 'sectionLinks') ? 'p-navgroup-link' : 'button') . '" data-xf-init="tooltip" title="' . 'Sidebar' . '">
				<i class="mdi mdi-dots-vertical"></i>
				<span class="uix_sidebarTrigger--phrase">' . 'Sidebar' . '</span>
			</a>
		';
		}
		$__compilerTemp3 .= '
	';
	}
	$__vars['uix_sidebarTrigger__content'] = $__templater->preEscaped('
	' . $__compilerTemp3 . '
');
	$__finalCompiled .= '

' . '

' . '

';
	if (!$__vars['uix_hideNavigation']) {
		$__finalCompiled .= '
';
		$__compilerTemp4 = '';
		if ($__templater->method($__vars['xf']['visitor'], 'canSearch', array())) {
			$__compilerTemp4 .= '
		<div class="uix_searchBar">
			<div class="uix_searchBarInner">
				<form action="' . $__templater->fn('link', array('search/search', ), true) . '" method="post" class="uix_searchForm" data-xf-init="quick-search">
					<a class="uix_search--close">
						' . $__templater->callMacro('uix_icons.less', 'icon', array(
				'icon' => 'close',
			), $__vars) . '
					</a>
					' . $__templater->formTextBox(array(
				'autocomplete' => 'off',
				'class' => 'js-uix_syncValue uix_searchInput uix_searchDropdown__trigger',
				'data-uixsync' => 'search',
				'name' => 'keywords',
				'placeholder' => 'Search' . $__vars['xf']['language']['ellipsis'],
				'aria-label' => 'Search',
				'data-menu-autofocus' => 'true',
			)) . '
					<a href="' . $__templater->fn('link', array('search', ), true) . '"
					   class="uix_search--settings u-ripple"
					   data-xf-key="' . $__templater->filter('/', array(array('for_attr', array()),), true) . '"
					   aria-label="' . $__templater->filter('Search', array(array('for_attr', array()),), true) . '"
					   aria-expanded="false"
					   aria-haspopup="true"
					   title="' . $__templater->filter('Search', array(array('for_attr', array()),), true) . '">
						' . $__templater->callMacro('uix_icons.less', 'icon', array(
				'icon' => 'settings',
			), $__vars) . '
					</a>
					<span class="';
			if ($__templater->fn('property', array('uix_searchButton', ), false)) {
				$__compilerTemp4 .= 'uix_search--submit';
			}
			$__compilerTemp4 .= ' uix_searchIcon">
						' . $__templater->callMacro('uix_icons.less', 'icon', array(
				'icon' => 'search',
			), $__vars) . '
					</span>
					' . $__templater->fn('csrf_input') . '
				</form>
			</div>

			';
			if ($__templater->fn('property', array('uix_searchIconBehavior', ), false) != 'dropdown') {
				$__compilerTemp4 .= '
				<a class="uix_searchIconTrigger p-navgroup-link p-navgroup-link--iconic p-navgroup-link--search u-ripple"
				   aria-label="' . 'Search' . '"
				   aria-expanded="false"
				   aria-haspopup="true"
				   title="' . 'Search' . '">
					<i aria-hidden="true"></i>
				</a>
			';
			}
			$__compilerTemp4 .= '

			';
			if ($__templater->fn('property', array('uix_searchIconBehavior', ), false) != 'expand') {
				$__compilerTemp4 .= '
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
			$__compilerTemp4 .= '

			<div class="menu menu--structural menu--wide" data-menu="menu" aria-hidden="true">
				<form action="' . $__templater->fn('link', array('search/search', ), true) . '" method="post"
					  class="menu-content"
					  data-xf-init="quick-search">
					<h3 class="menu-header">' . 'Search' . '</h3>
					' . '
					<div class="menu-row">
						';
			if ($__vars['searchConstraints']) {
				$__compilerTemp4 .= '
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
				$__compilerTemp5 = array(array(
					'value' => '',
					'label' => 'Everywhere',
					'_type' => 'option',
				));
				if ($__templater->isTraversable($__vars['searchConstraints'])) {
					foreach ($__vars['searchConstraints'] AS $__vars['constraintName'] => $__vars['constraint']) {
						$__compilerTemp5[] = array(
							'value' => $__templater->filter($__vars['constraint'], array(array('json', array()),), false),
							'label' => $__templater->escape($__vars['constraintName']),
							'_type' => 'option',
						);
					}
				}
				$__compilerTemp4 .= $__templater->formSelect(array(
					'name' => 'constraints',
					'class' => 'js-quickSearch-constraint',
					'aria-label' => 'Search within',
				), $__compilerTemp5) . '
							</div>
							';
			} else {
				$__compilerTemp4 .= '
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
			$__compilerTemp4 .= '
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
							<span class="inputGroup-text" id="ctrl_search_menu_by_member">' . 'By' . $__vars['xf']['language']['label_separator'] . '</span>
							<input class="input" name="c[users]" data-xf-init="auto-complete" placeholder="' . $__templater->filter('Member', array(array('for_attr', array()),), true) . '" aria-labelledby="ctrl_search_menu_by_member" />
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
				$__compilerTemp4 .= '
						<div class="menu-row">

							<div class="inputGroup">
								<input name="keywords"
											class="js-uix_syncValue"
											data-uixsync="search"
											placeholder="' . 'Search' . $__vars['xf']['language']['ellipsis'] . '"
											aria-label="' . 'Search' . '"
											type="hidden" />
								';
				$__compilerTemp6 = array(array(
					'value' => '',
					'label' => 'Everywhere',
					'_type' => 'option',
				));
				if ($__templater->isTraversable($__vars['searchConstraints'])) {
					foreach ($__vars['searchConstraints'] AS $__vars['constraintName'] => $__vars['constraint']) {
						$__compilerTemp6[] = array(
							'value' => $__templater->filter($__vars['constraint'], array(array('json', array()),), false),
							'label' => $__templater->escape($__vars['constraintName']),
							'_type' => 'option',
						);
					}
				}
				$__compilerTemp4 .= $__templater->formSelect(array(
					'name' => 'constraints',
					'class' => 'js-quickSearch-constraint',
					'aria-label' => 'Search within',
				), $__compilerTemp6) . '
							</div>
						</div>
					';
			} else {
				$__compilerTemp4 .= '
						<input name="keywords"
							class="js-uix_syncValue"
							data-uixsync="search"
							placeholder="' . 'Search' . $__vars['xf']['language']['ellipsis'] . '"
							aria-label="' . 'Search' . '"
							type="hidden" />
					';
			}
			$__compilerTemp4 .= '

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
	' . $__compilerTemp4 . '
');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

' . '

' . '

';
	if (!$__templater->fn('property', array('uix_removeWhatsNewButtons', ), false)) {
		$__finalCompiled .= '
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
';
	}
	$__finalCompiled .= '

' . '

' . '

';
	$__compilerTemp7 = '';
	if ($__vars['template'] != 'login') {
		$__compilerTemp7 .= '
		';
		if ($__templater->fn('property', array('uix_loginStyle', ), false) == 'dropdown') {
			$__compilerTemp7 .= '
			<a href="' . $__templater->fn('link', array('login', ), true) . '" class="p-navgroup-link p-navgroup-link--textual p-navgroup-link--logIn" data-xf-click="menu">
				<i></i>
				<span class="p-navgroup-linkText">' . 'Log in' . '</span>
			</a>
			<div class="menu menu--structural menu--medium" data-menu="menu" aria-hidden="true" data-href="' . $__templater->fn('link', array('login', ), true) . '"></div>
		';
		} else if ($__templater->fn('property', array('uix_loginStyle', ), false) == 'modal') {
			$__compilerTemp7 .= '
			<a href="' . $__templater->fn('link', array('login', ), true) . '" class="p-navgroup-link u-ripple p-navgroup-link--textual p-navgroup-link--logIn" data-xf-click="overlay" data-follow-redirects="on">
				<i></i>
				<span class="p-navgroup-linkText">' . 'Log in' . '</span>
			</a>
		';
		} else if ($__templater->fn('property', array('uix_loginStyle', ), false) == 'link') {
			$__compilerTemp7 .= '
			<a href="' . $__templater->fn('link', array('login', ), true) . '" class="p-navgroup-link u-ripple p-navgroup-link--textual p-navgroup-link--logIn" data-follow-redirects="on">
				<i></i>
				<span class="p-navgroup-linkText">' . 'Log in' . '</span>
			</a>
		';
		} else if ($__templater->fn('property', array('uix_loginStyle', ), false) == 'slidingPanel') {
			$__compilerTemp7 .= '
			<a href="' . $__templater->fn('link', array('login', ), true) . '" id="uix_loginPanel--trigger" class="p-navgroup-link u-ripple p-navgroup-link--textual p-navgroup-link--logIn" rel="nofollow" data-follow-redirects="on">
				<i></i>
				<span class="p-navgroup-linkText">' . 'Log in' . '</span>
			</a>
		';
		}
		$__compilerTemp7 .= '
	';
	}
	$__compilerTemp8 = '';
	if ($__vars['template'] != 'register_form') {
		$__compilerTemp8 .= '
		';
		if ($__templater->fn('property', array('uix_loginStyle', ), false) == 'modal') {
			$__compilerTemp8 .= '
			<a href="' . $__templater->fn('link', array('register', ), true) . '" class="p-navgroup-link u-ripple p-navgroup-link--textual p-navgroup-link--register" data-xf-click="overlay" data-follow-redirects="on">
				<i></i>
				<span class="p-navgroup-linkText">' . 'Register' . '</span>
			</a>
		';
		} else {
			$__compilerTemp8 .= '
			<a href="' . $__templater->fn('link', array('register', ), true) . '" class="p-navgroup-link u-ripple p-navgroup-link--textual p-navgroup-link--register" data-follow-redirects="on">
				<i></i>
				<span class="p-navgroup-linkText">' . 'Register' . '</span>
			</a>
		';
		}
		$__compilerTemp8 .= '
	';
	}
	$__vars['uix_loginTabs__component'] = $__templater->preEscaped('
	' . $__compilerTemp7 . '
	' . $__compilerTemp8 . '
');
	$__finalCompiled .= '

' . '

' . '

';
	if (!$__vars['uix_hideNavigation']) {
		$__finalCompiled .= '
';
		$__compilerTemp9 = '';
		if (($__vars['xf']['visitor']['user_state'] == 'rejected') OR ($__vars['xf']['visitor']['user_state'] == 'disabled')) {
			$__compilerTemp9 .= '
		<a href="' . $__templater->fn('link', array('account', ), true) . '"
		   class="p-navgroup-link u-ripple p-navgroup-link--iconic p-navgroup-link--user">
			' . $__templater->fn('avatar', array($__vars['xf']['visitor'], 'xxs', false, array(
				'href' => '',
			))) . '
			<span class="p-navgroup-linkText">' . $__templater->escape($__vars['xf']['visitor']['username']) . '</span>
		</a>

		<a href="' . $__templater->fn('link', array('logout', null, array('t' => $__templater->fn('csrf_token', array(), false), ), ), true) . '" class="p-navgroup-link">
			<span class="p-navgroup-linkText">' . '<b>Log out</b>' . '</span>
		</a>
		';
		} else {
			$__compilerTemp9 .= '
		<a href="' . $__templater->fn('link', array('account', ), true) . '"
			class="p-navgroup-link u-ripple p-navgroup-link--iconic p-navgroup-link--user"
			data-xf-click="menu"
			data-xf-key="' . $__templater->filter('m', array(array('for_attr', array()),), true) . '"
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
		   data-xf-key="' . $__templater->filter(',', array(array('for_attr', array()),), true) . '"
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
					';
			if ($__templater->method($__vars['xf']['visitor'], 'canStartConversation', array())) {
				$__compilerTemp9 .= '
						<span class="menu-footer-opposite">
							<a href="' . $__templater->fn('link', array('conversations/add', ), true) . '">' . 'Start a new conversation' . '</a>
						</span>
					';
			}
			$__compilerTemp9 .= '
				</div>
			</div>
		</div>

		<a href="' . $__templater->fn('link', array('account/alerts', ), true) . '"
		   class="p-navgroup-link u-ripple p-navgroup-link--iconic p-navgroup-link--alerts js-badge--alerts badgeContainer' . ($__vars['xf']['visitor']['alerts_unread'] ? ' badgeContainer--highlighted' : '') . '"
		   data-badge="' . $__templater->filter($__vars['xf']['visitor']['alerts_unread'], array(array('number', array()),), true) . '"
		   data-xf-click="menu"
		   data-xf-key="' . $__templater->filter('.', array(array('for_attr', array()),), true) . '"
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
	';
		}
		$__vars['uix_userTabs__component'] = $__templater->preEscaped('
	' . $__compilerTemp9 . '
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
	$__compilerTemp10 = '';
	if ((!$__vars['uix_hidePageTitle']) OR ($__vars['pageAction'] AND ((!$__templater->fn('property', array('uix_pageActionBreadcrumb', ), false)) AND ((!$__templater->fn('property', array('uix_removePageAction', ), false)) OR ((!$__templater->fn('in_array', array($__vars['template'], array('forum_list', 'forum_new_posts', 'thtopics_forum_newest_posts', 'thtrending_trending_view', 'thtopics_forum_latest_threads', 'thtopics_topic_list', ), ), false))))))) {
		$__compilerTemp10 .= '
		';
		$__compilerTemp11 = '';
		$__compilerTemp11 .= '
						';
		$__compilerTemp12 = '';
		$__compilerTemp12 .= '
									';
		$__compilerTemp13 = '';
		$__compilerTemp13 .= '
												';
		if (!$__vars['noH1']) {
			$__compilerTemp13 .= '
													<h1 class="p-title-value">' . $__templater->escape($__vars['h1']) . '</h1>
												';
		}
		$__compilerTemp13 .= '
											';
		if (strlen(trim($__compilerTemp13)) > 0) {
			$__compilerTemp12 .= '
										<div class="p-title ' . ($__vars['noH1'] ? 'p-title--noH1' : '') . '">
											' . $__compilerTemp13 . '
										</div>
									';
		}
		$__compilerTemp12 .= '

									';
		if (!$__templater->test($__vars['description'], 'empty', array())) {
			$__compilerTemp12 .= '
										<div class="p-description">' . $__templater->escape($__vars['description']) . '</div>
									';
		}
		$__compilerTemp12 .= '
								';
		if (strlen(trim($__compilerTemp12)) > 0) {
			$__compilerTemp11 .= '
							<div class="uix_headerInner">
								' . $__compilerTemp12 . '
							</div>
						';
		}
		$__compilerTemp11 .= '
						';
		$__compilerTemp14 = '';
		$__compilerTemp14 .= '
									';
		if ((!$__templater->fn('property', array('uix_pageActionBreadcrumb', ), false)) AND ((!$__templater->fn('property', array('uix_removePageAction', ), false)) OR ($__vars['template'] != 'forum_list'))) {
			$__compilerTemp14 .= '
										';
			$__compilerTemp15 = '';
			$__compilerTemp15 .= (isset($__templater->pageParams['pageAction']) ? $__templater->pageParams['pageAction'] : '');
			if (strlen(trim($__compilerTemp15)) > 0) {
				$__compilerTemp14 .= '
											<div class="p-title-pageAction">' . $__compilerTemp15 . '</div>
										';
			}
			$__compilerTemp14 .= '
									';
		}
		$__compilerTemp14 .= '
									' . $__templater->callMacro(null, 'uix_sidebarTrigger__component', array(
			'content' => $__vars['uix_sidebarTrigger__content'],
			'location' => 'titlebar',
		), $__vars) . '
								';
		if (strlen(trim($__compilerTemp14)) > 0) {
			$__compilerTemp11 .= '
							<div class="uix_headerInner--opposite">
								' . $__compilerTemp14 . '
							</div>
						';
		}
		$__compilerTemp11 .= '
					';
		if (!$__templater->test($__vars['headerHtml'], 'empty', array())) {
			$__compilerTemp10 .= '
			<div class="p-body-header">
				<div class="pageContent">
					' . $__templater->filter($__vars['headerHtml'], array(array('raw', array()),), true) . '
				</div>
			</div>
		';
		} else if (strlen(trim($__compilerTemp11)) > 0) {
			$__compilerTemp10 .= '
			<div class="p-body-header">
				<div class="pageContent">
					' . $__compilerTemp11 . '
				</div>
			</div>
		';
		}
		$__compilerTemp10 .= '
	';
	}
	$__vars['uix_titlebar__component'] = $__templater->preEscaped('
	' . $__compilerTemp10 . '
');
	$__finalCompiled .= '

' . '

' . '

';
	$__compilerTemp16 = '';
	if ($__vars['sidebar']) {
		$__compilerTemp16 .= '
	<div uix_component="MainSidebar" class="p-body-sidebar">
		<div data-ocm-class="offCanvasMenu-backdrop"></div>
		<div class="uix_sidebarInner' . ($__templater->fn('property', array('uix_stickySidebar', ), false) ? ' uix_stickyBodyElement' : '') . '">
			<div class="uix_sidebar--scroller">
				' . $__templater->callAdsMacro('container_sidebar_above', array(), $__vars) . '
				';
		if ($__templater->isTraversable($__vars['sidebar'])) {
			foreach ($__vars['sidebar'] AS $__vars['sidebarHtml']) {
				$__compilerTemp16 .= '
					' . $__templater->escape($__vars['sidebarHtml']) . '
				';
			}
		}
		$__compilerTemp16 .= '
				' . $__templater->callAdsMacro('container_sidebar_below', array(), $__vars) . '
			</div>
		</div>
	</div>
';
	}
	$__vars['uix_sidebar__component'] = $__templater->preEscaped('
' . $__compilerTemp16 . '
');
	$__finalCompiled .= '

' . '

' . '

';
	$__compilerTemp17 = '';
	if ($__templater->fn('property', array('publicLogoUrl', ), false) OR $__templater->fn('property', array('publicLogoUrl2x', ), false)) {
		$__compilerTemp17 .= '
				<img src="' . $__templater->fn('base_url', array($__templater->fn('property', array('publicLogoUrl', ), false), ), true) . '"
					 alt="' . $__templater->escape($__vars['xf']['options']['boardTitle']) . '"
					 ' . ($__templater->fn('property', array('publicLogoUrl2x', ), false) ? (('srcset="' . $__templater->fn('base_url', array($__templater->fn('property', array('publicLogoUrl2x', ), false), ), true)) . ' 2x"') : '') . ' />
			';
	} else {
		$__compilerTemp17 .= '
				<h2 class="uix_logo--text">';
		if ($__templater->fn('property', array('uix_logoIcon', ), false)) {
			$__compilerTemp17 .= '<i class="' . $__templater->fn('property', array('uix_logoIcon', ), true) . ' uix_logoIcon"></i>';
		}
		$__compilerTemp17 .= $__templater->fn('property', array('uix_logoText', ), true) . '</h2>
			';
	}
	$__compilerTemp18 = '';
	if ($__templater->fn('property', array('uix_logoSmall', ), false)) {
		$__compilerTemp18 .= '
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
			' . $__compilerTemp17 . '
		</a>
		' . $__compilerTemp18 . '
	</div>
');
	$__finalCompiled .= '

' . '

' . '

';
	$__compilerTemp19 = '';
	$__compilerTemp20 = '';
	$__compilerTemp20 .= '
					';
	$__compilerTemp21 = '';
	$__compilerTemp21 .= '
									';
	if ($__vars['xf']['visitor']['is_moderator'] AND $__vars['xf']['session']['unapprovedCounts']['total']) {
		$__compilerTemp21 .= '
										<a href="' . $__templater->fn('link', array('approval-queue', ), true) . '" class="p-staffBar-link badgeContainer badgeContainer--highlighted" data-badge="' . $__templater->filter($__vars['xf']['session']['unapprovedCounts']['total'], array(array('number', array()),), true) . '">
											' . 'Approval queue' . '
										</a>
									';
	}
	$__compilerTemp21 .= '

									' . $__templater->includeTemplate('mjst_moderator_bar', $__vars);
	if ($__vars['xf']['visitor']['is_moderator'] AND ((!$__vars['xf']['options']['reportIntoForumId']) AND $__vars['xf']['session']['reportCounts']['total'])) {
		$__compilerTemp21 .= '
										<a href="' . $__templater->fn('link', array('reports', ), true) . '"
											class="p-staffBar-link badgeContainer badgeContainer--visible ' . ((($__vars['xf']['session']['reportCounts']['total'] AND ($__vars['xf']['session']['reportCounts']['lastBuilt'] > $__vars['xf']['session']['reportLastRead'])) OR $__vars['xf']['session']['reportCounts']['assigned']) ? ' badgeContainer--highlighted' : '') . '"
											data-badge="' . ($__vars['xf']['session']['reportCounts']['assigned'] ? (($__templater->filter($__vars['xf']['session']['reportCounts']['assigned'], array(array('number', array()),), true) . ' / ') . $__templater->filter($__vars['xf']['session']['reportCounts']['total'], array(array('number', array()),), true)) : $__templater->filter($__vars['xf']['session']['reportCounts']['total'], array(array('number', array()),), true)) . '"
											title="' . ($__vars['xf']['session']['reportCounts']['lastBuilt'] ? (('Last report update' . $__vars['xf']['language']['label_separator'] . ' ') . $__templater->fn('date_time', array($__vars['xf']['session']['reportCounts']['lastBuilt'], ), true)) : '') . '">
											' . 'Reports' . '
										</a>
									';
	}
	$__compilerTemp21 .= '

									';
	$__compilerTemp22 = '';
	$__compilerTemp22 .= '
												' . '
												';
	if ($__vars['xf']['visitor']['is_moderator']) {
		$__compilerTemp22 .= '
													<a href="' . $__templater->fn('link', array('approval-queue', ), true) . '" class="menu-linkRow">' . 'Approval queue' . '</a>
												';
	}
	$__compilerTemp22 .= '
												';
	if ($__vars['xf']['visitor']['is_moderator'] AND (!$__vars['xf']['options']['reportIntoForumId'])) {
		$__compilerTemp22 .= '
													<a href="' . $__templater->fn('link', array('reports', ), true) . '" class="menu-linkRow" title="' . ($__vars['xf']['session']['reportCounts']['lastBuilt'] ? ('Last report update: ' . $__templater->fn('date_time', array($__vars['xf']['session']['reportCounts']['lastBuilt'], ), true)) : '') . '">' . 'Reports' . '</a>
												';
	}
	$__compilerTemp22 .= '
												' . '
												';
	if (strlen(trim($__compilerTemp22)) > 0) {
		$__compilerTemp21 .= '
										<a class="p-staffBar-link menuTrigger" data-xf-key="alt+m" data-xf-click="menu" role="button" tabindex="0" aria-expanded="false" aria-haspopup="true">' . '<font size="3"><i class="fa fa-gavel"></i></font>' . '</a>
										<div class="menu" data-menu="menu" aria-hidden="true">
											<div class="menu-content">
												<h4 class="menu-header">' . 'Staff tools' . '</h4>
												' . $__compilerTemp22 . '
											</div>
										</div>
									';
	}
	$__compilerTemp21 .= '

									';
	if ($__vars['xf']['visitor']['is_admin']) {
		$__compilerTemp21 .= '
										<a href="' . $__templater->fn('base_url', array('admin.php', ), true) . '" class="p-staffBar-link" target="_blank">' . '<font size="3"><i class="fa fa-cog"></i></font>' . '</a>
									';
	}
	$__compilerTemp21 .= '
' . $__templater->includeTemplate('lau_staff_bar', $__vars) . '

									';
	$__compilerTemp23 = '';
	$__compilerTemp23 .= '
													' . '
													';
	if ($__vars['xf']['visitor']['is_admin']) {
		$__compilerTemp23 .= '
														<a href="' . $__templater->fn('base_url', array('admin.php', ), true) . '" target="_blank" class="menu-linkRow">' . '<font size="3"><i class="fa fa-cog"></i></font>' . '</a>
													';
	}
	$__compilerTemp23 .= '
													' . '
													';
	if ($__vars['xf']['visitor']['is_moderator']) {
		$__compilerTemp23 .= '
														<a href="' . $__templater->fn('link', array('approval-queue', ), true) . '" class="menu-linkRow">' . 'Approval queue' . '</a>
													';
	}
	$__compilerTemp23 .= '
													';
	if ($__vars['xf']['visitor']['is_moderator'] AND (!$__vars['xf']['options']['reportIntoForumId'])) {
		$__compilerTemp23 .= '
														<a href="' . $__templater->fn('link', array('reports', ), true) . '" class="menu-linkRow" title="' . ($__vars['xf']['session']['reportCounts']['lastBuilt'] ? ('Last report update: ' . $__templater->fn('date_time', array($__vars['xf']['session']['reportCounts']['lastBuilt'], ), true)) : '') . '">' . 'Reports' . '</a>
													';
	}
	$__compilerTemp23 .= '
													';
	if ($__vars['xf']['visitor']['is_moderator'] AND $__vars['xf']['session']['unapprovedCounts']['total']) {
		$__compilerTemp23 .= '
														<a href="' . $__templater->fn('link', array('approval-queue', ), true) . '" class="menu-linkRow badgeContainer badgeContainer--highlighted" data-badge="' . $__templater->filter($__vars['xf']['session']['unapprovedCounts']['total'], array(array('number', array()),), true) . '">
															' . 'Approval queue' . '
														</a>
													';
	}
	$__compilerTemp23 .= '

													' . $__templater->includeTemplate('mjst_moderator_bar', $__vars);
	if ($__vars['xf']['visitor']['is_moderator'] AND ((!$__vars['xf']['options']['reportIntoForumId']) AND $__vars['xf']['session']['reportCounts']['total'])) {
		$__compilerTemp23 .= '
														<a href="' . $__templater->fn('link', array('reports', ), true) . '"
															class="menu-linkRow badgeContainer badgeContainer--visible ' . ((($__vars['xf']['session']['reportCounts']['total'] AND ($__vars['xf']['session']['reportCounts']['lastBuilt'] > $__vars['xf']['session']['reportLastRead'])) OR $__vars['xf']['session']['reportCounts']['assigned']) ? ' badgeContainer--highlighted' : '') . '"
															data-badge="' . ($__vars['xf']['session']['reportCounts']['assigned'] ? (($__templater->filter($__vars['xf']['session']['reportCounts']['assigned'], array(array('number', array()),), true) . ' / ') . $__templater->filter($__vars['xf']['session']['reportCounts']['total'], array(array('number', array()),), true)) : $__templater->filter($__vars['xf']['session']['reportCounts']['total'], array(array('number', array()),), true)) . '"
															title="' . ($__vars['xf']['session']['reportCounts']['lastBuilt'] ? ('Last report update' . $__templater->fn('date_time', array($__vars['xf']['session']['reportCounts']['lastBuilt'], ), true)) : '') . '">
															' . 'Reports' . '
														</a>
													';
	}
	$__compilerTemp23 .= '
												';
	if (strlen(trim($__compilerTemp23)) > 0) {
		$__compilerTemp21 .= '
										<a href="' . $__templater->fn('base_url', array('admin.php', ), true) . '" target="_blank" class="p-staffBar-link menuTrigger uix_adminTrigger" data-xf-click="menu" role="button" tabindex="0" aria-expanded="false" aria-haspopup="true">
											';
		if ($__vars['xf']['visitor']['is_admin']) {
			$__compilerTemp21 .= '
												' . '<font size="3"><i class="fa fa-cog"></i></font>' . '
											';
		} else {
			$__compilerTemp21 .= '
												' . '<font size="3"><i class="fa fa-gavel"></i></font>' . '
											';
		}
		$__compilerTemp21 .= '
										</a>
										<div class="menu" data-menu="menu" aria-hidden="true">
											<div class="menu-content">
												<h4 class="menu-header">' . 'Staff tools' . '</h4>
												' . $__compilerTemp23 . '
											</div>
										</div>
									';
	}
	$__compilerTemp21 .= '
								';
	if (strlen(trim($__compilerTemp21)) > 0) {
		$__compilerTemp20 .= '
						' . '
						';
		$__vars['uix_alwaysStaffBar'] = '1';
		$__compilerTemp20 .= '
						<div class="p-staffBar-inner hScroller" data-xf-init="h-scroller">
							<div class="hScroller-scroll">
								' . $__compilerTemp21 . '
							</div>
						</div>
					';
	}
	$__compilerTemp20 .= '

					';
	$__compilerTemp24 = '';
	$__compilerTemp24 .= '
								' . $__templater->callMacro(null, 'uix_visitorTabs__component', array(
		'socialMediaContent' => $__vars['uix_socialMediaContent'],
		'whatsNewContent' => $__vars['uix_whatsNew__component'],
		'searchContent' => $__vars['uix_search__component'],
		'loginTabsContent' => $__vars['uix_loginTabs__component'],
		'visitorContent' => $__vars['uix_userTabs__component'],
		'location' => 'staffBar',
	), $__vars) . '
							';
	if (strlen(trim($__compilerTemp24)) > 0) {
		$__compilerTemp20 .= '
						<div class="p-nav-opposite">
							';
		if ($__templater->fn('property', array('uix_staffBarBreakpoint', ), false) != '100%') {
			$__compilerTemp20 .= '
								';
			$__vars['uix_responsiveStaffBar'] = '1';
			$__compilerTemp20 .= '
							';
		} else {
			$__compilerTemp20 .= '
								';
			$__vars['uix_alwaysStaffBar'] = '1';
			$__compilerTemp20 .= '
							';
		}
		$__compilerTemp20 .= '
							' . $__compilerTemp24 . '
						</div>
					';
	}
	$__compilerTemp20 .= '

				';
	if (strlen(trim($__compilerTemp20)) > 0) {
		$__compilerTemp19 .= '
		<div class="p-staffBar ';
		if ($__templater->fn('property', array('uix_stickyStaffBar', ), false)) {
			$__compilerTemp19 .= 'uix_stickyBar';
		}
		$__compilerTemp19 .= '">
			<div class="pageContent">
				' . $__compilerTemp20 . '
			</div>
		</div>
	';
	}
	$__vars['uix_staffbar__component'] = $__templater->preEscaped('
	' . $__compilerTemp19 . '
');
	$__finalCompiled .= '

';
	if ((!$__vars['uix_alwaysStaffBar']) AND $__vars['uix_responsiveStaffBar']) {
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
	if (!$__vars['uix_hideNavigation']) {
		$__finalCompiled .= '
';
		$__compilerTemp25 = '';
		$__compilerTemp26 = '';
		$__compilerTemp26 .= '
					';
		if (!$__templater->test($__vars['selectedNavChildren'], 'empty', array()) AND ($__templater->fn('property', array('uix_viewportWidthRemoveSubNav', ), false) != '100%')) {
			$__compilerTemp26 .= '
						';
			$__vars['uix_subNavContentStatic'] = '1';
			$__compilerTemp26 .= '
						';
			$__vars['uix_htmlClasses'] = $__templater->preEscaped($__templater->escape($__vars['uix_htmlClasses']) . ' uix_hasSectionLinks');
			$__compilerTemp26 .= '
						<div class="p-sectionLinks-inner hScroller" data-xf-init="h-scroller">
							<div class="hScroller-scroll">
								<ul class="p-sectionLinks-list">
									';
			$__vars['i'] = 0;
			if ($__templater->isTraversable($__vars['selectedNavChildren'])) {
				foreach ($__vars['selectedNavChildren'] AS $__vars['navId'] => $__vars['navEntry']) {
					$__vars['i']++;
					$__compilerTemp26 .= '
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
			$__compilerTemp26 .= '
								</ul>
							</div>
						</div>
					';
		}
		$__compilerTemp26 .= '
					';
		$__compilerTemp27 = '';
		$__compilerTemp27 .= '
								';
		$__compilerTemp28 = '';
		$__compilerTemp28 .= '
										' . $__templater->callMacro(null, 'uix_visitorTabs__component', array(
			'socialMediaContent' => $__vars['uix_socialMediaContent'],
			'whatsNewContent' => $__vars['uix_whatsNew__component'],
			'searchContent' => $__vars['uix_search__component'],
			'loginTabsContent' => $__vars['uix_loginTabs__component'],
			'visitorContent' => $__vars['uix_userTabs__component'],
			'location' => 'tablinks',
		), $__vars) . '
									';
		if (strlen(trim($__compilerTemp28)) > 0) {
			$__compilerTemp27 .= '
									';
			$__vars['uix_subNavContentStatic'] = '1';
			$__compilerTemp27 .= '
									' . $__compilerTemp28 . '
								';
		}
		$__compilerTemp27 .= '
								' . $__templater->callMacro(null, 'uix_sidebarTrigger__component', array(
			'content' => $__vars['uix_sidebarTrigger__content'],
			'location' => 'sectionLinks',
		), $__vars) . '
							';
		if (strlen(trim($__compilerTemp27)) > 0) {
			$__compilerTemp26 .= '
						<div class="p-nav-opposite">
							' . $__compilerTemp27 . '
						</div>
					';
		}
		$__compilerTemp26 .= '
				';
		if (strlen(trim($__compilerTemp26)) > 0) {
			$__compilerTemp25 .= '
		<div class="p-sectionLinks">
			<div class="pageContent">
				' . $__compilerTemp26 . '
			</div>
		</div>
	';
		} else if ($__vars['selectedNavEntry']) {
			$__compilerTemp25 .= '
		<div class="p-sectionLinks p-sectionLinks--empty"></div>
	';
		}
		$__vars['subNavHtml'] = $__templater->preEscaped('
	' . $__compilerTemp25 . '
');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

' . '

';
	$__compilerTemp29 = '';
	if ($__templater->fn('property', array('uix_stickySidebar', ), false)) {
		$__compilerTemp29 .= ' uix_stickyBodyElement';
	}
	$__compilerTemp30 = '';
	$__compilerTemp31 = '';
	$__compilerTemp31 .= '
					';
	$__vars['i'] = 0;
	if ($__templater->isTraversable($__vars['navTree'])) {
		foreach ($__vars['navTree'] AS $__vars['navSection'] => $__vars['navEntry']) {
			if (($__vars['navSection'] != $__vars['xf']['app']['defaultNavigationId'])) {
				$__vars['i']++;
				$__compilerTemp31 .= '
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
	$__compilerTemp31 .= '
					';
	if (strlen(trim($__compilerTemp31)) > 0) {
		$__compilerTemp30 .= '
				<ul class="uix_sidebarNavList js-offCanvasNavSource">
					' . $__compilerTemp31 . '
				</ul>
				';
	}
	$__compilerTemp32 = '';
	if ($__vars['xf']['visitor']['user_id']) {
		$__compilerTemp32 .= '
					<ul class="uix_sidebarNavList">
						<li><div class="p-navEl u-ripple ' . (($__vars['uix_myAccountLinks'] == 'profile') ? 'is-selected' : '') . '"><div class="p-navEl__inner"><a data-nav-id="profile" href="' . $__templater->fn('link', array('members', $__vars['xf']['visitor'], ), true) . '" class="p-navEl-link">' . 'Profile' . '</a></div></div></li>
						<li><div class="p-navEl u-ripple ' . (($__vars['uix_myAccountLinks'] == 'alerts') ? 'is-selected' : '') . '"><div class="p-navEl__inner"><a data-nav-id="alerts" href="' . $__templater->fn('link', array('account/alerts', ), true) . '" class="p-navEl-link">' . 'Alerts' . '</a></div></div></li>
						<li><div class="p-navEl u-ripple ' . (($__vars['uix_myAccountLinks'] == 'settings') ? 'is-selected' : '') . '"><div class="p-navEl__inner"><a data-nav-id="settings" href="' . $__templater->fn('link', array('account/preferences', ), true) . '" class="p-navEl-link">' . 'Settings' . '</a></div></div></li>
					</ul>
				';
	}
	$__compilerTemp33 = '';
	$__compilerTemp34 = '';
	$__compilerTemp34 .= '
							' . $__templater->filter($__vars['uix_sidebarNavWidgets'], array(array('raw', array()),), true) . '
						';
	if (strlen(trim($__compilerTemp34)) > 0) {
		$__compilerTemp33 .= '
					<div class="uix_sidebarNav__inner__widgets">
						' . $__compilerTemp34 . '
					</div>
				';
	}
	$__vars['uix_sidebarNav__component'] = $__templater->preEscaped('
	<div class="uix_sidebarNav">
		<div class="uix_sidebarNav__inner ' . $__compilerTemp29 . '">
			<div class="uix_sidebar--scroller">
				' . $__compilerTemp30 . '
				' . '
				' . $__compilerTemp32 . '
				' . $__compilerTemp33 . '
			</div>
		</div>
	</div>
');
	$__finalCompiled .= '

' . '

' . '

' . '

' . '

' . '

' . '

';
	if (!$__vars['uix_hideBreadcrumb']) {
		$__finalCompiled .= '
	';
		$__vars['position'] = 0;
		$__vars['rootBreadcrumb'] = $__vars['navTree'][$__vars['xf']['options']['rootBreadcrumb']];
		$__compilerTemp35 = '';
		if ($__vars['rootBreadcrumb'] AND ($__vars['rootBreadcrumb']['href'] != $__vars['xf']['uri'])) {
			$__compilerTemp35 .= '
			';
			$__vars['position'] = ($__vars['position'] + 1);
			$__compilerTemp35 .= '
			' . $__templater->callMacro(null, 'crumb', array(
				'position' => $__vars['position'],
				'href' => $__vars['rootBreadcrumb']['href'],
				'value' => $__vars['rootBreadcrumb']['title'],
			), $__vars) . '
		';
		}
		$__compilerTemp36 = '';
		if ($__vars['selectedNavEntry'] AND ($__vars['selectedNavEntry']['href'] AND (($__vars['selectedNavEntry']['href'] != $__vars['xf']['uri']) AND ($__vars['selectedNavEntry']['href'] != $__vars['rootBreadcrumb']['href'])))) {
			$__compilerTemp36 .= '
			';
			$__vars['position'] = ($__vars['position'] + 1);
			$__compilerTemp36 .= '
			' . $__templater->callMacro(null, 'crumb', array(
				'position' => $__vars['position'],
				'href' => $__vars['selectedNavEntry']['href'],
				'value' => $__vars['selectedNavEntry']['title'],
			), $__vars) . '
		';
		}
		$__compilerTemp37 = '';
		if ($__templater->isTraversable($__vars['breadcrumbs'])) {
			foreach ($__vars['breadcrumbs'] AS $__vars['breadcrumb']) {
				if ($__vars['breadcrumb']['href'] != $__vars['xf']['uri']) {
					$__compilerTemp37 .= '
			';
					$__vars['position'] = ($__vars['position'] + 1);
					$__compilerTemp37 .= '
			' . $__templater->callMacro(null, 'crumb', array(
						'position' => $__vars['position'],
						'href' => $__vars['breadcrumb']['href'],
						'value' => $__vars['breadcrumb']['value'],
					), $__vars) . '
		';
				}
			}
		}
		$__vars['uix_breadcrumbCrumbContent'] = $__templater->preEscaped('
		' . '' . '
		
		' . '' . '
		' . $__compilerTemp35 . '

		' . $__compilerTemp36 . '
		' . $__compilerTemp37 . '
	');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	$__vars['breadcrumbCount'] = $__templater->preEscaped($__templater->filter($__templater->fn('count', array($__vars['breadcrumbs'], ), false), array(array('default', array(0, )),), true));
	$__finalCompiled .= '
';
	$__vars['navEntryCount'] = $__templater->preEscaped((($__vars['selectedNavEntry'] == null) ? 0 : 1));
	$__finalCompiled .= '

';
	if ($__vars['uix_breadcrumbCrumbContent'] AND (((($__templater->filter($__vars['navEntryCount'], array(array('escape', array()),), false) + $__templater->filter($__vars['breadcrumbCount'], array(array('escape', array()),), false)) != 1)) OR (!$__templater->fn('property', array('uix_hideSingleCrumb', ), false)))) {
		$__finalCompiled .= '
	';
		$__vars['uix_breadcrumbHasCrumbs'] = '1';
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

' . '

' . '


' . '

';
	$__vars['uix_topBreadcrumb__component'] = $__templater->preEscaped('
	' . $__templater->callAdsMacro('container_breadcrumb_top_above', array(), $__vars) . '
	' . $__templater->callMacro(null, 'breadcrumbs', array(
		'crumbContent' => $__vars['uix_breadcrumbCrumbContent'],
		'breadcrumbHasCrumbs' => $__vars['uix_breadcrumbHasCrumbs'],
	), $__vars) . '
	' . $__templater->callAdsMacro('container_breadcrumb_top_below', array(), $__vars) . '
');
	$__finalCompiled .= '

' . '

' . '

';
	$__compilerTemp38 = '';
	if (!$__templater->fn('property', array('uix_removeBottomBreadcrumb', ), false)) {
		$__compilerTemp38 .= '
		' . $__templater->callAdsMacro('container_breadcrumb_bottom_above', array(), $__vars) . '
		' . $__templater->callMacro(null, 'breadcrumbs', array(
			'crumbContent' => $__vars['uix_breadcrumbCrumbContent'],
			'breadcrumbHasCrumbs' => $__vars['uix_breadcrumbHasCrumbs'],
			'variant' => 'bottom',
		), $__vars) . '
		' . $__templater->callAdsMacro('container_breadcrumb_bottom_below', array(), $__vars) . '
	';
	}
	$__vars['uix_bottomBreadcrumb__component'] = $__templater->preEscaped('
	' . $__compilerTemp38 . '
');
	$__finalCompiled .= '

' . '


' . '

';
	$__compilerTemp39 = '';
	if (!$__vars['uix_hideNotices']) {
		$__compilerTemp39 .= '
		';
		if ($__vars['notices']['block']) {
			$__compilerTemp39 .= '
			' . $__templater->callMacro('notice_macros', 'notice_list', array(
				'type' => 'block',
				'notices' => $__vars['notices']['block'],
			), $__vars) . '
		';
		}
		$__compilerTemp39 .= '

		';
		if ($__vars['notices']['scrolling']) {
			$__compilerTemp39 .= '
			' . $__templater->callMacro('notice_macros', 'notice_list', array(
				'type' => 'scrolling',
				'notices' => $__vars['notices']['scrolling'],
			), $__vars) . '
		';
		}
		$__compilerTemp39 .= '
	';
	}
	$__vars['uix_notices'] = $__templater->preEscaped('
	' . $__compilerTemp39 . '
');
	$__finalCompiled .= '

' . '

' . '

';
	$__compilerTemp40 = '';
	if ((!$__vars['uix_hideExtendedFooter']) AND $__templater->fn('property', array('uix_enableExtendedFooter', ), false)) {
		$__compilerTemp40 .= '
			' . $__templater->includeTemplate('uix_extendedFooter', $__vars) . '
		';
	}
	$__compilerTemp41 = '';
	$__compilerTemp42 = '';
	$__compilerTemp42 .= '
									';
	if (($__templater->fn('property', array('uix_pageWidthToggle', ), false) != 'disabled') AND $__vars['uix_canTogglePageWidth']) {
		$__compilerTemp42 .= '
										<li><a id="uix_widthToggle--trigger" data-xf-init="tooltip" title="' . 'Toggle width' . '" >' . $__templater->callMacro('uix_icons.less', 'icon', array(
			'icon' => 'collapse',
		), $__vars) . '</a></li>
									';
	}
	$__compilerTemp42 .= '
									';
	if ($__templater->method($__vars['xf']['visitor'], 'canChangeStyle', array()) AND (!$__templater->fn('property', array('uix_hideStyleChoose', ), false))) {
		$__compilerTemp42 .= '
										<li><a href="' . $__templater->fn('link', array('misc/style', ), true) . '" data-xf-click="overlay" data-xf-init="tooltip" title="' . 'Style chooser' . '" rel="nofollow">' . $__templater->escape($__vars['xf']['style']['title']) . '</a></li>
									';
	}
	$__compilerTemp42 .= '
									';
	if ($__templater->method($__vars['xf']['visitor'], 'canChangeLanguage', array())) {
		$__compilerTemp42 .= '
										<li><a href="' . $__templater->fn('link', array('misc/language', ), true) . '" data-xf-click="overlay" data-xf-init="tooltip" title="' . 'Language chooser' . '" rel="nofollow"><i class="fa fa-globe" aria-hidden="true"></i> ' . $__templater->escape($__vars['xf']['language']['title']) . '</a></li>
									';
	}
	$__compilerTemp42 .= '
								';
	if (strlen(trim($__compilerTemp42)) > 0) {
		$__compilerTemp41 .= '
						<div class="p-footer-row-main">
							<ul class="p-footer-linkList p-footer-choosers">
								' . $__compilerTemp42 . '
							</ul>
						</div>
					';
	}
	$__compilerTemp43 = '';
	if ($__templater->method($__vars['xf']['visitor'], 'canUseContactForm', array())) {
		$__compilerTemp43 .= '
							';
		if ($__vars['xf']['contactUrl']) {
			$__compilerTemp43 .= '
								<li><a href="' . $__templater->escape($__vars['xf']['contactUrl']) . '" data-xf-click="' . (($__vars['xf']['options']['contactUrl']['overlay'] OR ($__vars['xf']['options']['contactUrl']['type'] == 'default')) ? 'overlay' : '') . '">' . 'Contact us' . '</a></li>
							';
		}
		$__compilerTemp43 .= '
						';
	}
	$__compilerTemp44 = '';
	if ($__vars['xf']['tosUrl']) {
		$__compilerTemp44 .= '
							<li><a href="' . $__templater->escape($__vars['xf']['tosUrl']) . '">' . 'Terms and rules' . '</a></li>
						';
	}
	$__compilerTemp45 = '';
	if ($__vars['xf']['privacyPolicyUrl']) {
		$__compilerTemp45 .= '
							<li><a href="' . $__templater->escape($__vars['xf']['privacyPolicyUrl']) . '">' . 'Privacy policy' . '</a></li>
						';
	}
	$__compilerTemp46 = '';
	if ($__vars['xf']['helpPageCount']) {
		$__compilerTemp46 .= '
							<li><a href="' . $__templater->fn('link', array('help', ), true) . '">' . 'Help' . '</a></li>
						';
	}
	$__compilerTemp47 = '';
	if ($__vars['xf']['homePageUrl']) {
		$__compilerTemp47 .= '
							<li><a href="' . $__templater->escape($__vars['xf']['homePageUrl']) . '">' . 'Home' . '</a></li>
						';
	}
	$__compilerTemp48 = '';
	$__compilerTemp49 = '';
	$__compilerTemp49 .= '
								' . $__templater->fn('copyright') . '
								' . $__templater->callback('ThemeHouse\\Core\\Branding', 'renderStyleBranding', '', array());
	$__vars['thBrandingDisplayed'] = '1';
	$__compilerTemp49 .= '
								| <a href="http://www.mpm.pm/" title="XenForo Add-ons" target="_blank" class="u-concealed">Email Check by MPM.PM</a>

<div class="discord-copyright">
	<a href="https://xenforo.com/community/resources/6058/"
		target="_blank">Discord Integration</a> &copy; Jason Axelrod of
	<a href="https://8wayrun.com/" target="_blank">8WAYRUN</a>
</div>
							';
	if (strlen(trim($__compilerTemp49)) > 0) {
		$__compilerTemp48 .= '
						<div class="p-footer-copyright">
							' . $__compilerTemp49 . '
						</div>
					';
	}
	$__compilerTemp50 = '';
	$__compilerTemp51 = '';
	$__compilerTemp51 .= '
								' . $__templater->callMacro('debug_macros', 'debug', array(
		'controller' => $__vars['controller'],
		'action' => $__vars['actionMethod'],
		'template' => $__vars['template'],
	), $__vars) . '
							';
	if (strlen(trim($__compilerTemp51)) > 0) {
		$__compilerTemp50 .= '
						<div class="p-footer-debug">
							' . $__compilerTemp51 . '
						</div>
					';
	}
	$__vars['uix_footer'] = $__templater->preEscaped('
	<footer class="p-footer" id="footer">

		' . $__compilerTemp40 . '

		<div class="p-footer-inner">
			<div class="pageContent">
				<div class="p-footer-row">
					' . $__compilerTemp41 . '
				</div>
				<div class="p-footer-row-opposite">
					<ul class="p-footer-linkList">
						' . $__templater->includeTemplate('mjst_footer_link', $__vars) . $__compilerTemp43 . '

						' . $__compilerTemp44 . '

						' . $__compilerTemp45 . '

						' . $__compilerTemp46 . '

						' . $__compilerTemp47 . '

						<li><a href="#top" title="' . 'Top' . '" data-xf-click="scroll-to"><i class="fa fa-arrow-up" aria-hidden="true"></i></a></li>

						<li><a href="' . $__templater->fn('link', array('forums/index.rss', '-', ), true) . '" target="_blank" class="p-footer-rssLink" title="' . $__templater->filter('RSS', array(array('for_attr', array()),), true) . '"><span aria-hidden="true"><i class="fa fa-rss"></i><span class="u-srOnly">' . 'RSS' . '</span></span></a></li>
					</ul>
				</div>
			</div>
		</div>

		<div class="p-footer-copyrightRow">
			<div class="pageContent">
				<div class="uix_copyrightBlock">
					' . $__compilerTemp48 . '

					' . $__compilerTemp50 . '
				</div>
				' . '
				' . $__templater->callMacro(null, 'uix_socialMedia__component', array(
		'content' => $__vars['uix_socialMediaContent'],
		'location' => 'copyright',
	), $__vars) . '
			</div>
		</div>
	</footer>
');
	$__finalCompiled .= '

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
	<meta name="viewport" content="width=device-width, initial-scale=1, viewport-fit=cover">

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
	if (!$__vars['head']['meta_type']) {
		$__finalCompiled .= '
		' . $__templater->callMacro('metadata_macros', 'type', array(
			'type' => 'website',
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
	if (!$__vars['head']['meta_share_url']) {
		$__finalCompiled .= '
		' . $__templater->callMacro('metadata_macros', 'share_url', array(
			'shareUrl' => $__vars['xf']['fullUri'],
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
		<meta name="theme-color" content="' . $__templater->fn('parse_less_color', array($__templater->fn('property', array('metaThemeColor', ), false), ), true) . '" />
		<meta name="msapplication-TileColor" content="' . $__templater->fn('property', array('metaThemeColor', ), true) . '">
	';
	}
	$__finalCompiled .= '

	' . $__templater->callMacro('helper_js_global', 'head', array(
		'app' => 'public',
	), $__vars) . '

	';
	if ($__templater->fn('property', array('publicFaviconUrl', ), false)) {
		$__finalCompiled .= '
		<link rel="icon" type="image/png" href="' . $__templater->fn('base_url', array($__templater->fn('property', array('publicFaviconUrl', ), false), true, ), true) . '" sizes="32x32" />
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

	';
	$__vars['uix_stickyStaffBarHeight'] = '0';
	$__finalCompiled .= '

	';
	if ($__templater->fn('property', array('uix_stickyStaffBar', ), false) AND ($__vars['uix_responsiveStaffBar'] OR $__vars['uix_alwaysStaffBar'])) {
		$__finalCompiled .= '
		';
		$__vars['uix_stickyStaffBarHeight'] = $__templater->fn('property', array('uix_stickyStaffBarHeight', ), false);
		$__finalCompiled .= '
	';
	}
	$__finalCompiled .= '

	' . $__templater->includeTemplate('page_style', $__vars) . '
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
	$__compilerTemp52 = '';
	$__compilerTemp53 = '';
	$__compilerTemp53 .= '
							';
	if ($__templater->fn('property', array('uix_viewportShowLogoBlock', ), false) != '0') {
		$__compilerTemp53 .= '
								' . $__templater->callMacro(null, 'uix_logo__component', array(
			'content' => $__vars['uix_logo__component'],
		), $__vars) . '
							';
	}
	$__compilerTemp53 .= '

							';
	$__compilerTemp54 = '';
	$__compilerTemp54 .= '
										' . $__templater->callMacro(null, 'uix_visitorTabs__component', array(
		'socialMediaContent' => $__vars['uix_socialMediaContent'],
		'whatsNewContent' => $__vars['uix_whatsNew__component'],
		'searchContent' => $__vars['uix_search__component'],
		'loginTabsContent' => $__vars['uix_loginTabs__component'],
		'visitorContent' => $__vars['uix_userTabs__component'],
		'location' => 'header',
	), $__vars) . '
									';
	if (strlen(trim($__compilerTemp54)) > 0) {
		$__compilerTemp53 .= '
								<div class="p-nav-opposite">
									' . $__compilerTemp54 . '
								</div>
							';
	}
	$__compilerTemp53 .= '
						';
	if (strlen(trim($__compilerTemp53)) > 0) {
		$__compilerTemp52 .= '
					<div class="p-header-content">
						' . $__compilerTemp53 . '
					</div>
				';
	}
	$__vars['uix_headerContent'] = $__templater->preEscaped('
				' . $__compilerTemp52 . '
			');
	$__finalCompiled .= '

			' . '
			
			';
	if ((!$__templater->fn('property', array('uix_navAboveHeader', ), false))) {
		$__finalCompiled .= '
				' . $__templater->callMacro(null, 'uix_logoBlock', array(
			'content' => $__vars['uix_headerContent'],
		), $__vars) . '
			';
	}
	$__finalCompiled .= '

			';
	$__compilerTemp55 = '';
	if (!$__vars['uix_hideNavigation']) {
		$__compilerTemp55 .= '
							';
		$__vars['uix_badgeCounter'] = ($__vars['xf']['visitor']['conversations_unread'] + $__vars['xf']['visitor']['alerts_unread']);
		$__compilerTemp55 .= '
							';
		if (($__templater->fn('property', array('uix_visitorTabsMobile', ), false) == 'canvas')) {
			$__compilerTemp55 .= '
								';
			$__vars['uix_visitorTabCanvas'] = '1';
			$__compilerTemp55 .= '
							';
		} else {
			$__compilerTemp55 .= '
								';
			$__vars['uix_visitorTabCanvas'] = '0';
			$__compilerTemp55 .= '
							';
		}
		$__compilerTemp55 .= '
							<a class="p-nav-menuTrigger  badgeContainer' . (($__vars['uix_visitorTabCanvas'] AND ($__vars['xf']['visitor']['alerts_unread'] OR $__vars['xf']['visitor']['conversations_unread'])) ? ' badgeContainer--highlighted' : '') . '" data-badge="' . $__templater->filter($__vars['uix_badgeCounter'], array(array('number', array()),), true) . '" data-xf-click="off-canvas" data-menu=".js-headerOffCanvasMenu" role="button" tabindex="0">
								<i aria-hidden="true"></i>
								<span class="p-nav-menuText">' . 'Menu' . '</span>
							</a>
							';
		if (($__templater->fn('property', array('uix_navigationType', ), false) == 'sidebarNav') AND ($__templater->fn('property', array('uix_pageStyle', ), false) == 'covered')) {
			$__compilerTemp55 .= '
							<a class="p-nav-menuTrigger uix_sidebarNav--trigger" id="uix_sidebarNav--trigger">
								<i aria-hidden="true"></i>
								<span class="p-nav-menuText">' . 'Menu' . '</span>
							</a>
							';
		}
		$__compilerTemp55 .= '
						';
	}
	$__compilerTemp56 = '';
	if (!$__vars['uix_hideNavigation']) {
		$__compilerTemp56 .= '
							';
		if (($__templater->fn('property', array('uix_navigationType', ), false) != 'sidebarNav') OR ($__templater->fn('property', array('uix_pageStyle', ), false) != 'covered')) {
			$__compilerTemp56 .= '
							<div class="p-nav-scroller hScroller" data-xf-init="h-scroller" data-auto-scroll=".p-navEl.is-selected">
								<div class="hScroller-scroll">
									<ul class="p-nav-list js-offCanvasNavSource">
									';
			$__vars['i'] = 0;
			if ($__templater->isTraversable($__vars['navTree'])) {
				foreach ($__vars['navTree'] AS $__vars['navSection'] => $__vars['navEntry']) {
					if (($__vars['navSection'] != $__vars['xf']['app']['defaultNavigationId'])) {
						$__vars['i']++;
						$__compilerTemp56 .= '
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
			$__compilerTemp56 .= '
									</ul>
								</div>
							</div>
							';
		}
		$__compilerTemp56 .= '

							';
		if ($__templater->fn('property', array('uix_activeNavTitle', ), false)) {
			$__compilerTemp56 .= '
								<div class="uix_activeNavTitle">
									<span>
										';
			if ($__vars['uix_mobileActiveNav']) {
				$__compilerTemp56 .= '
											' . $__templater->escape($__vars['uix_mobileActiveNav']) . '
										';
			} else if ($__vars['selectedNavEntry']['href']) {
				$__compilerTemp56 .= '
											' . $__templater->escape($__vars['selectedNavEntry']['title']) . '
										';
			} else {
				$__compilerTemp56 .= '
										';
			}
			$__compilerTemp56 .= '
									</span>
								</div>
							';
		}
		$__compilerTemp56 .= '
						';
	}
	$__compilerTemp57 = '';
	$__compilerTemp58 = '';
	$__compilerTemp58 .= '
										' . $__templater->callMacro(null, 'uix_visitorTabs__component', array(
		'socialMediaContent' => $__vars['uix_socialMediaContent'],
		'whatsNewContent' => $__vars['uix_whatsNew__component'],
		'searchContent' => $__vars['uix_search__component'],
		'loginTabsContent' => $__vars['uix_loginTabs__component'],
		'visitorContent' => $__vars['uix_userTabs__component'],
		'location' => 'navigation',
	), $__vars) . '
										' . $__templater->callMacro(null, 'uix_sidebarTrigger__component', array(
		'content' => $__vars['uix_sidebarTrigger__content'],
		'location' => 'navigation',
	), $__vars) . '
									';
	if (strlen(trim($__compilerTemp58)) > 0) {
		$__compilerTemp57 .= '
								<div class="p-nav-opposite">
									' . $__compilerTemp58 . '
								</div>
							';
	}
	$__vars['navHtml'] = $__templater->preEscaped('
				<nav class="p-nav">
					<div class="p-nav-inner">
						' . $__compilerTemp55 . '

						' . $__templater->callMacro(null, 'uix_logo__component', array(
		'content' => $__vars['uix_logo__component'],
	), $__vars) . '

						' . $__compilerTemp56 . '

							' . $__templater->callMacro(null, 'uix_search__component', array(
		'location' => 'navigationLeft',
		'content' => $__vars['uix_search__component'],
	), $__vars) . '

							' . $__compilerTemp57 . '
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
		$__finalCompiled .= '" data-top-offset-min="' . $__templater->escape($__vars['uix_stickyStaffBarHeight']) . '" data-top-offset-max="' . $__templater->escape($__vars['uix_stickyStaffBarHeight']) . '" data-top-offset-breakpoint="' . $__templater->fn('property', array('uix_viewportShowLogoBlock', ), true) . '">
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
		$__finalCompiled .= '" data-top-offset-min="' . $__templater->escape($__vars['uix_stickyStaffBarHeight']) . '" data-top-offset-max="' . $__templater->escape($__vars['uix_stickyStaffBarHeight']) . '" data-top-offset-breakpoint="' . $__templater->fn('property', array('uix_viewportShowLogoBlock', ), true) . '">
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
			
			';
	if ($__templater->fn('property', array('uix_navAboveHeader', ), false)) {
		$__finalCompiled .= '
				' . $__templater->callMacro(null, 'uix_logoBlock', array(
			'content' => $__vars['uix_headerContent'],
		), $__vars) . '
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
			' . $__templater->callMacro(null, 'uix_mainTabComponent', array(
		'location' => 'header',
		'content' => $__vars['uix_mainTabComponent'],
	), $__vars) . '
			' . $__templater->callMacro(null, 'uix_titlebar__component', array(
		'location' => 'header',
		'content' => $__vars['uix_titlebar__component'],
	), $__vars) . '
			' . $__templater->filter($__vars['uix_headerExtra'], array(array('raw', array()),), true) . '
		</div>

		' . '
		<div class="offCanvasMenu offCanvasMenu--nav js-headerOffCanvasMenu" data-menu="menu" aria-hidden="true" data-ocm-builder="navigation">
			<div class="offCanvasMenu-backdrop" data-menu-close="true"></div>
			<div class="offCanvasMenu-content">
				' . $__templater->includeTemplate('uix_canvasTabs', $__vars) . '
				' . $__templater->includeTemplate('uix_canvasPanels', $__vars) . '

				' . '
			</div>
		</div>

		' . '

		' . $__templater->callMacro(null, 'uix_titlebar__component', array(
		'location' => 'belowHeader',
		'content' => $__vars['uix_titlebar__component'],
	), $__vars) . '

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
					' . $__templater->button('
						' . $__templater->callMacro('uix_icons.less', 'icon', array(
			'icon' => 'warning',
		), $__vars) . ' View Documentation
					', array(
			'href' => 'https://www.themehouse.com/help/documentation/uix2',
			'class' => 'button--primary',
		), '', array(
		)) . '
				</div>
				';
	}
	$__finalCompiled .= '
				<!--XF:EXTRA_OUTPUT-->

				' . $__templater->callMacro(null, 'uix_notices', array(
		'location' => 'aboveMainContainer',
		'content' => $__vars['uix_notices'],
	), $__vars) . '

				' . $__templater->callMacro(null, 'uix_titlebar__component', array(
		'location' => 'aboveMainContainer',
		'content' => $__vars['uix_titlebar__component'],
	), $__vars) . '

				' . $__templater->callMacro('uix_welcomeSection', 'welcomeSection', array(
		'contentTemplate' => $__vars['template'],
		'location' => 'aboveMainContainer',
		'showWelcomeSection' => $__vars['uix_showWelcomeSection'],
	), $__vars) . '

				' . $__templater->callMacro(null, 'uix_topBreadcrumb__component', array(
		'location' => 'aboveMainContainer',
		'content' => $__vars['uix_topBreadcrumb__component'],
	), $__vars) . '

				' . $__templater->callMacro(null, 'uix_mainTabComponent', array(
		'location' => 'aboveMainContainer',
		'content' => $__vars['uix_mainTabComponent'],
	), $__vars) . '

				';
	if ($__vars['xf']['session']['lau_id']) {
		$__finalCompiled .= '
	<div class="blockMessage blockMessage--important blockMessage--iconic">
		' . '' . $__templater->escape($__vars['xf']['session']['lau_from_name']) . ', you are currently using ' . $__templater->escape($__vars['xf']['session']['lau_to_name']) . '\'s account.' . '
	</div>
';
	}
	$__finalCompiled .= '

' . $__templater->callMacro('browser_warning_macros', 'javascript', array(), $__vars) . '
				' . $__templater->callMacro('browser_warning_macros', 'browser', array(), $__vars) . '

				<div uix_component="MainContainer" class="uix_contentWrapper">

					' . $__templater->callMacro(null, 'uix_notices', array(
		'location' => 'mainContainerTop',
		'content' => $__vars['uix_notices'],
	), $__vars) . '

					' . $__templater->callAdsMacro('container_content_above', array(), $__vars) . '
					' . $__templater->callMacro('uix_welcomeSection', 'welcomeSection', array(
		'contentTemplate' => $__vars['template'],
		'location' => 'mainContainerTop',
		'showWelcomeSection' => $__vars['uix_showWelcomeSection'],
	), $__vars) . '
					' . $__templater->callMacro(null, 'uix_topBreadcrumb__component', array(
		'location' => 'mainContainerTop',
		'content' => $__vars['uix_topBreadcrumb__component'],
	), $__vars) . '
					' . $__templater->callMacro(null, 'uix_titlebar__component', array(
		'location' => 'mainContainerTop',
		'content' => $__vars['uix_titlebar__component'],
	), $__vars) . '
					' . $__templater->callMacro(null, 'uix_mainTabComponent', array(
		'location' => 'mainContainerTop',
		'content' => $__vars['uix_mainTabComponent'],
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
									<div class="uix_sidebar--scroller">
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
							</div>
						';
	}
	$__finalCompiled .= '

						' . $__templater->callMacro(null, 'uix_sidebar__component', array(
		'content' => $__vars['uix_sidebar__component'],
		'location' => 'left',
	), $__vars) . '
						<div uix_component="MainContent" class="p-body-content">
							<!-- ABOVE MAIN CONTENT -->
							' . $__templater->callMacro(null, 'uix_notices', array(
		'location' => 'aboveMainContent',
		'content' => $__vars['uix_notices'],
	), $__vars) . '
							' . $__templater->callMacro(null, 'uix_topBreadcrumb__component', array(
		'location' => 'aboveMainContent',
		'content' => $__vars['uix_topBreadcrumb__component'],
	), $__vars) . '
							' . $__templater->callMacro('uix_welcomeSection', 'welcomeSection', array(
		'contentTemplate' => $__vars['template'],
		'location' => 'aboveMainContent',
		'showWelcomeSection' => $__vars['uix_showWelcomeSection'],
	), $__vars) . '
							' . $__templater->callMacro(null, 'uix_titlebar__component', array(
		'location' => 'aboveMainContent',
		'content' => $__vars['uix_titlebar__component'],
	), $__vars) . '
							' . $__templater->callMacro(null, 'uix_mainTabComponent', array(
		'location' => 'aboveMainContent',
		'content' => $__vars['uix_mainTabComponent'],
	), $__vars) . '
							<div class="p-body-pageContent">
								' . $__templater->callMacro(null, 'uix_notices', array(
		'location' => 'mainContentTop',
		'content' => $__vars['uix_notices'],
	), $__vars) . '
								' . $__templater->callMacro('uix_welcomeSection', 'welcomeSection', array(
		'contentTemplate' => $__vars['template'],
		'location' => 'mainContentTop',
		'showWelcomeSection' => $__vars['uix_showWelcomeSection'],
	), $__vars) . '
								' . $__templater->callMacro(null, 'uix_topBreadcrumb__component', array(
		'location' => 'mainContentTop',
		'content' => $__vars['uix_topBreadcrumb__component'],
	), $__vars) . '
								' . $__templater->callMacro(null, 'uix_titlebar__component', array(
		'location' => 'mainContentTop',
		'content' => $__vars['uix_titlebar__component'],
	), $__vars) . '
								' . $__templater->callMacro(null, 'uix_mainTabComponent', array(
		'location' => 'mainContentTop',
		'content' => $__vars['uix_mainTabComponent'],
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
		'location' => 'mainContentBottom',
	), $__vars) . '
							</div>
							<!-- BELOW MAIN CONTENT -->
							' . $__templater->callAdsMacro('container_content_below', array(), $__vars) . '
							' . $__templater->callMacro(null, 'uix_bottomBreadcrumb__component', array(
		'content' => $__vars['uix_bottomBreadcrumb__component'],
		'location' => 'belowMainContent',
	), $__vars) . '
						</div>

						' . $__templater->callMacro(null, 'uix_sidebar__component', array(
		'content' => $__vars['uix_sidebar__component'],
		'location' => 'right',
	), $__vars) . '
					</div>
					' . $__templater->callMacro(null, 'uix_bottomBreadcrumb__component', array(
		'content' => $__vars['uix_bottomBreadcrumb__component'],
		'location' => 'mainContainerBottom',
	), $__vars) . '
				</div>
				' . $__templater->callMacro(null, 'uix_bottomBreadcrumb__component', array(
		'content' => $__vars['uix_bottomBreadcrumb__component'],
		'location' => 'belowMainContainer',
	), $__vars) . '
				' . $__templater->callMacro(null, 'uix_footer', array(
		'location' => 'insideContent',
		'content' => $__vars['uix_footer'],
		'insideContent' => $__templater->fn('property', array('uix_footerInsideContent', ), false),
	), $__vars) . '
			</div>
		</div>

		' . $__templater->callMacro(null, 'uix_footer', array(
		'location' => 'bottom',
		'content' => $__vars['uix_footer'],
		'insideContent' => $__templater->fn('property', array('uix_footerInsideContent', ), false),
	), $__vars) . '

		';
	$__compilerTemp59 = '';
	$__compilerTemp59 .= '
					';
	if ($__templater->fn('property', array('scrollJumpButtons', ), false)) {
		$__compilerTemp59 .= '
						<div class="u-scrollButtons js-scrollButtons" data-trigger-type="' . $__templater->fn('property', array('scrollJumpButtons', ), true) . '">
							' . $__templater->button('<i class="fa fa-arrow-up"></i><span class="u-srOnly">' . 'Top' . '</span>', array(
			'href' => '#top',
			'class' => 'button--scroll',
			'data-xf-click' => 'scroll-to',
		), '', array(
		)) . '
							';
		if ($__templater->fn('property', array('scrollJumpButtons', ), false) != 'up') {
			$__compilerTemp59 .= '
								' . $__templater->button('<i class="fa fa-arrow-down"></i><span class="u-srOnly">' . 'Bottom' . '</span>', array(
				'href' => '#footer',
				'class' => 'button--scroll',
				'data-xf-click' => 'scroll-to',
			), '', array(
			)) . '
							';
		}
		$__compilerTemp59 .= '
						</div>
					';
	}
	$__compilerTemp59 .= '
					';
	if ($__templater->fn('property', array('uix_fab', ), false) != 'never') {
		$__compilerTemp59 .= '
						';
		$__compilerTemp60 = '';
		$__compilerTemp60 .= (isset($__templater->pageParams['pageAction']) ? $__templater->pageParams['pageAction'] : '');
		if (strlen(trim($__compilerTemp60)) > 0) {
			$__compilerTemp59 .= '
							<div class="p-title-pageAction">' . $__compilerTemp60 . '</div>
						';
		}
		$__compilerTemp59 .= '
					';
	}
	$__compilerTemp59 .= '
				';
	if (strlen(trim($__compilerTemp59)) > 0) {
		$__finalCompiled .= '
			<div class="uix_fabBar uix_fabBar--active">
				' . $__compilerTemp59 . '
			</div>
		';
	}
	$__finalCompiled .= '
		';
	if (($__templater->fn('property', array('uix_fab', ), false) != 'never') AND (!$__templater->fn('property', array('uix_fabScroll', ), false))) {
		$__finalCompiled .= '
			';
		$__compilerTemp61 = '';
		$__compilerTemp61 .= (isset($__templater->pageParams['pageAction']) ? $__templater->pageParams['pageAction'] : '');
		if (strlen(trim($__compilerTemp61)) > 0) {
			$__finalCompiled .= '
				<div class="uix_fabBar uix_fabBar--mirror">
					<div class="p-title-pageAction">' . $__compilerTemp61 . '</div>
				</div>
			';
		}
		$__finalCompiled .= '
		';
	}
	$__finalCompiled .= '
		';
	if ($__templater->fn('property', array('uix_visitorTabsMobile', ), false) == 'tabbar') {
		$__finalCompiled .= '
			' . $__templater->callMacro('uix_tabBar', 'uix_tabBar', array(), $__vars) . '
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
	';
	if ($__vars['notices']['bottom_fixer']) {
		$__finalCompiled .= '
		' . $__templater->callMacro('notice_macros', 'notice_list', array(
			'type' => 'bottom_fixer',
			'notices' => $__vars['notices']['bottom_fixer'],
		), $__vars) . '
	';
	}
	$__finalCompiled .= '
</div>

' . $__templater->includeTemplate('uix_config', $__vars) . '

' . $__templater->callMacro('helper_js_global', 'body', array(
		'app' => 'public',
		'jsState' => $__vars['jsState'],
	), $__vars) . '

';
	if ($__templater->fn('property', array('uix_loginStyle', ), false) == 'slidingPanel') {
		$__finalCompiled .= '
	<div class="uix__loginForm uix__loginForm--login">
		<div class="uix__loginForm--panel">
			';
		$__compilerTemp62 = $__vars;
		$__compilerTemp62['uix_loginPreventAutoFocus'] = '1';
		$__finalCompiled .= $__templater->includeTemplate('login', $__compilerTemp62) . '
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

';
	return $__finalCompiled;
});