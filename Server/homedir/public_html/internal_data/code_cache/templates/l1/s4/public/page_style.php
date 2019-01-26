<?php
// FROM HASH: b368baa45d91b1be73e5ba106451b807
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<style>
	.uix_headerContainer .p-navSticky.is-sticky {
		top: ' . $__templater->escape($__vars['uix_stickyStaffBarHeight']) . ' !important;
	}

	';
	if ($__vars['uix_responsiveStaffBar'] AND (!$__vars['uix_alwaysStaffBar'])) {
		$__finalCompiled .= '
		@media (max-width: ' . $__templater->fn('property', array('uix_staffBarBreakpoint', ), true) . ') {
			.uix_headerContainer .p-navSticky.is-sticky {
				top: 0 !important;
			}
		}
	';
	}
	$__finalCompiled .= '

	';
	$__vars['uix_stickyNavHeightTotal'] = '0';
	$__finalCompiled .= '
	';
	$__vars['uix_stickyNavPrimary'] = '0';
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
			$__vars['uix_stickyNavPrimary'] = $__templater->fn('property', array('uix_stickyNavHeight', ), false);
			$__finalCompiled .= '
		';
		} else if ($__templater->fn('property', array('publicNavSticky', ), false) == 'all') {
			$__finalCompiled .= '
			';
			$__vars['uix_stickyNavPrimary'] = $__templater->fn('property', array('uix_stickyNavHeight', ), false);
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
	$__vars['uix_subNavBreakpoint'] = $__templater->fn('property', array('uix_viewportWidthRemoveSubNav', ), false);
	$__finalCompiled .= '

	';
	if ((!$__vars['uix_subNavContentStatic']) AND $__vars['uix_subNavHasSidebarTrigger']) {
		$__finalCompiled .= '
		';
		$__vars['uix_subNavBreakpoint'] = '$uix_sidebarBreakpoint';
		$__finalCompiled .= '
	';
	}
	$__finalCompiled .= '

	';
	if (((!$__vars['uix_subNavContentStatic']) AND $__vars['uix_subNavHasSidebarTrigger']) OR $__vars['uix_subNavContentStatic']) {
		$__finalCompiled .= '
		';
		$__vars['uix_stickyTotal'] = (($__vars['uix_stickyStaffBarHeight'] + $__vars['uix_stickyNavHeightTotal']) + $__templater->fn('property', array('elementSpacer', ), false));
		$__finalCompiled .= '
		.uix_stickyBodyElement:not(.offCanvasMenu) {
			top: ' . $__templater->escape($__vars['uix_stickyTotal']) . 'px !important;
			min-height: calc(100vh - ' . $__templater->escape($__vars['uix_stickyTotal']) . 'px) !important;
		}
		#XF .u-anchorTarget {
			height: ' . $__templater->escape($__vars['uix_stickyTotal']) . 'px;
			margin-top: -' . $__templater->escape($__vars['uix_stickyTotal']) . 'px;
		}

		';
		if ($__vars['uix_responsiveStaffBar'] AND (!$__vars['uix_alwaysStaffBar'])) {
			$__finalCompiled .= '
			@media(max-width: ' . $__templater->fn('property', array('uix_staffBarBreakpoint', ), true) . ') {
				';
			$__vars['uix_stickyTotal'] = ($__vars['uix_stickyNavHeightTotal'] + $__templater->fn('property', array('elementSpacer', ), false));
			$__finalCompiled .= '
				.uix_stickyBodyElement:not(.offCanvasMenu) {
					top: ' . $__templater->escape($__vars['uix_stickyTotal']) . 'px !important;
					min-height: calc(100vh - ' . $__templater->escape($__vars['uix_stickyTotal']) . 'px) !important;
				}
				#XF .u-anchorTarget {
					height: ' . $__templater->escape($__vars['uix_stickyTotal']) . 'px;
					margin-top: -' . $__templater->escape($__vars['uix_stickyTotal']) . 'px;
				}
			}
		';
		}
		$__finalCompiled .= '

		';
		if ($__vars['uix_subNavBreakpoint'] != '100%') {
			$__finalCompiled .= '
			@media (max-width: ' . $__templater->escape($__vars['uix_subNavBreakpoint']) . ') {
		';
		}
		$__finalCompiled .= '
				.p-sectionLinks {display: none;}

				';
		$__vars['uix_stickyTotal'] = (($__vars['uix_stickyStaffBarHeight'] + $__vars['uix_stickyNavPrimary']) + $__templater->fn('property', array('elementSpacer', ), false));
		$__finalCompiled .= '

				.uix_stickyBodyElement:not(.offCanvasMenu) {
					top: ' . $__templater->escape($__vars['uix_stickyTotal']) . 'px !important;
					min-height: calc(100vh - ' . $__templater->escape($__vars['uix_stickyTotal']) . 'px) !important;
				}
				#XF .u-anchorTarget {
					height: ' . $__templater->escape($__vars['uix_stickyTotal']) . 'px;
					margin-top: -' . $__templater->escape($__vars['uix_stickyTotal']) . 'px;
				}

				';
		if ($__vars['uix_responsiveStaffBar'] AND (!$__vars['uix_alwaysStaffBar'])) {
			$__finalCompiled .= '
					@media(max-width: ' . $__templater->fn('property', array('uix_staffBarBreakpoint', ), true) . ') {
						';
			$__vars['uix_stickyTotal'] = ($__vars['uix_stickyNavPrimary'] + $__templater->fn('property', array('elementSpacer', ), false));
			$__finalCompiled .= '

						.uix_stickyBodyElement:not(.offCanvasMenu) {
							top: ' . $__templater->escape($__vars['uix_stickyTotal']) . 'px !important;
							min-height: calc(100vh - ' . $__templater->escape($__vars['uix_stickyTotal']) . 'px) !important;
						}
						#XF .u-anchorTarget {
							height: ' . $__templater->escape($__vars['uix_stickyTotal']) . 'px;
							margin-top: -' . $__templater->escape($__vars['uix_stickyTotal']) . 'px;
						}
					}
				';
		}
		$__finalCompiled .= '
		';
		if ($__vars['uix_subNavBreakpoint'] != '100%') {
			$__finalCompiled .= '
			}
		';
		}
		$__finalCompiled .= '
	';
	} else {
		$__finalCompiled .= '
		';
		$__vars['uix_stickyTotal'] = (($__vars['uix_stickyStaffBarHeight'] + $__vars['uix_stickyNavPrimary']) + $__templater->fn('property', array('elementSpacer', ), false));
		$__finalCompiled .= '

		.uix_stickyBodyElement:not(.offCanvasMenu) {
			top: ' . $__templater->escape($__vars['uix_stickyTotal']) . 'px !important;
			min-height: calc(100vh - ' . $__templater->escape($__vars['uix_stickyTotal']) . 'px) !important;
		}
		#XF .u-anchorTarget {
			height: ' . $__templater->escape($__vars['uix_stickyTotal']) . 'px;
			margin-top: -' . $__templater->escape($__vars['uix_stickyTotal']) . 'px;
		}
	';
	}
	$__finalCompiled .= '
	
	.uix_sidebarNav .uix_sidebar--scroller {max-height: calc(100vh - ' . $__templater->escape($__vars['uix_stickyTotal']) . 'px);}
	';
	if ($__templater->fn('property', array('uix_scrollableSidebar', ), false)) {
		$__finalCompiled .= '
		.uix_sidebarInner .uix_sidebar--scroller {max-height: calc(100vh - ' . $__templater->escape($__vars['uix_stickyTotal']) . 'px);}
	';
	}
	$__finalCompiled .= '
	';
	if ($__templater->fn('property', array('uix_scrollableSidenav', ), false)) {
		$__finalCompiled .= '
		.p-body-sideNavInner .uix_sidebar--scroller {max-height: calc(100vh - ' . $__templater->escape($__vars['uix_stickyTotal']) . 'px);}
	';
	}
	$__finalCompiled .= '
</style>';
	return $__finalCompiled;
});