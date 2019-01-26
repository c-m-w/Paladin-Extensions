<?php
// FROM HASH: ab1c89b4bdf246bd3b59989bbe665c78
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '// MAIN HEADER ROW

.p-header
{
	.xf-publicHeader();
	';
	if ($__templater->fn('property', array('uix_pageStyle', ), false) == 'fixed') {
		$__finalCompiled .= '
		.m-pageWidth();
	';
	}
	$__finalCompiled .= '

	.p-header-logo img {max-width: @xf-uix_logoWidth;}

	a
	{
		color: inherit;
	}
	
	.p-header-logo img {width: 100%;}
}

.p-header-inner
{
	';
	if ($__templater->fn('property', array('uix_pageStyle', ), false) != 'fixed') {
		$__finalCompiled .= '
		.m-pageWidth();
	';
	}
	$__finalCompiled .= '
	position: relative;
}

.p-header-content
{
	// padding: @xf-paddingMedium 0;

	display: flex;
	flex-wrap: wrap;
	justify-content: space-between;
	align-items: center;
	max-width: 100%;

	.has-no-flexbox &
	{
		display: table;
		width: 100%;
	}
	
	';
	if ($__templater->fn('property', array('uix_viewportCenterLogo', ), false) == '100%') {
		$__finalCompiled .= '
		justify-content: center;
		flex-direction: column;
		
		.p-nav-opposite {margin-top: @xf-paddingLarge; margin-left: 0;}
		.p-header-logo {margin-right: 0;}
	';
	}
	$__finalCompiled .= '
	
	@media (max-width: @xf-uix_viewportCenterLogo) {
		justify-content: center;
		flex-direction: column;
		
		.p-nav-opposite {margin-top: @xf-paddingLarge; margin-left: 0;}
		.p-header-logo {margin-right: 0;}
	}
}

.p-header-logo
{
	.has-no-flexbox &
	{
		display: table-cell;
	}

	vertical-align: middle;
	// margin-right: auto;

	a
	{
		color: inherit;
		text-decoration: none;
	}

	&.p-header-logo--text
	{
		font-size: @xf-fontSizeLargest;
	}

	&.p-header-logo--image
	{
		img
		{
			// vertical-align: bottom;
			// max-width: 100%;
			// max-height: 200px;
		}
	}

	.uix_logoIcon {.xf-uix_logoIconStyle();}
}


@media (max-width: @xf-responsiveNarrow)
{
	.p-header-logo
	{
		// max-width: 100px;

		&.p-header-logo--text
		{
			font-size: @xf-fontSizeLarge;
			font-weight: @xf-fontWeightNormal;
			.m-overflowEllipsis();
		}
	}

	.p-navgroup-link
	{
		.p-navGroup--member &
		{
			margin-left: 5px;

			&:first-of-type
			{
				margin-left: 0;
			}
		}

	}
}

';
	if ($__templater->fn('property', array('uix_rightAlignNavigation', ), false)) {
		$__finalCompiled .= '
	@media (min-width: @xf-publicNavCollapseWidth) {
		.p-nav-inner .p-nav-opposite,
		.p-sectionLinks .p-nav-opposite {margin-left: 0;}

		.p-nav-inner .p-nav-scroller,
		.p-sectionLinks .p-sectionLinks-inner {margin-right: 0; margin-left: auto;}
	}
';
	}
	return $__finalCompiled;
});