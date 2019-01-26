<?php
// FROM HASH: 6363f159df74e849f4b2a0b9162a7d09
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '// ################################# DATA LISTS ###################

.dataList
{
	max-width: 100%;

	&.dataList--separated
	{
		border-top: @xf-borderSize solid @xf-borderColorLight;
		border-bottom: @xf-borderSize solid @xf-borderColorLight;
	}

	&.dataList--separatedTop
	{
		border-top: @xf-borderSize solid @xf-borderColorLight;
	}

	&.dataList--separatedBottom
	{
		border-bottom: @xf-borderSize solid @xf-borderColorLight;
	}

	&.dataList--contained
	{
		overflow-x: auto;
		max-height: 85vh;
	}

	@media (max-width: @xf-responsiveMedium)
	{
		overflow-x: auto;
	}
}

.dataList-table
{
	width: 100%;
	border-collapse: separate;
	border-spacing: 0;
}

.dataList-rowGroup
{
	&.is-hidden
	{
		display: none;
	}
}

.m-adjustDataListCellPadding(@paddingV; @paddingH)
{
	padding: @paddingV @paddingH;

	&.dataList-cell--action,
	&.dataList-cell--link
	{
		padding: 0;

		a,
		label,
		.dataList-blockLink
		{
			padding: @paddingV @paddingH;
		}
	}
}

.dataList-row
{
	&:hover:not(.dataList-row--noHover):not(.dataList-row--header)
	{
		background: fade(@xf-contentHighlightBg, 50%);
	}

	&.dataList-row--header
	{
		.dataList-cell
		{
			.xf-dataListHeader();
			// .m-adjustDataListCellPadding(@xf-dataListPaddingV/2, @xf-dataListPaddingH);
			.m-textColoredLinks();
			text-align: left;

			&.dataList-cell--min
			{
				text-align: center;
			}
		}
	}

	&.dataList-row--subSection
	{
		.dataList-cell
		{
			.xf-dataListSection();
			.m-adjustDataListCellPadding(@xf-dataListPaddingV/2, @xf-dataListPaddingH);

			a { color: inherit; }
		}

		&:hover:not(.dataList-row--noHover) .dataList-cell
		{
			.xf-dataListSection(background);
		}
	}

	&.dataList-row--note
	{
		.dataList-cell
		{
			text-align: center;
			font-style: italic;
		}
	}

	&.dataList-row--deleted
	{
		.dataList-cell
		{
			opacity: .5;
		}
	}

	&.dataList-row--highlighted
	{
		font-weight: @xf-fontWeightHeavy;
	}

	&.dataList-row--custom
	{
		> .dataList-cell:first-child
		{
			border-left: @xf-borderSizeFeature solid red;
		}

		.dataList-cell--link a
		{
			color: red;
		}
	}

	&.dataList-row--parentCustom
	{
		> .dataList-cell:first-child
		{
			border-left: @xf-borderSizeFeature solid orange;
		}

		.dataList-cell--link a
		{
			color: orange;
		}
	}

	&.dataList-row--protected
	{
		> .dataList-cell:first-child
		{
			border-left: @xf-borderSizeFeature solid @xf-borderColorFeature;
		}
	}

	&.is-hidden
	{
		display: none;
	}

	&.dataList-row--disabled
	{
		.dataList-cell--link a
		{
			color: @xf-textColorMuted;
			.m-transition();
		}
	}

	tbody:last-child &:last-child .dataList-cell
	{
		border-bottom: none;
	}
}

.dataList-cell
{
	vertical-align: middle;
	padding: @xf-dataListPaddingV @xf-dataListPaddingH;
	border-bottom: @xf-borderSize solid @xf-borderColorFaint;

	&.dataList-cell--main
	{
		min-width: 180px;
	}

	&.dataList-cell--link,
	&.dataList-cell--action
	{
		padding: 0;
	}

	&.dataList-cell--alt,
	&.dataList-cell--action
	{
		background: @xf-contentAltBg;
	}

	&.dataList-cell--separated
	{
		border-left: @xf-borderSize solid @xf-borderColorFaint;
	}

	&.dataList-cell--min,
	&.dataList-cell--action
	{
		width: 1%;
		white-space: nowrap;
		word-wrap: normal;
		text-align: center;
	}

	&.dataList-cell--action
	{
		font-size: @xf-fontSizeSmaller;
	}

	&.dataList-cell--action,
	&.dataList-cell--link
	{
		cursor: pointer;
		text-decoration: none;

		&.dataList-cell--alt:hover,
		&.dataList-cell--action:hover
		{
			background: @xf-contentHighlightBg;
		}

		a,
		label,
		.dataList-blockLink
		{
			padding: @xf-dataListPaddingV @xf-dataListPaddingH;
			display: block;
			height: 100%;
			text-decoration: none;
			cursor: pointer;
		}

		&.dataList-cell--iconic
		{
			a,
			label.iconic,
			.dataList-blockLink
			{
				padding: ((@xf-dataListPaddingV) / 2) @xf-dataListPaddingH;
			}
		}

		input
		{
			cursor: pointer;
		}
	}
	
	&.dataList-cell--highlighted
	{
		background: @xf-contentHighlightBg;
	}

	&.dataList-cell--image
	{
		padding: 0;

		a
		{
			padding: 0;
		}

		img,
		.dataList-imagePlaceholder
		{
			display: block;
			margin: auto;
			font-size: 30px;
		}
	}

	&.dataList-cell--imageSmall
	{
		img,
		.dataList-imagePlaceholder
		{
			height: 41px;
			max-width: 41px;
			line-height: 41px;
		}

		.avatar
		{
			.m-avatarSize(41px);
			border-radius: 2px;
		}
	}

	&.dataList-cell--imageSmallWide
	{
		img,
		.dataList-imagePlaceholder
		{
			height: 41px;
			max-width: 82px;
			line-height: 41px;
		}

		.avatar
		{
			.m-avatarSize(41px);
			border-radius: 0;
		}
	}

	&.dataList-cell--imageMedium
	{
		img,
		.dataList-imagePlaceholder
		{
			height: 54px;
			max-width: 54px;
			line-height: 54px;
		}

		.avatar
		{
			.m-avatarSize(54px);
			border-radius: 0;
		}
	}

	&.dataList-cell--imageMediumWide
	{
		img,
		.dataList-imagePlaceholder
		{
			height: 54px;
			max-width: 108px;
			line-height: 54px;
		}

		.avatar
		{
			.m-avatarSize(54px);
			border-radius: 0;
		}
	}

	&.dataList-cell--responsiveMenuTrigger,
	&.dataList-cell--fauxResponsiveMenuTrigger
	{
		display: none;
	}

	&.dataList-cell--breakWord
	{
		word-break: break-word;
	}

	&.dataList-cell--hint,
	.dataList-row--subSection &.dataList-cell--hint
	{
		text-align: right;
		font-size: @xf-fontSizeSmaller;
		color: @xf-textColorMuted;
	}

	// create ten depth classes for the appearance of nested items
	.depthLoop(@i) when (@i <= 10)
	{
		&.dataList-cell--d@{i} { text-indent: (@i - 1) * 25px; }
		.depthLoop(@i + 1);
	}
	.depthLoop(1);

	.is-match
	{
		text-decoration: underline;
		color: red;
	}

	@media (max-width: @xf-responsiveMedium)
	{
		&.dataList-cell--responsiveMenuItem,
		&.dataList-cell--fauxResponsiveMenuItem
		{
			display: none !important;
		}

		&.dataList-cell--responsiveMenuTrigger,
		&.dataList-cell--fauxResponsiveMenuTrigger
		{
			display: table-cell;
		}
	}
}

.dataList-imagePlaceholder
{
	&:after
	{
		content: \'?\';
	}
}

.dataList-mainRow,
.dataList-textRow,
.dataList-subRow
{
	width: 0;
	min-width: 100%;
	line-height: 1.4;
	max-height: 1.4em;
	overflow: hidden;
	white-space: nowrap;
	word-wrap: normal;
	text-overflow: ellipsis;

	&:empty { display: none; }
}

.dataList-mainRow
{
	font-weight: @xf-fontWeightHeavy;

	.dataList-row--subSection &
	{
		font-weight: @xf-fontWeightNormal;
	}
}

.dataList-secondRow
{
	display: block;
	font-size: @xf-fontSizeSmallest;
}

.dataList-hint,
.dataList-subRow
{
	color: @xf-textColorMuted;
	font-size: @xf-fontSizeSmaller;
	font-weight: @xf-fontWeightNormal;
}

.dataList-hint
{
	display: inline;
}

.dataList-delete
{
	&:after
	{
		.m-faBase();
		.m-faContent(@fa-var-trash-o, .79em);
		' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'close',
	), $__vars) . '
	}
}

.dataList-row--footer .dataList-cell
{
	// note that this is applied as a cell style which has higher priority than the row styles normally applied
	padding: @xf-dataListPaddingV/2 @xf-dataListPaddingH;
	border-bottom: none;
	.xf-dataListFooter();
}

.dataList--responsive
{
	.dataList-table,
	tbody,
	thead,
	tfoot
	{
		display: block;
	}

	.dataList-row
	{
		display: block;

		&.dataList-row--headerResponsive
		{
			display: none;
		}
	}

	.dataList-cell
	{
		display: block;
		width: auto;

		&[data-cell-label]
		{
			display: flex;
			align-items: center;
			text-align: right;
			
			> *
			{
				min-width: 0;
			}

			&:before
			{
				content: attr(data-cell-label) ":";
				padding-right: @xf-dataListPaddingH;
				margin-right: auto;
				word-break: normal;
			}

			> .input:first-child:last-child
			{
				display: inline;
			}

			a
			{
				// commonly a URL, but needed to prevent a potential overflow
				min-width: 0;
			}
		}

		&.dataList-cell--link,
		&.dataList-cell--action
		{
			&[data-cell-label]:before
			{
				padding: @xf-dataListPaddingV @xf-dataListPaddingH;
			}
		}
	}

	.dataList-row:not(.dataList-row--header):not(.dataList-row--subSection)
	{
		border-bottom: @xf-borderSize solid @xf-borderColorLight;

		.dataList-cell
		{
			border-bottom: none;
		}
	}

	tbody:last-child .dataList-row:not(.dataList-row--header):not(.dataList-row--subSection):last-child
	{
		border-bottom: none;
	}

	.dataList-mainRow,
	.dataList-textRow,
	.dataList-subRow
	{
		width: auto;
		min-width: 0;
	}
}';
	return $__finalCompiled;
});