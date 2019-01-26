<?php
// FROM HASH: 26adc7e1992be177d4884541160e042b
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '.uix_headerContainer {
	.breadcrumb {
		';
	if ($__templater->fn('property', array('uix_pageStyle', ), false) == 'fixed') {
		$__finalCompiled .= '
			.m-pageWidth();
		';
	}
	$__finalCompiled .= '
		
		.pageContent {
			';
	if ($__templater->fn('property', array('uix_pageStyle', ), false) != 'fixed') {
		$__finalCompiled .= '
				.m-pageWidth();
			';
	}
	$__finalCompiled .= '
		}
	}
}

.breadcrumb {
	margin-bottom: @xf-elementSpacer;
	.xf-uix_breadcrumbWrapper();
	
	&.p-breadcrumb--bottom {
		margin-top: @xf-elementSpacer;
		margin-bottom: 0;
	}
	
	.pageContent {
		display: flex;
		align-items: center;
	}
}

.uix_headerContainer .breadcrumb .pageContent {
	';
	if ($__templater->fn('property', array('uix_pageStyle', ), false) != 'fixed') {
		$__finalCompiled .= '
		.m-pageWidth();
	';
	}
	$__finalCompiled .= '
}

.p-breadcrumbs
{
	.m-listPlain();
	.m-clearFix();

	// margin-bottom: 5px;
	// line-height: 1.5;
	display: flex;
	align-items: center;
	flex-grow: 1;
	.xf-uix_breadcrumbStyle();
	
	i {font-size: @xf-uix_iconSize;}

	&.p-breadcrumbs--bottom
	{
		// margin-top: @xf-elementSpacer;
		margin-bottom: 0;
	}

	> li
	{
		float: left;
		margin-right: .5em;
		font-size: @xf-fontSizeSmall;
		display: flex;
		align-items: center;
		font-size: inherit;

		a
		{
			display: inline-block;
			vertical-align: bottom;
			max-width: 300px;
			.m-overflowEllipsis();
			.xf-uix_breadcrumbItem();
		}

		&:after,
		&:before
		{
			.m-faBase();
			// font-size: 90%;
			color: @xf-textColorMuted;
		}

		&:after
		{
			.m-faContent(@fa-var-angle-right, .36em, ltr);
			.m-faContent(@fa-var-angle-left, .36em, rtl);
			' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'chevron-right',
	), $__vars) . '
			margin-left: .5em;
		}
		
		&:first-child {
			padding-left: 0;
		}

		&:last-child
		{
			margin-right: 0;
			
			&:after {display: none;}

			a
			{
				font-weight: @xf-fontWeightHeavy;
				.xf-uix_breadcrumbItem__active();
				
				
			}
		}
	}
}

@media (max-width: @xf-responsiveMedium)
{
	.p-breadcrumbs > li a
	{
		max-width: 200px;
	}
}

@media (max-width: @xf-responsiveNarrow)
{
	.p-breadcrumbs
	{
		> li
		{
			font-size: @xf-fontSizeSmallest;
			.xf-buttonBase();
			.xf-buttonDefault();
			display: none;

			&:last-child
			{
				// display: block;
				display: flex;
			}

			a
			{
				max-width: 90vw;
				color: inherit !important;
			}

			&:after
			{
				display: none;
			}

			&:before
			{
				// .m-faContent(@fa-var-chevron-left, .72em, ltr);
				// .m-faContent(@fa-var-chevron-right, .72em, rtl);
				// margin-right: .5em;
				' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'chevron-left',
	), $__vars) . '
				font-size: @xf-uix_iconSizeLarge !important;
				color: inherit;
			}
		}
	}
}';
	return $__finalCompiled;
});