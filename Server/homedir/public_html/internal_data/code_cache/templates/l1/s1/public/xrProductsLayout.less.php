<?php
// FROM HASH: 5cb92238e066748b676f6cdfc21b1a0c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->fn('property', array('xm_xrProductManagerOn', ), false) == '1') {
		$__finalCompiled .= '
';
		if (($__vars['template'] != 'xr_pm_overview') AND ($__vars['template'] != 'xr_pm_category_view')) {
			$__finalCompiled .= '

';
			if ($__templater->fn('property', array('xm_disableProductCategory', ), false) == '1') {
				$__finalCompiled .= '
	@media (min-width: ' . ($__templater->fn('property', array('responsiveWide', ), false) + 1) . 'px) {
		body[data-template=\'xr_pm_overview\'] .p-body-sideNav {
    		display: none;
		}
	}
';
			}
			$__finalCompiled .= '

';
			if ($__templater->fn('property', array('xm_disableResponsiveProductCategory', ), false) == '1') {
				$__finalCompiled .= '
	@media (max-width: ' . ($__templater->fn('property', array('responsiveWide', ), false) + 1) . 'px) {
		.has-js .p-body-sideNavTrigger {
    		display: none !important;
		}	
	}
';
			}
			$__finalCompiled .= '

// Product Label
';
			if ($__templater->fn('property', array('xm_productRibbonPrice', ), false) == '1') {
				$__finalCompiled .= '
	.structItem.gridCol .structItem-title .label {
		display: none;
	}
';
			}
			$__finalCompiled .= '

// Product Title
';
			if ($__templater->fn('property', array('xm_productsTitle', ), false) == '1') {
				$__finalCompiled .= '
	.structItem.gridCol .structItem-title {
		display: none;
	}
';
			}
			$__finalCompiled .= '

// Product Small Title
';
			if ($__templater->fn('property', array('xm_productSmallTitle', ), false) == '1') {
				$__finalCompiled .= '
	.structItem.gridCol .structItem-minor > ul {
		display: none;
	}
';
			}
			$__finalCompiled .= '

// Product Info
';
			if ($__templater->fn('property', array('xm_productInfo', ), false) == '1') {
				$__finalCompiled .= '
.structItem.gridCol .structItem-productInfo {
    display: none;
}
';
			}
			$__finalCompiled .= '

// Product Info
';
			if ($__templater->fn('property', array('xm_productMainFeatures', ), false) == '1') {
				$__finalCompiled .= '
.structItem.gridCol .structItem-cell.structItem-cell--productMeta dl {
    display: none;
}
';
			}
			$__finalCompiled .= '

// Ribbon Price
';
			if ($__templater->fn('property', array('xm_productRibbonPrice', ), false) == '1') {
				$__finalCompiled .= '
.structItem.gridCol .structItem-cell.structItem-cell--productThumb {
	.price {
		.xf-xm_productRibbonPriceStyle()
		position: absolute;
		&:before {
			.xf-xm_productRibbonPriceStyleBefore()
			content: " ";
			position: absolute;
			left: 0;
			bottom: -10px;
			width: 0;
			height: 0;
		}
	}
}
';
			}
			$__finalCompiled .= '

// Grid Column & Grid Span Background
.structItem.gridCol.gridSpan {
	&:nth-child(even) {
		background-color: transparent;
	}
}
.structItem.gridCol {
	.structItem-cell.structItem-cell--productMeta {
		.button--product {
			display: none;
		}
		width: 100% !important;
	}
	.structItem-title {
		font-weight: @xf-fontWeightNormal;
		span.u-muted {
			float: right;
			font-weight: @xf-fontWeightNormal;
		}
	}
	.structItem-iconContainer {
		img {
			display: flex;
			width: 100%;
			overflow: hidden;
			flex-wrap: wrap;
			overflow: hidden;
			background-position: center center;
			background-repeat: no-repeat;
			background-size: cover;
		}
	}
	.structItem-cell.structItem-cell--productThumb {
		padding: 10px 0 !important;
		display: flex;
		flex-direction: column;
	}
	.structItem-cell {
		width: 100%;
	}
}
.structItemContainer.gridSection {
	padding: 0px;
	margin: 0;
	display: flex;
	flex-wrap: wrap;
}
.gridSection.gridGroup {
	.structItem {
		display: flex;
		flex-wrap: wrap;
	}
}
// Grid Column
.structItem.gridCol
{
	width: ' . ((100 / $__templater->fn('property', array('xm_defaultPerRow', ), false)) - 2) . '%;
	margin-right: 1%;
	margin-left: 1%;
	display: block;
	float: left;
}

	@media (min-width:@xf-responsiveWide) 
	{
		.gridCol:nth-child(' . $__templater->fn('property', array('xm_defaultPerRow', ), true) . 'n+1)
		{
		   clear: both;
		}
	}

	@media (max-width:@xf-responsiveWide)
	{
		
		.structItem.gridCol:nth-child(' . $__templater->fn('property', array('xm_defaultPerRow', ), true) . 'n+1),
		.structItem.gridSpan:nth-child(~"calc{\'' . $__templater->fn('property', array('xm_defaultPerRow', ), true) . ' + 1\'}n+1")
		{
			clear: none;
		}
		
		.structItem.gridSpan,
		.structItem.gridCol
		{
			width: ' . ((100 / $__templater->fn('property', array('xm_wideWidthPerRow', ), false)) - 2) . '%;
		}
		
		.structItem.gridSpan:nth-child(' . $__templater->fn('property', array('xm_wideWidthPerRow', ), true) . 'n+1),
		.structItem.gridCol:nth-child(' . $__templater->fn('property', array('xm_wideWidthPerRow', ), true) . 'n+1)
		{
			clear: both;
		}

		.structItem.gridCol .structItem-cell, .structItem.gridCol .structItem-cell, .structItem.gridCol .xrpmThumbnail
		{
			display: block;
			width: 100%;
			height: auto;
		}	
	}

	@media (max-width: @xf-responsiveMedium) {
		
		.structItem.gridSpan:nth-child(' . $__templater->fn('property', array('xm_wideWidthPerRow', ), true) . 'n+1),
		.structItem.gridCol:nth-child(' . $__templater->fn('property', array('xm_wideWidthPerRow', ), true) . 'n+1)
		{
			clear: none;
		}
		
		.structItem.gridSpan,
		.structItem.gridCol
		{
			width: ' . ((100 / $__templater->fn('property', array('xm_mediumWidthPerRow', ), false)) - 2) . '%;
		}
		
		.structItem.gridSpan:nth-child(' . $__templater->fn('property', array('xm_mediumWidthPerRow', ), true) . 'n+1),
		.structItem.gridCol:nth-child(' . $__templater->fn('property', array('xm_mediumWidthPerRow', ), true) . 'n+1)
		{
			clear: both;
		}
		.structItem.gridCol .structItem-cell, .structItem.gridCol .structItem-cell,  .structItem.gridCol .xrpmThumbnail
		{
			display: block;
			width: 100%;
		}
	}

	@media (max-width: @xf-responsiveNarrow) {
		
		.gridGroup
		{
			margin-left: 10%;
			margin-right: 10%;
		}
		
		.structItem.gridSpan:nth-child(' . $__templater->fn('property', array('xm_mediumWidthPerRow', ), true) . 'n+1),
		.structItem.gridCol:nth-child(' . $__templater->fn('property', array('xm_mediumWidthPerRow', ), true) . 'n+1)
		{
			clear: both;
		}
		
		.structItem.gridSpan,
		.structItem.gridCol
		{
			width: ' . ((100 / $__templater->fn('property', array('xm_narrowWidthPerRow', ), false)) - 2) . '%;
		}
		
		.structItem.gridSpan:nth-child(' . $__templater->fn('property', array('xm_narrowWidthPerRow', ), true) . 'n+1),
		.structItem.gridCol:nth-child(' . $__templater->fn('property', array('xm_narrowWidthPerRow', ), true) . 'n+1)
		{
			clear: both;
		}
	}

	@media (max-width:340px)
	{
		.gridGroup
		{
			margin-left: 10%;
			margin-right: 10%;
		}
		
		.structItem.gridSpan:nth-child(' . $__templater->fn('property', array('xm_mediumWidthPerRow', ), true) . 'n+1),
		.structItem.gridCol:nth-child(' . $__templater->fn('property', array('xm_mediumWidthPerRow', ), true) . 'n+1)
		{
			clear: both;
		}
		
		.structItem.gridSpan,
		.structItem.gridCol
		{
			width: ' . ((100 / $__templater->fn('property', array('xm_narrowWidthPerRow', ), false)) - 2) . '%;
		}
		
		.structItem.gridSpan:nth-child(' . $__templater->fn('property', array('xm_narrowWidthPerRow', ), true) . 'n+1),
		.structItem.gridCol:nth-child(' . $__templater->fn('property', array('xm_narrowWidthPerRow', ), true) . 'n+1)
		{
			clear: both;
		}
	}
	
	@media (min-width: @xf-responsiveWide) {	
	
		body[data-template=\'xr_pm_overview\'] {
			.structItem-cell.structItem-cell--productThumb 
			{
				width: 100%;
			}
			.xrpmThumbnail 
			{
				width: 100%;
				height: auto;
			}
		}
		body[data-template=\'xr_pm_category_view\'] {
			.structItem.gridCol .structItem-cell.structItem-cell--productThumb 
			{
				width: 100%;
			}
			.xrpmThumbnail 
			{
				width: 100%;
				height: auto;
			}
		}
	}	
';
		}
		$__finalCompiled .= '
';
	}
	return $__finalCompiled;
});