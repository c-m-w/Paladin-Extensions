<?php
// FROM HASH: c817df94d396b22b4fb8a5724eeef54c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '// STICKY NAV SETUP

.uix_headerContainer .p-navSticky
{
	z-index: @zIndex-1;

	&.is-sticky
	{
		z-index: @zIndex-4;
		// .m-dropShadow(0, 2px, 5px, 0px, .26);
		box-shadow: @xf-uix_elevation1;
		position: fixed !important;
		top: 0;
		bottom: auto !important;
		left: 0;
		right: 0;

		';
	if ($__templater->fn('property', array('uix_pageStyle', ), false) != 'covered') {
		$__finalCompiled .= '
			.m-pageWidth();
			padding: 0 !important;

			> * {
				width: 100%;
			}
		';
	}
	$__finalCompiled .= '

		';
	if ($__templater->fn('property', array('uix_pageStyle', ), false) == 'fluid') {
		$__finalCompiled .= '
			> * {
				max-width: 100%;
			}
		';
	}
	$__finalCompiled .= '

		.p-nav-inner {
			height: @xf-uix_stickyNavHeight;

			// .p-header-logo {display: inline-flex;}
			
			.p-navEl,
			.p-navEl-link {max-height: @xf-uix_stickyNavHeight;}
			
			' . '
		}
		
		';
	if ($__templater->fn('property', array('publicNavSticky', ), false)) {
		$__finalCompiled .= '
			.p-sectionLinks {
				border-bottom: 0;
				
				.pageContent {
					height: @xf-uix_stickySectionLinkHeight;
					// *:not(.hScroller-scroll) {max-height: @xf-uix_stickySectionLinkHeight;}
				}
			}
		';
	}
	$__finalCompiled .= '
	}
}

';
	if ($__templater->fn('property', array('uix_stickyStaffBar', ), false)) {
		$__finalCompiled .= '
	.p-staffBar.is-sticky {
		position: fixed !important;
		bottom: auto !important;
		top: 0 !important;
		left: 0;
		right: 0;
		z-index: 400;

		.pageContent {
			height: @xf-uix_stickyStaffBarHeight;
		}

		// *:not(.hScroller-scroll) {max-height: @xf-uix_stickyStaffBarHeight;}
	}
';
	}
	$__finalCompiled .= '

@supports (position: sticky) or (position: -webkit-sticky)
{
	.p-navSticky
	{
		// position: -webkit-sticky;
		// position: sticky;
		top: 0;

		&.is-sticky-broken,
		&.is-sticky-disabled
		{
			position: static;
			top: auto;
		}
	}
}';
	return $__finalCompiled;
});