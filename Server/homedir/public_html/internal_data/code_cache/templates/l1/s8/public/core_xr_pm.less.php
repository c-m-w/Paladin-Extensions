<?php
// FROM HASH: 7b388c83f357e9ff8ed9b0507fc6ec75
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '@_xrpmThumbSize: xf-option(\'xr_pm_thumbnail_size\', px);
@_xrpmThumbDisplaySize: (@_xrpmThumbSize) / 2.3;
@_xrpmThumbDisplaySizeMedium: (@_xrpmThumbSize) / 3;
@_xrpmThumbDisplaySizeSmall: (@_xrpmThumbSize) / 6;
@_structItem-cellPaddingH: ((@xf-paddingMedium) + (@xf-paddingLarge)) / 2; // average
@_structItem-cellPaddingV: @xf-paddingLarge;

.structItem-cell
{
	&.structItem-cell--productThumb
	{
		width: ((@_xrpmThumbDisplaySize) + (@_structItem-cellPaddingH) * 2);
		position: relative;

		&.structItem-cell--productThumb--medium
		{
			width: ((@_xrpmThumbDisplaySizeMedium) + (@_structItem-cellPaddingH) * 2);
			position: relative;
		}

		@media (max-width: @xf-responsiveMedium)
		{
			display: block;
			margin-left: auto;
			margin-right: auto;
		}
	}

	&.structItem-cell--main
	{
		&.structItem-cell--productMain
		{
			.structItem-productInfo
			{
				margin-top: @xf-paddingSmall;
				font-size: @xf-fontSizeSmaller;

				> ul
				{
					padding: 0;
					margin: @xf-paddingSmall 0;

					> li
					{
						list-style-position: inside;
						.m-overflowEllipsis();
					}
				}
			}

			@media (max-width: @xf-responsiveMedium)
			{
				padding-left: @_structItem-cellPaddingH;
				width: 100%;
				display: block;
			}
		}
	}

	&.structItem-cell--productMeta
	{
		width: 230px;

		.button--product
		{
			display: block;
			width: 90%;
			margin-bottom: 5px;
			margin-right: 5px;
		}

		@media (max-width: @xf-responsiveWide)
		{
			width: 180px;
		}

		@media (max-width: @xf-responsiveMedium)
		{
			width: 100%;
			display: block;
		}
	}
}

.xrpmThumbnail
{
	display: block;
	width: @_xrpmThumbDisplaySize;
	height: @_xrpmThumbDisplaySize;

	&.xrpmThumbnail--small
	{
		width: @_xrpmThumbDisplaySizeSmall;
		height: @_xrpmThumbDisplaySizeSmall;
	}

	&.xrpmThumbnail--dataList
	{
		width: 54px;
		height: 54px;
	}

	&.xrpmThumbnail--medium
	{
		width: @_xrpmThumbDisplaySizeMedium;
		height: @_xrpmThumbDisplaySizeMedium;
	}

	&.xrpmThumbnail--default
	{
		background: mix(@xf-textColorMuted, @xf-avatarBg, 25%);
		text-align: center;
		text-decoration: none !important;

		-webkit-user-select: none;
		-moz-user-select: none;
		-ms-user-select: none;
		user-select: none;

		position: relative;

		> span:before
		{
			.m-faBase();
			.m-faContent(@fa-var-ellipsis-h);
			font-size: 60px;
			position: absolute;
			left: 50%;
			top: 50%;
			transform: translate(-50%, -50%);
			color: @xf-textColorMuted;
			.m-textOutline(@xf-textColorMuted, xf-intensify(@xf-textColorMuted, 20%));

			.xrpmThumbnail--small&,
			.xrpmThumbnail--dataList&
			{
				font-size: @xf-fontSizeLarge * 2;
			}
		}
	}
}

.listFeatures
{
	margin-top: 2px;
}

.tabs
{
	&.tabs--product
	{
		.tabs-extra
		{
			a
			{
				display: inline-block;
			}
		}
	}
}';
	return $__finalCompiled;
});