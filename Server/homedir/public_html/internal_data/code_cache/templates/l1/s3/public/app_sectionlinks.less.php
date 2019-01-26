<?php
// FROM HASH: c0636f6e7a08d20f804ebbabb2326133
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
	
	.p-sectionLinks--group {display: flex;}

	.hScroller-action
	{
		.m-hScrollerActionColorVariation(
			xf-default(@xf-publicSubNav--background-color, transparent),
			@xf-publicSubNav--color,
			@xf-publicSubNavElHover--color
		);
	}

	&.p-sectionLinks--empty
	{
		height: 10px;
		display: none;
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
		';
	}
	$__finalCompiled .= '
		';
	if ($__templater->fn('property', array('uix_pageStyle', ), false) != 'fixed') {
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
		padding-top: @xf-paddingMedium;
		padding-bottom: @xf-paddingMedium;

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
		padding-top: 2px;
		padding-bottom: 2px;
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