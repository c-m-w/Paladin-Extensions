<?php
// FROM HASH: 74ae9b95fd819befdbd1b41e4e0bc6ce
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '@_departmentList-statsCellBreakpoint: 1000px;
.department
{
	& + .department
	{
		border-top: @xf-borderSize solid @xf-borderColorFaint;
	}
}

.department-body
{
	display: table;
	table-layout: fixed;
	width: 100%;
}
.department-main
{
	display: table-cell;
	vertical-align: middle;
	padding: @xf-paddingLarge;
}

.department-stats
{
	display: table-cell;
	width: 170px;
	vertical-align: middle;
	text-align: center;
	padding: @xf-paddingLarge 0;

	> dl.pairs.pairs--rows
	{
		width: 50%;
		float: left;
		margin: 0;
		padding: 0 @xf-paddingMedium/2;

		&:first-child
		{
			padding-left: 0;
		}

		&:last-child
		{
			padding-right: 0;
		}
	}

	&.department-stats--single
	{
		width: 100px;

		> dl.pairs.pairs--rows
		{
			width: 100%;
			float: none;
		}
	}

	&.department-stats--triple
	{
		width: 240px;

		> dl.pairs.pairs--rows
		{
			width: 33.333%;
		}
	}

	@media (max-width: @_departmentList-statsCellBreakpoint)
	{
		display: none;
	}
}

.department-title
{
	margin: 0;
	padding: 0;
	font-size: @xf-fontSizeLarge;
	font-weight: @xf-fontWeightNormal;

	.department--unread &
	{
		font-weight: @xf-fontWeightHeavy;
	}
}

.department-description
{
	font-size: @xf-fontSizeSmall;
	color: @xf-textColorDimmed;

	&.department-description--tooltip
	{
		.has-js.has-no-touchevents &
		{
			display: none;
		}
	}
}

.department-meta
{
	font-size: @xf-fontSizeSmall;
}

.department-statsMeta
{
	display: none;

	@media (max-width: @_departmentList-statsCellBreakpoint)
	{
		display: inline;
	}
}

.department-bonus
{
	font-size: @xf-fontSizeSmall;
	color: @xf-textColorMuted;
	text-align: right;
}

@media (max-width: @xf-responsiveMedium)
{
	.department-main
	{
		display: block;
		width: auto;
	}

	.department-description,
	.department-stats
	{
		display: none;
	}
}';
	return $__finalCompiled;
});