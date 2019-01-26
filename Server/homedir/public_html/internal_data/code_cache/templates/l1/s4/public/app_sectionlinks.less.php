<?php
// FROM HASH: d61cfcc2aec3217fcd6588987a1fba0d
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '// SUB SECTION LINKS

.p-sectionLinks
{
	.xf-publicSubNav();
	';
	if ($__templater->fn('property', array('uix_pageStyle', ), false) == 'fixed') {
		$__finalCompiled .= '
		.m-pageWidth();
	';
	}
	$__finalCompiled .= '
	
	transition: ease-in .15s all;
	
	.p-sectionLinks--group {
		display: flex; 
		align-items: center;
		
		';
	if ($__templater->fn('property', array('uix_rightAlignNavigation', ), false)) {
		$__finalCompiled .= '
			&:first-child {
				margin-left: auto;
			}
		';
	}
	$__finalCompiled .= '
	}

	.hScroller-action
	{
		.m-hScrollerActionColorVariation(
			xf-default(@xf-publicSubNav--background-color, transparent),
			@xf-publicSubNav--color,
			@xf-publicSubNavElHover--color
		);
	}
	
	.p-nav-opposite a:not(.button)
	{
		color: inherit;

		&:hover {
			.xf-publicSubNavElHover();
		}
	}

	&.p-sectionLinks--empty
	{
		height: 10px;
		';
	if (!$__templater->fn('property', array('publicNavSelected--background-color', ), false)) {
		$__finalCompiled .= '
			display: none;
		';
	}
	$__finalCompiled .= '
	}

	.pageContent {
		display: flex;
		align-items: center;
		position: relative;
		justify-content: space-between;
		';
	if ($__templater->fn('property', array('publicNavSticky', ), false)) {
		$__finalCompiled .= '
			min-height: @xf-uix_stickySectionLinkHeight;
			height: @xf-uix_stickySectionLinkHeight;
		';
	}
	$__finalCompiled .= '
		';
	if ($__templater->fn('property', array('uix_pageStyle', ), false) == 'covered') {
		$__finalCompiled .= '
			.m-pageWidth();
		';
	}
	$__finalCompiled .= '
	}

	.p-navgroup .p-navgroup-link i:after,
	.p-navSearch-trigger i:after {font-size: @xf-uix_iconFont;}
	.p-navgroup-link.p-navgroup-link--user .avatar {
		.m-avatarSize(@xf-uix_iconSize);
		font-size: @xf-uix_iconSizeLarge;
	}
	.p-navSearch-trigger,
	.p-navgroup .p-navgroup-link {padding: @xf-paddingSmall @xf-paddingLarge;}
}

.p-sectionLinks-inner
{
	// .m-clearFix();
	// .m-pageWidth();

	// padding-left: max(0px, @xf-pageEdgeSpacer - @xf-publicSubNavPaddingH);
	// padding-right: max(0px, @xf-pageEdgeSpacer - @xf-publicSubNavPaddingH);
	margin-right: auto;
}


.p-sectionLinks-list
{
	.m-listPlain();

	font-size: 0;

	a
	{
		color: inherit;
	}

	> li
	{
		display: inline-block;
	}

	.m-navElHPadding(@xf-publicSubNavPaddingH);

	.p-navEl
	{
		font-size: @xf-publicSubNav--font-size;
		// padding-top: @xf-paddingMedium;
		// padding-bottom: @xf-paddingMedium;

		&:hover
		{
			.xf-publicSubNavElHover();

			a
			{
				text-decoration: @xf-publicSubNavElHover--text-decoration;
			}
		}
		' . '
	}

	.p-navEl-link,
	.p-navEl-splitTrigger
	{
		padding-top: @xf-publicSubNavPaddingV;
		padding-bottom: @xf-publicSubNavPaddingV;
	}
}

';
	if (($__templater->fn('property', array('uix_searchPosition', ), false) != 'tablinks') AND (($__templater->fn('property', array('uix_loginTriggerPosition ', ), false) != 'tablinks') AND ($__templater->fn('property', array('uix_userTabsPosition ', ), false) != 'tablinks'))) {
		$__finalCompiled .= '

	@media (max-width: @xf-publicNavCollapseWidth) {
		.has-js .p-sectionLinks-inner
		{
			display: none;
		}
	}

';
	}
	return $__finalCompiled;
});