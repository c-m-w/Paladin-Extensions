<?php
// FROM HASH: 08ea63e295dda00bd05d58ec705f7017
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '// ############################ RESOURCE LIST ######################
.ticketId{
	color: @xf-textColorAttention;
	font-family: @xf-fontFamilyCode;
	word-wrap: normal;
}
.structItem-ticketTagLine
{
	font-size: @xf-fontSizeSmaller;
	margin-top: @xf-paddingSmall;
}

.structItem-cell.structItem-cell--ticketMeta
{
	width: 210px;
}

.structItem-metaItem--rating
{
	font-size: @xf-fontSizeSmall;
}

.mjstStatus{
	border: 1px solid transparent;
	border-radius: @xf-borderRadiusMedium;
	display: inline-block;
	padding: 1px .35em;
	font-size: 80%;
	line-height: ((@xf-lineHeightDefault) * .9);
	text-decoration: none;
}
.structItem-cell{
	.mjstStatus{
		float: right;
	}
}
.mjstPrioriy{
	border: 1px solid transparent;
	border-radius: @xf-borderRadiusMedium;
	display: inline-block;
	padding: 1px .35em;
	font-size: 80%;
	line-height: ((@xf-lineHeightDefault) * .9);
	text-decoration: none;
	color: #ffffff;
	&--1{
		background: #e20000;
		border-color: #af0000;
	}
	&--2{
		background: #7cc3e0;
		border-color: #53b0d6;
	}
	&--3{
		color: #000000;
		background: #c0c0c0;
		border-color: #a7a7a7;
	}
}

@media (max-width: @xf-responsiveWide)
{
	.structItem-cell.structItem-cell--ticketMeta
	{
		width: 190px;
		font-size: @xf-fontSizeSmaller;
	}
}

@media (max-width: @xf-responsiveMedium)
{
	.structItem-cell.structItem-cell--ticketMeta
	{
		display: block;
		width: auto;
		float: left;
		padding-top: 0;
		padding-left: 0;
		padding-right: 0;
		color: @xf-textColorMuted;

		.pairs
		{
			display: inline;

			&:before,
			&:after
			{
				display: none;
			}

			> dt,
			> dd
			{
				display: inline;
				float: none;
				margin: 0;
			}
		}

		.structItem-metaItem
		{
			display: inline;
		}

		.ratingStarsRow
		{
			display: inline;

			.ratingStarsRow-text
			{
				display: none;
			}
		}

		.structItem-metaItem--lastUpdate > dt
		{
			display: none;
		}

		.structItem-metaItem + .structItem-metaItem:before
		{
			display: inline;
			content: "\\20\\00B7\\20";
			color: @xf-textColorMuted;
		}
	}
}

// #################################### RESOURCE BODY / VIEW ########################

.ticketBody
{
	display: flex;
}

.ticketBody-main
{
	flex: 1;
	min-width: 0;
	padding: @xf-blockPaddingV @xf-blockPaddingH;
}

.ticketBody-sidebar
{
	flex: 0 0 auto;
	width: 250px;
	.xf-contentAltBase();
	border-left: @xf-borderSize solid @xf-borderColor;
	padding: @xf-blockPaddingV @xf-blockPaddingH;
	font-size: @xf-fontSizeSmall;

	> :first-child
	{
		margin-top: 0;
	}

	> :last-child
	{
		margin-bottom: 0;
	}
}

.ticketBody-fields
{
	&.ticketBody-fields--before
	{
		margin-bottom: @xf-paddingLarge;
		padding-bottom: @xf-paddingMedium;
		border-bottom: @xf-borderSize solid @xf-borderColorLight;
	}

	&.ticketBody-fields--after
	{
		margin-top: @xf-paddingLarge;
		padding-top: @xf-paddingMedium;
		border-top: @xf-borderSize solid @xf-borderColorLight;
	}
}

.ticketBody-attachments
{
	margin: .5em 0;
}

.ticketBody .actionBar-set
{
	margin-top: @xf-messagePadding;
	font-size: @xf-fontSizeSmall;
}

.ticketSidebarGroup
{
	margin-bottom: @xf-elementSpacer;

	&.ticketSidebarGroup--buttons
	{
		> .button
		{
			display: block;
			margin: 5px 0;

			&:first-child
			{
				margin-top: 0;
			}

			&:last-child
			{
				margin-bottom: 0;
			}
		}
	}
}

.ticketSidebarGroup-title
{
	margin: 0;
	padding: 0;

	font-size: @xf-fontSizeLarge;
	font-weight: @xf-fontWeightNormal;
	color: @xf-textColorFeature;
	padding-bottom: @xf-paddingMedium;

	.m-hiddenLinks();
}

.ticketSidebarList
{
	.m-listPlain();

	> li
	{
		padding: @xf-paddingSmall 0;

		&:first-child
		{
			padding-top: 0;
		}

		&:last-child
		{
			padding-bottom: 0;
		}
	}
}
.urgency{
	line-height: 48px;
	width: 30px;
	text-align: center;
	display: inline-block;
	i{
		font-size: 24px;
		color: #e20000;
	}
	&.urgency-2{
		i{
			color: #7cc3e0;
		}
	}
	&.urgency-3{
		i{
			color: #c0c0c0;
		}
	}
}

@media (max-width: @xf-responsiveWide)
{
	.ticketBody
	{
		display: block;
	}

	.ticketBody-sidebar
	{
		width: auto;
		border-left: none;
		border-top: @xf-borderSize solid @xf-borderColor;
	}

	.ticketSidebarGroup
	{
		max-width: 600px;
		margin-left: auto;
		margin-right: auto;
	}
}

' . $__templater->includeTemplate('mjst_status_styles.less', $__vars);
	return $__finalCompiled;
});