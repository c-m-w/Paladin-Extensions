<?php
// FROM HASH: a5d1a01234457188ca82e7c6c1cd2cf5
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->includeTemplate('uix_icons.less', $__vars) . '
' . $__templater->includeTemplate('uix_buttonRipple.less', $__vars) . '
' . $__templater->includeTemplate('uix_extendedFooter.less', $__vars) . '

*::selection,
 {
  .xf-uix_textSelection(); /* WebKit/Blink Browsers */
}
*::-moz-selection {
  .xf-uix_textSelection(); /* Gecko Browsers */
}

/* --- Sticky kit header fix --- */

.uix_headerContainer--stickyFix {height: 1px; visibility: hidden;}
.uix_headerContainer {margin-top: -1px !important;}

/* --- Node Grid Styling for UI.X ONLY --- */

';
	if ($__templater->fn('property', array('th_enableGrid_nodes', ), false)) {
		$__finalCompiled .= '

.node + .node {border: none;}

.uix_nodeList .block-container .node-footer--more a:before {
	' . $__templater->callMacro('uix_icons.less', 'content', array(
			'icon' => 'arrow-right',
		), $__vars) . '
	font-size: @xf-uix_iconSize;
}

.uix_nodeList .block-container .node-footer--createThread:before {
	' . $__templater->callMacro('uix_icons.less', 'content', array(
			'icon' => 'new-thread',
		), $__vars) . '
	font-size: @xf-uix_iconSize;
}

';
	}
	$__finalCompiled .= '

.uix_adminTrigger {display: none !important;}

';
	if ($__templater->fn('property', array('uix_collapseStaffbarLinks', ), false)) {
		$__finalCompiled .= '
@media (max-width: @xf-uix_viewportCollapseStaffLinks) {
	.p-staffBar-link {display: none;}
	.uix_adminTrigger {display: inline-block !important;}
}
';
	}
	$__finalCompiled .= '


/***** extra user info postbit collapse *******/

';
	if ($__templater->fn('property', array('uix_collapseExtraInfo', ), false)) {
		$__finalCompiled .= '
.thThreads__userExtra--toggle {
	text-align: center;
	margin-top: @xf-paddingMedium;

	.thThreads__userExtra--trigger {
		transition: ease-in transform .2s .2s;
		display: inline-block;

		&:hover {cursor: pointer;}

		&:before {
			.m-faBase();
			.m-faContent(@fa-var-chevron-down);
		}
	}
}
';
	}
	$__finalCompiled .= '

.thThreads__message-userExtras {
	height: 0;
	overflow: hidden;
	transition: ease-in height .2s;
}

@media (max-width: @xf-messageSingleColumnWidth) {
	.thThreads__message-userExtras {display: none;}
	.thThreads__userExtra--toggle {display: none;}
}

.userExtra--expand  {
	.thThreads__message-userExtras {height: auto;}
	.thThreads__userExtra--trigger {transform: rotate(-180deg);}
}


/*------- category collapse ------- */

.category--collapsed.block--category {
	margin: 0;

	.uix_block-body--outer {
    	height: 0 !important;
		opacity: 0;
		pointer-events: none;
	}

	.categoryCollapse--trigger {transform: rotate(-180deg);}
}

.categoryCollapse--trigger {
	transition: ease-in transform .3s;
}

.block--category .uix_block-body--outer {
	transition: ease-in height 0.3s, ease-in opacity 0.3s;
	opacity: 1;
}

/*------- Sidebar collapse ------- */

.button.uix_sidebarTrigger {
	display: inline-flex;
	align-items: center;

	@media (max-width: @xf-uix_sidebarBreakpoint) {
		display: none;
	}

	i {
		transform: rotate(0);
		transition: ease-in transform .2s;
		font-size: @xf-uix_iconSizeLarge;
	}
}

.p-body-sidebar {
	transition: ease-in width .2s, ease-in opacity .2s .3s;
	opacity: 1;
	max-height: 100%;

	* {transition: ease-in font-size .01s;}
}

@media (min-width: @xf-responsiveWide) {
.uix_sidebarCollapsed {
		.p-body-sidebar {
			transition: ease-in width 0.2s 0.2s, ease-in opacity 0.2s, ease-in font-size .1s .3s;
			width: 0;
			opacity: 0;

			* {
				font-size: 0 !important;
				transition: ease-in font-size .1s .4s;
			}
		}

		.p-body-main--withSidebar .p-body-content {
			width: 100%;
			max-width: 100%;
		}
	}
}

.uix_sidebarCollapsed .uix_sidebarTrigger i {
	transform: rotate(-180deg);
}

';
	if ($__templater->fn('property', array('uix_sidebarLeft', ), false)) {
		$__finalCompiled .= '
	.button.uix_sidebarTrigger {
		flex-direction: row-reverse;

		i {transform: rotate(-180deg);}
	}
	.uix_sidebarCollapsed .uix_sidebarTrigger i {transform: rotate(0);}
';
	}
	$__finalCompiled .= '

/*------- navigation icons------- */

';
	if ($__templater->fn('property', array('uix_navTabIcons', ), false)) {
		$__finalCompiled .= '

.p-navEl-link:before {
	.m-faBase();
	.xf-uix_navTabIconStyle();
}

.p-navEl-link {
	&[data-nav-id="home"]:before {' . $__templater->callMacro('uix_icons.less', 'content', array(
			'icon' => 'home',
		), $__vars) . '}
	&[data-nav-id="forums"]:before {' . $__templater->callMacro('uix_icons.less', 'content', array(
			'icon' => 'forum',
		), $__vars) . '}
	&[data-nav-id="whatsNew"]:before {' . $__templater->callMacro('uix_icons.less', 'content', array(
			'icon' => 'whats-new',
		), $__vars) . '}
	&[data-nav-id="members"]:before {' . $__templater->callMacro('uix_icons.less', 'content', array(
			'icon' => 'user-multiple',
		), $__vars) . '}
	&[data-nav-id="profile"]:before {' . $__templater->callMacro('uix_icons.less', 'content', array(
			'icon' => 'user',
		), $__vars) . '}
	&[data-nav-id="alerts"]:before {' . $__templater->callMacro('uix_icons.less', 'content', array(
			'icon' => 'alert',
		), $__vars) . '}
	&[data-nav-id="settings"]:before {' . $__templater->callMacro('uix_icons.less', 'content', array(
			'icon' => 'settings',
		), $__vars) . '}
	&[data-nav-id="xfmg"]:before {' . $__templater->callMacro('uix_icons.less', 'content', array(
			'icon' => 'media',
		), $__vars) . '}
	&[data-nav-id="xfrm"]:before {' . $__templater->callMacro('uix_icons.less', 'content', array(
			'icon' => 'resource',
		), $__vars) . '}
	&[data-nav-id="support"]:before {' . $__templater->callMacro('uix_icons.less', 'content', array(
			'icon' => 'support',
		), $__vars) . '}
	&[data-nav-id="premium"]:before {' . $__templater->callMacro('uix_icons.less', 'content', array(
			'icon' => 'premium',
		), $__vars) . '}
}

';
	}
	$__finalCompiled .= '

/* ---Force header content fluid --- */

';
	if (($__templater->fn('property', array('uix_navigationType', ), false) == 'sidebarNav') AND ($__templater->fn('property', array('uix_pageStyle', ), false) == 'covered')) {
		$__finalCompiled .= '
	.p-staffBar .pageContent,
	.p-header-inner,
	.p-nav-inner,
	.p-sectionLinks .pageContent {max-width: 100%;}
';
	}
	$__finalCompiled .= '

/* ---Sidebar Navigation --- */

.uix_headerContainer .p-nav-menuTrigger.uix_sidebarNav--trigger {display: none;}

';
	if (($__templater->fn('property', array('uix_navigationType', ), false) == 'sidebarNav') AND ($__templater->fn('property', array('uix_pageStyle', ), false) == 'covered')) {
		$__finalCompiled .= '

@media (min-width: ' . ($__templater->fn('property', array('publicNavCollapseWidth', ), false) + 1) . 'px ) {
	.uix_page--fluid.sidebarNav--active .p-body-inner {
		width: calc( ~"100% - ' . $__templater->fn('property', array('uix_sidebarNavWidth', ), true) . ' - ' . ($__templater->fn('property', array('elementSpacer', ), false) * 2) . 'px");
	}

	.uix_headerContainer .p-nav-menuTrigger.uix_sidebarNav--trigger {display: inline-block;}
	.uix_page--fixed.sidebarNav--active .p-body-inner {
		@media (max-width: @uix_sidebarNavBreakpoint) {
			width: calc( ~"100% - ' . $__templater->fn('property', array('uix_sidebarNavWidth', ), true) . ' - ' . ($__templater->fn('property', array('elementSpacer', ), false) * 2) . 'px");
		}

		@media (min-width: @uix_sidebarNavBreakpoint ) {
			left: -105px;
		}
	}
}
';
	}
	$__finalCompiled .= '

.uix_sidebarNav__inner__widgets {
	padding: @xf-paddingMedium;
}

.sidebarNav--active .uix_sidebarNav {
	margin-left: 0;
}

.uix_stickyBodyElement:not(.offCanvasMenu) {
	position: sticky;
}

';
	if ($__templater->fn('property', array('uix_stickySidebar', ), false)) {
		$__finalCompiled .= '
	.uix_sidebarInner,
	.p-body-sideNavInner:not(.offCanvasMenu) {
		position: static;
	}
	@media (min-width: ' . ($__templater->fn('property', array('uix_sidebarBreakpoint', ), false) + 1) . 'px ) {
		.uix_sidebarInner,
		.p-body-sideNavInner {
			position: sticky;
		}
	}
';
	}
	$__finalCompiled .= '

.uix_sidebarNav {

	width: @xf-uix_sidebarNavWidth;
	min-width: @xf-uix_sidebarNavWidth;
	margin-left: -' . $__templater->fn('property', array('uix_sidebarNavWidth', ), true) . ';
	';
	if ($__templater->fn('property', array('uix_pageStyle', ), false) != 'covered') {
		$__finalCompiled .= '
		padding-top: @xf-elementSpacer;
	';
	}
	$__finalCompiled .= '
	z-index: 1;
	transition: ease-in margin-left .2s;

	@media (max-width: @xf-publicNavCollapseWidth) {
		margin-left: -' . $__templater->fn('property', array('uix_sidebarNavWidth', ), true) . ' !important;
	}

	.uix_sidebarNavList {
		margin: 0;
		padding: 0;
		border-bottom: 1px solid @xf-borderColor;
		line-height: 40px;

		&:last-child {border-bottom: none;}

		.uix_sidebarNav__subNav {
			display: block;
			height: 0;
			overflow: hidden;
			transition: ease-in height .3s;

			&.subNav--expand {height: auto;}
		}

		.menu-linkRow {
			padding: 0 @xf-paddingLarge;
			white-space: nowrap;
			text-overflow: ellipsis;
			overflow: hidden;
			color: @xf-textColorDimmed;
			border: none;

			&:hover {
				background-color: rgba(0,0,0,.05);
				border: none;
			}
		}

		> li {
			display: block;

			.p-navEl:before, .p-navEl:after {display: none;}

			.p-navEl__inner {
				display: flex;
				align-items: center;
			}

			.is-selected .p-navEl__inner {
				color: @xf-uix_primaryColor;
			}

			.is-selected .p-navEl__inner {
				background-color: rgba(0,0,0,.08);

				.p-navEl-link, {
					color: inherit;
				}
			}

			.p-navEl {display: block;}

			.p-navEl__inner:hover,
			.blockLink:hover {
				background-color: rgba(0,0,0,.05);
			}

			.p-navEl-link,
			.blockLink {
				display: flex;
				align-items: center;
				padding: 0 @xf-paddingLarge;
				color: @xf-textColorDimmed;
				background: none;
				width: 100%;
				text-decoration: none;
				float: none;

				&:before {
					font-size: @xf-uix_iconSizeLarge !important;
					padding-right: 1em;
				}
			}

			.blockLink {
				padding-left: 50px;
			}

			.uix_sidebarNav--trigger {
				padding: 0 @xf-paddingLarge;
				font-size: @xf-uix_iconSize;
				transition: ease-in transform .3s;
				color: inherit;

				&.is-expanded {transform: rotate(-180deg);}
			}

			.p-navEl-splitTrigger {display: none;}
		}
	}
}

/* ---VISITOR TABS --- */

.p-account {

	background-color: transparent;

	.p-navgroup-link {
		display: flex;
		align-items: center;
		border: none;
	}
}


/* ---SEARCH BAR --- */

.p-quickSearch .input {
	color: @xf-uix_searchBar--color;

	&::placeholder {color: @xf-uix_searchBar--color;}
}

.uix_searchBar {
	display: inline-flex;

	@media (max-width: @xf-uix_search_maxResponsiveWidth) {
		';
	if ($__templater->fn('property', array('uix_searchPosition', ), false) == 'navigationLeft') {
		$__finalCompiled .= '
			order: 1;
		';
	}
	$__finalCompiled .= '
	}

	@media (min-width: ' . ($__templater->fn('property', array('uix_search_maxResponsiveWidth', ), false) + 1) . 'px ) {
		max-width: @xf-uix_searchBarWidth;
		width: 1000px;
		display: flex;
		// min-width: @xf-uix_searchBarWidth;
		';
	if ($__templater->fn('property', array('uix_searchPosition', ), false) == 'navigationLeft') {
		$__finalCompiled .= '
			margin: 0 @xf-paddingMedium;
		';
	} else {
		$__finalCompiled .= '
			margin-left: .5em;
		';
	}
	$__finalCompiled .= '
	}

	.uix_searchBarInner {
		display: inline-flex;
		pointer-events: none;
		align-items: center;
		left: 20px;
		right: 20px;

		justify-content: flex-end;
		bottom: 0;
		top: 0;
		transition: ease-in background-color .3s;
		flex-grow: 1;
		left: 0px;
		right: 0px;

		@media (min-width: @xf-uix_search_maxResponsiveWidth) {
			';
	if ($__templater->fn('property', array('uix_searchPosition', ), false) == 'navigationLeft') {
		$__finalCompiled .= '
				width: 100%;
			';
	}
	$__finalCompiled .= '
		}


		.uix_searchIcon {
			position: absolute;
			bottom: 0;
			top: 0;
			';
	if (!$__templater->fn('property', array('uix_searchButton', ), false)) {
		$__finalCompiled .= '
				left: 0;
			';
	} else {
		$__finalCompiled .= '
				right: 0;
			';
	}
	$__finalCompiled .= '
		}

		';
	if ($__templater->fn('property', array('uix_searchIconBehavior', ), false) == 'expandMobile') {
		$__finalCompiled .= '
			@media (max-width: @xf-responsiveMedium)  {
				position: absolute;
			}
		';
	} else if ($__templater->fn('property', array('uix_searchIconBehavior', ), false) == 'expand') {
		$__finalCompiled .= '
			position: absolute;
		';
	}
	$__finalCompiled .= '

		.uix_searchForm {
			display: inline-flex;
			align-items: center;
			transition: ease-in flex-grow .3s, ease-in max-width .3s, ease-in background-color .2s;
			flex-grow: 0;
			max-width: @xf-uix_searchBarWidth;
			width: 100%;
		    pointer-events: all;
			position: relative;
			.xf-uix_searchBar();

			&.uix_searchForm--focused {
				.xf-uix_searchBarFocus();
				.input {
					&::placeholder {color: @xf-uix_searchBarPlaceholderFocusColor;}
				}

				i {color: @xf-uix_searchIconFocusColor;}
			}

			.uix_search--settings i,
			.uix_search--close i {display: none;}

			i {
				.xf-uix_searchIcon();
				height: @xf-uix_searchBarHeight;
				display: inline-flex;
				align-items: center;
				transition: ease-in color .2s;
			}

			.input {
				height: @xf-uix_searchBarHeight;
				border: none;
				transition: ease-in color .2s;
				&::placeholder {color: @xf-uix_searchBarPlaceholderColor;}
				color: inherit;
				';
	if (!$__templater->fn('property', array('uix_searchButton', ), false)) {
		$__finalCompiled .= '
					text-indent: 30px;
				';
	}
	$__finalCompiled .= '

			}
		}
	}

	.p-navgroup-link {display: none;}

	@media(max-width: @xf-uix_search_maxResponsiveWidth) {
		.uix_searchBarInner .uix_searchForm {width: 0; overflow: hidden; border: none;}
	}

	';
	if ($__templater->fn('property', array('uix_searchIconBehavior', ), false) != 'expandMobile') {
		$__finalCompiled .= '
		@media (max-width: @xf-uix_search_maxResponsiveWidth) {
			.p-navgroup-link {display: inline-flex;}
			.minimalSearch--detailed & .p-navgroup-link {display: inline-flex;}
		}
	';
	} else if ($__templater->fn('property', array('uix_searchIconBehavior', ), false) == 'expandMobile') {
		$__finalCompiled .= '
			@media(max-width: @xf-uix_search_maxResponsiveWidth) and (min-width: @xf-responsiveMedium) {
			.p-navgroup-link {display: inline-flex;}
			.p-navgroup-link.uix_searchIconTrigger {display: none;}
		}

		@media (max-width: @xf-uix_search_maxResponsiveWidth) and (max-width: @xf-responsiveMedium) {
			.p-navgroup-link.uix_searchIconTrigger {display: inline-flex;}
			.p-navgroup-link {display: none;}

			.minimalSearch--detailed & .p-navgroup-link.uix_searchIconTrigger {display: none;}
			.minimalSearch--detailed & .p-navgroup-link {display: inline-flex;}

		}
	';
	}
	$__finalCompiled .= '

}

.uix_searchBar .uix_searchDropdown__menu {
    // margin-top: 10px;
    display: none;
    position: absolute;
    top: @xf-uix_searchBarHeight;
    right: 0;
    opacity: 0;
    width: @xf-uix_searchBarWidth;
    @media(max-width: @xf-uix_search_maxResponsiveWidth) {
        width: 100%;
    }

    &.uix_searchDropdown__menu--active {
        display: block;
        opacity: 1;
        pointer-events: all;
    }
}

.uix_search--close {
	cursor: pointer;
}

@media(max-width: @xf-uix_search_maxResponsiveWidth) {

.minimalSearch--active .uix_searchBar .uix_searchBarInner {
    position: absolute;
}

.minimalSearch--active .uix_searchBar .uix_searchBarInner .uix_searchForm {
	flex-grow: 1;
	display: inline-flex !important;
	padding: 0 @xf-paddingMedium;
	max-width: 100%;
}

.minimalSearch--active .uix_searchBar .uix_searchBarInner .uix_searchForm {
	i {
		display: inline-block;
		padding: 0;
		line-height: @xf-uix_searchBarHeight;
	}

	.uix_searchIcon i {display: none;}
	.uix_searchInput {text-indent: 0;}
}

.p-navgroup-link--search,
.p-navgroup-link {transition: ease opacity .2s .3s; opacity: 1;}

.minimalSearch--active {
	.p-navgroup-link--search,
	.p-navgroup-link {
		opacity: 0;
		transition: ease opacity .2s;
		pointer-events: none;
	}
}

';
	if ($__templater->fn('property', array('uix_searchPosition', ), false) == 'navigation') {
		$__finalCompiled .= '

.p-nav-inner > * {transition: ease-in opacity .2s; opacity: 1;}

.minimalSearch--active.p-nav-inner > *,
.minimalSearch--active.p-nav-inner .p-account,
.minimalSearch--active.p-nav-inner .uix_searchBar .uix_searchIconTrigger,
.minimalSearch--active.p-nav-inner .p-discovery > *:not(.uix_searchBar) {opacity: 0;}

.minimalSearch--active.p-nav-inner .p-discovery,
.minimalSearch--active.p-nav-inner .p-nav-opposite {opacity: 1;}
';
	}
	$__finalCompiled .= '

';
	if ($__templater->fn('property', array('uix_searchPosition', ), false) == 'navigationLeft') {
		$__finalCompiled .= '

.p-nav-inner > *:not(.uix_searchBar),
.p-nav-inner .uix_searchBar .uix_searchIconTrigger {transition: ease-in opacity .2s; opacity: 1;}

.minimalSearch--active.p-nav-inner > *:not(.uix_searchBar),
.minimalSearch--active.p-nav-inner .p-account,
.minimalSearch--active.p-nav-inner .uix_searchBar .uix_searchIconTrigger,
.minimalSearch--active.p-nav-inner .p-discovery,
.minimalSearch--active.p-nav-inner .p-nav-opposite {opacity: 0;}

';
	}
	$__finalCompiled .= '

';
	if ($__templater->fn('property', array('uix_searchPosition', ), false) == 'tablinks') {
		$__finalCompiled .= '

.p-sectionLinks .pageContent > * {transition: ease opacity .2s; opacity: 1;}

.minimalSearch--active.p-sectionLinks .pageContent > * {opacity: 0;}

.p-sectionLinks .pageContent .uix_searchBar {opacity: 1;}

';
	}
	$__finalCompiled .= '

';
	if ($__templater->fn('property', array('uix_searchPosition', ), false) == 'header') {
		$__finalCompiled .= '

.p-header-content > * {transition: ease opacity .2s; opacity: 1;}

.minimalSearch--active.p-header-content > *:not(.p-nav-opposite) {opacity: 0;}

.minimalSearch--active.p-header-content .uix_searchBar {opacity: 1;}
';
	}
	$__finalCompiled .= '

';
	if ($__templater->fn('property', array('uix_searchPosition', ), false) == 'staffBar') {
		$__finalCompiled .= '

.p-staffBar .pageContent > * {transition: ease opacity .2s; opacity: 1;}

.minimalSearch--active.p-staffBar .pageContent > * {opacity: 0;}

.minimalSearch--active.p-staffBar .pageContent .uix_searchBar {opacity: 1;}
';
	}
	$__finalCompiled .= '
}

/* ---UTILITIES --- */

.media__container {
	display: flex;
	.media--left {margin-right: @xf-paddingMedium;}
}

/* ---FOOTER --- */

.uix_fabBar {
	';
	if (!$__templater->fn('property', array('uix_fabScroll', ), false)) {
		$__finalCompiled .= '
		background-color: @xf-uix_fabBarBackground;
		height: 60px;
		padding: @xf-paddingLarge 0;
	';
	}
	$__finalCompiled .= '
	';
	if ($__templater->fn('property', array('uix_fab', ), false) == 'mobile') {
		$__finalCompiled .= '
	@media (min-width: @xf-uix_fabVw) {
		display: none;
	}
	';
	}
	$__finalCompiled .= '

	.p-title-pageAction {
		position: fixed;
		';
	if ($__templater->fn('property', array('uix_fabScroll', ), false)) {
		$__finalCompiled .= '
			bottom: -150px;
		';
	} else {
		$__finalCompiled .= '
			bottom: @xf-paddingLarge;
		';
	}
	$__finalCompiled .= '
		right: @xf-paddingLarge;
		transition: ease-in .2s bottom;
		z-index: 5;

		.button {
			border-radius: 100%;
			height: 60px;
			width: 60px;
		    padding: 0;
			font-size: 0;
			display: none;
		    align-items: center;
		    justify-content: center;
			box-shadow: @xf-uix_elevation2;
			background: @xf-buttonCta--background-color;
			color: @xf-buttonCta--color;

			&:last-child {display: flex;}

			.button-text:before {font-size: @xf-uix_iconSizeLarge; margin: 0;}
		}
	}

	&.uix_fabBar--active .p-title-pageAction {bottom: @xf-paddingLarge;}
}

#uix_jumpToFixed {
    font-size: 24px;
    color: #FFF;
    background-color: @xf-uix_secondaryColor;
    padding: 8px;
    margin: 16px;
    border-radius: 2px;
    position: fixed;
    z-index: 1;
    transition: opacity 0.4s;
    display: block;
    padding: 0;
    bottom: 0;
    right: 0;
    left: auto;
}

#uix_jumpToFixed a:first-child {
    padding-bottom: 4px;
}

#uix_jumpToFixed a {
    color: inherit;
    display: block;
    padding: 8px;
}

#uix_jumpToFixed a:last-child {
    padding-top: 4px;
}

/* ---Login form sliding panel --- */

.uix__loginForm--panel {
	background: @xf-contentHighlightBg;
	overflow: hidden;
	position: absolute;
	z-index: 200;
	transition: ease-in .2s transform;
	left: 0;
	right: 0;
	transform: translateY(-100%);
	top: 0;
}

.uix__loginForm--mask {
	position: absolute;
	top: 0;
	left: 0;
	right: 0;
	background-color: transparent;
	transition: ease-in .2s background-color;

}

.uix__loginForm.is-active .uix__loginForm--panel {transform: translateY(0);}

.uix__loginForm.is-active .uix__loginForm--mask {
	background-color: rgba(0,0,0,.4);
	bottom: 0;
}

.uix__loginForm--panel form {
	.m-pageWidth();
}

.uix__loginForm--panel .block-container,
.uix__loginForm--panel .formRow > dt,
.uix__loginForm--panel .formRow > dd,
.uix__loginForm--panel .formSubmitRow-bar {
	background: none;
	box-shadow: none;
	border: none;
}

.uix__loginForm--panel .block-outer {display: none;}

/* ---Canvas Panels --- */

.sidePanel__tabPanels {
	position: relative;
}

.sidePanel__tabPanel {
	height: 0;

	-moz-transition: -moz-transform 0.3s cubic-bezier(0.22, 0.61, 0.36, 1);
	-o-transition: transform 0.3s cubic-bezier(0.22, 0.61, 0.36, 1);
	-o-transition: -o-transform 0.3s cubic-bezier(0.22, 0.61, 0.36, 1);
	-webkit-transition: -webkit-transform 0.3s cubic-bezier(0.22, 0.61, 0.36, 1);
	transition: -webkit-transform 0.3s cubic-bezier(0.22, 0.61, 0.36, 1);
	transition: transform 0.3s cubic-bezier(0.22, 0.61, 0.36, 1);

	float: left;
	width: 100%;
}

.sidePanel__tabPanel.is-left {
	transform: translate3d(300px, 0, 0);
	position: absolute;
	top: 0;
	overflow-y: hidden;
}

.sidePanel__tabPanel.is-right {
	transform: translate3d(300px, 0, 0);
	position: absolute;
	top: 0;
	overflow-y: hidden;
}

.sidePanel__tabPanel.is-active {
	transform: translate3d(0, 0, 0);
	display: block;
	height: auto;
	overflow-y: auto;
}

.sidePanel--visitor .sidePanel__tabPanel.is-active {
	margin-bottom: 50px;
}

.sidePanel__tabPanel.is-hidden {
	visibility: hidden;
}

.sidePanel__tabs {
	display: -ms-flexbox;
	display: -webkit-flex;
	display: flex;
	flex: 0 0 auto;
	padding: 0;
	margin: 0;

	-webkit-justify-content: space-between;
	-ms-flex-pack: justify;
	justify-content: space-between;
}

.sidePanel__tabs li {
	max-width: 50%;
	-webkit-flex: 1 1 auto;
	-ms-flex: 1 1 auto;
	flex: 1 1 auto;
	color: rgba(255,255,255,.7);
}

a.sidePanel__tab {
	font-size: 18px;
	color: rgba(255, 255, 255, 0.75);
	background-color: @xf-uix_primaryColor;
	padding-right: 10px;
	padding-left: 10px;
	border-width: 0;
	border-right-style: solid;
	border-right-color: rgba(255,255,255,.1);
	display: block;
	cursor: pointer;
	text-align: center;
	line-height:50px;
	white-space: nowrap;
	text-overflow: ellipsis;
	overflow: hidden;
	height: 50px;
}

a.sidePanel__tab:hover {color: #fff;}

a.sidePanel__tab.is-active {
	color: #fff;
	box-shadow: inset 0 -3px rgba(0,0,0,.2);
}

.uix_discussionList {
	.xf-uix_discussionList();
}

[type=checkbox], [type=radio], legend {margin-right: .5em;}

.structItem-extraInfo [type=checkbox] {margin-right: 0;}

.uix_messageContent {
	flex-grow: 1;
	display: flex;
	flex-direction: column;
	justify-content: space-between;
	width: 100%;
}

.uix_socialMedia {
	display: inline-flex;
	flex-wrap: wrap;
	margin: 0 -6px;
	padding: 0;

	li {display: inline-block;}

	li a {
		margin: 6px;
		line-height: 1;
		display: inline-block;
		.xf-uix_socialMediaIcon();
	}
}

.uix_headerContainer {
	display: flex;
	flex-direction: column;
	';
	if ($__templater->fn('property', array('uix_pageStyle', ), false) != 'wrapped') {
		$__finalCompiled .= '
		@media (min-width: ' . ($__templater->fn('property', array('responsiveEdgeSpacerRemoval', ), false) + 1) . 'px) {
			margin-top: @xf-uix_headerWhiteSpace;
		}
	';
	}
	$__finalCompiled .= '
	';
	if ($__templater->fn('property', array('uix_detachedNavigation', ), false)) {
		$__finalCompiled .= '
		margin-bottom: @xf-elementSpacer;
	';
	}
	$__finalCompiled .= '

	> *:not(.p-nav) {
		margin-bottom: @xf-uix_headerWhiteSpace;
		&:last-child {margin-bottom: 0;}
	}
}

.uix_pageWrapper--fixed {
	';
	if ($__templater->fn('property', array('uix_pageStyle', ), false) != 'wrapped') {
		$__finalCompiled .= '
		width: 100%;
	';
	}
	$__finalCompiled .= '
	';
	if ($__templater->fn('property', array('uix_pageStyle', ), false) == 'wrapped') {
		$__finalCompiled .= '
		.m-pageWidth();
		.uix_page--fluid & {
			@media (min-width: @xf-pageWidthMax) {
				max-width: 95%;
			}
		}
		@media (max-width: @xf-responsiveEdgeSpacerRemoval) {
			padding: 0;
		}
	';
	}
	$__finalCompiled .= '
	position: relative;
	left: 0;
	transition: max-width .2s, ease-in left .2s;
}


/* --- post thread widget --- */

.uix_postThreadWidget {
	border-top: 4px solid @xf-uix_primaryColor;
	text-align: center;
	padding: @xf-paddingLarge;
	color: @xf-textColorDimmed;

	i {
		height: 50px;
		width: 50px;
		line-height: 50px;
		border-radius: 100%;
		background-color: fade(@xf-uix_primaryColor, 20%);
		color: @xf-uix_primaryColor;
		display: inline-block;
		font-size: @xf-uix_iconSizeLarge;
	}

	.uix_postThreadWidget__title {
		font-size: @xf-fontSizeLarger;
		font-weight: @xf-fontWeightHeavy;
		padding: @xf-paddingMedium 0;
		color: @xf-textColor;
	}

	.button {margin-top: @xf-paddingMedium;}
}

/* --- border radius javascript --- */
.uix_smartBorder--noTop {
	border-bottom-left-radius: @xf-borderRadiusLarge !important;
	border-bottom-right-radius: @xf-borderRadiusLarge !important;
}
.uix_smartBorder--noBottom {
	border-top-left-radius: @xf-borderRadiusLarge !important;
	border-top-right-radius: @xf-borderRadiusLarge !important;
}
.uix_smartBorder--default {
	border-top-left-radius: @xf-borderRadiusLarge !important;
	border-top-right-radius: @xf-borderRadiusLarge !important;
	border-bottom-left-radius: @xf-borderRadiusLarge !important;
	border-bottom-right-radius: @xf-borderRadiusLarge !important;
}

/* --- TH Nodes --- */
html.has-flexbox .thNodes__nodeList .block-container {
	.node-footer--more a:before {
		' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'arrow-right',
	), $__vars) . '
		font-size: 18px;
		padding-right: 6px;
	}

	.node-footer--createThread:before {
		' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'plus',
	), $__vars) . '
		font-size: 18px;
	}
}


/* --- show logoblock for desktop  --- */

';
	if ($__templater->fn('property', array('uix_enableLogoBlock', ), false)) {
		$__finalCompiled .= '

	@media (max-width: ' . ($__templater->fn('property', array('uix_viewportShowLogoBlock', ), false) - 1) . 'px ) {
		.p-header {

			&:not(.p-header--hasExtraContent) {display: none;}

			.p-header-logo {display: none;}

			';
		if ($__templater->fn('property', array('uix_logoBlockSearch', ), false)) {
			$__finalCompiled .= '
				.uix_searchBar {display: none;}
			';
		}
		$__finalCompiled .= '

			';
		if ($__templater->fn('property', array('uix_socialMediaLogoBlock', ), false)) {
			$__finalCompiled .= '
				.uix_socialMedia {display: none;}
			';
		}
		$__finalCompiled .= '
		}
	}

	@media (min-width: @xf-uix_viewportShowLogoBlock) {
		.p-nav-inner .p-header-logo {display: none;}

		';
		if ($__templater->fn('property', array('uix_logoBlockSearch', ), false)) {
			$__finalCompiled .= '
			.uix_headerContainer > *:not(.p-header) .uix_searchBar {display: none;}
		';
		}
		$__finalCompiled .= '

		';
		if ($__templater->fn('property', array('uix_socialMediaLogoBlock', ), false)) {
			$__finalCompiled .= '
			.uix_headerContainer > *:not(.p-header) .uix_socialMedia {display: none;}
		';
		}
		$__finalCompiled .= '

		html:not(.uix_alwaysStaffBar) .p-staffBar {display: none;}
	}

';
	} else {
		$__finalCompiled .= '

	.p-header:not(.p-header--hasExtraContent) {display: none;}

';
	}
	return $__finalCompiled;
});